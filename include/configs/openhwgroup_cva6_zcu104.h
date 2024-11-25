#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#define CFG_SYS_SDRAM_BASE 0x80000000
#define CFG_SYS_INIT_SP_ADDR (CFG_SYS_SDRAM_BASE + SZ_2M)

#define CFG_SYS_INIT_RAM_ADDR CFG_SYS_SDRAM_BASE
#define CFG_SYS_INIT_RAM_SIZE 0x10000000

#define CFG_SYS_MALLOC_LEN SZ_8M

#define CFG_SYS_MAX_FLASH_BANKS 1
#define CFG_SYS_FLASH_BASE 0x0

#define CFG_EXTRA_ENV_SETTINGS                                                 \
  "bootargs=loglevel=8\0"                                                      \
  "uimage_sector_start=0x100000\0"                                             \
  "uimage_size=0x8000\0"

#endif
