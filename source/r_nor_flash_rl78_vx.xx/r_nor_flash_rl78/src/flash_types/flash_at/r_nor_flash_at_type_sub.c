/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * System Name  : NOR FLASH driver software
 * File Name    : r_nor_flash_at_type_sub.c
 * Version      : 1.00
 * Device       : -
 * Abstract     : Sub module
 * Tool-Chain   : -
 * OS           : not use
 * H/W Platform : -
 * Description  : NOR FLASH Sub file
 * Limitation   : None
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_nor_flash_rl78_if.h"                /* FLASH driver I/F definitions                 */
#include "r_nor_flash_rl78_config.h"            /* FLASH driver Configuration definitions       */
#include "../../r_nor_flash_private.h"          /* FLASH driver Private module definitions      */


/* Check flash memory types. */
#if IS_SUPPORTING_AT()


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/*---------- Definitions of FLASH command -----------*/
#define NOR_FLASH_AT_CMD_WREN   (0x06U) /* Write Enable                                 */
#define NOR_FLASH_AT_CMD_WRDI   (0x04U) /* Write Disable                                */
#define NOR_FLASH_AT_CMD_RDSR1  (0x05U) /* Read Status Register 1                       */
#define NOR_FLASH_AT_CMD_RDSR2  (0x35U) /* Read Status Register 2                       */
#define NOR_FLASH_AT_CMD_RDSR3  (0x15U) /* Read Status Register 3                       */
#define NOR_FLASH_AT_CMD_WRSR1  (0x01U) /* Write Status Register 1                      */
#define NOR_FLASH_AT_CMD_WRSR2  (0x31U) /* Write Status Register 2                      */
#define NOR_FLASH_AT_CMD_WRSR3  (0x11U) /* Write Status Register 3                      */
#define NOR_FLASH_AT_CMD_FREAD  (0x0bU) /* Fast Read                                    */
#define NOR_FLASH_AT_CMD_RDSCUR (0x48U) /* Read Security Registers                      */
#define NOR_FLASH_AT_CMD_PP     (0x02U) /* Page Program                                 */
#define NOR_FLASH_AT_CMD_PSCUR  (0x42U) /* Program Security Registers                   */
#define NOR_FLASH_AT_CMD_ESCUR  (0x44U) /* Erase Security Registers                     */
#define NOR_FLASH_AT_CMD_BE4K   (0x20U) /* Block Erase (4KB)                            */
#define NOR_FLASH_AT_CMD_BE32K  (0x52U) /* Block Erase (32KB)                           */
#define NOR_FLASH_AT_CMD_BE64K  (0xd8U) /* Block Erase (64KB)                           */
#define NOR_FLASH_AT_CMD_CE     (0x60U) /* Chip Erase                                   */
#define NOR_FLASH_AT_CMD_RDID   (0x9fU) /* Read JEDEC ID                                */


/*--------- Command transmission processing ----------*/
/* Write Enable command */
#define R_NOR_FLASH_AT_CMD_WREN()       (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_WREN, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Write Disable command */
#define R_NOR_FLASH_AT_CMD_WRDI()       (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_WRDI, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Read Status Register 1 command */
#define R_NOR_FLASH_AT_CMD_RDSR1()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_RDSR1, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Read Status Register 2 command */
#define R_NOR_FLASH_AT_CMD_RDSR2()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_RDSR2, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Read Status Register 3 command */
#define R_NOR_FLASH_AT_CMD_RDSR3()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_RDSR3, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Write Status Register 1 command */
#define R_NOR_FLASH_AT_CMD_WRSR1()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_WRSR1, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Write Status Register 2 command */
#define R_NOR_FLASH_AT_CMD_WRSR2()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_WRSR2, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Write Status Register 3 command */
#define R_NOR_FLASH_AT_CMD_WRSR3()      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_WRSR3, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Erase Security Registers command */
#define R_NOR_FLASH_AT_CMD_ESCUR(addr, addr_size)   (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_ESCUR, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE))
/* Block Erase (4KB) command */
#define R_NOR_FLASH_AT_CMD_BE4K(addr, addr_size)    (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_BE4K, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE+(addr_size)))
/* Block Erase (32KB) command */
#define R_NOR_FLASH_AT_CMD_BE32K(addr, addr_size)   (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_BE32K, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE+(addr_size)))
/* Block Erase (64KB) command */
#define R_NOR_FLASH_AT_CMD_BE64K(addr, addr_size)   (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_BE64K, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE+(addr_size)))
/* Chip Erase command */
#define R_NOR_FLASH_AT_CMD_CE(addr)     (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_CE,   (uint32_t)(addr), \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* Read JEDEC ID command */
#define R_NOR_FLASH_AT_CMD_RDID()       (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_RDID, (uint32_t)0, \
                                                            NOR_FLASH_AT_CMD_SIZE))
/* READ Command */
/* 1 Dummy cycle is indicated as "1". */
/* Fast Read command */
#define R_NOR_FLASH_AT_CMD_FREAD(addr, addr_size)   (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_FREAD, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE+(addr_size)+1))
/* Read Security Registers command */
#define R_NOR_FLASH_AT_CMD_RDSCUR(addr, addr_size)  (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_RDSCUR, \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE+(addr_size)+1))
/* Page Program Command */
#define R_NOR_FLASH_AT_CMD_PP(addr, addr_size)      (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_PP,  \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE))
/* Program Security Registers Command */
#define R_NOR_FLASH_AT_CMD_PSCUR(addr, addr_size)   (r_nor_flash_at_send_cmd(NOR_FLASH_AT_CMD_PSCUR,  \
                                                            (uint32_t)(addr), NOR_FLASH_AT_CMD_SIZE))


/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
/* uint32_t <-> uint8_t conversion */
typedef union
{
    uint32_t    ul;
    uint8_t     uc[4];
} u_nor_flash_at_exchg_long_t;      /* total 4 bytes */


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
static uint32_t s_nor_flash_at_cmdbuf[8/sizeof(uint32_t)];  /* Command transmission buffer */

/* Command transmission */
static e_nor_flash_status_t r_nor_flash_at_send_cmd (uint8_t cmd, uint32_t addr, uint8_t cmdsize);

/* Writing enable */
static e_nor_flash_status_t r_nor_flash_at_write_enable (void);

static e_nor_flash_status_t r_nor_flash_at_check_busy_reg_write (void);

static void                 r_nor_flash_at_cmd_set (uint8_t cmd, uint32_t addr, uint8_t cmdsize);


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_init_port
 * Description  : Initialize the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_at_init_port(void)
{
    r_nor_flash_cs_init();                         /* SS# "H" */
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_init_port
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_reset_port
 * Description  : Reset the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_at_reset_port(void)
{
    r_nor_flash_cs_reset();                        /* SS# "H" */
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_reset_port
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_send_cmd
 * Description  : Sends a FLASH command.
 * Arguments    : uint8_t            cmd                    ;   Command data
 *              : uint32_t           addr                   ;   Address data
 *              : uint8_t            cmdsize                ;   Command size
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
static e_nor_flash_status_t r_nor_flash_at_send_cmd(uint8_t cmd, uint32_t addr, uint8_t cmdsize)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_at_cmd_set(cmd, addr, cmdsize);
    
    /* The upper layer software should set to the single mode. */
    /* Send a command using the single mode. */
    /* Cast from 8-bit data to 16-bit data. */
    ret = r_nor_flash_drvif_tx((uint16_t)cmdsize, (uint8_t *)&s_nor_flash_at_cmdbuf[0]);

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_send_cmd
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_enable
 * Description  : Executes a Write Enable operation.
 *              : Issues the Write Enable command and sets the WEL bit.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
static e_nor_flash_status_t r_nor_flash_at_write_enable(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Write Enable command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_WREN();

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_enable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_disable
 * Description  : Executes a Write Disable operation.
 *              : Issues the Write Disable command and clears the WEL bit.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_disable(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Write Disable command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_WRDI();

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_disable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg1
 * Description  : Reads status from the status register 1 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 1 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg1(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Status Register 1 command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_RDSR1();
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Receive data from the status register using the single mode. */
    ret = r_nor_flash_drvif_rx(NOR_FLASH_AT_STSREG1_SIZE, p_status);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_read_stsreg1
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg2
 * Description  : Reads status from the status register 2 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 2 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg2(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Status Register 2 command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_RDSR2();
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Receive data from the status register using the single mode. */
    ret = r_nor_flash_drvif_rx(NOR_FLASH_AT_STSREG2_SIZE, p_status);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_read_stsreg2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg3
 * Description  : Reads status from the status register 3 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 3 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg3(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Status Register 3 command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_RDSR3();
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Receive data from the status register using the single mode. */
    ret = r_nor_flash_drvif_rx(NOR_FLASH_AT_STSREG3_SIZE, p_status);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_read_stsreg3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_set_write_protect
 * Description  : Makes a write-protection setting using Block Lock (BP) protection mode.
 *              : The BP2, BP1 and BP0 bit of status register are set as follows by
 *              : write-protection setting data (wpsts).
 *              :
 *              :    wpsts=0x00  :   BP2=0, BP1=0, BP0=0
 *              :    wpsts=0x01  :   BP2=0, BP1=0, BP0=1
 *              :    wpsts=0x02  :   BP2=0, BP1=1, BP0=0
 *              :    wpsts=0x03  :   BP2=0, BP1=1, BP0=1
 *              :    wpsts=0x04  :   BP2=1, BP1=0, BP0=0
 *              :    wpsts=0x05  :   BP2=1, BP1=0, BP0=1
 *              :    wpsts=0x06  :   BP2=1, BP1=1, BP0=0
 *              :    wpsts=0x07  :   BP2=1, BP1=1, BP0=1
 *              :
 *              : The TB bit of status register 1 is set.
 *              :    TB (Top/Bottom)
 *              :        1: Bottom area protect
 *              :        0: Top area protect
 *              : The SEC bit of status register 1 is set.
 *              :    SEC (Block Protection)
 *              :        1: Select small block size protection
 *              :        0: Select large block size protection
 *              :
 * Arguments    : uint8_t            wpsts          ;   Write-protection setting data
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM               ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : A SRWD bit is fixed to 0.
 *              : Please confirm the status register.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_set_write_protect(uint8_t wpsts)
{
    e_nor_flash_status_t ret     = NOR_FLASH_SUCCESS;
    uint8_t              reg;
    uint8_t              stsreg1 = 0;

    if (wpsts > NOR_FLASH_AT_WP_WHOLE_MEM)
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1(&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

    /* Store the write-protection information. */
    reg = (uint8_t)((stsreg1 & (uint8_t)(~(NOR_FLASH_AT_REG1_BPMASK | NOR_FLASH_AT_REG1_SRP0))) | (wpsts << 2));

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Therefore set Write Protection Selection (WPSEL) to 0 (default). */
    /* Execute the Write Status Register command operation using the single mode. */
    /* Execute the Read Status Register command operation using the single mode 
       in r_nor_flash_mx_write_stsreg(). */
    ret = r_nor_flash_at_write_stsreg1(&reg);

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_set_write_protect
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_stsreg1
 * Description  : Writes status from the write status storage buffer to the status register 1.
 *              : 
 *              :        Bit 7: Status Register Protection (SRP0)
 *              :        Bit 6: Block Protection (SEC)
 *              :        Bit 5: Top or Bottom Protection (TB)
 *              :        Bits 4 to 2: Block protect 2 - 0 (BP2 - BP0)
 *              :                  Set to 1, a designated memory area is protected from PROGRAM and ERASE operations.
 *              :        Bit 1: Write Enable Latch Status (WEL)
 *              :                  1: Device is Write Enabled.
 *              :                  0: Device is not Write Enabled (default).
 *              :        Bit 0: Ready/Busy Status (RDY/BSY)
 *              :                  1: Device is busy with an internal operation.
 *              :                  0: Device is ready.
 *              :
 * Arguments    : uint8_t     * p_reg              ;   Status register 1 setting data buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                ;   Successful operation
 *              : NOR_FLASH_ERR_HARD               ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_stsreg1(uint8_t * p_reg)
{
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1         = 0;       /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */
    e_nor_flash_status_t ret             = NOR_FLASH_SUCCESS;
    uint8_t              data_size       = 0;
    uint8_t              data_buff[2];

    data_buff[0] = 0;
    data_buff[1] = 0;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1(&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))  /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Sets configuration fixed data for writing. */
    data_buff[0] = NOR_FLASH_AT_CMD_WRSR1;
    data_buff[1] = (*p_reg) | NOR_FLASH_AT_REG1_WEL;
    data_size    = NOR_FLASH_AT_CMD_SIZE + NOR_FLASH_AT_WSTSREG1_SIZE;

    /* Transmit data to the status register using the single mode. */
    ret = r_nor_flash_drvif_tx(data_size, &data_buff[0]);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_stsreg1
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_stsreg2
 * Description  : Writes status from the write status storage buffer to the status register 2.
 * Arguments    : uint8_t     * p_reg               ;   Status register 2 setting data buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_stsreg2(uint8_t * p_reg)
{
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1        = 0;        /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */
    e_nor_flash_status_t ret            = NOR_FLASH_SUCCESS;
    uint8_t              data_size      = 0;
    uint8_t              data_buff[2];

    data_buff[0] = 0;
    data_buff[1] = 0;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1(&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))  /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Sets configuration fixed data for writing. */
    data_buff[0] = NOR_FLASH_AT_CMD_WRSR2;
    data_buff[1] = *p_reg;
    data_size    = NOR_FLASH_AT_CMD_SIZE + NOR_FLASH_AT_WSTSREG2_SIZE;

    /* Transmit data to the status register 2 using the single mode. */
    ret = r_nor_flash_drvif_tx(data_size, &data_buff[0]);
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_stsreg2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_stsreg3
 * Description  : Writes status from the write status storage buffer to the status register 3.
 * Arguments    : uint8_t     * p_reg               ;   Status register 3 setting data buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_stsreg3(uint8_t * p_reg)
{
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1        = 0;    /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */
    e_nor_flash_status_t ret            = NOR_FLASH_SUCCESS;
    uint8_t              data_size      = 0;
    uint8_t              data_buff[2];

    data_buff[0] = 0;
    data_buff[1] = 0;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1(&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Sets configuration fixed data for writing. */
    data_buff[0] = NOR_FLASH_AT_CMD_WRSR3;
    data_buff[1] = *p_reg;
    data_size    = NOR_FLASH_AT_CMD_SIZE + NOR_FLASH_AT_WSTSREG3_SIZE;

    /* Transmit data to the status register 3 using the single mode. */
    ret = r_nor_flash_drvif_tx(data_size, &data_buff[0]);
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_stsreg3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read
 * Description  : Reads data from the specified address (addr) for the specified number (cnt) of bytes
 *              : and stores to the specified buffer (pData).
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Temporary Number of bytes to be read
 *              :    uint8_t          * pData               ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret       = NOR_FLASH_SUCCESS;
    uint8_t              addr_size = 0;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the READ command using the single mode. */
    addr_size = NOR_FLASH_AT_ADDR_SIZE;

    ret = R_NOR_FLASH_AT_CMD_FREAD(p_nor_flash_info->addr, addr_size);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Set data size to receive. */
    p_nor_flash_info->data_cnt = p_nor_flash_info->cnt;

    /* Receive data from memory array. */
    /* The lower layer software should use the data_cnt as receiving counter. */
    ret = r_nor_flash_drvif_rx(p_nor_flash_info->data_cnt, p_nor_flash_info->p_data);
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    p_nor_flash_info->cnt    -= p_nor_flash_info->data_cnt;     /* Updates the cnt. */
    p_nor_flash_info->p_data += p_nor_flash_info->data_cnt;
    p_nor_flash_info->addr   += p_nor_flash_info->data_cnt;

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_read
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_scurreg_page
 * Description  : Reads data from the specified address (addr) for the specified number (cnt) of bytes
 *              : and stores to the specified buffer (pData).
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Temporary Number of bytes to be read
 *              :    uint8_t          * pData               ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_scurreg_page(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret       = NOR_FLASH_SUCCESS;
    uint8_t              addr_size = 0;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Issue the Read The Security Register command. */
    addr_size = NOR_FLASH_AT_ADDR_SIZE;

    ret = R_NOR_FLASH_AT_CMD_RDSCUR(p_nor_flash_info->addr, addr_size);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Set data size to receive. */
    p_nor_flash_info->data_cnt = p_nor_flash_info->cnt;

    /* Receive data from memory array. */
    /* The lower layer software should use the data_cnt as receiving counter. */
    ret = r_nor_flash_drvif_rx(p_nor_flash_info->data_cnt, p_nor_flash_info->p_data);
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    p_nor_flash_info->cnt    -= p_nor_flash_info->data_cnt;     /* Updates the cnt. */
    p_nor_flash_info->p_data += p_nor_flash_info->data_cnt;
    p_nor_flash_info->addr   += p_nor_flash_info->data_cnt;

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_read_scurreg_page
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_page
 * Description  : Writes data from the specified buffer (pData)
 *              : to the specified address (addr) for the specified number (data_cnt) of bytes.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Write start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be written
 *              :    uint16_t           data_cnt            ;   Number of bytes to be written in a page
 *              :    uint8_t          * p_data              ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                     ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : A write exceeding the write page isn't allowed.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_page(st_nor_flash_info_t * p_nor_flash_info)
{
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1   = 0;     /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */
    e_nor_flash_status_t ret       = NOR_FLASH_SUCCESS;
    uint8_t              addr_size = 0;
    uint8_t            * p_cmdbuf  = (uint8_t *)&s_nor_flash_at_cmdbuf[0];  /* Get uint8_t pointer */

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1((uint8_t *)&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))      /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Issue the WRITE command using the single mode. */
    addr_size = NOR_FLASH_AT_ADDR_SIZE;

    ret = R_NOR_FLASH_AT_CMD_PP(p_nor_flash_info->addr, addr_size);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    /* CMD Dummy. */
    r_nor_flash_at_cmd_set(0, p_nor_flash_info->addr, NOR_FLASH_AT_CMD_SIZE+addr_size);
    ret = r_nor_flash_drvif_tx(addr_size, ++p_cmdbuf);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    /* Transmit data to memory. */
    ret = r_nor_flash_drvif_tx(p_nor_flash_info->data_cnt, p_nor_flash_info->p_data);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_page
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_scurreg_page
 * Description  : Writes data to security register page from the specified buffer (pData)
 *              : to the specified address (addr) for the specified number (data_cnt) of bytes.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Write start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be written
 *              :    uint16_t           data_cnt            ;   Number of bytes to be written in a page
 *              :    uint8_t          * p_data              ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                     ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : A write exceeding the write page isn't allowed.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_scurreg_page(st_nor_flash_info_t * p_nor_flash_info)
{
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1   = 0;     /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */
    e_nor_flash_status_t ret       = NOR_FLASH_SUCCESS;
    uint8_t              addr_size = 0;
    uint8_t            * p_cmdbuf  = (uint8_t *)&s_nor_flash_at_cmdbuf[0];  /* Get uint8_t pointer */

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1((uint8_t *)&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))      /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Issue the Write The Security Register command. */
    addr_size = NOR_FLASH_AT_ADDR_SIZE;

    ret = R_NOR_FLASH_AT_CMD_PSCUR(p_nor_flash_info->addr, addr_size);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    /* CMD Dummy. */
    r_nor_flash_at_cmd_set(0, p_nor_flash_info->addr, NOR_FLASH_AT_CMD_SIZE+addr_size);
    ret = r_nor_flash_drvif_tx(addr_size, ++p_cmdbuf);

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    /* Transmit data to memory. */
    ret = r_nor_flash_drvif_tx(p_nor_flash_info->data_cnt, p_nor_flash_info->p_data);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_write_scurreg_page
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_erase
 * Description  : FLASH_MODE_B4K_ERASE (4KB)        ;   Erases the data of specified block (Addr).
 *              : FLASH_MODE_B32K_ERASE (32KB)      ;   Erases the data of specified block (Addr).
 *              : FLASH_MODE_B64K_ERASE (64KB)      ;   Erases the data of specified block (Addr).
 *              : FLASH_MODE_C_ERASE                ;   Erases the all data of specified chip (Addr).
 * Arguments    : st_nor_flash_erase_info_t * p_nor_flash_erase_info    ; Flash memory erase information
 *              :    uint32_t        addr           ;   First address of specified sector
 *              :    uint8_t         mode           ;   Type of erase command
 *              :                                   ;   NOR_FLASH_MODE_B4K_ERASE   ; Block Erase (4KB)
 *              :                                   ;   NOR_FLASH_MODE_B32K_ERASE  ; Block Erase (32KB)
 *              :                                   ;   NOR_FLASH_MODE_B64K_ERASE  ; Block Erase (64KB)
 *              :                                   ;   NOR_FLASH_MODE_C_ERASE     ; Chip Erase
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM               ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : Flash memory can be erased to only when write-protection has been canceled.
 *              : (1) Block Erase
 *              :   Data of the specified block in the protected block (64KB) can't be erased and
 *              :   error result is returned.
 *              : (2) Chip Erase
 *              :   Data of the protected chip in the proteted block (64KB) can't be erased and
 *              :   error result is returned.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_erase(st_nor_flash_erase_info_t * p_nor_flash_erase_info)
{
    e_nor_flash_status_t ret       = NOR_FLASH_SUCCESS;
    uint32_t             mem_size  = 0;
    uint8_t              addr_size = 0;
#if (NOR_FLASH_CFG_WEL_CHK == 1)
    uint8_t              stsreg1   = 0;     /* Status buffer */
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    mem_size  = NOR_FLASH_AT_MEM_SIZE;
    addr_size = NOR_FLASH_AT_ADDR_SIZE;

    if (mem_size <= p_nor_flash_erase_info->addr)
    {
        return NOR_FLASH_ERR_PARAM;
    }

#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if ((NOR_FLASH_MODE_B4K_ERASE  != p_nor_flash_erase_info->mode) &&
        (NOR_FLASH_MODE_B32K_ERASE != p_nor_flash_erase_info->mode) &&
        (NOR_FLASH_MODE_B64K_ERASE != p_nor_flash_erase_info->mode) &&
        (NOR_FLASH_MODE_SCUR_ERASE != p_nor_flash_erase_info->mode) &&
        (NOR_FLASH_MODE_C_ERASE    != p_nor_flash_erase_info->mode))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable command operation using the single mode. */
    ret = r_nor_flash_at_write_enable();
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#if (NOR_FLASH_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1((uint8_t *)&stsreg1);
    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
    if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WEL))      /* WEL bit =0 : In Write Disable State  */
    {
        return NOR_FLASH_ERR_WEL_CHK;
    }
#endif  /* #if (NOR_FLASH_CFG_WEL_CHK == 1) */

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* Issue the Erase command using the single mode. */
    /* The upper layer software should check and set the mode correctly to "p_nor_flash_erase_info->mode". */ 
    if (NOR_FLASH_MODE_B4K_ERASE == p_nor_flash_erase_info->mode)
    {
        p_nor_flash_erase_info->addr &= NOR_FLASH_AT_B4K_ADDR;
        ret = R_NOR_FLASH_AT_CMD_BE4K(p_nor_flash_erase_info->addr, addr_size);
    }
    else if (NOR_FLASH_MODE_B32K_ERASE == p_nor_flash_erase_info->mode)
    {
        p_nor_flash_erase_info->addr &= NOR_FLASH_AT_B32K_ADDR;
        ret = R_NOR_FLASH_AT_CMD_BE32K(p_nor_flash_erase_info->addr, addr_size);
    }
    else if (NOR_FLASH_MODE_B64K_ERASE == p_nor_flash_erase_info->mode)
    {
        p_nor_flash_erase_info->addr &= NOR_FLASH_AT_B64K_ADDR;
        ret = R_NOR_FLASH_AT_CMD_BE64K(p_nor_flash_erase_info->addr, addr_size);
    }
    else if (NOR_FLASH_MODE_SCUR_ERASE == p_nor_flash_erase_info->mode)
    {
        p_nor_flash_erase_info->addr &= NOR_FLASH_AT_SCUR_ADDR;
        ret = R_NOR_FLASH_AT_CMD_ESCUR(p_nor_flash_erase_info->addr, addr_size);
    }
    else
    {
        p_nor_flash_erase_info->addr &= 0x00000000;
        ret = R_NOR_FLASH_AT_CMD_CE(p_nor_flash_erase_info->addr);
    }

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H"*/

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_erase
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_rdid
 * Description  : Reads Manufacture ID, Device ID.
 *              : ID data of 3 bytes are stored in the following order.
 *              :        (1) Manufacturer ID - 1 byte
 *              :        (2) Device ID - 2 bytes
 * Arguments    : uint8_t          * p_data             ;   ID data storage buffer pointer (3 bytes)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_rdid(uint8_t * p_data)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    r_nor_flash_set_cs(NOR_FLASH_LOW);          /* SS# "L" */
    r_nor_flash_wait_lp();

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Configuration Register command using the single mode. */
    ret = R_NOR_FLASH_AT_CMD_RDID();
    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_wait_lp();
        r_nor_flash_set_cs(NOR_FLASH_HI);       /* SS# "H" */
        return ret;
    }

    r_nor_flash_wait_lp();

    /* Receive the Manufacture Identification, Identification and Memory capacity using the single mode. */
    ret = r_nor_flash_drvif_rx(NOR_FLASH_AT_IDDATA_SIZE, p_data);

    r_nor_flash_wait_lp();
    r_nor_flash_set_cs(NOR_FLASH_HI);           /* SS# "H" */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_rdid
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_check_busy
 * Description  : Checks busy for the Page Program, Erase and Write Status Register command operation.
 * Arguments    : e_nor_flash_check_busy_t  mode        ;   Mode of error check
 *              :                                       ;   NOR_FLASH_MODE_REG_WRITE_BUSY
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation (FLASH is ready)
 *              : NOR_FLASH_SUCCESS_BUSY                ;   Successful operation (FLASH is busy)
 *              : NOR_FLASH_ERR_PARAM                   ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_check_busy(e_nor_flash_check_busy_t mode)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Checks mode of wait operation. */
    if (NOR_FLASH_MODE_REG_WRITE_BUSY == mode)
    {
        /* Wait until the ready using single mode for the Write Status Register command operation. */
        ret = r_nor_flash_at_check_busy_reg_write();
        if (NOR_FLASH_SUCCESS > ret)
        {
            return ret;
        }
    }
    else
    {
        return NOR_FLASH_ERR_PARAM;
    }

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_check_busy
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_check_busy_reg_write
 * Description  : Waits for the ready after busy.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation (Flash memory is ready)
 *              : NOR_FLASH_SUCCESS_BUSY                ;   Successful operation (Flash memory is busy)
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : If uses "Delay Task", minimum uint is 1ms.
 *              : This is for the Write Status Register (WRSR) command.
 *********************************************************************************************************************/
static e_nor_flash_status_t r_nor_flash_at_check_busy_reg_write(void)
{
    e_nor_flash_status_t ret     = NOR_FLASH_SUCCESS;
    uint8_t              stsreg1 = 0;               /* Receive temp buffer for Status Register */

    /* Execute the Read Status Register command operation using the single mode. */
    ret = r_nor_flash_at_read_stsreg1((uint8_t *)&stsreg1);
    if (NOR_FLASH_SUCCESS == ret)
    {
        /* Ready/Busy check */
        if (0x00 == (stsreg1 & NOR_FLASH_AT_REG1_WIP))
        {
            ret = NOR_FLASH_SUCCESS;                /* Ready */
        }
        else
        {
            ret = NOR_FLASH_SUCCESS_BUSY;           /* Busy */
        }
    }
    else
    {
        return ret;
    }

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_check_busy_reg_write
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_cmd_set
 * Description  : Command and address setting.
 *              : Converts little endian data or big endian data.
 * Arguments    : uint8_t            cmd                ;   Command data
 *              : uint32_t           addr               ;   Address data
 *              : uint8_t            cmdsize            ;   Command size
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
static void r_nor_flash_at_cmd_set(uint8_t cmd, uint32_t addr, uint8_t cmdsize)
{
    u_nor_flash_at_exchg_long_t tmp;
    uint8_t                   * p_cmdbuf = (uint8_t *)&s_nor_flash_at_cmdbuf[0];    /* Get uint8_t pointer */

    tmp.ul = addr;

    if (NOR_FLASH_AT_CMD_SIZE == cmdsize)
    {
        *p_cmdbuf = cmd;
    }
    else if (4 == cmdsize)
    {
        *(p_cmdbuf++) = cmd;
        *(p_cmdbuf++) = tmp.uc[2];
        *(p_cmdbuf++) = tmp.uc[1];
        *p_cmdbuf     = tmp.uc[0];
    }
    else /* (5 == cmdsize) */
    {
        *(p_cmdbuf++) = cmd;
        *(p_cmdbuf++) = tmp.uc[2];
        *(p_cmdbuf++) = tmp.uc[1];
        *(p_cmdbuf++) = tmp.uc[0];
        *p_cmdbuf     = NOR_FLASH_DUMMY_DATA;
    }
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_cmd_set
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_get_memory_info
 * Description  : Gets the memory size and page size.
 * Arguments    : st_nor_flash_mem_info_t * p_nor_flash_mem_info    ;   Flash memory size information
 *              :    uint32_t               mem_size                ;   Max memory size
 *              :    uint32_t               wpag_size               ;   Write page size
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_at_get_memory_info(st_nor_flash_mem_info_t * p_nor_flash_mem_info)
{
    /* Get memory information. */
    p_nor_flash_mem_info->mem_size  = NOR_FLASH_AT_MEM_SIZE;
    p_nor_flash_mem_info->wpag_size = NOR_FLASH_AT_PAGE_SIZE;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_get_memory_info
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_check_cnt
 * Description  : Checks counter.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Not used
 *              :    uint8_t          * p_data              ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_check_cnt(st_nor_flash_info_t * p_nor_flash_info)
{
    if ((0 == p_nor_flash_info->cnt) || ((NOR_FLASH_AT_MEM_SIZE - p_nor_flash_info->cnt) < p_nor_flash_info->addr))
    {
        return NOR_FLASH_ERR_PARAM;
    }
    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_check_cnt
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_check_scurreg_cnt
 * Description  : Checks counter of internal buffer within a security register page.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Not used
 *              :    uint8_t          * p_data              ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_check_scurreg_cnt(st_nor_flash_info_t * p_nor_flash_info)
{
    if ((0 == p_nor_flash_info->cnt) || (NOR_FLASH_AT_PAGE_SIZE < p_nor_flash_info->cnt))
    {
        return NOR_FLASH_ERR_PARAM;
    }
    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_check_scurreg_cnt
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_page_calc
 * Description  : Calculates the writable bytes from the start address to the page boundary.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Not used
 *              :    uint8_t          * p_data              ;   Read data storage buffer pointer
 * Return Value : Writable size (bytes)
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
uint16_t r_nor_flash_at_page_calc(st_nor_flash_info_t * p_nor_flash_info)
{
    uint16_t tmpcnt = 0;

    tmpcnt = (uint16_t)((((p_nor_flash_info->addr + NOR_FLASH_AT_PAGE_SIZE) / NOR_FLASH_AT_PAGE_SIZE)
            * NOR_FLASH_AT_PAGE_SIZE) - p_nor_flash_info->addr);
    return tmpcnt;
}
/**********************************************************************************************************************
 End of function r_nor_flash_at_page_calc
 *********************************************************************************************************************/


#endif  /* IS_SUPPORTING_AT */

/* End of File */
