//http://cryptopals.com/sets/1/challenges/1

#include "helper.h"

int main()
{
  char *hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  char *answer = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  
  unsigned char *bytes = hexToBytes(hex);
  char *b64 = bytesToB64(bytes);

  if(strcmp(answer, b64) == 0)
    printf("Success!\n");
  
  else
    printf("Failure!\n");

  free(bytes);
  free(b64);
}
