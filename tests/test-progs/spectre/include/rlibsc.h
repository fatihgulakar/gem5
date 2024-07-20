#include <stddef.h>
#include <stdint.h>

// -----------------------
// Common implementation +
// -----------------------

// Get number of retired instructions
static inline size_t rdinstret() {
  size_t val;
  asm volatile("rdinstret %0" : "=r"(val));
  return val;
}

// Get number of spend CPU cycpes
static inline size_t rdcycle() {
  size_t val;
  asm volatile("rdcycle %0" : "=r"(val));
  return val;
}

// Lower resolutin timestamp
static inline uint64_t rdtime() {
  uint64_t val;
  asm volatile("rdtime %0" : "=r"(val));
  return val;
}

// rdcycle but via the csr instead of pseudo instruction
static inline uint64_t get_cycle_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, cycle" : "=r"(val));
  return val;
}

// rdtime but via the csr instead of pesudo instruction
static inline uint64_t get_time_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, time" : "=r"(val));
  return val;
}

// rdinstret but via the csr instead of pesudo instruction
static inline uint64_t get_retire_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, instret" : "=r"(val));
  return val;
}

// Counter thread to get a timer
static uint64_t count_thread(uint64_t spins) {
  uint64_t val;
  for (uint64_t i = 0; i < spins; i++) {
    val++;
    asm("" ::: "memory"); // Prevents loop optimization
  }
  return val;
}

// Flushes the I-Cache using the fence.i instruction
static inline void fencei() { asm volatile("fence.i"); }

// Fenche instruction
static inline void fence() {
  asm volatile ("fence");
}

// Access memory location
static inline void maccess(void *addr) {
  asm volatile("ld a7, (%0)" : : "r"(addr) : "a7", "memory");
}

// ------------------------------
// C906 specific implementaions +
// ------------------------------
#if defined(C906) || defined(C910)

// Flushes virtual address from the D-Cache
static inline void flush(void *addr) {
  asm volatile("xor a7, a7, a7\n"
               "add a7, a7, %0\n"
               ".long 0x278800b" // DCACHE.CIVA a7
               :
               : "r"(addr)
               : "a7", "memory");
}

// Flushes virtual address from the I-Cache
static inline void iflush(void* addr) {
    asm volatile("xor a7, a7, a7\n"
                 "add a7, a7, %0\n"
                 ".long 0x308800b" // ICACHE.IVA a7
                 : : "r"(addr) : "a7","memory");
}


// -----------------------------
// U74 specific implementaions +
// -----------------------------
#elif defined(U74)

#endif
