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
#include <stdio.h>
#include "hsafe/sha1.h"

// Debug functions
#define HSAFE_DEBUG_LEVEL 0
#ifdef HSAFE_DEBUG_LEVEL
    #define DEBUG_PRINT(level, msg, args...) \
        if (level <= HSAFE_DEBUG_LEVEL) { \
            fprintf(hsafe_output, msg, ## args); \
            update_linecount(); \
        }
#else
    #define DEBUG_PRINT(level, msg, args...) if (0);
#endif

#define OPSHIFT 8

#define HSAFE_MAX_BLOCK_LENGTH 256 /* Maximum of number of instructions, longer blocks will be cut-off  */
#define HSAFE_MAX_INST_LENGTH 16 /* Length of an instruction in bytes */
#define HSAFE_ADDR_MASK 0xFF

#define HSAFE_BB_BUFFER_SIZE 128

#define HSAFE_OUTPUT_FILENAME "hs.log"
#define HSAFE_OUTPUT_TEMP_DIR "/run/shm"  // RAM disk directory

typedef struct HSafeInstruction {
  uint16_t addr;
  uint8_t mem[HSAFE_MAX_INST_LENGTH];
} HSafeInstruction;

typedef struct HSafeBBNode {
  uint64_t startPc;
  uint64_t bblockIndex;
} HSafeBBNode;

extern HSafeBBNode* HSafe_BB_Buffer;
extern long hsafe_node_count;
void hsafe_save_node(uint64_t startPc, uint64_t bblockIndex);
void hsafe_flush_output(void);

// We utilize the first HSafeInstruction to store the block index.
// This helps with memory alignment in sha1 calculation.
typedef struct HSafeCodeBlock {
  HSafeInstruction *insts; // size HSAFE_MAX_BLOCK_LENGTH
  uint64_t startPc;
  uint64_t currentInstIndex;
  sha1nfo hash;
} HSafeCodeBlock;

// Assuming ONE vCPU for now
typedef struct HSafeGlobalState {
  uint8_t isInitialized;
  uint8_t isActive;
  uint64_t bblockCount;
  uint64_t targetCr3;
  uint32_t targetESP0;
  sha1result curHash;
} HSafeGlobalState;

#define MAX_LINE_PER_FILE 1000000

extern FILE *hsafe_output;
extern long hsafe_linecount;
void update_linecount(void);

extern HSafeGlobalState gHSafeState;

void hsafe_init(void);

void hsafe_dump_cb(HSafeCodeBlock *cb);

// hash1 = hash1 XOR hash2
void hsafe_xhash(sha1result *hash1, const sha1result *hash2);

void hasfe_xhashInit(sha1result *hash);
