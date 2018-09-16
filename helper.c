#include "helper.h"

unsigned char* hexToBytes(char *hex, int *bytesLength)
{
  size_t length = strlen(hex); //length of hex string
  int numBytes = 0; //number of bytes in byte array
  char padHex[length + 2]; //in case length of hex string is odd

  //length of hex string is even
  if(length % 2 == 0)
    numBytes = length/2;

  //length of hex string is odd
  else
  {
    numBytes = (length + 1) / 2;
    padHex[0] = '0'; //pad with 0 character

    for(int i = 0; i < length; i++)
    {
      padHex[i+1] = hex[i];
    }
    padHex[length+1] = '\0'; //char array should end with '\0'
    hex = padHex;
  }

  //byte array that will be returned
  unsigned char* byteArray = malloc(sizeof(unsigned char) * numBytes);
  *bytesLength = numBytes;
  int j = 0; //for accessing byteArray
  unsigned char firstHalf; //first 4 bits of a byte
  unsigned char secondHalf; //last 4 bits of a byte

  //Goes thru hex string and puts each pair of hex characters into one byte
  for(int i = 0; i < length; i+=2)
  {
    //if/else blocks converts ascii values to hex values
    if(hex[i] >= '0' && hex[i] <= '9')
      firstHalf = hex[i] - 48;

    else if(hex[i] >= 'a' && hex[i] <= 'f')
      firstHalf = hex[i] - 87;

    if(hex[i+1] >= '0' && hex[i+1] <= '9')
      secondHalf = hex[i+1] - 48;

    else if(hex[i+1] >= 'a' && hex[i+1] <= 'f')
      secondHalf = hex[i+1] - 87;

    //a byte's first four bits is from firstHalf, last 4 from secondHalf
    byteArray[j] = (firstHalf << 4) + secondHalf;
    j++;
  }
  return byteArray;
}

unsigned char* b64ToBytes(char *b64, int *bytesLength)
{
  size_t length = strlen(b64); //length of base64 string
  int numBytes = (length * 6) / 8;
  
  //byte array that will be returned
  unsigned char* byteArray = malloc(sizeof(unsigned char) * numBytes);

  char index[length]; //stores index of each base64 character
  //for loop goes thru and maps each character to their index value
  for(int i = 0; i < length; i++)
  {
    switch(b64[i])
    {
      case 'A' ... 'Z':
        index[i] = b64[i] - 'A';
        break;
      case 'a' ... 'z':
        index[i] = b64[i] - 'a' + 26;
        break;
      case '0' ... '9':
        index[i] = b64[i] - '0' + 52;
        break;
      case '+':
        index[i] = 62;
        break;
      case '/':
        index[i] = 63;
        break;
    }
  }

  int j = 0;
  int k = 0;
  //Goes thru index values of b64 string and stores 8-bits into each byte array index
  for(int i = numBytes - 1; i > -1; i--)
  {
    switch(j % 3)
    {
      case 0:
        byteArray[i] = ((index[length - 2 - k] & 3) << 6) + index[length - 1 - k];
        break;

      case 1:
        byteArray[i] = ((index[length - 3 - k] & 15) << 4) + ((index[length - 2 - k] & 60) >> 2);
        break;

      case 2:
        byteArray[i] = (index[length - 4 - k] << 2) + ((index[length - 3 - k] & 48) >> 4);
        k += 4;
        break;
    }
    j++;
  }

  //handles padding
  if(b64[length-1] == '=')
  {
    numBytes--;
    if(b64[length - 2] == '=')
      numBytes--;
    byteArray = realloc(byteArray, sizeof(unsigned char) * numBytes);
  }
  *bytesLength = numBytes;
  return byteArray;
}

char* bytesToHex(unsigned char* bytes, int numBytes)
{
  int numHex = 2 * numBytes; //number of hex characters

  //hex string that will be returned
  char *hex = malloc(sizeof(char) * (numHex + 1));
  hex[numHex] = '\0'; //make sure string is null-terminated

  int j = 0;
  //Go thru byte array 4 bits at a time
  for(int i = 0; i < numHex; i++)
  {
    if(i % 2 == 0)
      hex[i] = (bytes[j] & 240) >> 4;
    else
    {
      hex[i] = (bytes[j] & 15);
      j++;
    }
  }

  //map int values to hex characters
  for(int i = 0; i < numHex; i++)
  {
    switch(hex[i])
    {
      case 0 ... 9:
        hex[i] += '0';
        break;

      case 10 ... 15:
        hex[i] += 'a' - 10;
        break;
    }
  }
  return hex;
}

char* bytesToB64(unsigned char* bytes, int numBytes)
{
  int numB64 = ((numBytes * 8) + 5) / 6; //number of Base64 characters

  //Base64 string that will be returned. +1 for '\0'
  char *b64 = malloc(sizeof(char) * (numB64 + 1));
  b64[numB64] = '\0'; //end of string

  int j = 0;
  int k = 0;

  //Goes thru byte array 6 bits at a time
  for(int i = numB64-1; i > -1; i--)
  {
    switch(j % 4)
    {
      case 0:
        b64[i] = bytes[numBytes-1 - k] & 63;
        break;

      case 1:
        b64[i] = ((bytes[numBytes - 2 - k] & 15) << 2) | ((bytes[numBytes-1 - k] & 192)>>6);
        break;

      case 2:
        b64[i] = ((bytes[numBytes - 3 - k] & 3) << 4) | ((bytes[numBytes - 2 - k] & 240)>>4);
        break;

      case 3:
        b64[i] = (bytes[numBytes -3 - k] & 252) >> 2;
        k += 3;
        break;
    }
    j++;
  }

  //maps values to bas64 characters
  for(int i = 0; i < numB64; i++)
  {
    switch(b64[i])
    {
      case 0 ... 25:
        b64[i] += 'A';
        break;
      case 26 ... 51:
        b64[i] += 'a' - 26;
        break;
      case 52 ... 61:
        b64[i] += '0' - 52;
        break;
      case 62:
        b64[i] = '+';
        break;
      case 63:
        b64[i] = '/';
        break;
    }
  }
  return b64;
}

int hammingDistance(char *string1, char *string2, int length1, int length2)
{
  int count = 0; //number of differing bits
  int maxLength;

  if(length1 >= length2)
    maxLength = length1;
  else
    maxLength = length2;

  //Outer for loop goes thru each character, inner thru each bit of 8-bit characters
  for(int i = 0; i < maxLength; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(((string1[i] >> j) & 1) ^ ((string2[i] >> j) & 1))
        count++;
    }
  }
  return count;
}

float scoreCharFreq(unsigned char *bytes, int length)
{
  float score = 0;

  for(int i = 0; i < length; i++)
  {
    switch(bytes[i])
    {
      case 'A':
      case 'a':
        score += 8.12;
        break;
      case 'B':
      case 'b':
        score += 1.49;
        break;
      case 'C':
      case 'c':
        score += 2.71;
        break;
      case 'D':
      case 'd':
        score += 4.32;
        break;
      case 'E':
      case 'e':
        score += 12.02;
        break;
      case 'F':
      case 'f':
        score += 2.30;
        break;
      case 'G':
      case 'g':
        score +=  2.03;
        break;
      case 'H':
      case 'h':
        score += 5.92;
        break;
      case 'I':
      case 'i':
        score += 7.31;
        break;
      case 'J':
      case 'j':
        score += 0.10;
        break;
      case 'K':
      case 'k':
        score += 0.69;
        break;
      case 'L':
      case 'l':
        score += 3.98;
        break;
      case 'M':
      case 'm':
        score += 2.61;
        break;
      case 'N':
      case 'n':
        score += 6.95;
        break;
      case 'O':
      case 'o':
        score += 7.68;
        break;
      case 'P':
      case 'p':
        score += 1.82;
        break;
      case 'Q':
      case 'q':
        score += 0.11;
        break;
      case 'R':
      case 'r':
        score += 6.02;
        break;
      case 'S':
      case 's':
        score += 6.28;
        break;
      case 'T':
      case 't':
        score += 9.10;
        break;
      case 'U':
      case 'u':
        score += 2.88;
        break;
      case 'V':
      case 'v':
        score += 1.11;
        break;
      case 'W':
      case 'w':
        score += 2.09;
        break;
      case 'X':
      case 'x':
        score += 0.17;
        break;
      case 'Y':
      case 'y':
        score += 2.11;
        break;
      case 'Z':
      case 'z':
        score += 0.07;
        break;
      case ' ':
        score += 10;
        break;
    }
  }
  return score;
}
