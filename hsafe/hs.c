/**
 * hs.c
 * Cryptographic signature for execution traces
 * Author: Cuong Pham (phammanhcuong@gmail.com)
 * June 1, 2015
 **/
#include "hsafe/hs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

HSafeGlobalState gHSafeState;
FILE *hsafe_output;
long hsafe_linecount = 0;
int hsafe_filecount = 0;

void hsafe_init(void) {
  char filename[256];
  printf("Initializing HSafe global state.\n");
  sprintf(filename, "%s%d", HSAFE_OUTPUT_FILENAME, hsafe_filecount);
  hsafe_output = fopen(filename, "w");
  gHSafeState.isInitialized = 0;
  gHSafeState.isActive = 0;
}

void update_linecount(void) {
  char filename[256];
  hsafe_linecount++;
  if (hsafe_linecount > MAX_LINE_PER_FILE) {
    fclose(hsafe_output);
    hsafe_linecount = 0;
    hsafe_filecount++;
    sprintf(filename, "%s%d", HSAFE_OUTPUT_FILENAME, hsafe_filecount);
    hsafe_output = fopen(filename, "w");
  }
}
void hsafe_dump_cb(HSafeCodeBlock *cb) {
  int i, j;
  printf("============== Code Block Dump Begin ==============\n");
  printf("   startPc = 0x%lx; len = %ld\n", cb->startPc, cb->currentInstIndex);
  for (i = 0; i < cb->currentInstIndex; ++i) {
    HSafeInstruction *inst = & cb->insts[i];
    printf("     [%03d - 0x%08lx]: ",
           (unsigned int) i,
           (unsigned long) inst->addr);
    for (j = 0; j < HSAFE_MAX_INST_LENGTH; ++j) {
      printf("%02x ", inst->mem[j]);
    }
    printf("\n");
  }
  printf("==============  Code Block Dump End  ==============\n");
}
