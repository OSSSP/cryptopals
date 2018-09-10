#include "helper.h"

int main()
{
  char *hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

  int length; //number of bytes in byte array
  unsigned char *bytes = hexToBytes(hex, &length);
  unsigned char bytesXOR[length+1]; //+1 for '\0'
  unsigned char temp[length+1]; //+1 for '\0'
  bytesXOR[length] = '\0';
  temp[length] = '\0';
  float highScore = 0;

  //Loops through 256 characters
  for(int i = 0; i < 256; i++)
  {
    //xor's byte array with single character
    for(int j = 0; j < length; j++)
    {
      temp[j] = bytes[j] ^ i;
    }
    float score = scoreCharFreq(temp, length);
    if(score > highScore)
    {
      highScore = score;
      memcpy(bytesXOR, temp, length);
    }
  }
  printf("%s\n", bytesXOR);
  free(bytes);
}
