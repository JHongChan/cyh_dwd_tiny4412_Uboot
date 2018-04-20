/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG ORIGEN (EXYNOS4412) board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_TINY4412_H
#define __CONFIG_TINY4412_H

#include <configs/exynos4-common.h>

/* High Level Configuration Options */
#define CONFIG_EXYNOS4412		1	/* which is a EXYNOS4412 SoC */
#define CONFIG_TINY4412			1	/* working with TINY4412*/

#define CONFIG_SUPPORT_EMMC_BOOT	1 	 /* support u-boot in eMMC */

/* DEBUG UART */
#if ! defined(CONFIG_SPL_BUILD)
#if 0
	/* U-BOOT DEBUG */
	#define DEBUG
#endif
#else
#if 0
	/* SPL DEBUG */
	#define CONFIG_DEBUG_UART			1 
	#define CONFIG_SPL_SERIAL_SUPPORT	1
	#define CONFIG_SPL_GPIO_SUPPORT		1
	#define CONFIG_DEBUG_UART_S5P		1
	#define CONFIG_DEBUG_UART_BASE		0x13800000
	#define CONFIG_DEBUG_UART_CLOCK		(100000000)
#endif
#endif

/* MMC CONFIG  */
#define CONFIG_BLK			1

/* USB */
#define CONFIG_USB_EHCI_EXYNOS         1

/* USB-KEYBOARD */
#define CONFIG_SYS_STDIO_DEREGISTER 	1 

/* ETHERNET */
#define CONFIG_USB_HOST_ETHER          1
#define CONFIG_USB_ETHER_DM9621                1

/* BOOTP */
#define CONFIG_BOOTP_SERVERIP          1

#define CONFIG_SYS_DCACHE_OFF		1

/* ORIGEN has 4 bank of DRAM */
#define CONFIG_NR_DRAM_BANKS		4
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE			(256 << 20)	/* 256 MB */

/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x6000000)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)

#define CONFIG_SYS_TEXT_BASE           0x43E00000

#define CONFIG_MACH_TYPE		MACH_TYPE_ORIGEN

/* select serial console configuration */
#define CONFIG_SERIAL0
#define CONFIG_BAUDRATE                        115200

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC0,115200n8\0"

#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

/* MMC SPL */
#define COPY_BL2_FNPTR_ADDR	0x02020030
#define CONFIG_SPL_TEXT_BASE	0x02023400

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x40008000\0" \
	"rdaddr=0x48000000\0" \
	"kerneladdr=0x40008000\0" \
	"ramdiskaddr=0x48000000\0" \
	"console=ttySAC0,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
        "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
        "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
                "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
	"fi;" \
	"load mmc ${mmcdev} ${loadaddr} uImage; bootm ${loadaddr} "

#define CONFIG_CLK_1000_400_200

#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

/*
 *    SD MMC layout:
 *    +------------+------------------------------------------------------------+
 *    |                                                                         |
 *    |            |            |               |              |                |
 *    |   512B     |   8K(bl1)  |    16k(bl2)   |   16k(ENV)   |  512k(u-boot)  |
 *    |            |            |               |              |                |
 *    |                                                                         |
 *    +------------+------------------------------------------------------------+
 *	eMMC layout:
 *    +------------------------------------------------------------------------------------------+
 *    |                                                                                          |
 *    |            |            |               |              |                |                |
 *    |   512B     |   8K(bl1)  |    16k(bl2)   |  1M(u-boot)  |    92k(TZSW)   |    16K(ENV)    |
 *    |            |            |               |              |                |                |
 *    |                                                                                          |
 *    +------------------------------------------------------------------------------------------+
 *
 */

#if (1)
       #define CONFIG_SYS_MMC_ENV_DEV  (2)                     /* Need match ts of mmc id */
       #define RESERVE_BLOCK_SIZE              (512)
#else
       #define CONFIG_SYS_MMC_ENV_DEV  (4)                     /* Need match ts of mmc id */
       #define RESERVE_BLOCK_SIZE              (0)
#endif


#define CONFIG_ENV_SIZE			(16 << 10)	/* 16 KB */
#define BL1_SIZE				(8 << 10) 	/* 8K reserved for BL1*/
#define BL2_SIZE				(16 << 10)	/* 16K reserved for BL2 */
#define TZSW_SIZE				(92 << 10)	/* 92K tzsw size */
#define CONFIG_ENV_OFFSET		(RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE + COPY_BL2_SIZE  + TZSW_SIZE)

#define CONFIG_SPL_LDSCRIPT    "board/samsung/common/exynos-uboot-spl.lds"
#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_SYS_INIT_SP_ADDR		0x02040000

/* U-Boot copy size from boot Media to DRAM.*/
#define COPY_BL2_SIZE		0x100000
#define BL2_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE)/512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE/512)


/*#define CONFIG_ENV_OFFSET_REDUND*/

#endif	/* __CONFIG_H */
