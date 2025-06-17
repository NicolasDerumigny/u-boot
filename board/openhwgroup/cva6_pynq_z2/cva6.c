#include <init.h>

int board_init(void) { return 0; }

int ft_board_setup(void *fdt, struct bd_info *bd) { return 0; }

void *board_fdt_blob_setup(int *err) {
  *err = 0;
  return ((void *)0x82200000);
}
