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
  byte result = 0;
  bool bin_rep[8] = {false};

  int i = 0;
  while(b2 > 0)
  {
    if ((b2 - (0x80 >> i)) >= 0)
    {
      bin_rep[i] = true;
      b2 = b2 - (0x80 >> i);
    }
    else
    {
      bin_rep[i] = false;
    }

    i++;
  }

  b2 = b1;
  for (int i = 7; i >= 0; i--)
  {
    if (bin_rep[i])
    {
      result = add(result, b2);
    }
    b2 = xtime(b2);
  }

  return result;
}

byte inv(byte b1)
{
  if (b1 == 0)
  {
    return 0;
  }
  byte power[8] = {0};

  power[0] = b1;
  for (size_t i = 1; i < 8; i++)
  {
    power[i] = mul(power[i - 1], power[i - 1]);
  }

  byte result = 1;
  for (size_t i = 1; i < 8; i++)
  {
    result = mul(result, power[i]);
  }

  return result;
}

/*byte euclid_ext(byte b1, byte b2)
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
*/
word poly_add(word w1, word w2)
{
  word w3;

  for (size_t i = 0; i < 4; i++)
  {
    w3.b[i] = add(w1.b[i], w2.b[i]);
  }

  return w3;
}

word poly_mul(word w1, word w2)
{
  word w3;

  w3.b[0] = 0;
  w3.b[1] = 0;
  w3.b[2] = 0;
  w3.b[3] = 0;

  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      w3.b[j] = add(mul(w1.b[(j - i) % 4], w2.b[i]), w3.b[j]);
    }
  }

  return w3;
}

word poly_xtime(word w1)
{
  byte temp = w1.b[3];
  w1.b[3] = w1.b[2];
  w1.b[2] = w1.b[1];
  w1.b[1] = w1.b[0];
  w1.b[0] = temp;

  return w1;
}

byte affine(byte b)
{
  byte result = 0;

  byte b1 = inv(b);

  for (size_t i = 0; i < 8; i++)
  {
    for (size_t j = 0; j < 8; j++)
    {
      result = add(result, mul(affine_matrix[i][j], (b1 >> j) & 1) << i);
    }
  }

  return add(result,0x63);
}




