#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//converts hex string to byte array
unsigned char* hexToBytes(char *hex, int *bytesLength);

//converts byte array to Hex string
char* bytesToHex(unsigned char* bytes, int numBytes);

//converts byte array to Base64 string
char* bytesToB64(unsigned char* bytes, int numBytes);

//scores using English letter frequency
//http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
float scoreCharFreq(unsigned char *bytes, int length);
