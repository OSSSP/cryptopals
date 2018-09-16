//http://cryptopals.com/sets/1/challenges/4

#include "helper.h"

int main()
{
  FILE *fp;
  fp = fopen("ch4.txt", "r");

  if(fp == NULL)
  {
    printf("Cannot open file!\n");
    exit(EXIT_FAILURE);
  }

  float highScore = 0;
  unsigned char *bytesXOR = malloc(sizeof(unsigned char) * 1);
  char line[62]; //60 for actual hex chars, +2 for \n and \0

  //Go thru text file line by line till EOF
  while(fgets(line, sizeof(line), fp) != NULL)
  {
    //Remove \n from end of each line
    if(line[strlen(line)-1] == '\n')
      line[strlen(line)-1] = '\0';

    int length; //number of bytes in byte array
    unsigned char *bytes = hexToBytes(line, &length); //raw bytes of hex string
    unsigned char temp[length+1];
    temp[length] = '\0';

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
        bytesXOR = realloc(bytesXOR, sizeof(unsigned char) * (length + 1));
        memcpy(bytesXOR, temp, length+1);
      }
    }
    free(bytes);
  }
  fclose(fp);
  printf("%s", bytesXOR);
}
