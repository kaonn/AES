#include <stdio.h>
#include <stdlib.h>
#include "finite_field.h"

int main(int argc, char **argv)
{
  if (argc > 4)
  {
    printf("%s\n", "usage: ./debug <n1> <n2>");
    return 0;
  }

  byte b2 = 0;
  byte b1 = strtol(argv[2], NULL, 16);
  if (argc == 4)
  {
    b2 = strtol(argv[3], NULL, 16);
  }

  switch(argv[1][1]){
    case 'm': 
      printf("%x\n", mul(b1, b2));
      break;

      case 'a': 
      printf("%x\n", add(b1, b2));
      break;

      case 'i': 
      printf("%x\n", inv(b1));
      break;
  }
  
  
  return 0;
}
