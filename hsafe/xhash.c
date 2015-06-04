#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hsafe/hs.h"
#include "hsafe/sha1.h"

// hash1 = hash1 XOR hash2
void hsafe_xhash(sha1result *hash1, const sha1result *hash2)
{
  int i;
  for (i = 0; i < HASH_LENGTH; i++) {
    hash1->data[i] = hash1->data[i] ^ hash2->data[i];
  }
}

void hasfe_xhashInit(sha1result *hash)
{
  memset(hash->data, 0, HASH_LENGTH);
}
