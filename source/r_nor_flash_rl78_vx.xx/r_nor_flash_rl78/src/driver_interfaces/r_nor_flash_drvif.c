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
 * File Name    : r_nor_flash_drvif.c
 * Version      : 1.00
 * Device       : -
 * Abstract     : IO I/F module
 * Tool-Chain   : -
 * OS           : not use
 * H/W Platform : -
 * Description  : NOR FLASH I/O file
 * Limitation   : none
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
#define NOR_FLASH_CSI_TIMER_CH_FLG          (0)
#define NOR_FLASH_CSI_TIMER_CH_COUNT        (1)
#define NOR_FLASH_CSI_TIMER_CH_MAX_COUNT    (2)
#define NOR_FLASH_CSI_TIMER_MIN_TIME        (100U)      /* 100ms */
#define NOR_FLASH_CSI_SECTOR_SIZE           (256U)      /* 1 sector size */

#define NOR_FLASH_CSI_CLOSE                 (0U)
#define NOR_FLASH_CSI_OPEN                  (1U)

#define NOR_FLASH_DTCD_TRANSFER_BLOCKSIZE   (0x01U)     /* transfer block size */
#define NOR_FLASH_DTCD0_TRANSFER_BYTE       (0x01U)     /* number of transfers */
#define NOR_FLASH_DTCD1_TRANSFER_BYTE       (0x00U)     /* number of transfers */


/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
extern st_dtc_data_t __near R_NOR_FLASH_DTCD_0;
extern st_dtc_data_t __near R_NOR_FLASH_DTCD_1;

static volatile uint8_t     s_nor_flash_sio_dummy;
#endif  /* #if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC) */

static volatile bool        s_nor_flash_transfer_busy = false;
static volatile uint32_t    s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_MAX_COUNT+1];

static void                 r_nor_flash_drvif_csi_start_timer (uint32_t msec);
static e_nor_flash_status_t r_nor_flash_drvif_csi_check_timer (void);
static void                 r_nor_flash_drvif_csi_end_timer (void);
static e_nor_flash_status_t r_nor_flash_drvif_csi_wait (uint16_t size);

#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
static void                 r_nor_flash_drvif_dtc_open (void);
static void                 r_nor_flash_drvif_dtc_close (void);
static void                 r_nor_flash_drvif_dtc_enable (void);
static void                 r_nor_flash_drvif_dtc_disable (void);
static void                 r_nor_flash_drvif_dtc_set_tx (uint16_t txcnt, uint8_t * p_data);
static void                 r_nor_flash_drvif_dtc_set_rx (uint16_t rxcnt, uint8_t * p_data);
#endif  /* #if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC) */

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_open
 * Description  : Initializes I/O driver.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_drvif_open(void)
{
#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    r_nor_flash_drvif_dtc_open();
#endif

    R_NOR_FLASH_CSI_START();
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_open
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_close
 * Description  : Resets I/O driver.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_drvif_close(void)
{
#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    r_nor_flash_drvif_dtc_close();
#endif

    R_NOR_FLASH_CSI_STOP();
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_close
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_tx
 * Description  : Transmits data.
 * Arguments    : uint16_t      txcnt                       ;   Number of bytes to be write
 *              : uint8_t     * p_data                      ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_drvif_tx(uint16_t txcnt, uint8_t * p_data)
{
    e_nor_flash_status_t ret     = NOR_FLASH_SUCCESS;
    MD_STATUS            ret_drv = MD_OK;

    s_nor_flash_transfer_busy = true;
#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    if (1 < txcnt)
    {
        r_nor_flash_drvif_dtc_set_tx(txcnt, p_data);
        r_nor_flash_drvif_dtc_enable();
    }
    ret_drv = R_NOR_FLASH_CSI_SEND(p_data, 1);
#else
    ret_drv = R_NOR_FLASH_CSI_SEND(p_data, txcnt);
#endif
    if (MD_OK != ret_drv)
    {
        return NOR_FLASH_ERR_HARD;
    }

    /* Wait for transmission completion. */
    ret = r_nor_flash_drvif_csi_wait(txcnt);
#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    if (1 < txcnt)
    {
        r_nor_flash_drvif_dtc_disable();
    }
#endif

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_tx
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_rx
 * Description  : Receives data.
 * Arguments    : uint16_t      rxcnt                       ;   Number of bytes to be read
 *              : uint8_t     * p_data                      ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_drvif_rx(uint16_t rxcnt, uint8_t * p_data)
{
    e_nor_flash_status_t ret     = NOR_FLASH_SUCCESS;
    MD_STATUS            ret_drv = MD_OK;

#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    uint16_t cnt;
#endif

#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
    /* WAIT_LOOP */
    while (0 != rxcnt)
    {
        s_nor_flash_transfer_busy = true;

        if (NOR_FLASH_CSI_SECTOR_SIZE <= rxcnt)
        {
            cnt = NOR_FLASH_CSI_SECTOR_SIZE;
        }
        else
        {
            cnt = rxcnt;
        }

        if (1 < cnt)
        {
            r_nor_flash_drvif_dtc_set_rx(cnt, p_data);
            r_nor_flash_drvif_dtc_enable();
        }
        ret_drv = R_NOR_FLASH_CSI_RECEIVE(p_data + (cnt - 1), 1);

        if (MD_OK != ret_drv)
        {
            return NOR_FLASH_ERR_HARD;
        }

        /* Wait for transmission completion. */
        ret = r_nor_flash_drvif_csi_wait(rxcnt);

        if (1 < cnt)
        {
            r_nor_flash_drvif_dtc_disable();
        }

        if (NOR_FLASH_SUCCESS > ret)
        {
            break;
        }

        rxcnt  -= cnt;
        p_data += cnt;
    }
#else /* NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC */
    s_nor_flash_transfer_busy = true;
    ret_drv = R_NOR_FLASH_CSI_RECEIVE(p_data, rxcnt);

    if (MD_OK != ret_drv)
    {
        return NOR_FLASH_ERR_HARD;
    }

    /* Wait for transmission completion. */
    ret = r_nor_flash_drvif_csi_wait(rxcnt);
#endif /* NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC */

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_rx
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_1ms_interval
 * Description  : 1ms Interval Timer call function for driver interface.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_drvif_1ms_interval(void)
{
    if (0 != s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_FLG])
    {
        s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_COUNT]++;
    }
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_1ms_interval
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_callback
 * Description  : Clear the SPI communication in progress flag.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void r_nor_flash_drvif_csi_callback(void)
{
    s_nor_flash_transfer_busy = false;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_csi_callback
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_start_timer
 * Description  : Sets timer for checking timeout and start timer.
 * Arguments    : msec -
 *                    timeout(msec order)
 * Return Value : none
 *********************************************************************************************************************/
static void r_nor_flash_drvif_csi_start_timer(uint32_t msec)
{
    s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_FLG]       = 1;
    s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_COUNT]     = 0;
    s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_MAX_COUNT] = msec;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_csi_start_timer
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_check_timer
 * Description  : Checks timeout to set r_nor_flash_drvif_csi_start_timer function.
 *              : If timeout,return NOR_FLASH_ERR_HARD. 
 *              : In the case of others, return NOR_FLASH_SUCCESS.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS -
 *                    Successful operation
 *                NOR_FLASH_ERR_HARD -
 *                    Hardware error
 *********************************************************************************************************************/
static e_nor_flash_status_t r_nor_flash_drvif_csi_check_timer(void)
{
    e_nor_flash_status_t ret                        = NOR_FLASH_SUCCESS;
    uint32_t             s_nor_flash_csi_timer_cnt1 = s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_COUNT];
    uint32_t             s_nor_flash_csi_timer_cnt2 = s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_MAX_COUNT];

    /* ---- Check compare ---- */
    if (s_nor_flash_csi_timer_cnt1 >= s_nor_flash_csi_timer_cnt2)
    {
        ret = NOR_FLASH_ERR_HARD;
    }
    else
    {
        ret = NOR_FLASH_SUCCESS;
    }

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_csi_check_timer
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_end_timer
 * Description  : Stops timer to set r_nor_flash_drvif_csi_start_timer function.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_csi_end_timer(void)
{
    s_nor_flash_csi_timer_cnt[NOR_FLASH_CSI_TIMER_CH_FLG] = 0;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_csi_end_timer
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_wait
 * Description  : Waits for reception completion.
 * Arguments    : size -
 *                    Size of data
 * Return Value : NOR_FLASH_SUCCESS -
 *                    Successful operation
 *                NOR_FLASH_ERR_HARD -
 *                    Hardware error
 *********************************************************************************************************************/
static e_nor_flash_status_t r_nor_flash_drvif_csi_wait(uint16_t size)
{
    e_nor_flash_status_t ret  = NOR_FLASH_SUCCESS;
    uint16_t             time = NOR_FLASH_CSI_TIMER_MIN_TIME;     // 100ms

    /* ---- Check DTC transfer end.  --- */
    /* Timeout value depends on transfer size. 
       Minimum time is 100ms. When the data count exceeds 10 sectors (1 sector = 256 bytes),
       increase 10ms time for 1 sector increase.*/
    if ((NOR_FLASH_CSI_SECTOR_SIZE * 10) < size)
    {
        time = (time + (((size / NOR_FLASH_CSI_SECTOR_SIZE) - 10) * 10));
    }

    /* Start timer. */
    r_nor_flash_drvif_csi_start_timer(time);

    /* WAIT_LOOP */
    while (1)
    {
        /* Check timeout. */
        if (NOR_FLASH_ERR_HARD == r_nor_flash_drvif_csi_check_timer())
        {
            ret = NOR_FLASH_ERR_HARD;
            break;
        }
        if (false == s_nor_flash_transfer_busy)
        {
            break;
        }
    }

    r_nor_flash_drvif_csi_end_timer();

    return ret;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_csi_wait
 *********************************************************************************************************************/

#if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC)
/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_open
 * Description  : Opens DTC module.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_open(void)
{
    /* Set DTCD0 */
    R_NOR_FLASH_DTCD_0.dtccr = _00_DTC_DATA_SIZE_8BITS | _10_DTC_CHAIN_TRANSFER_ENABLE | 
                            _08_DTC_DEST_ADDR_INCREMENTED | _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    R_NOR_FLASH_DTCD_0.dtbls = NOR_FLASH_DTCD_TRANSFER_BLOCKSIZE;
    R_NOR_FLASH_DTCD_0.dtcct = NOR_FLASH_DTCD0_TRANSFER_BYTE;
    R_NOR_FLASH_DTCD_0.dtrld = 0x00U;
    R_NOR_FLASH_DTCD_0.dtsar = NOR_FLASH_CSI_SIO_ADDRESS;
    R_NOR_FLASH_DTCD_0.dtdar = _0000_DTCD0_DEST_ADDRESS;

    /* Set DTCD1 */
    R_NOR_FLASH_DTCD_1.dtccr = _00_DTC_DATA_SIZE_8BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | 
                            _00_DTC_DEST_ADDR_FIXED | _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_TRANSFER_MODE_NORMAL;
    R_NOR_FLASH_DTCD_1.dtbls = NOR_FLASH_DTCD_TRANSFER_BLOCKSIZE;
    R_NOR_FLASH_DTCD_1.dtcct = NOR_FLASH_DTCD1_TRANSFER_BYTE;
    R_NOR_FLASH_DTCD_1.dtrld = 0x00U;
    R_NOR_FLASH_DTCD_1.dtsar = _0000_DTCD1_SRC_ADDRESS;
    R_NOR_FLASH_DTCD_1.dtdar = NOR_FLASH_CSI_SIO_ADDRESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_open
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_close
 * Description  : Resets DTC module.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_close(void)
{
    ;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_close
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_enable
 * Description  : Enables DTC module.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_enable(void)
{
    R_NOR_FLASH_DTC_START();
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_enable
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_disable
 * Description  : Disables DTC module.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_disable(void)
{
    R_NOR_FLASH_DTC_STOP();
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_disable
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_set_tx
 * Description  : Transmits data.
 * Arguments    : uint16_t      txcnt               ;   Transfer count
 *              : uint8_t     * p_data              ;   Source address
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_set_tx(uint16_t txcnt, uint8_t * p_data)
{
    R_NOR_FLASH_DTCD_0.dtccr = _00_DTC_DATA_SIZE_8BITS | _10_DTC_CHAIN_TRANSFER_ENABLE | 
                            _00_DTC_DEST_ADDR_FIXED | _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    R_NOR_FLASH_DTCD_0.dtcct = (uint8_t)(txcnt - 1);
    R_NOR_FLASH_DTCD_0.dtsar = NOR_FLASH_CSI_SIO_ADDRESS;

    /* CODE CHECKER, this is OK as a comment aligns with the cast */
    R_NOR_FLASH_DTCD_0.dtdar = (uint16_t) &s_nor_flash_sio_dummy;

    R_NOR_FLASH_DTCD_1.dtccr = _00_DTC_DATA_SIZE_8BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | 
                            _00_DTC_DEST_ADDR_FIXED | _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_TRANSFER_MODE_NORMAL;

    /* CODE CHECKER, this is OK as a comment aligns with the cast */
    R_NOR_FLASH_DTCD_1.dtsar = (uint16_t)(p_data + 1);

    R_NOR_FLASH_DTCD_1.dtdar = NOR_FLASH_CSI_SIO_ADDRESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_set_tx
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_dtc_set_rx
 * Description  : Receives data.
 * Arguments    : uint16_t       rxcnt               ;   Transfer count
 *              : uint8_t      * p_data              ;   Source address
 * Return Value : None
 *********************************************************************************************************************/
static void r_nor_flash_drvif_dtc_set_rx(uint16_t rxcnt, uint8_t * p_data)
{
    R_NOR_FLASH_DTCD_0.dtccr = _00_DTC_DATA_SIZE_8BITS | _10_DTC_CHAIN_TRANSFER_ENABLE | 
                            _08_DTC_DEST_ADDR_INCREMENTED | _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    R_NOR_FLASH_DTCD_0.dtcct = (uint8_t)(rxcnt - 1);
    R_NOR_FLASH_DTCD_0.dtsar = NOR_FLASH_CSI_SIO_ADDRESS;

    /* CODE CHECKER, this is OK as a comment aligns with the cast */
    R_NOR_FLASH_DTCD_0.dtdar = (uint16_t)p_data;

    R_NOR_FLASH_DTCD_1.dtccr = _00_DTC_DATA_SIZE_8BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | 
                            _00_DTC_DEST_ADDR_FIXED | _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    s_nor_flash_sio_dummy    = NOR_FLASH_DUMMY_DATA;

    /* CODE CHECKER, this is OK as a comment aligns with the cast */
    R_NOR_FLASH_DTCD_1.dtsar = (uint16_t) &s_nor_flash_sio_dummy;

    R_NOR_FLASH_DTCD_1.dtdar = NOR_FLASH_CSI_SIO_ADDRESS;
}
/**********************************************************************************************************************
 End of function r_nor_flash_drvif_dtc_set_rx
 *********************************************************************************************************************/

#endif  /* #if (NOR_FLASH_CFG_MODE_TRNS & NOR_FLASH_TRNS_DTC) */

/* End of File */
