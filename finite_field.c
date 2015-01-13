#include <stdbool.h>
#include "finite_field.h"

const byte affine_matrix[8][8] =  { {1, 0, 0, 0, 1, 1, 1, 1},
                                    {1, 1, 0, 0, 0, 1, 1, 1},
                                    {1, 1, 1, 0, 0, 0, 1, 1},
                                    {1, 1, 1, 1, 0, 0, 0, 1},
                                    {1, 1, 1, 1, 1, 0, 0, 0},
                                    {0, 1, 1, 1, 1, 1, 0, 0},
                                    {0, 0, 1, 1, 1, 1, 1, 0},
                                    {0, 0, 0, 1, 1, 1, 1, 1} };
byte add(byte b1, byte b2)
{
  return b1 ^ b2;
}

byte xtime(byte b)
{
  uint16_t result = b << 1;

  if (result >= 0x100)
  {
    return result ^ 0x11B;
  }

  return result;
}

byte mul(byte b1, byte b2)
{
  byte b3 = b2;
  byte result = 0;
  bool bin_rep[8] = {false, false, false, false, false, false, false, false};

  int i = 0;
  while(b3 > 0)
  {
    if ((b3 - (0x80 >> i)) >= 0)
    {
      bin_rep[i] = true;
      b3 = b3 - (0x80 >> i);
    }
    else
    {
      bin_rep[i] = false;
    }

    i++;
  }

  b3 = b1;
  for (int i = 7; i >= 0; i--)
  {
    if (bin_rep[i])
    {
      result = add(result, b3);
    }
    b3 = xtime(b3);
  }

  return result;
}

byte inv(byte b1)
{
  if (b1 == 0)
  {
    return 0;
  }
  byte power[8];

  power[0] = b1;
  for (int i = 1; i < 8; i++)
  {
    power[i] = mul(power[i - 1], power[i - 1]);
  }

  byte result = 1;
  for (int i = 1; i < 8; i++)
  {
    result = mul(result, power[i]);
  }

  return result;
}

byte euclid_ext(byte b1, byte b2)
{
  byte q = 0;
  uint16_t rp = b2;
  byte r = b1;
  byte tp = 0;
  byte t = 1;

  int temp = 0;
  while(r > 0)
  {
    q = rp/r;

    temp = r;
    r = rp - q*r;
    rp = temp;

    temp = t;
    t = tp - q*t;
    tp = temp;
  }

  return tp;
}

word poly_add(word w1, word w2)
{
  word w3;
  w3.b3 = add(w1.b3, w2.b3);
  w3.b2 = add(w1.b2, w2.b2);
  w3.b1 = add(w1.b1, w2.b1);
  w3.b0 = add(w1.b0, w2.b0);

  return w3;
}

word poly_mul(word w1, word w2)
{
  word w3;
  w3.b0 = add(add(mul(w1.b0, w2.b0), mul(w1.b3, w2.b1)),add(mul(w1.b2, w2.b2),
    mul(w1.b1, w2.b3)));
  w3.b1 = add(add(mul(w1.b1, w2.b0), mul(w1.b0, w2.b1)),add(mul(w1.b3, w2.b2), 
    mul(w1.b2, w2.b3)));
  w3.b2 = add(add(mul(w1.b2, w2.b0), mul(w1.b1, w2.b1)),add(mul(w1.b0, w2.b2), 
    mul(w1.b3, w2.b3)));
  w3.b3 = add(add(mul(w1.b3, w2.b0), mul(w1.b2, w2.b1)),add(mul(w1.b1, w2.b2), 
    mul(w1.b0, w2.b3)));

  return w3;
}

word poly_xtime(word w1)
{
  byte temp = w1.b3;
  w1.b3 = w1.b2;
  w1.b2 = w1.b1;
  w1.b1 = w1.b0;
  w1.b0 = temp;

  return w1;
}

byte affine(byte b)
{
  byte result = 0;
  for (size_t i = 0; i < 8; i++)
  {
    for (size_t j = 0; j < 8; j++)
    {
      result += mul(affine_matrix[i][j], (b >> j) & 1) << i;
    }
  }

  return add(result, 0x63);
}




