/**
 * hs.h
 * Cryptographic signature for execution traces
 * Author: Cuong Pham (phammanhcuong@gmail.com)
 * May 28, 2015
 **/
#pragma once

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdint.h>
#include "hsafe/sha1.h"

#define OPSHIFT 8

#define HSAFE_MAX_BLOCK_LENGTH 2048 /* Maximum of number of instructions, longer blocks will be cut-off  */
#define HSAFE_MAX_INST_LENGTH 16 /* Length of an instruction in bytes */
#define HSAFE_ADDR_MASK 0xFFFF

typedef struct HSafeInstruction {
  uint16_t addr;
  uint8_t mem[HSAFE_MAX_INST_LENGTH];
} HSafeInstruction;

// We utilize the first HSafeInstruction to store the block index.
// This helps with memory alignment in sha1 calculation.
typedef struct HSafeCodeBlock {
  struct HSafeInstruction insts[HSAFE_MAX_BLOCK_LENGTH];
  uint64_t startPc;
  uint64_t currentInstIndex;
  sha1nfo hash;
} HSafeCodeBlock;

// Assuming ONE vCPU for now
typedef struct HSafeGlobalState {
  uint8_t isInitialized;
  uint8_t isActive;
  uint64_t bblockCount;
  sha1result curHash;
} HSafeGlobalState;

extern HSafeGlobalState gHSafeState;

void hsafe_init(void);

void hsafe_dump_cb(HSafeCodeBlock *cb);

// hash1 = hash1 XOR hash2
void hsafe_xhash(sha1result *hash1, const sha1result *hash2);

void hasfe_xhashInit(sha1result *hash);
