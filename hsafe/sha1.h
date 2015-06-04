/* public api for steve reid's public domain SHA-1 implementation */
/* this file is in the public domain */

#pragma once

#include <inttypes.h>
#include <stdint.h>

/* #include "hsafe/Platform.h" */

/* typedef struct SHA1_CTX */
/* { */
/*     uint32_t state[5]; */
/*     uint32_t count[2]; */
/*     uint8_t  buffer[64]; */
/* } SHA1_CTX; */


/* typedef struct ShaDigest { */
/*   uint8_t bytes[SHA1_DIGEST_SIZE]; */
/* } ShaDigest; */

/* void SHA1_Init(SHA1_CTX* context); */
/* void SHA1_Update(SHA1_CTX* context, const uint8_t* data, const size_t len); */
/* void SHA1_Final(SHA1_CTX* context, ShaDigest *digest); */

/* // digest1 = digest1 XOR digest2 */
/* void SHA1_xhash(ShaDigest *digest1, const ShaDigest *digest2); */

/* void SHA1_initXHash(ShaDigest *digest); */

/* void digest_to_hex(const ShaDigest *digest, char *output); */


/* header */

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

typedef struct sha1nfo {
    uint32_t buffer[BLOCK_LENGTH/4];
    uint32_t state[HASH_LENGTH/4];
    uint32_t byteCount;
    uint8_t bufferOffset;
    uint8_t keyBuffer[BLOCK_LENGTH];
    uint8_t innerHash[HASH_LENGTH];
} sha1nfo;

typedef struct sha1result {
    uint8_t data[HASH_LENGTH];
} sha1result;
/* public API - prototypes - TODO: doxygen*/

/**
 */
void sha1_init(sha1nfo *s);
/**
 */
void sha1_writebyte(sha1nfo *s, uint8_t data);
/**
 */
void sha1_write(sha1nfo *s, const char *data, uint32_t len);
/**
 */
sha1result* sha1_result(sha1nfo *s);
/**
 */
void sha1_initHmac(sha1nfo *s, const uint8_t* key, int keyLength);
/**
 */
sha1result* sha1_resultHmac(sha1nfo *s);

void sha1_info2hex(sha1nfo *hash, char *output);

void sha1_result2hex(const sha1result *hash, char *output);
