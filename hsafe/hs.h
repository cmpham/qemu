/**
 * hs.h
 * Cryptographic signature for execution traces
 * Author: Cuong Pham (phammanhcuong@gmail.com)
 * May 28, 2015
 **/
#pragma once

#define OPSHIFT 8

static inline void gen_instr_end(DisasContext *s);

static inline void gen_block_start(DisasContext *s, struct TranslationBlock *tb, uint64_t pc);

static inline void gen_block_end(DisasContext *s /*, struct TranslationBlock *tb*/);
