// https://cryptopals.com/sets/1/challenges/4

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

  unsigned char *bytesXOR = malloc(sizeof(unsigned char) * 1);
  char line[62]; //60 for actual hex chars, +2 for \n and \0
  float highScore = 0;

  //Go thru text file line by line till EOF
  while(fgets(line, sizeof(line), fp) != NULL)
  {
    //Remove \n from end of each line
    if(line[strlen(line)-1] == '\n')
      line[strlen(line)-1] = '\0';

    int length; //number of bytes in byte array
    unsigned char *bytes = hexToBytes(line, &length); //raw bytes of hex string
    bytesXOR = realloc(bytesXOR, sizeof(unsigned char) * (length + 1));
    bytesXOR[length] = '\0';

    singleByteXOR(bytes, bytesXOR, length, &highScore);
    free(bytes);
  }
  fclose(fp);
  printf("%s", bytesXOR);
  free(bytesXOR);
}
