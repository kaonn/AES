#include "aes.h"
#include "finite_field.h"

state hex_to_state(state s, byte hex[])
{
  for (size_t j = 0; j < 4; j++)
  {
    for (size_t i = 0; i < 4; i++)
    {
      s->b[i][j] = hex[i + 4*j];
    }
  }
  
  return s;
}

state byte_sub(state s)
{
  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      s->b[i][j] = affine(s->b[i][j]);
    }
  }

  return s;
}

state shift_rows(state s)
{
  byte temp[4] = {0};

  for (size_t i = 1; i < 4; i++)
  {
    
    for (size_t j = 0; j < 4; j++)
    {
      temp[j] = s->b[i][j];
    }

    for (size_t j = 0; j < 4; j++)
    {
      s->b[i][j] = temp[(j + i) % 4];
    }
    
  }

  return s;
}

word get_column(state s, size_t col)
{
  word w;

  for (size_t i = 0; i < 4; i++)
  {
    w.b[i] = s->b[i][col];
  }

  return w;
}

state mix_columns(state s)
{
  word w;

  w.b[0] = 2;
  w.b[1] = 1;
  w.b[2] = 1;
  w.b[3] = 3;

  for (size_t i = 0; i < 4; i++)
  {
    word new_col = poly_mul(w, get_column(s, i));

    for (size_t j = 0; j < 4; j++)
    {
      s->b[j][i] = new_col.b[j];
    }
  }

  return s;
}

void key_expansion(byte key[], word w[], uint8_t Nk, uint8_t Nb, uint8_t Nr)
{
  word temp;

  for (size_t i = 0; i < Nk; i++)
  {
    temp.b[0] = key[4 * i];
    temp.b[1] = key[4 * i + 1];
    temp.b[2] = key[4 * i + 2];
    temp.b[3] = key[4 * i + 3];
    w[i] = temp;
  }

  for (size_t i = Nk; i < Nb * (Nr + 1); i++)
  {
    temp.b[0] = w[i - 1].b[0];
    temp.b[1] = w[i - 1].b[1];
    temp.b[2] = w[i - 1].b[2];
    temp.b[3] = w[i - 1].b[3];
  }
}

void print_word(word w)
{
  for (size_t i = 0; i < 4; i++)
  {
    printf("%02X ", w.b[i]);
  }
  printf("%s\n", "");
}

void print_state(state s)
{
  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      printf("%02X ", s->b[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void encrypt_single(byte plain[], byte key[], uint8_t key_length)
{
  plain[0] = 0;
  key[0] = 0;
  key_length = 0; 
}

void encrypt(state s, byte hex[])
{
  const uint8_t Nb = 4;
  const uint8_t Nk = 4;
  const uint8_t Nr = 10;

  word w1;

  w1.b[0] = 2;
  w1.b[1] = 1;
  w1.b[2] = 1;
  w1.b[3] = 3;

  word w2;

  w2.b[0] = 0xdb;
  w2.b[1] = 0x13;
  w2.b[2] = 0x53;
  w2.b[3] = 0x45;

  word w[44];

  hex_to_state(s, hex);

  key_expansion(hex, w, Nk, Nb, Nr);
  
  print_word(w[0]);
  print_word(w[1]);
  //print_state(s);
}

/*void encrypt(byte *plain, byte *key, uint8_t key_length)
{
  plain = NULL;
  key = NULL;
  key_length = 0;
}*/



