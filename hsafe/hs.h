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

static inline void hsafe_custom_instruction(DisasContext *s, target_ulong arg);

static inline void gen_instr_end(DisasContext *s)
{
    if (s && !s->done_instr_end) {
        s->done_instr_end = 1;
    }
}

static inline void gen_block_start(DisasContext *s, struct TranslationBlock *tb, uint64_t pc)
{

}

static inline void gen_block_end(DisasContext *s /*, struct TranslationBlock *tb*/)
{

}

static inline void hsafe_custom_instruction(DisasContext *s, target_ulong arg)
{
    uint8_t opc = (arg >> OPSHIFT) & 0xFF;
    switch(opc) {
      case 0x60: /* profile_init */
        printf("\tprofile_init\n");
        break;

      case 0x61: /* profile_stop */
        printf("\tprofile_stop\n");
        break;

      case 0x62: /* profile_block_begin */
        printf("\tprofile_block_begin\n");
        break;

      case 0x63: /* profile_block_end */
        printf("\tprofile_block_end\n");
        break;

      default:
        printf("\tUnsupported opcode\n");
    }
}
