#include <stdlib.h>
#include <stdio.h>

typedef uint8_t byte;
struct word_header
{
  byte b3;
  byte b2;
  byte b1;
  byte b0;
};
typedef struct word_header word;

struct state_header
{
  byte b[4][4];
};

typedef struct state_header state;

void encrypt(byte *plain, byte *key, uint8_t key_length);
