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

HSafeBBNode *HSafe_BB_Buffer;

long hsafe_node_count = 0;
char hsafe_output_str[HSAFE_BB_BUFFER_SIZE * 32];

void hsafe_init(void) {
  char filename[256];
  printf("Initializing HSafe global state.\n");
  sprintf(filename, "%s/%s%d", HSAFE_OUTPUT_TEMP_DIR, HSAFE_OUTPUT_FILENAME, hsafe_filecount);
  hsafe_output = fopen(filename, "w");
  gHSafeState.isInitialized = 0;
  gHSafeState.isActive = 0;
  HSafe_BB_Buffer = (HSafeBBNode *) malloc((HSAFE_BB_BUFFER_SIZE + 1) * sizeof(HSafeBBNode));
}

void hsafe_flush_output(void) {
  int i, length;
  length = 0;
  for (i = 0; i < hsafe_node_count; ++i) {
    length += sprintf(hsafe_output_str + length, "%" PRIu64 "; 0x%" PRIx64 "\n",
          /* (unsigned long long) */ HSafe_BB_Buffer[i].bblockIndex,
          /* (unsigned long long) */ HSafe_BB_Buffer[i].startPc);
  }

  fwrite(hsafe_output_str, length, 1, hsafe_output);
  fflush(hsafe_output);
  update_linecount(); 
}

void hsafe_save_node(uint64_t startPc, uint64_t bblockIndex) {
  HSafe_BB_Buffer[hsafe_node_count].startPc = startPc;
  HSafe_BB_Buffer[hsafe_node_count].bblockIndex = bblockIndex;
  hsafe_node_count++;
  if (hsafe_node_count >= HSAFE_BB_BUFFER_SIZE) {
    // flush to file
    hsafe_flush_output();
    hsafe_node_count = 0;
  }
}

void update_linecount(void) {
  char filename[256];
  char new_location[256];
  char cmd[512];
  hsafe_linecount++;
  if (hsafe_linecount > MAX_LINE_PER_FILE) {
    fclose(hsafe_output);

    // Moving file to the current dir
    sprintf(filename, "%s/%s%d", HSAFE_OUTPUT_TEMP_DIR, HSAFE_OUTPUT_FILENAME, hsafe_filecount);
    sprintf(new_location, "%s%d", HSAFE_OUTPUT_FILENAME, hsafe_filecount);
    sprintf(cmd, "mv %s %s", filename, new_location);
    if (system(cmd) != -1) {
      printf("Moved file %s to %s.\n", filename, new_location);
    } else {
      printf("Failed to move file %s to %s.\n", filename, new_location);
      perror( NULL );
    }

    // Start writing to a new file
    hsafe_linecount = 0;
    hsafe_filecount++;
    sprintf(filename, "%s/%s%d", HSAFE_OUTPUT_TEMP_DIR, HSAFE_OUTPUT_FILENAME, hsafe_filecount);
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
