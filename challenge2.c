// https://cryptopals.com/sets/1/challenges/2

#include "helper.h"

int main()
{
  char *hex1 = "1c0111001f010100061a024b53535009181c";
  char *hex2 = "686974207468652062756c6c277320657965";
  char *answer = "746865206b696420646f6e277420706c6179";

  int length;
  unsigned char *bytes1 = hexToBytes(hex1, &length);
  unsigned char *bytes2 = hexToBytes(hex2, &length);
  unsigned char bytes3[length];

  for(int i = 0; i < length; i++)
  {
    bytes3[i] = bytes1[i] ^ bytes2[i];
  }

  char *hex3 = bytesToHex(bytes3, length);

  if(strcmp(answer, hex3) == 0)
    printf("Success!\n");
  else
    printf("Failure!\n");

  free(bytes1);
  free(bytes2);
  free(hex3);
}
