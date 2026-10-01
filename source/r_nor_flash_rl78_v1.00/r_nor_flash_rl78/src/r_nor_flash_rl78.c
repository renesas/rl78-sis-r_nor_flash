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
 * File Name    : r_nor_flash.c
 * Version      : 1.00
 * Device       : -
 * Abstract     : User I/F file
 * Tool-Chain   : -
 * OS           : not use
 * H/W Platform : -
 * Description  : NOR FLASH User I/F file
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
#include "r_nor_flash_private.h"                /* FLASH driver Private module definitions      */

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
 Private (static) variables and functions
 *********************************************************************************************************************/
static volatile uint8_t s_nor_flash_open = NOR_FLASH_SIS_CLOSE;


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_Open
 *****************************************************************************************************************/ /**
 * @brief This function is run first when using the APIs of the serial flash memory control software.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_ALREADY_OPEN    NOR FLASH SIS module already opened
 * @details   Initialize the slave device selection pin. After initialization, the pin is in a high-output state.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Open(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_CLOSE != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_ALREADY_OPEN;
    }

    ret = r_nor_flash_init_port();

    s_nor_flash_open = NOR_FLASH_SIS_OPEN;

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_Open
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_Close
 *****************************************************************************************************************/ /**
 * @brief This function is used to close the serial flash memory control software when it is in use.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @details   Reset the slave device selection pin. After initialization, the pin is in a input state.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Close(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    ret = r_nor_flash_reset_port();

    s_nor_flash_open = NOR_FLASH_SIS_CLOSE;

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_Close
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadStatus
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register.
 * @param[out] p_status
 *             Status register storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @details   Reads the status register and stores the contents in p_status. See section R_NOR_FLASH_ReadStatus()
 *            in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_status)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_status(p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadStatus
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadStatus2
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register 2. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[out] p_status
 *             Status register 2 storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Reads the status register and stores the contents in p_status. See section R_NOR_FLASH_ReadStatus2()
 *            in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus2(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_status)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_status2(p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadStatus2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadStatus3
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register 3. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[out] p_status
 *             Status register 3 storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Reads the status register and stores the contents in p_status. See section R_NOR_FLASH_ReadStatus3()
 *            in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus3(uint8_t * p_status)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_status)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_status3(p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadStatus3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteStatus
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 1. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] p_reg
 *             Status register 1 setting data buffer
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   The values set in p_reg is written to the status register 1.
 *            See section R_NOR_FLASH_WriteStatus() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_reg)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_status(p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteStatus
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteStatus2
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 2. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] p_reg
 *             Status register 2 setting data buffer
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   The values set in p_reg is written to the status register 2.
 *            See section R_NOR_FLASH_WriteStatus2() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus2(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_reg)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_status2(p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteStatus2
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteStatus3
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 3. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] p_reg
 *             Status register 3 setting data buffer
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   The values set in p_reg is written to the status register 3.
 *            See section R_NOR_FLASH_WriteStatus3() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus3(uint8_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_reg)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_status3(p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteStatus3
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_SetWriteProtect
 *****************************************************************************************************************/ /**
 * @brief This function is used to make write protect settings.
 * @param[in] wpsts
 *             Write protect setting data
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 * @details   Make write protect settings. SRWD is cleared to 0. See section R_NOR_FLASH_SetWriteProtect() in the
 *            application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_SetWriteProtect(uint8_t wpsts)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    ret = r_nor_flash_set_write_protect(wpsts);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_SetWriteProtect
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteDisable
 *****************************************************************************************************************/ /**
 * @brief This function is used to disable write operation.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @details   Transmits the Write Disable command and clears the WEL bit in the status register.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDisable(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    ret = r_nor_flash_write_disable();

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteDisable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadData
 *****************************************************************************************************************/ /**
 * @brief This function is used to read data from the serial flash memory.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_ReadData() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @details   Reads the specified number of bytes of data from the specified address in the serial flash memory and
 *            stores the data in p_data.\n
 *            The maximum read address is the serial flash memory capacity - 1.\n
 *            Rollover read operations are not supported. After the end address is read, processing ends.
 *            It is then necessary to reset the address and call this API function again.\n
 *            NOR_FLASH_ERR_PARAM is returned if the total value of the read byte count, cnt, and specified address,
 *            addr, exceeds the maximum read address.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadData(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if ((0 == p_nor_flash_info) || (0 == p_nor_flash_info->p_data))
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_data(p_nor_flash_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadData
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteDataPage
 *****************************************************************************************************************/ /**
 * @brief This function is used to write data to the serial flash memory in single-page units.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_WriteDataPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 * @details   Writes the specified number of bytes of data (up to a maximum size of 1 page) in p_data to the serial
 *            flash memory, starting from the specified address.\n
 *            When writing a large volume of data, communication is divided into page units. This prevents a situation
 *            in which other processing is not possible while communication is in progress. \n
 *            Writing to the serial flash memory is only possible when write protect has been canceled.\n
 *            It is not possible to write to a protected page. Attempting to do so returns the error NOR_FLASH_ERR_WP.\n
 *            The maximum write address is the serial flash memory capacity - 1.\n
 *            The maximum write byte count (cnt) setting value is the capacity of the serial flash memory.\n
 *            NOR_FLASH_ERR_PARAM is returned if the total value of the write byte count, cnt, and specified address,
 *            addr, exceeds the maximum write address.\n
 *            When a byte count exceeding 1 page is specified, the remaining byte count and next address information
 *            remain in the serial flash memory information structure (p_flash_info) after processing of a single page
 *            write finishes. It is possible to write the remaining bytes by specifying p_flash_info unmodified in
 *            this API function again.\n
 *            After this user API function finishes successfully, the serial flash memory transitions to the write
 *            cycle. Do not fail to confirm that the write has finished with R_NOR_FLASH_CheckBusy(). If an attempt
 *            is made to perform the next read or write processing while a write cycle is in progress, the serial
 *            flash memory will not accept that processing. \n
 *            R_NOR_FLASH_CheckBusy() can be called at any time specified by the user. This makes it possible for the
 *            user application to perform other processing while a write cycle is in progress.\n
 *            See section R_NOR_FLASH_WriteDataPage() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDataPage(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if ((0 == p_nor_flash_info) || (0 == p_nor_flash_info->p_data))
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_data_page(p_nor_flash_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteDataPage
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_Erase
 *****************************************************************************************************************/ /**
 * @brief Based on the mode setting, this function erases all the data in the specified sector (sector erase),
          all the data in the specified block (block erase: 32 KB block or 64 KB block), or all the data on
          the specified chip (chip erase).
 * @param[in] p_nor_flash_erase_info
 *             Serial flash memory erase information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_Erase() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 * @details   For sector erase, specify the start address of the sector in addr.\n
 *            For block erase, specify the start address of the block in addr.\n
 *            For security erase, specify the start address of the security register pages in addr.\n
 *            For chip erase, set addr to 0x00000000.\n
 *            When this user API function completes successfully, the serial flash memory transitions to an erase
 *            cycle. Do not fail to confirm erase completion with R_NOR_FLASH_CheckBusy(). If the next read or write
 *            processing starts when a previous erase cycle is in progress, the serial flash memory will not accept
 *            the new processing. \n
 *            R_NOR_FLASH_CheckBusy() can be called at any time specified by the user. This allows a user application
 *            to perform other processing while an erase cycle is in progress. \n
 *            See section R_NOR_FLASH_Erase() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Erase(st_nor_flash_erase_info_t * p_nor_flash_erase_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_nor_flash_erase_info)
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_erase_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_erase(p_nor_flash_erase_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_Erase
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_CheckBusy
 *****************************************************************************************************************/ /**
 * @brief This function is used to perform polling to determine if a write or erase operation has finished.
 * @param[in] mode
 *             Completion wait processing setting. See section R_NOR_FLASH_CheckBusy() in the application note for
 *             details.
 * @retval    NOR_FLASH_SUCCESS             Normal end, and write finished
 * @retval    NOR_FLASH_SUCCESS_BUSY        Normal end, and write in progress
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @details   Determines whether or not a write or erase operation has finished.
 * @note      R_NOR_FLASH_CheckBusy() can be called at any time specified by the user. This makes it possible for the
 *            user application to perform other processing while a write cycle is in progress.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_CheckBusy(e_nor_flash_check_busy_t mode)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    ret = r_nor_flash_check_busy(mode);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_CheckBusy
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadId
 *****************************************************************************************************************/ /**
 * @brief This function is used to read ID information.
 * @param[in,out] p_data
 *             ID information storage buffer. The size differs depending on the serial flash memory product used.
 *             See section R_NOR_FLASH_ReadId() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @details   Stores ID information for the serial flash memory in p_data.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadId(uint8_t * p_data)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_data)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_id(p_data);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadId
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_GetMemoryInfo
 *****************************************************************************************************************/ /**
 * @brief This function is used to fetch the serial flash memory size information.
 * @param[out] p_nor_flash_mem_info
 *             Serial flash memory size information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_GetMemoryInfo() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @details   Fetches serial flash memory size information.
 * @note      None.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_GetMemoryInfo(st_nor_flash_mem_info_t * p_nor_flash_mem_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_nor_flash_mem_info)
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_mem_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_get_memory_info(p_nor_flash_mem_info);
    
    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_GetMemoryInfo
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadConfiguration
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in,out] p_config
 *             Configuration register storage buffer. The size differs depending on the serial NOR flash memory
 *             product used. See section R_NOR_FLASH_ReadConfiguration() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Reads the configuration register(s) of the serial NOR Flash memory and stores the contents in p_config.
 *            See section R_NOR_FLASH_ReadConfiguration() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadConfiguration(uint8_t * p_config)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_config)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_configuration(p_config);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadConfiguration
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteConfiguration
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] p_reg
 *             Register information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_WriteConfiguration() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   The values set in p_reg->config1 and p_reg->config2 are written to the configuration register.
 *            See section R_NOR_FLASH_WriteConfiguration() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteConfiguration(st_nor_flash_reg_info_t * p_reg)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_reg)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_configuration(p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteConfiguration
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_Set4byteAddressMode
 *****************************************************************************************************************/ /**
 * @brief This function is used to set the address mode to 4-byte address mode. It is a dedicated API function for
 *        MX25L, MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   See section R_NOR_FLASH_Set4byteAddressMode() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Set4byteAddressMode(void)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    ret = r_nor_flash_set_4byte_address_mode();

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_Set4byteAddressMode
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadSecurity
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the security register. It is a dedicated API function for MX25L, MX66L, or
 *        MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[out] p_scur
 *             Security register  storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Reads the security register and stores the contents in p_scur.
 *            See section R_NOR_FLASH_ReadSecurity() in the application note for details.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadSecurity(uint8_t * p_scur)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if (0 == p_scur)
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_security(p_scur);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadSecurity
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_ReadDataSecurityPage
 *****************************************************************************************************************/ /**
 * @brief This function is used to read data from the security register. It is a dedicated API function for AT25QF
 *        family serial NOR flash memory of Renesas Electronics.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_ReadDataSecurityPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Reads the specified number of bytes of data from the specified address in the security register and
 *            stores the data in p_data.\n
 *            The maximum read address is the page size - 1.\n
 *            Rollover read operations are not supported. After the end address is read, processing ends.
 *            It is then necessary to reset the address and call this API function again.\n
 *            NOR_FLASH_ERR_PARAM is returned if the total value of the read byte count, cnt, and specified address,
 *            addr, exceeds the maximum read address.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadDataSecurityPage(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if ((0 == p_nor_flash_info) || (0 == p_nor_flash_info->p_data))
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_read_data_security_page(p_nor_flash_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_ReadDataSecurityPage
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_WriteDataSecurityPage
 *****************************************************************************************************************/ /**
 * @brief This function is used to write data to the security register page in single-page units. It is a dedicated
 *        API function for AT25QF family serial NOR flash memory of Renesas Electronics.
 * @param[in] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_WriteDataSecurityPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 * @details   Writes the specified number of bytes of data (up to a maximum size of 1 page) in p_data to the security
 *            register pages, starting from the specified address.\n
 *            When writing a large volume of data, communication is divided into page units. This prevents a situation
 *            in which other processing is not possible while communication is in progress. \n
 *            Writing to the security register pages is only possible when they are not locked.\n
 *            It is not possible to write to a locked page. Attempting to do so returns the error NOR_FLASH_ERR_WP.\n
 *            The maximum write byte count (cnt) setting value is the capacity of the security register page size.\n
 *            NOR_FLASH_ERR_PARAM is returned if the total value of the write byte count, cnt, and specified address,
 *            addr, exceeds the maximum write address.
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDataSecurityPage(st_nor_flash_info_t * p_nor_flash_info)
{
    e_nor_flash_status_t ret = NOR_FLASH_SUCCESS;

    if (NOR_FLASH_SIS_OPEN != s_nor_flash_open)
    {
        return NOR_FLASH_ERR_NOT_OPEN;
    }

    /* Check parameters. */
#if (NOR_FLASH_CFG_PARAM_CHECKING_ENABLE)
    if ((0 == p_nor_flash_info) || (0 == p_nor_flash_info->p_data))
    {
        return NOR_FLASH_ERR_PARAM;
    }

    /* Check 2-byte boundaries. */
    if (0 != ((uint16_t)p_nor_flash_info & NOR_FLASH_ADDR_BOUNDARY))
    {
        return NOR_FLASH_ERR_PARAM;
    }
#endif /* NOR_FLASH_CFG_PARAM_CHECKING_ENABLE */

    ret = r_nor_flash_write_data_security_page(p_nor_flash_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_WriteDataSecurityPage
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_GetVersion
 *****************************************************************************************************************/ /**
 * @brief This function is used to fetch the serial flash memory version information.
 * @param     None
 * @retval    Version number.   Upper 2 bytes: major version, lower 2 bytes: minor version.
 * @details   Returns the version information.
 * @note      None
 *********************************************************************************************************************/
uint32_t R_NOR_FLASH_GetVersion(void)
{
    /* Upper 2 bytes are major version, lower 2 bytes are minor version */
    uint32_t version = ((uint32_t)NOR_FLASH_VERSION_MAJOR << 16) | NOR_FLASH_VERSION_MINOR;

    return version;
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_GetVersion
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_Interval
 *****************************************************************************************************************/ /**
 * @brief This function calls the interval timer counter function of the SPI(CSI) software. When using the DTC, use a 
 *        timer to call this function at 1 ms intervals.
 * @param     None
 * @retval    None
 * @details   Increments the internal timer counter of the SPI (CSI) communication software while waiting for the 
 *            DTC transfer to finish.
 * @note      User a timer or the like to call this function at 1 ms intervals.
 *********************************************************************************************************************/
void R_NOR_FLASH_Interval(void)
{
    r_nor_flash_drvif_1ms_interval();
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_Interval
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_NOR_FLASH_SendendNotification
 *****************************************************************************************************************/ /**
 * @brief This function calls the SPI (CSI) software's transmit complete function.Call this function from the code 
 *        generation transmission completion function.
 * @param     None
 * @retval    None
 * @details   Processes the completion of SPI (CSI) communication transmission.
 * @note      Call this function from the transmission completion callback function of SPI(CSI) communication.
 *********************************************************************************************************************/
void R_NOR_FLASH_SendendNotification(void)
{
    r_nor_flash_drvif_csi_callback();
}
/**********************************************************************************************************************
 End of function R_NOR_FLASH_SendendNotification
 *********************************************************************************************************************/

/* End of File */
