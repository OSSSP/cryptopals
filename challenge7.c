//http://cryptopals.com/sets/1/challenges/7

#include "helper.h"
#include <openssl/evp.h>

int decrypt(unsigned char *ciphertext, int cipherLength, unsigned char *key,
    unsigned char *plaintext);

int main()
{
  FILE *fp;
  fp = fopen("ch7.txt", "r");
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

  unsigned char key[16] = "YELLOW SUBMARINE";
  unsigned char plaintext[numBytes];

  int decryptLength = decrypt(bytes, numBytes, key, plaintext);
  free(bytes);
  plaintext[decryptLength] = '\0';
  printf("%s", plaintext);
}

int decrypt(unsigned char *ciphertext, int cipherLength, unsigned char *key,
    unsigned char *plaintext)
{
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);
  int len = 0;
  int plainLength = 0;

  if(1 != EVP_DecryptInit_ex(&ctx, EVP_aes_128_ecb(), NULL, key, NULL))
  {
    printf("Error at init!\n");
    exit(1);
  }

  if(1 != EVP_DecryptUpdate(&ctx, plaintext, &len, ciphertext, cipherLength))
  {
    printf("Error at update!\n");
    exit(1);
  }
  plainLength += len;

  if(1 != EVP_DecryptFinal_ex(&ctx, plaintext + len, &len))
  {
    printf("Error at final!\n");
    exit(1);
  }
  plainLength += len;
  EVP_CIPHER_CTX_cleanup(&ctx);
  return plainLength;
}
