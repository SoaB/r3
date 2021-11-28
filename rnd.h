#ifndef HEADER_727957CFCE7C7BF6
#define HEADER_727957CFCE7C7BF6

#include <stdint.h>

typedef struct {
  uint64_t state;
  uint64_t inc;
} random_t;

static random_t rnd_rng = {0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL};

void rnd_Seed(uint64_t seed, uint64_t seq);
uint32_t rnd_R32(void);
uint32_t rnd_UniBound32(uint32_t bound);
uint32_t rnd_R32n(uint32_t min, uint32_t max);
float rnd_F();
float rnd_Fn(float n);
///////////////////////////////////////////////////////////////////////
void rnd_Seed(uint64_t seed, uint64_t seq) {
  rnd_rng.state = 0U;
  rnd_rng.inc = (seq << 1u) | 1u;
  rnd_R32();
  rnd_rng.state += seed;
  rnd_R32();
}

uint32_t rnd_R32(void) {
  uint64_t oldstate = rnd_rng.state;
  rnd_rng.state = oldstate * 6364136223846793005ULL + rnd_rng.inc;
  uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}
uint32_t rnd_R32n(uint32_t min, uint32_t max) {
  uint32_t val = rnd_R32();
  return (val % (max - min + 1)) + min;
}
uint32_t rnd_UniBound32(uint32_t bound) {
  uint32_t threshold = -bound % bound;
  for (;;) {
    uint32_t r = rnd_R32();
    if (r >= threshold)
      return r % bound;
  }
}

float rnd_F() {
  uint32_t value = rnd_R32();
  return (float)value / (float)UINT32_MAX;
}

float rnd_Fn(float n) {

  return rnd_F() * n;
}
#endif // header guard
