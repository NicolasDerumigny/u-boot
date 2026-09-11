#include <init.h>

int board_init(void)
{
	return 0;
}

int ft_board_setup(void *fdt, struct bd_info *bd)
{
	return 0;
}

#if defined(CFG_SYS_DRAM_TEST)

/* RISC-V machine code for:
 *   addi a0, zero, 42   # return value = 42
 *   ret                 # jalr zero, ra, 0
 */
static const u32 test_code[] = {
	0x02a00513, /* addi a0, zero, 42 */
	0x00008067, /* ret               */
};

static int test_execution(uint64_t addr)
{
	void *target = (void *)addr;
	int (*fn)(void) = (int (*)(void))addr;
	int ret;
	register int a0 __asm__("a0");
	a0 = 0;

	memcpy(target, test_code, sizeof(test_code));

	ret = fn();
	return ret == 42;
}

int testdram(void)
{
	uint64_t *pstart = (uint64_t *)CFG_SYS_MEMTEST_START;
	uint64_t *pend = (uint64_t *)CFG_SYS_MEMTEST_END;
	uint64_t step = CFG_SYS_MEMTEST_STEP / sizeof(uint64_t);
	uint64_t *p;

	debug("DRAM test phase 1:\n");
	for (p = pstart; p < pend; p += step)
		*p = 0xaaaaaaaa;

	for (p = pstart; p < pend; p += step) {
		if (*p != 0xaaaaaaaa) {
			printf("DRAM test phase 1 fails at: %08llx\n",
			       (uint64_t)p);
			return 1;
		}
	}

	debug("DRAM test phase 2:\n");
	for (p = pstart; p < pend; p += step)
		*p = 0x55555555;

	for (p = pstart; p < pend; p += step) {
		if (*p != 0x55555555) {
			printf("DRAM test phase 2 fails at: %08llx\n",
			       (uint64_t)p);
			return 1;
		}
	}

	debug("Testing execution...\n");
	for (p = pstart; p < pend; p += step) {
		if (!test_execution((uint64_t)p)) {
			printf("DRAM execution test fails at: %08llx\n",
			       (uint64_t)p);
			return 1;
		}
	}
	debug("Done\n");

	debug("DRAM test passed.\n");
	return 0;
}
#endif
