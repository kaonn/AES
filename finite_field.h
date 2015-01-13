#include <stdlib.h>
#include "aes.h"

byte add(byte b1, byte b2);
byte mul(byte b1, byte b2);
byte xtime(byte b1);
byte inv(byte b1);

word poly_add(word w1, word w2);
word poly_mul(word w1, word w2);
word poly_xtime(word w1);
byte affine(byte b);