// https://cryptopals.com/sets/1/challenges/3

#include "../helper.h"

int main()
{
  char *hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

  int length; //number of bytes in byte array
  unsigned char *bytes = hexToBytes(hex, &length);
  unsigned char bytesXOR[length+1]; //+1 for '\0'
  bytesXOR[length] = '\0';
  float highScore = 0;

  singleByteXOR(bytes, bytesXOR, length, &highScore);

  printf("%s\n", bytesXOR);
  free(bytes);
}
