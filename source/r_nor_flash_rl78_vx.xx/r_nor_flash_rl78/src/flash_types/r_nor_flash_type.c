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
 * File Name    : r_nor_flash_type.c
 * Version      : 1.00
 * Device       : -
 * Abstract     : memory type I/F file
 * Tool-Chain   : -
 * OS           : not use
 * H/W Platform : -
 * Description  : Flash memory type I/F file
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
#include "../r_nor_flash_private.h"             /* FLASH driver Private module definitions      */


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_init_port
 * Description  : Sets FLASH control ports.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_init_port(void)
{
#if IS_SUPPORTING_AT()
    r_nor_flash_at_init_port();            /* SS# initialization */
#elif IS_SUPPORTING_MX()
    r_nor_flash_mx_init_port();            /* SS# initialization */
#endif

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_init_port
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_reset_port
 * Description  : Resets setting of ports.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_reset_port(void)
{
#if IS_SUPPORTING_AT()
    r_nor_flash_at_reset_port();            /* SS# reset */
#elif IS_SUPPORTING_MX()
    r_nor_flash_mx_reset_port();            /* SS# reset */
#endif

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_reset_port
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status
 * Description  : Reads status from the status register and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Read Status Register. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_read_stsreg1(p_status);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_read_stsreg(p_status);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_status
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status2
 * Description  : Reads status from the status register 2 and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API       ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status2(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Read Status Register. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_read_stsreg2(p_status);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_status2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status3
 * Description  : Reads status from the status register 3 and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API       ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status3(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Read Status Register. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_read_stsreg3(p_status);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_status3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_set_write_protect
 * Description  : Sets the write-protection setting to write-protection setting data (wpsts).
 * Arguments    : uint8_t            wpsts              ;   Write-protection setting data
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                   ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                 ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : A SRWD bit is fixed to 0.
 *              : Please confirm the status register.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_set_write_protect(uint8_t wpsts)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Execute the Write Status Register (WRSR) command operation using the single mode. */
    /* Execute the Read Status Register (RDSR) command operation using the single mode 
       in r_nor_flash_set_write_protect(). */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_set_write_protect(wpsts);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_set_write_protect(wpsts);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_set_write_protect
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_disable
 * Description  : Clears the WEL bit.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_disable(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Execute the Write Disable command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_disable();
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_write_disable();
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_disable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_data
 * Description  : Reads data from the specified address (addr) for the specified number (cnt) of bytes
 *              : and stores to the specified buffer (p_data).
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Not used
 *              :    uint8_t          * p_data              ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : The maximum read address is Flash memory size - 1.
 **********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_data(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_check_cnt(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_check_cnt(p_nor_flash_info);
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Execute the READ command operation. */
    /* The SPI mode and bit rate should be set at the start of the following operation */
    /* and return to default at the end of the following operation. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_read(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_read(p_nor_flash_info);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_data
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_data_page
 * Description  : Writes data from the specified buffer (p_data)
 *              : to the specified address (addr) for the specified number (cnt) of bytes.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Write start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be written
 *              :    uint16_t           data_cnt            ;   Number of bytes to be written in a page
 *              :    uint8_t          * p_data              ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                     ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : FLASH can be written to only when write-protection has been canceled.
 *              : The maximum write address is Flash memory size - 1.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_data_page(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret    = NOR_FLASH_SUCCESS;
    uint16_t             tmpcnt = 0;

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_check_cnt(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_check_cnt(p_nor_flash_info);
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }

#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Writing page calculation */
#if IS_SUPPORTING_AT()
    tmpcnt = r_nor_flash_at_page_calc(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    tmpcnt = r_nor_flash_mx_page_calc(p_nor_flash_info);
#endif

    if (tmpcnt > p_nor_flash_info->cnt)
    {
        p_nor_flash_info->data_cnt = p_nor_flash_info->cnt;
    }
    else
    {
        p_nor_flash_info->data_cnt = tmpcnt;
    }
        
    /* Execute the WRITE command operation using the single mode. */
    /* The SPI mode and bit rate should be set at the start of the following operation */
    /* and return to default at the end of the following operation. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_page(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_write_page(p_nor_flash_info);
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_drvif_close();
        return ret;
    }

    /* Update the writing information. */
    p_nor_flash_info->cnt    -= p_nor_flash_info->data_cnt;
    p_nor_flash_info->p_data += p_nor_flash_info->data_cnt;
    p_nor_flash_info->addr   += p_nor_flash_info->data_cnt;

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_data_page
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_erase
 * Description  : Erases the data.
 * Arguments    : st_nor_flash_erase_info_t * p_nor_flash_erase_info ; Flash memory erase information
 *              :    uint32_t                 addr          ;   First address of specified sector
 *              :    uint8_t                  mode          ;   Type of erase command
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                     ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : Flash memory can be erased to only when write-protection has been canceled.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_erase(st_nor_flash_erase_info_t * p_nor_flash_erase_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Execute the Erase command operation. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_erase(p_nor_flash_erase_info);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_erase(p_nor_flash_erase_info);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_erase
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_check_busy
 * Description  : Checks busy.
 * Arguments    : e_nor_flash_check_busy_t  mode        ;   Mode of error check
 *              :                                       ;   NOR_FLASH_MODE_REG_WRITE_BUSY
 *              :                                       ;   NOR_FLASH_MODE_PROG_BUSY
 *              :                                       ;   NOR_FLASH_MODE_ERASE_BUSY
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation (FLASH is ready)
 *              : NOR_FLASH_SUCCESS_BUSY                ;   Successful operation (FLASH is busy)
 *              : NOR_FLASH_ERR_PARAM                   ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_check_busy(e_nor_flash_check_busy_t mode)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Checks busy. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_check_busy(mode);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_check_busy(mode);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_check_busy
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_id
 * Description  : Reads Manufacture ID and Device ID.
 * Arguments    : uint8_t          * p_data             ;   ID data storage buffer pointer (3 bytes)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation (FLASH is ready)
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_id(uint8_t * p_data)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Read ID command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_rdid(p_data);
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_rdid(p_data);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_id
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_get_memory_info
 * Description  : Gets the memory size and page size.
 * Arguments    : st_nor_flash_mem_info_t * p_nor_flash_mem_info;   Flash memory size information
 *              :    uint32_t               mem_size            ;   Max memory size
 *              :    uint32_t               wpag_size           ;   Write page size
 * Return Value : NOR_FLASH_SUCCESS                             ;   Successful operation
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_get_memory_info(st_nor_flash_mem_info_t * p_nor_flash_mem_info)
{
#if IS_SUPPORTING_AT()
    r_nor_flash_at_get_memory_info(p_nor_flash_mem_info);
#elif IS_SUPPORTING_MX()
    r_nor_flash_mx_get_memory_info(p_nor_flash_mem_info);
#endif

    return NOR_FLASH_SUCCESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_get_memory_info
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_configuration
 * Description  : Reads status from the configuration register and stores to the configuration storage buffer.
 * Arguments    : uint8_t       * p_config          ;   Read configuration storage buffer (1 byte or 2 bytes)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_configuration(uint8_t * p_config)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Read Configurtion Register (RDCR) command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_read_configreg(p_config);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_configuration
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_configuration
 * Description  : Writes from the write configuration storage buffer to the configuration register.
 * Arguments    : st_nor_flash_reg_info_t * p_reg       ;   Flash memory register information
 *              :     uint8_t               status      ;   Status register setting data
 *              :     uint8_t               config1     ;   Configuration or Configuration-1 register setting data
 *              :     uint8_t               config2     ;   Configuration-2 register setting data
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                 ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API       ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_configuration(st_nor_flash_reg_info_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Write Register (WRR) command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_write_configuration(p_reg);
#endif

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_configuration
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status
 * Description  : Writes from the write status storage buffer to the status register 1.
 * Arguments    : uint8_t         * p_reg           ;   Status register 1 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Write Register (WRR) command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_stsreg1(p_reg);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_status
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status2
 * Description  : Writes from the write status storage buffer to the status register 2.
 * Arguments    : uint8_t         * p_reg           ;   Status register 2 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status2(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Write Register (WRR) command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_stsreg2(p_reg);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_status2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status3
 * Description  : Writes from the write status storage buffer to the status register 3.
 * Arguments    : uint8_t         * p_reg           ;   Status register 1 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status3(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Write Register (WRR) command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_stsreg3(p_reg);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_status3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_set_4byte_address_mode
 * Description  : Issues a ENTER 4-BYTE MODE (EN4B) command.
 *              : Call this function once at system activation after calling R_NOR_FLASH_Open().
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : In the case of MX25L/MX66L/MX25R,
 *              : please confirm that the "4 BYTE" bit in the configuration register is "1" after this processing.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_set_4byte_address_mode(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Issues the Enter 4-byte Address Mode command using the single mode. */
#if IS_SUPPORTING_AT()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_enter_4addr();
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_set_4byte_address_mode
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_security
 * Description  : Reads status from the security register and stores to the security storage buffer (p_scur).
 * Arguments    : uint8_t   * p_scur                ;   Security storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_security(uint8_t * p_scur)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Executes the Read Security Register command operation using the single mode. */
#if IS_SUPPORTING_AT()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#elif IS_SUPPORTING_MX()
    ret = r_nor_flash_mx_read_scurreg(p_scur);
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_security
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_data_security_page
 * Description  : Reads data from the specified address (addr) for the specified number (cnt) of bytes
 *              : and stores to the specified buffer (p_data).
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Read start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be read
 *              :    uint16_t           data_cnt            ;   Not used
 *              :    uint8_t          * p_data              ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API           ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : The maximum read address is Page size - 1.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_data_security_page(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_check_scurreg_cnt(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Execute the READ command operation. */
    /* The SPI mode and bit rate should be set at the start of the following operation */
    /* and return to default at the end of the following operation. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_read_scurreg_page(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_read_data_security_page
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_data_security_page
 * Description  : Writes data to security register pages from the specified buffer (p_data)
 *              : to the specified address (addr) for the specified number (cnt) of bytes.
 * Arguments    : st_nor_flash_info_t * p_nor_flash_info    ;   Flash memory information
 *              :    uint32_t           addr                ;   Write start address
 *              :    uint16_t           cnt                 ;   Number of bytes to be written
 *              :    uint16_t           data_cnt            ;   Number of bytes to be written in a page
 *              :    uint8_t          * p_data              ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_PARAM                       ;   Parameter error
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                     ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API           ;   Non Supported API error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : FLASH can be written to only when write-protection has been canceled.
 *              : The maximum write address is Flash memory size - 1.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_data_security_page(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret    = NOR_FLASH_SUCCESS;
    uint16_t             tmpcnt = 0;

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_check_scurreg_cnt(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        return ret;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    /* Open driver interface. */
    r_nor_flash_drvif_open();

    r_nor_flash_init_port();                /* Port initialization */

    /* Writing page calculation */
#if IS_SUPPORTING_AT()
    tmpcnt = r_nor_flash_at_page_calc(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    if (tmpcnt > p_nor_flash_info->cnt)
    {
        p_nor_flash_info->data_cnt = p_nor_flash_info->cnt;
    }
    else
    {
        p_nor_flash_info->data_cnt = tmpcnt;
    }

    /* Execute the WRITE command operation using the single mode. */
    /* The SPI mode and bit rate should be set at the start of the following operation */
    /* and return to default at the end of the following operation. */
#if IS_SUPPORTING_AT()
    ret = r_nor_flash_at_write_scurreg_page(p_nor_flash_info);
#elif IS_SUPPORTING_MX()
    ret = NOR_FLASH_ERR_NON_SUPPORTED_API;
#endif

    if (NOR_FLASH_SUCCESS > ret)
    {
        r_nor_flash_drvif_close();
        return ret;
    }

    /* Update the writing information. */
    p_nor_flash_info->cnt    -= p_nor_flash_info->data_cnt;
    p_nor_flash_info->p_data += p_nor_flash_info->data_cnt;
    p_nor_flash_info->addr   += p_nor_flash_info->data_cnt;

    /* Close driver interface. */
    r_nor_flash_drvif_close();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_write_data_security_page
 *********************************************************************************************************************/


/* End of File */
