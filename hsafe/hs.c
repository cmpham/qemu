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

void hsafe_init(void) {
    printf("Initializing HSafe global state.\n");
    gHSafeState.isInitialized = 0;
    gHSafeState.isActive = 0;
}
