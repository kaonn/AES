#include "aes.h"

state hex_to_state(byte *hex)
{
  state s;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      s.b[j][i] = hex[i + 4*j];
    }
  }

  return s;
}

state byte_sub(state s);
void encrypt_single(byte *plain, byte *key, uint8_t key_length)
{
  plain = NULL;
  key = NULL;
  key_length = 0; 
}

void encrypt(byte *plain, byte *key, uint8_t key_length)
{
  plain = NULL;
  key = NULL;
  key_length = 0;
}
