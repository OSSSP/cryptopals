//http://cryptopals.com/sets/1/challenges/8

#include "helper.h"

int main()
{
  FILE *fp;
  fp = fopen("ch8.txt", "r");

  if(fp == NULL)
  {
    printf("Cannot open file!\n");
    exit(EXIT_FAILURE);
  }

  int mostMatches = 0;
  int lineSize = 256;
  char *line = malloc(sizeof(char) * lineSize);
  int charsRead = 0;
  int linesRead = 0; //lines read from ch8.txt
  int ecbLineNum = 0; //line number of line encrypted with ECB
  char *ecbLine = malloc(sizeof(char) * lineSize);

  //read file until EOF
  while(1)
  {
    char c = fgetc(fp);
    if(feof(fp))
      break;

    //Reached end of line
    if(c == '\n')
    {
      linesRead++;
      int matches = 0;
      line[charsRead] = '\0'; //null-terminate string
     
      //Go thru hex string 32 characters (representing 16 bytes) at a time
      for(int i = 0; i < strlen(line) - 32; i += 32)
      {
        char block1[33]; //contains 32 hex chars and null character
        strncpy(block1, line + i, 32);
        block1[32] = '\0'; //null-terminate hex string
      
        //compare 32 hex char (16 bytes) block with other 16 byte blocks
        for(int j = i + 32; j < strlen(line); j += 32)
        {
          char block2[33];
          strncpy(block2, line + j, 32);
          block2[32] = '\0';
          if(strcmp(block1, block2) == 0)
            matches++;
        }
      }
      if(matches > mostMatches)
      {
        mostMatches = matches;
        ecbLine = realloc(ecbLine, sizeof(char) * lineSize);
        strcpy(ecbLine, line);
        ecbLineNum = linesRead;
      }
      charsRead = 0;
      continue;
    }
    line[charsRead] = c;
    charsRead++;

    //make sure line has enough space to read line from file
    if(charsRead >= lineSize)
    {
      lineSize *= 2;
      line = realloc(line, sizeof(char) * lineSize);
    }
  }
  fclose(fp);
  free(line);
  free(ecbLine);
  printf("Line number %d has been encrypted with ECB\n", ecbLineNum);
}
