//http://cryptopals.com/sets/1/challenges/5

#include "helper.h"

int main()
{
  char *text = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  char *answer = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  char *key = "ICE";
  unsigned char bytesXOR[strlen(text)];

  //Encrypt text using repeating-key XOR (ICE)
  for(int i = 0; i < strlen(text); i++)
  {
    bytesXOR[i] = text[i] ^ key[i % 3];
  }

  char *hex = bytesToHex(bytesXOR, strlen(text)); //hex string of bytes array

  if(strcmp(answer, hex) == 0)
    printf("Success!\n");

  else
    printf("Failure!\n");

  free(hex);

}
