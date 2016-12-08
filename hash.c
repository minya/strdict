#include <stdio.h>
#include "hash.h"

const uint32_t FNV_offset_basis_32 = 2166136261;
const uint32_t FNV_prime_32 = 16777619;

uint32_t FNV_hash(char *s)
{
    uint32_t hash = FNV_offset_basis_32;
    for (char *c = s; *c != 0; ++c) {
        hash = (hash * FNV_prime_32) % ~0;
        hash = hash ^ (*c);
    }
    return hash;
}
