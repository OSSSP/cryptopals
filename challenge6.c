//http://cryptopals.com/sets/1/challenges/6

#include "helper.h"

int main()
{
  //Test whether hammingDistance function works
  char *string1 = "this is a test";
  char *string2 = "wokka wokka!!!";
  int test = hammingDistance(string1, string2, strlen(string1), strlen(string2));
  assert(test == 37);

  FILE *fp;
  fp = fopen("ch6.txt", "r");
  if(fp == NULL)
  {
    printf("Cannot open file!\n");
    exit(EXIT_FAILURE);
  }
  int bufferSize = 2048;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int charsRead = 0;

  //read file until EOF
  while(1)
  {
    char c = fgetc(fp);
    if(feof(fp))
      break;
    if(c == '\n')
      continue;
    buffer[charsRead] = c;
    charsRead++;
    //make sure buffer has enough space to read file
    if(charsRead >= bufferSize)
    {
      bufferSize *= 2;
      buffer = realloc(buffer, sizeof(char) * bufferSize);
    }
  }
  fclose(fp);
  buffer[charsRead] = '\0';
  int numBytes;
  unsigned char *bytes = b64ToBytes(buffer, &numBytes);
  free(buffer);

  float minDistance = INT_MAX;
  int correctKeySize;

  //Try key lengths between 2 and 40 (inclusive)
  for(int i = 2; i < 41; i++)
  {
    char firstBytes[i]; //holds first keysize worth of bytes
    char secondBytes[i]; //holds second keysize worth of bytes
    char thirdBytes[i]; //holds third keysize worth of bytes
    char fourthBytes[i]; //holds fourth keysize worth of bytes
    for(int j = 0; j < i * 4; j++)
    {
      if(j < i)
        firstBytes[j] = bytes[j];
      else if(j < i * 2)
        secondBytes[j - i] = bytes[j];
      else if(j < i * 3)
        thirdBytes[j - (i * 2)] = bytes[j];
      else
        fourthBytes[j - (i * 3)] = bytes[j];
    }
    //edit distance between the keysize worth of bytes
    int editDistance = hammingDistance(firstBytes, secondBytes, i, i) +
      hammingDistance(firstBytes, thirdBytes, i, i) + hammingDistance(firstBytes, fourthBytes, i, i) +
      hammingDistance(secondBytes, thirdBytes, i , i) + hammingDistance(secondBytes, fourthBytes, i, i) + 
      hammingDistance(thirdBytes, fourthBytes, i, i);

    float averageDistance = editDistance / 6;
    float normalDistance = averageDistance / i;
    //key with lowest normal distance is the correct key size
    if(normalDistance < minDistance)
    {
      minDistance = normalDistance;
      correctKeySize = i;
    }
  }

  char key[correctKeySize + 1];
  key[correctKeySize] = '\0';

  //break cipher text into blocks of keysize length
  //and solve each one as single-character XOR
  for(int i = 0; i < correctKeySize; i++)
  {
    unsigned char block[numBytes / correctKeySize];
    int k = 0;
    //transpose blocks so that first block contains first byte of every block
    //second block second byte, and so on and so forth
    for(int j = i; j < numBytes; j+= correctKeySize)
    {
      block[k] = bytes[j];
      k++;
    }

    //xor of block with single character
    unsigned char bytesXOR[(numBytes / correctKeySize)];
    float highScore = 0;
    char keyChar; //character that was used to xor block
    key[i] = singleByteXOR(block, bytesXOR, (numBytes / correctKeySize), &highScore);
  }

  char plaintext[numBytes + 1];
  plaintext[numBytes] = '\0';
  //apply repeating-key XOR to ciphertext to get plaintext
  for(int i = 0; i < numBytes; i++)
  {
    plaintext[i] = bytes[i] ^ key[i % correctKeySize];
  }
  free(bytes);
  printf("%s", plaintext);
}
