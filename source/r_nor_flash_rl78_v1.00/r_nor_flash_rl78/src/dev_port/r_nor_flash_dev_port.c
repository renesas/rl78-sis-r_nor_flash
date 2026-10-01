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
 * File Name    : r_nor_flash_dev_port.c
 * Version      : 1.00
 * Device       : -
 * Abstract     : Device port file
 * Tool-Chain   : -
 * OS           : not use
 * H/W Platform : -
 * Description  : NOR FLASH driver device port source file
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
#define NOR_FLASH_DELAY_TIME_MICRO      (1000000U)
#define NOR_FLASH_DELAY_OVERHEAD_CYCLES (10U)
#define NOR_FLASH_CYCLES_PER_LOOP       (5U)


/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Private global variables and functions
 *********************************************************************************************************************/
volatile uint16_t g_nor_flash_loop_cnt;

/**********************************************************************************************************************
 * Function Name: r_nor_flash_cs_init
 * Description  : Initialize the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_cs_init(void)
{
    volatile uint32_t fclk_rate;
    volatile uint32_t delay_cycles;

    fclk_rate = R_BSP_GetFclkFreqHz();    /* Get the current ICLK frequency. */
    delay_cycles = (fclk_rate / NOR_FLASH_DELAY_TIME_MICRO);
    if (NOR_FLASH_DELAY_OVERHEAD_CYCLES < delay_cycles)
    {
        delay_cycles -= NOR_FLASH_DELAY_OVERHEAD_CYCLES;
        if (NOR_FLASH_CYCLES_PER_LOOP < delay_cycles)
        {
            g_nor_flash_loop_cnt = (uint16_t)(delay_cycles / NOR_FLASH_CYCLES_PER_LOOP);
        }
        else
        {
            g_nor_flash_loop_cnt = 1U;
        }
    }
    else
    {
        g_nor_flash_loop_cnt = 1U;
    }

    NOR_FLASH_PXX_CS  = NOR_FLASH_HI;       /* Output data is High. */
    NOR_FLASH_PMXX_CS = 0;                  /* Set port to output */
}
/**********************************************************************************************************************
 End of function r_nor_flash_cs_init
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_cs_reset
 * Description  : Reset the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_cs_reset(void)
{
    NOR_FLASH_PMXX_CS = 1;                  /* Set port to input */
}
/**********************************************************************************************************************
 End of function r_nor_flash_cs_reset
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_set_cs
 * Description  : Sets the state of CS pin.
 * Arguments    : uint8_t lv                    ;   CS output level
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_set_cs(uint8_t lv)
{
    NOR_FLASH_PXX_CS = lv;
}
/**********************************************************************************************************************
 End of function r_nor_flash_set_cs
 *********************************************************************************************************************/


/* End of File */
