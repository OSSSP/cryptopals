#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

//converts hex string to byte array
unsigned char* hexToBytes(char *hex, int *bytesLength);

//converts base64 string to byte array
unsigned char* b64ToBytes(char *b64, int *bytesLength);

//converts byte array to Hex string
char* bytesToHex(unsigned char* bytes, int numBytes);

//converts byte array to Base64 string
char* bytesToB64(unsigned char* bytes, int numBytes);

//Computes the Hamming Distance between two strings (number of differing bits)
int hammingDistance(char *string1, char *string2, int length1, int length2);

//Goes through 256 characters and XORs byte array with each character
//Returns character that produces the best frequency score
char singleByteXOR(unsigned char *bytes, unsigned char *bytesXOR, int length, float *highScore);

//scores using English letter frequency
//http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
float scoreCharFreq(unsigned char *bytes, int length);
