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
 * File Name    : r_nor_flash_private.h
 * Version      : 1.00
 * Description  : NOR FLASH driver private header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 *********************************************************************************************************************/
/* FLASH driver flash memory type file */
#if (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) || (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25QF)
#include "./src/flash_types/flash_at/r_nor_flash_at_type_sub.h"
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX25L) || (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX66L) || \
    (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX25R)
#include "./src/flash_types/flash_mx/r_nor_flash_mx_type_sub.h"
#else
    #error "Unsupported NOR FLASH TYPE"
#endif

/* FLASH driver port header file */
#include "./src/dev_port/r_nor_flash_dev_port.h"


#ifndef R_NOR_FLASH_PRIVATE_H
#define R_NOR_FLASH_PRIVATE_H


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define IS_SUPPORTING_AT() ((NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) || \
                            (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25QF))

#define IS_SUPPORTING_MX() ((NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX25L) || \
                            (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX66L) || \
                            (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_MX25R))

/* Definition of OPEN state management */
#define NOR_FLASH_SIS_CLOSE             (0U)                        /* NOR FLASH SIS module CLOSE           */
#define NOR_FLASH_SIS_OPEN              (1U)                        /* NOR FLASH SIS module OPEN            */

/* Define address size */
#define NOR_FLASH_ADDR_3BYTES           (3U)
#define NOR_FLASH_ADDR_4BYTES           (4U)

/* Address Mode */
#define NOR_FLASH_MODE_3BYTE            (0U)                        /* 3-byte Address Mode                  */
#define NOR_FLASH_MODE_4BYTE            (1U)                        /* 4-byte Address Mode                  */

/* Address boundary */
#define NOR_FLASH_ADDR_BOUNDARY         (0x0001U)

/* Dummy data */
#define NOR_FLASH_DUMMY_DATA            (0xFFU)

/* CSI channel name & SIO register address */
#if (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH0)
    #define NOR_FLASH_CSI_NAME              Config_CSI00            /* CSI channel name "Config_CSI00" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO00)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH1)
    #define NOR_FLASH_CSI_NAME              Config_CSI01            /* CSI channel name "Config_CSI01" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO01)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH2)
    #define NOR_FLASH_CSI_NAME              Config_CSI10            /* CSI channel name "Config_CSI10" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO10)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH3)
    #define NOR_FLASH_CSI_NAME              Config_CSI11            /* CSI channel name "Config_CSI11" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO11)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH4)
    #define NOR_FLASH_CSI_NAME              Config_CSI20            /* CSI channel name "Config_CSI20" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO20)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH5)
    #define NOR_FLASH_CSI_NAME              Config_CSI21            /* CSI channel name "Config_CSI21" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO21)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH6)
    #define NOR_FLASH_CSI_NAME              Config_CSI30            /* CSI channel name "Config_CSI30" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO30)      /* SIO register address */
#elif (NOR_FLASH_CFG_DRVR_CH == NOR_FLASH_DRVR_CH7)
    #define NOR_FLASH_CSI_NAME              Config_CSI31            /* CSI channel name "Config_CSI31" */
    #define NOR_FLASH_CSI_SIO_ADDRESS       ((uint16_t)&SIO31)      /* SIO register address */
#endif

/* **** Definition of string conversion to access CSI functions **** */
#define NOR_FLASH_CSI_START_FUNC1( x )          R_##x##_Start               /* String "R_x_Start" */
#define NOR_FLASH_CSI_START_FUNC2( x )          NOR_FLASH_CSI_START_FUNC1( x )
#define NOR_FLASH_CSI_STOP_FUNC1( x )           R_##x##_Stop                /* String "R_x_Stop" */
#define NOR_FLASH_CSI_STOP_FUNC2( x )           NOR_FLASH_CSI_STOP_FUNC1( x )
#define NOR_FLASH_CSI_SEND_RECEIVE_FUNC1( x )   R_##x##_Send_Receive        /* String "R_x_Send_Receive" */
#define NOR_FLASH_CSI_SEND_RECEIVE_FUNC2( x )   NOR_FLASH_CSI_SEND_RECEIVE_FUNC1( x )

#define R_NOR_FLASH_CSI_START()                 NOR_FLASH_CSI_START_FUNC2( NOR_FLASH_CSI_NAME )()
#define R_NOR_FLASH_CSI_STOP()                  NOR_FLASH_CSI_STOP_FUNC2( NOR_FLASH_CSI_NAME )()
#define R_NOR_FLASH_CSI_SEND( x, y )            NOR_FLASH_CSI_SEND_RECEIVE_FUNC2( NOR_FLASH_CSI_NAME )( x, y, NULL )
#define R_NOR_FLASH_CSI_RECEIVE( x, y )         NOR_FLASH_CSI_SEND_RECEIVE_FUNC2( NOR_FLASH_CSI_NAME )( NULL, y, x )

/* DTCD Number */
#if (NOR_FLASH_CFG_DTCD_NO == 0)
    #define NOR_FLASH_DTCD_NO_0             0
    #define NOR_FLASH_DTCD_NO_1             1
#elif (NOR_FLASH_CFG_DTCD_NO == 1)
    #define NOR_FLASH_DTCD_NO_0             1
    #define NOR_FLASH_DTCD_NO_1             2
#elif (NOR_FLASH_CFG_DTCD_NO == 2)
    #define NOR_FLASH_DTCD_NO_0             2
    #define NOR_FLASH_DTCD_NO_1             3
#elif (NOR_FLASH_CFG_DTCD_NO == 3)
    #define NOR_FLASH_DTCD_NO_0             3
    #define NOR_FLASH_DTCD_NO_1             4
#elif (NOR_FLASH_CFG_DTCD_NO == 4)
    #define NOR_FLASH_DTCD_NO_0             4
    #define NOR_FLASH_DTCD_NO_1             5
#elif (NOR_FLASH_CFG_DTCD_NO == 5)
    #define NOR_FLASH_DTCD_NO_0             5
    #define NOR_FLASH_DTCD_NO_1             6
#elif (NOR_FLASH_CFG_DTCD_NO == 6)
    #define NOR_FLASH_DTCD_NO_0             6
    #define NOR_FLASH_DTCD_NO_1             7
#elif (NOR_FLASH_CFG_DTCD_NO == 7)
    #define NOR_FLASH_DTCD_NO_0             7
    #define NOR_FLASH_DTCD_NO_1             8
#elif (NOR_FLASH_CFG_DTCD_NO == 8)
    #define NOR_FLASH_DTCD_NO_0             8
    #define NOR_FLASH_DTCD_NO_1             9
#elif (NOR_FLASH_CFG_DTCD_NO == 9)
    #define NOR_FLASH_DTCD_NO_0             9
    #define NOR_FLASH_DTCD_NO_1             10
#elif (NOR_FLASH_CFG_DTCD_NO == 10)
    #define NOR_FLASH_DTCD_NO_0             10
    #define NOR_FLASH_DTCD_NO_1             11
#elif (NOR_FLASH_CFG_DTCD_NO == 11)
    #define NOR_FLASH_DTCD_NO_0             11
    #define NOR_FLASH_DTCD_NO_1             12
#elif (NOR_FLASH_CFG_DTCD_NO == 12)
    #define NOR_FLASH_DTCD_NO_0             12
    #define NOR_FLASH_DTCD_NO_1             13
#elif (NOR_FLASH_CFG_DTCD_NO == 13)
    #define NOR_FLASH_DTCD_NO_0             13
    #define NOR_FLASH_DTCD_NO_1             14
#elif (NOR_FLASH_CFG_DTCD_NO == 14)
    #define NOR_FLASH_DTCD_NO_0             14
    #define NOR_FLASH_DTCD_NO_1             15
#elif (NOR_FLASH_CFG_DTCD_NO == 15)
    #define NOR_FLASH_DTCD_NO_0             15
    #define NOR_FLASH_DTCD_NO_1             16
#elif (NOR_FLASH_CFG_DTCD_NO == 16)
    #define NOR_FLASH_DTCD_NO_0             16
    #define NOR_FLASH_DTCD_NO_1             17
#elif (NOR_FLASH_CFG_DTCD_NO == 17)
    #define NOR_FLASH_DTCD_NO_0             17
    #define NOR_FLASH_DTCD_NO_1             18
#elif (NOR_FLASH_CFG_DTCD_NO == 18)
    #define NOR_FLASH_DTCD_NO_0             18
    #define NOR_FLASH_DTCD_NO_1             19
#elif (NOR_FLASH_CFG_DTCD_NO == 19)
    #define NOR_FLASH_DTCD_NO_0             19
    #define NOR_FLASH_DTCD_NO_1             20
#elif (NOR_FLASH_CFG_DTCD_NO == 20)
    #define NOR_FLASH_DTCD_NO_0             20
    #define NOR_FLASH_DTCD_NO_1             21
#elif (NOR_FLASH_CFG_DTCD_NO == 21)
    #define NOR_FLASH_DTCD_NO_0             21
    #define NOR_FLASH_DTCD_NO_1             22
#elif (NOR_FLASH_CFG_DTCD_NO == 22)
    #define NOR_FLASH_DTCD_NO_0             22
    #define NOR_FLASH_DTCD_NO_1             23
#endif

/* **** Definition of string conversion to access DTC functions **** */
#define NOR_FLASH_DTCD1( x )                dtc_controldata_##x         /* String "dtc_controldata_x" */
#define NOR_FLASH_DTCD2( x )                NOR_FLASH_DTCD1( x )

#define R_NOR_FLASH_DTCD_0                  NOR_FLASH_DTCD2( NOR_FLASH_DTCD_NO_0 )
#define R_NOR_FLASH_DTCD_1                  NOR_FLASH_DTCD2( NOR_FLASH_DTCD_NO_1 )

#define NOR_FLASH_DTC_START_FUNC1( x )      R_DTCD##x##_Start           /* String "R_DTCDx_Start" */
#define NOR_FLASH_DTC_START_FUNC2( x )      NOR_FLASH_DTC_START_FUNC1( x )
#define NOR_FLASH_DTC_STOP_FUNC1( x )       R_DTCD##x##_Stop            /* String "R_DTCDx_Stop" */
#define NOR_FLASH_DTC_STOP_FUNC2( x )       NOR_FLASH_DTC_STOP_FUNC1( x )

#define R_NOR_FLASH_DTC_START()             NOR_FLASH_DTC_START_FUNC2( NOR_FLASH_DTCD_NO_0 )()
#define R_NOR_FLASH_DTC_STOP()              NOR_FLASH_DTC_STOP_FUNC2( NOR_FLASH_DTCD_NO_0 )()


/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
/* r_nor_flash_type.c */
/**********************************************************************************************************************
 * Function Name: r_nor_flash_init_port
 * Description  : Sets FLASH control ports.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_init_port (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_reset_port
 * Description  : Resets setting of ports.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_reset_port (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status
 * Description  : Reads status from the status register and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status (uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_set_write_protect
 * Description  : Sets the write-protection setting to write-protection setting data (wpsts).
 * Arguments    : uint8_t            wpsts              ;   Write-protection setting data
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK                 ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : A SRWD bit is fixed to 0.
 *              : Please confirm the status register.
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_set_write_protect (uint8_t wpsts);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_disable
 * Description  : Clears the WEL bit.
 * Arguments    : None
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_disable (void);

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
e_nor_flash_status_t r_nor_flash_read_data (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_write_data_page (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_erase (st_nor_flash_erase_info_t * p_nor_flash_erase_info);

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
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_check_busy (e_nor_flash_check_busy_t mode);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_id
 * Description  : Reads Manufacture ID and Device ID.
 * Arguments    : uint8_t          * p_data             ;   ID data storage buffer pointer (3 bytes)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation (FLASH is ready)
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_id (uint8_t * p_data);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_get_memory_info
 * Description  : Gets the memory size and page size.
 * Arguments    : st_nor_flash_mem_info_t * p_nor_flash_mem_info;   Flash memory size information
 *              :    uint32_t               mem_size            ;   Max memory size
 *              :    uint32_t               wpag_size           ;   Write page size
 * Return Value : NOR_FLASH_SUCCESS                             ;   Successful operation
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_get_memory_info (st_nor_flash_mem_info_t * p_nor_flash_mem_info);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_configuration
 * Description  : Reads status from the configuration register and stores to the configuration storage buffer.
 * Arguments    : uint8_t       * p_config          ;   Read configuration storage buffer (1 byte or 2 bytes)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_configuration (uint8_t * p_config_reg);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status2
 * Description  : Reads status from the status register 2 and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API       ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status2 (uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_status3
 * Description  : Reads status from the status register 3 and stores to the read status storage buffer (p_status).
 * Arguments    : uint8_t       * p_status              ;   Read status storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API       ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_status3 (uint8_t * p_status);

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
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_configuration (st_nor_flash_reg_info_t * p_reg);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status
 * Description  : Writes from the write status storage buffer to the status register 1.
 * Arguments    : uint8_t         * p_reg           ;   Status register 1 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status (uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status2
 * Description  : Writes from the write status storage buffer to the status register 2.
 * Arguments    : uint8_t         * p_reg           ;   Status register 2 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status2 (uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_write_status3
 * Description  : Writes from the write status storage buffer to the status register 3.
 * Arguments    : uint8_t         * p_reg           ;   Status register 1 setting data buffer
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_write_status3 (uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_read_security
 * Description  : Reads status from the security register and stores to the security storage buffer (p_scur).
 * Arguments    : uint8_t   * p_scur                ;   Security storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_NON_SUPPORTED_API   ;   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_read_security (uint8_t * p_scur);

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
e_nor_flash_status_t r_nor_flash_read_data_security_page (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_write_data_security_page (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_set_4byte_address_mode (void);

/* r_nor_flash_drvif.c */
/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_open
 * Description  : Initializes I/O driver.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_drvif_open (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_close
 * Description  : Resets I/O driver.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_drvif_close (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_tx
 * Description  : Transmits data.
 * Arguments    : uint16_t      txcnt                       ;   Number of bytes to be write
 *              : uint8_t     * p_data                      ;   Write data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_drvif_tx (uint16_t txcnt, uint8_t * p_data);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_rx
 * Description  : Receives data.
 * Arguments    : uint16_t      rxcnt                       ;   Number of bytes to be read
 *              : uint8_t     * p_data                      ;   Read data storage buffer pointer
 * Return Value : NOR_FLASH_SUCCESS                         ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                        ;   Hardware error
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_drvif_rx (uint16_t rxcnt, uint8_t * p_data);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_1ms_interval
 * Description  : 1ms Interval Timer call function for driver interface.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_drvif_1ms_interval (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_drvif_csi_callback
 * Description  : Clear the SPI communication in progress flag.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_drvif_csi_callback (void);


/* r_nor_flash_dev_port.c */
/**********************************************************************************************************************
 * Function Name: r_nor_flash_cs_init
 * Description  : Initialize the port.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_cs_init (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_cs_reset
 * Description  : Reset the port.
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_cs_reset (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_set_cs
 * Description  : Sets the state of CS pin.
 * Arguments    : uint8_t lv                    ;   CS output level
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_set_cs (uint8_t lv);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_wait_lp
 * Description  : Loop Timer Processing
 * Arguments    : uint8_t unit                  ;   Timer unit
 * Return Value : None
 *********************************************************************************************************************/
void                 r_nor_flash_wait_lp (void);


#endif /* R_NOR_FLASH_PRIVATE_H */

/* End of File */
