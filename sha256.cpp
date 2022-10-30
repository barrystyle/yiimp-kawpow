#include <cstring>
#include <openssl/sha.h>

void sha256_hash(const char *input, char *output, unsigned int len)
{
        if (!len) {
            len = strlen((const char *)input);
        }

        SHA256((const unsigned char*)input, len, (unsigned char*)output);
}

void sha256_double_hash(const char *input, char *output, unsigned int len)
{
        char output1[32];

        SHA256((const unsigned char*)input, len, (unsigned char*)output1);
        SHA256((const unsigned char*)output1, 32, (unsigned char*)output);
}

