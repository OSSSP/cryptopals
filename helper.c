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

char* bytesToHex(unsigned char* bytes, int numBytes)
{
  int numHex = 2 * numBytes;

  char *hex = malloc(sizeof(char) * (numHex + 1));
  hex[numHex] = '\0';

  int j = 0;
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
