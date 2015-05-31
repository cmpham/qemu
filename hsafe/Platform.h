//-----------------------------------------------------------------------------
// Platform-specific functions and macros

#pragma once

#include <stdint.h>

inline uint32_t rotl32 ( uint32_t x, int8_t r );
inline uint64_t rotl64 ( uint64_t x, int8_t r );
inline uint32_t rotr32 ( uint32_t x, int8_t r );
inline uint64_t rotr64 ( uint64_t x, int8_t r );

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)
#define	ROTR32(x,y)	rotr32(x,y)
#define ROTR64(x,y)	rotr64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#include <strings.h>
#define _stricmp strcasecmp

//-----------------------------------------------------------------------------
