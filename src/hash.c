#include <openssl/sha.h>
#include <string.h>
#include "../include/hash.h"
#include <stdio.h>

void hashPassword(const char* password, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void printHash(unsigned char* hash) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}
