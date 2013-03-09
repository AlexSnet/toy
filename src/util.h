#ifndef UTIL_H
#define UTIL_H

#define STR(x) #x
#define STR_EXPAND(x) STR(x)

#define ALIGNED(n) __attribute__((aligned(n)))
#define PACKED __attribute__((packed))
#define SECTION(name) __attribute__((section(name)))

typedef __builtin_va_list va_list;
#define va_start(vargs, last_param) __builtin_va_start(vargs, last_param)
#define va_end(vargs) __builtin_va_end(vargs)
#define va_arg(vargs, arg_type) __builtin_va_arg(vargs, arg_type)

#define NULL (void*)0

typedef _Bool bool;
#define true (bool)1
#define false (bool)0

static inline const char *bool_str(bool value) {
  return value ? "true" : "false";
}

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#ifdef __LP64__
typedef long int64_t;
typedef unsigned long uint64_t;
typedef unsigned long size_t;
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef unsigned int size_t;
#endif

#define UINT8_MAX (uint8_t)0xff
#define UINT16_MAX (uint16_t)0xffff
#define UINT32_MAX (uint32_t)0xffffffff
#define UINT64_MAX (uint64_t)0xffffffffffffffffL

#define INT_BITS(value, low, high)              \
  (value << (sizeof(value) * 8 - 1 - high) >>   \
   (sizeof(value) * 8 - 1 - high + low))

#define ROUND_DIV(dividend, divisor) \
  (((dividend) + (divisor) - 1) / (divisor))

// minimal number of elements with total size >= given size
#define SIZE_ELEMENTS(size, element_size) \
  (((size) + (element_size) - 1) / (element_size))

#define ASM __asm__
#define ASMV __asm__ __volatile__

static inline int bsr(uint64_t value) {
  uint64_t index;
  ASMV("bsrq %1, %0" : "=r"(index) : "mr"(value));
  return (int)index;
}

static inline uint8_t inb(uint16_t port) {
  uint8_t value;
  ASMV("inb %%dx, %%al" : "=a"(value) : "d"(port));
  return value;
}

static inline void outb(uint16_t port, uint8_t value) {
  ASMV("outb %%al, %%dx" : : "a"(value), "d"(port));
}

static inline uint64_t rdmsr(uint32_t msr) {
  uint32_t low, high;
  ASMV("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
  return ((uint64_t)high << 32) + low;
}

static inline void wrmsr(uint32_t msr, uint64_t value) {
  uint32_t low = (uint32_t)value, high = (uint32_t)(value >> 32);
  ASMV("wrmsr" : : "a"(low), "d"(high), "c"(msr));
}

size_t strlen(const char *str);
char *strrev(char *str);

void *memset(void *ptr, int value, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
int memcmp(const void *buf1, const void *buf2, size_t size);
void *memmem(const void *buf1, size_t size1, const void *buf2, size_t size2);

// negative radix means uppercase result string
char *ultoa(unsigned long value, char *buf, int radix);

int putchar(int chr);
int printf(const char *format, ...);

#define LOG_ERROR(format, ...)                          \
  { printf("%s: ", __func__);                           \
    printf(format, ##__VA_ARGS__); printf("\n"); }
#define LOG_INFO(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#ifdef DEBUG
#define LOG_DEBUG(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#endif

#endif // UTIL_H
