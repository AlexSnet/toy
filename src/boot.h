#ifndef BOOT_H
#define BOOT_H

#define CR0_PG (1 << 31)
#define CR0_PE (1 << 0)
#define CR4_OSFXSR (1 << 9)
#define CR4_PAE (1 << 5)
#define MSR_EFER 0xC0000080
#define MSR_EFER_LME (1 << 8)
#define MSR_FS_BASE 0xC0000100
#define MSR_GS_BASE 0xC0000101

#define SEGMENT_CODE (1 << 3)
#define SEGMENT_DATA (2 << 3)

#define RFLAGS_IF (1 << 9)

static inline int get_started_cpus() {
  extern int started_cpus;
  return started_cpus;
}

#endif // BOOT_H
