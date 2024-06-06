#ifndef HASH_H
#define HASH_H
#define HASH_LENGTH 32  // For example, assuming your hash length is 32 bytes

void hashPassword(const char* password, unsigned char* hash);
void printHash(unsigned char* hash);

#endif // HASH_H

