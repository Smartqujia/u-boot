/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __LS1088_COMMON_H
#define __LS1088_COMMON_H


#define CONFIG_REMAKE_ELF
#define CONFIG_FSL_LAYERSCAPE
#define CONFIG_MP

#include <asm/arch/stream_id_lsch3.h>
#include <asm/arch/config.h>
#include <asm/arch/soc.h>

/* Link Definitions */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_FSL_OCRAM_BASE + 0xfff0)

/* Link Definitions */
#ifdef CONFIG_QSPI_BOOT
#define CONFIG_SYS_TEXT_BASE            0x20100000
#else
#define CONFIG_SYS_TEXT_BASE		0x30100000
#endif

#define CONFIG_SUPPORT_RAW_INITRD


#define CONFIG_SKIP_LOWLEVEL_INIT

#define CONFIG_FSL_DDR_INTERACTIVE	/* Interactive debugging */

#define CONFIG_VERY_BIG_RAM
#define CONFIG_SYS_DDR_SDRAM_BASE	0x80000000UL
#define CONFIG_SYS_FSL_DDR_SDRAM_BASE_PHY	0
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_SYS_DDR_BLOCK2_BASE	0x8080000000ULL
#define CONFIG_SYS_FSL_DDR_MAIN_NUM_CTRLS	1
/*
 * SMP Definitinos
 */
#define CPU_RELEASE_ADDR		secondary_boot_func

#ifdef CONFIG_PCI
#define CONFIG_CMD_PCI
#endif

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2048 * 1024)

/* I2C */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_I2C_MXC_I2C4		/* enable I2C bus 4 */

/* Serial Port */
#define CONFIG_CONS_INDEX       1
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE     1
#define CONFIG_SYS_NS16550_CLK          (get_bus_freq(0) / 2)

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/* IFC */
#define CONFIG_FSL_IFC

/*
 * During booting, IFC is mapped at the region of 0x30000000.
 * But this region is limited to 256MB. To accommodate NOR, promjet
 * and FPGA. This region is divided as below:
 * 0x30000000 - 0x37ffffff : 128MB : NOR flash
 * 0x38000000 - 0x3BFFFFFF : 64MB  : Promjet
 * 0x3C000000 - 0x40000000 : 64MB  : FPGA etc
 *
 * To accommodate bigger NOR flash and other devices, we will map IFC
 * chip selects to as below:
 * 0x5_1000_0000..0x5_1fff_ffff	Memory Hole
 * 0x5_2000_0000..0x5_3fff_ffff	IFC CSx (FPGA, NAND and others 512MB)
 * 0x5_4000_0000..0x5_7fff_ffff	ASIC or others 1GB
 * 0x5_8000_0000..0x5_bfff_ffff	IFC CS0 1GB (NOR/Promjet)
 * 0x5_C000_0000..0x5_ffff_ffff	IFC CS1 1GB (NOR/Promjet)
 *
 * For e.g. NOR flash at CS0 will be mapped to 0x580000000 after relocation.
 * CONFIG_SYS_FLASH_BASE has the final address (core view)
 * CONFIG_SYS_FLASH_BASE_PHYS has the final address (IFC view)
 * CONFIG_SYS_FLASH_BASE_PHYS_EARLY has the temporary IFC address
 * CONFIG_SYS_TEXT_BASE is linked to 0x30000000 for booting
 */

#define CONFIG_SYS_FLASH_BASE			0x580000000ULL
#define CONFIG_SYS_FLASH_BASE_PHYS		0x80000000
#define CONFIG_SYS_FLASH_BASE_PHYS_EARLY	0x00000000

#define CONFIG_SYS_FLASH1_BASE_PHYS		0xC0000000
#define CONFIG_SYS_FLASH1_BASE_PHYS_EARLY	0x8000000

#ifndef __ASSEMBLY__
unsigned long long get_qixis_addr(void);
#endif

#define QIXIS_BASE				get_qixis_addr()
#define QIXIS_BASE_PHYS				0x20000000
#define QIXIS_BASE_PHYS_EARLY			0xC000000


#define CONFIG_SYS_NAND_BASE			0x530000000ULL
#define CONFIG_SYS_NAND_BASE_PHYS		0x30000000


/* MC firmware */
/* TODO Actual DPL max length needs to be confirmed with the MC FW team */
#define CONFIG_SYS_LS_MC_DPC_MAX_LENGTH	    0x20000
#define CONFIG_SYS_LS_MC_DRAM_DPC_OFFSET    0x00F00000
#define CONFIG_SYS_LS_MC_DPL_MAX_LENGTH	    0x20000
#define CONFIG_SYS_LS_MC_DRAM_DPL_OFFSET    0x00F20000
#define CONFIG_SYS_LS_MC_AIOP_IMG_MAX_LENGTH	0x200000
#define CONFIG_SYS_LS_MC_DRAM_AIOP_IMG_OFFSET	0x07000000
/*
 * Carve out a DDR region which will not be used by u-boot/Linux
 *
 * It will be used by MC and Debug Server. The MC region must be
 * 512MB aligned, so the min size to hide is 512MB.
 */

#if defined(CONFIG_FSL_MC_ENET)
#define CONFIG_SYS_LS_MC_DRAM_BLOCK_MIN_SIZE		(512UL * 1024 * 1024)
#endif

#define CONFIG_FSL_CAAM			/* Enable SEC/CAAM */

/* Command line configuration */
#define CONFIG_CMD_GREPENV
#define CONFIG_CMD_CACHE

/* Miscellaneous configurable options */
#define CONFIG_SYS_LOAD_ADDR	(CONFIG_SYS_DDR_SDRAM_BASE + 0x10000000)

/* Physical Memory Map */
#define CONFIG_CHIP_SELECTS_PER_CTRL	4

#define CONFIG_NR_DRAM_BANKS		2

#define CONFIG_HWCONFIG
#define HWCONFIG_BUFFER_SIZE		128

/* #define CONFIG_DISPLAY_CPUINFO */

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS		\
	"hwconfig=fsl_ddr:bank_intlv=auto\0"	\
	"loadaddr=0x80100000\0"			\
	"kernel_addr=0x100000\0"		\
	"ramdisk_addr=0x800000\0"		\
	"ramdisk_size=0x2000000\0"		\
	"fdt_high=0xa0000000\0"			\
	"initrd_high=0xffffffffffffffff\0"	\
	"kernel_start=0x581000000\0"		\
	"kernel_load=0xa0000000\0"		\
	"kernel_size=0x2800000\0"		\
	"console=ttyAMA0,38400n8\0"		\
	"mcinitcmd=fsl_mc start mc 0x580a00000"	\
	" 0x580e00000 \0"

#define CONFIG_BOOTARGS		"console=ttyS0,115200 root=/dev/ram0 " \
				"earlycon=uart8250,mmio,0x21c0500 " \
				"ramdisk_size=0x3000000 default_hugepagesz=2m" \
				" hugepagesz=2m hugepages=256"
#if defined(CONFIG_QSPI_BOOT)
#define CONFIG_BOOTCOMMAND	"sf probe 0:0;" \
				"sf read 0x80200000 0xd00000 0x100000;"\
				" fsl_mc apply dpl 0x80200000 &&" \
				" sf read $kernel_load $kernel_start" \
				" $kernel_size && bootm $kernel_load"
#else /* NOR BOOT*/
#define CONFIG_BOOTCOMMAND	"fsl_mc apply dpl 0x580d00000 &&" \
				" cp.b $kernel_start $kernel_load" \
				" $kernel_size && bootm $kernel_load"
#endif

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE /* Boot args buffer */
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMDLINE_EDITING		1
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_MAXARGS		64	/* max command args */

#define CONFIG_PANIC_HANG	/* do not reset board on panic */

#define CONFIG_SYS_BOOTM_LEN   (64 << 20)      /* Increase max gunzip size */

#endif /* __LS1088_COMMON_H */
