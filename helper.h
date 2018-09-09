#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* hexToBytes(char *hex); //converts hex string to byte array
int lengthBytes(unsigned char* bytes); //returns number of bytes in byte array
char* bytesToB64(unsigned char* bytes); //converts byte array to Base64 string
