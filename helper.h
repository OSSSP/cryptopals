#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* hexToBytes(char *hex, int *bytesLength); //converts hex string to byte array
char* bytesToHex(unsigned char* bytes, int numBytes); //converts byte array to Hex string
char* bytesToB64(unsigned char* bytes, int numBytes); //converts byte array to Base64 string
