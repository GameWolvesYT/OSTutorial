#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct 
{
	uint32_t flags;
	uint32_t memory_lo;
	uint32_t memory_hi;
	uint32_t boot_device;
	uint32_t cmd_ln;
	uint32_t mods_cnt;
	uint32_t mods_addr;
	uint32_t syms0;
	uint32_t syms1;
	uint32_t syms2;
	uint32_t mmap_len;
	uint32_t mmap_addr;
	uint32_t drives_len;
	uint32_t drives_addr;
	uint32_t conf_table;
	uint32_t boot_name;
	uint32_t apm_table;
	uint32_t vbe_ctrl_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_io_seg;
	uint32_t vbe_io_off;
	uint16_t vbe_io_len;
} __attribute__((packed)) multiboot_info_t;

#endif