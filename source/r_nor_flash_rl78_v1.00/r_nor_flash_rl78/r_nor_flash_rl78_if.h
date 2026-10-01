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
 * File Name    : r_nor_flash_rl78_if.h
 * Version      : 1.00
 * Description  : NOR FLASH driver interface header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 *********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#include "r_smc_entry.h"


#ifndef R_NOR_FLASH_RL78_IF_H
#define R_NOR_FLASH_RL78_IF_H


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/* Driver version */
#define NOR_FLASH_VERSION_MAJOR         (0x01U)
#define NOR_FLASH_VERSION_MINOR         (0x00U)

/* Definitions of FLASH MEMORY TYPE */
#define NOR_FLASH_TYPE_AT25SF           (0)         /* Renesas Electronics AT25SF       */
#define NOR_FLASH_TYPE_AT25QF           (1)         /* Renesas Electronics AT25QF       */
#define NOR_FLASH_TYPE_MX25L            (2)         /* Macronix MX25L                   */
#define NOR_FLASH_TYPE_MX66L            (3)         /* Macronix MX66L                   */
#define NOR_FLASH_TYPE_MX25R            (4)         /* Macronix MX25R                   */

/* Definitions of FLASH MEMORY SIZE */
#define NOR_FLASH_SIZE_4M               (0)         /* 4M-bit (512K Bytes)              */
#define NOR_FLASH_SIZE_8M               (1)         /* 8M-bit (1M Bytes)                */
#define NOR_FLASH_SIZE_16M              (2)         /* 16M-bit (2M Bytes)               */
#define NOR_FLASH_SIZE_32M              (3)         /* 32M-bit (4M Bytes)               */
#define NOR_FLASH_SIZE_64M              (4)         /* 64M-bit (8M Bytes)               */
#define NOR_FLASH_SIZE_128M             (5)         /* 128M-bit (16M Bytes)             */
#define NOR_FLASH_SIZE_256M             (6)         /* 256M-bit (32M Bytes)             */
#define NOR_FLASH_SIZE_512M             (7)         /* 512M-bit (64M Bytes)             */
#define NOR_FLASH_SIZE_1G               (8)         /* 1G-bit (128M Bytes)              */

/* Definitions of device driver channel no. */
#define NOR_FLASH_DRVR_CH0              (0)         /* CSI00                            */
#define NOR_FLASH_DRVR_CH1              (1)         /* CSI01                            */
#define NOR_FLASH_DRVR_CH2              (2)         /* CSI10                            */
#define NOR_FLASH_DRVR_CH3              (3)         /* CSI11                            */
#define NOR_FLASH_DRVR_CH4              (4)         /* CSI20                            */
#define NOR_FLASH_DRVR_CH5              (5)         /* CSI21                            */
#define NOR_FLASH_DRVR_CH6              (6)         /* CSI30                            */
#define NOR_FLASH_DRVR_CH7              (7)         /* CSI31                            */

/* Definitions of data transfer method */
#define NOR_FLASH_TRNS_CPU              (0x1000U)
#define NOR_FLASH_TRNS_DTC              (0x2000U)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
/* Enumeration for return values */
typedef enum e_nor_flash_status
{
    NOR_FLASH_SUCCESS_BUSY          = 1,    /* Successful operation (EERPOM is busy)    */
    NOR_FLASH_SUCCESS               = 0,    /* Successful operation                     */
    NOR_FLASH_ERR_PARAM             = -1,   /* Parameter error                          */
    NOR_FLASH_ERR_HARD              = -2,   /* HARD error                               */
    NOR_FLASH_ERR_NOT_OPEN          = -3,   /* NOR FLASH SIS module not open            */
    NOR_FLASH_ERR_ALREADY_OPEN      = -4,   /* NOR FLASH SIS module already opened      */
    NOR_FLASH_ERR_WEL_CHK           = -5,   /* WEL Check error                          */
    NOR_FLASH_ERR_NON_SUPPORTED_API = -6    /* Non Supported API error                  */
} e_nor_flash_status_t;

typedef enum e_nor_flash_erase_mode
{
    NOR_FLASH_MODE_C_ERASE = 1,
    NOR_FLASH_MODE_B4K_ERASE,
    NOR_FLASH_MODE_B32K_ERASE,
    NOR_FLASH_MODE_B64K_ERASE,
    NOR_FLASH_MODE_SCUR_ERASE,
    NOR_FLASH_MODE_S_ERASE
} e_nor_flash_erase_mode_t;

typedef enum e_nor_flash_check_busy
{
    NOR_FLASH_MODE_REG_WRITE_BUSY = 1,
    NOR_FLASH_MODE_PROG_BUSY,
    NOR_FLASH_MODE_ERASE_BUSY
} e_nor_flash_check_busy_t;

/* Flash memory information */
typedef struct
{
    uint32_t        addr;               /* Address to issue a command               */
    uint16_t        cnt;                /* Number of bytes to be read/written       */
    uint16_t        data_cnt;           /* Temporary counter or Number of bytes to be written in a page */
    uint8_t       * p_data;             /* Data storage buffer pointer              */
} st_nor_flash_info_t;                  /* 10 bytes                                 */

/* Flash memory size information */
typedef struct
{
    uint32_t        mem_size;           /* Max memory size                          */
    uint32_t        wpag_size;          /* Write page size                          */
} st_nor_flash_mem_info_t;              /* 8 bytes                                  */

/* Flash memory erase information */
typedef struct
{
    uint32_t                    addr;   /* Address to issue a command               */
    e_nor_flash_erase_mode_t    mode;   /* Mode of erase                            */
} st_nor_flash_erase_info_t;            /* 6 bytes                                  */

/* Flash memory register information */
typedef struct
{
    uint8_t         status;             /* Status register                           */
    uint8_t         config1;            /* Configuration or Configuration-1 register */
    uint8_t         config2;            /* Configuration-2 register                  */
    uint8_t         rsv[1];
} st_nor_flash_reg_info_t;              /* 4 bytes                                   */


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

/* ---- API for all flash memory  ---- */
/* Function Name : R_NOR_FLASH_Open */
/******************************************************************************************************************//**
 * @brief This function is run first when using the APIs of the serial flash memory control software.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_ALREADY_OPEN    NOR FLASH SIS module already opened
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Open (void);

/* Function Name : R_NOR_FLASH_Close */
/******************************************************************************************************************//**
 * @brief This function is used to close the serial flash memory control software when it is in use.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Close (void);

/* Function Name : R_NOR_FLASH_ReadStatus */
/******************************************************************************************************************//**
 * @brief This function is used to read the status register.
 * @param[out] p_status
 *             Status register storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus (uint8_t * p_status);

/* Function Name : R_NOR_FLASH_SetWriteProtect */
/******************************************************************************************************************//**
 * @brief This function is used to make write protect settings.
 * @param[in] wpsts
 *             Write protect setting data
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_SetWriteProtect (uint8_t wpsts);

/* Function Name : R_NOR_FLASH_WriteDisable */
/******************************************************************************************************************//**
 * @brief This function is used to disable write operation.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDisable (void);

/* Function Name : R_NOR_FLASH_ReadData */
/******************************************************************************************************************//**
 * @brief This function is used to read data from the serial flash memory.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_ReadData() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadData (st_nor_flash_info_t * p_nor_flash_info);

/* Function Name : R_NOR_FLASH_WriteDataPage */
/******************************************************************************************************************//**
 * @brief This function is used to write data to the serial flash memory in single-page units.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 2-byte boundary.
 *             See section R_NOR_FLASH_WriteDataPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDataPage (st_nor_flash_info_t * p_nor_flash_info);

/* Function Name : R_NOR_FLASH_Erase */
/******************************************************************************************************************//**
 * @brief Based on the mode setting, this function erases all the data in the specified sector (sector erase),
          all the data in the specified block (block erase: 32 KB block or 64 KB block), or all the data on
          the specified chip (chip erase).
 * @param[in] p_nor_flash_erase_info
 *             Serial flash memory erase information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_NOR_FLASH_Erase() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK         WEL Check error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Erase (st_nor_flash_erase_info_t * p_nor_flash_erase_info);

/* Function Name : R_NOR_FLASH_CheckBusy */
/******************************************************************************************************************//**
 * @brief This function is used to perform polling to determine if a write or erase operation has finished.
 * @param[in] mode
 *             Completion wait processing setting. See section R_NOR_FLASH_CheckBusy() in the application note for
 *             details.
 * @retval    NOR_FLASH_SUCCESS             Normal end, and write finished
 * @retval    NOR_FLASH_SUCCESS_BUSY        Normal end, and write in progress
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_CheckBusy (e_nor_flash_check_busy_t mode);

/* Function Name : R_NOR_FLASH_ReadId */
/******************************************************************************************************************//**
 * @brief This function is used to read ID information.
 * @param[in,out] p_data
 *             ID information storage buffer. The size differs depending on the serial flash memory product used.
 *             See section R_NOR_FLASH_ReadId() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 * @retval    NOR_FLASH_ERR_HARD            Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN        NOR FLASH SIS module not open
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadId (uint8_t * p_data);

/* Function Name : R_NOR_FLASH_GetMemoryInfo */
/******************************************************************************************************************//**
 * @brief This function is used to fetch the serial flash memory size information.
 * @param[out] p_nor_flash_mem_info
 *             Serial flash memory size information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_NOR_FLASH_GetMemoryInfo() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS             Successful operation
 * @retval    NOR_FLASH_ERR_PARAM           Parameter error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_GetMemoryInfo (st_nor_flash_mem_info_t * p_nor_flash_mem_info);

/* Function Name : R_NOR_FLASH_GetVersion */
/******************************************************************************************************************//**
 * @brief This function is used to fetch the serial flash memory version information.
 * @param     None
 * @retval    Version number.   Upper 2 bytes: major version, lower 2 bytes: minor version.
 *********************************************************************************************************************/
uint32_t             R_NOR_FLASH_GetVersion (void);

/* Function Name : R_NOR_FLASH_Interval */
/******************************************************************************************************************//**
 * @brief This function calls the interval timer counter function of the SPI(CSI) software. When using the DTC, use a 
 *        timer to call this function at 1 ms intervals.
 * @param     None
 * @retval    None
 *********************************************************************************************************************/
void                 R_NOR_FLASH_Interval (void);

/* Function Name : R_NOR_FLASH_SendendNotification */
/******************************************************************************************************************//**
 * @brief This function calls the SPI (CSI) software's transmit complete function.Call this function from the code 
 *        generation transmission completion function.
 * @param     None
 * @retval    None
 *********************************************************************************************************************/
void                 R_NOR_FLASH_SendendNotification (void);

/* ---- API for specific flash memory ---- */
/* Function Name : R_NOR_FLASH_ReadConfiguration */
/******************************************************************************************************************//**
 * @brief This function is used to read the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[out] p_config
 *             Configuration register storage buffer. The size differs depending on the serial NOR flash memory
 *             product used. See section R_NOR_FLASH_ReadConfiguration() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadConfiguration (uint8_t * p_config);

/* Function Name : R_NOR_FLASH_WriteConfiguration */
/******************************************************************************************************************//**
 * @brief This function is used to write the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] p_reg
 *             Register information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_NOR_FLASH_WriteConfiguration() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteConfiguration (st_nor_flash_reg_info_t * p_reg);

/* Function Name : R_NOR_FLASH_Set4byteAddressMode */
/******************************************************************************************************************//**
 * @brief This function is used to set the address mode to 4-byte address mode. It is a dedicated API function for
 *        MX25L, MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param     None
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_Set4byteAddressMode (void);

/* Function Name : R_NOR_FLASH_ReadSecurity */
/******************************************************************************************************************//**
 * @brief This function is used to read the security register. It is a dedicated API function for MX25L, MX66L, or
 *        MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[out] p_scur
 *             Security register  storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadSecurity (uint8_t * p_scur);

/* Function Name : R_NOR_FLASH_WriteStatus */
/******************************************************************************************************************//**
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
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus (uint8_t * p_reg);

/* Function Name : R_NOR_FLASH_WriteStatus2 */
/******************************************************************************************************************//**
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
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus2 (uint8_t * p_reg);

/* Function Name : R_NOR_FLASH_WriteStatus3 */
/******************************************************************************************************************//**
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
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteStatus3 (uint8_t * p_reg);

/* Function Name : R_NOR_FLASH_ReadStatus2 */
/******************************************************************************************************************//**
 * @brief This function is used to read the status register 2. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[out] p_status
 *             Status register 2 storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus2 (uint8_t * p_status);

/* Function Name : R_NOR_FLASH_ReadStatus3 */
/******************************************************************************************************************//**
 * @brief This function is used to read the status register 3. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[out] p_status
 *             Status register 3 storage buffer (size: 1 byte)
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadStatus3 (uint8_t * p_status);

/* Function Name : R_NOR_FLASH_ReadDataSecurityPage */
/******************************************************************************************************************//**
 * @brief This function is used to read data from the security register. It is a dedicated API function for AT25QF
 *        family serial NOR flash memory of Renesas Electronics.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_NOR_FLASH_ReadDataSecurityPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_ReadDataSecurityPage (st_nor_flash_info_t * p_nor_flash_info);

/* Function Name : R_NOR_FLASH_WriteDataSecurityPage */
/******************************************************************************************************************//**
 * @brief This function is used to write data to the security register page in single-page units. It is a dedicated
 *        API function for AT25QF family serial NOR flash memory of Renesas Electronics.
 * @param[in,out] p_nor_flash_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_NOR_FLASH_WriteDataSecurityPage() in the application note for details.
 * @retval    NOR_FLASH_SUCCESS                 Successful operation
 * @retval    NOR_FLASH_ERR_PARAM               Parameter error
 * @retval    NOR_FLASH_ERR_HARD                Hardware error
 * @retval    NOR_FLASH_ERR_NOT_OPEN            NOR FLASH SIS module not open
 * @retval    NOR_FLASH_ERR_WEL_CHK             WEL Check error
 * @retval    NOR_FLASH_ERR_NON_SUPPORTED_API   Non Supported API error
 *********************************************************************************************************************/
e_nor_flash_status_t R_NOR_FLASH_WriteDataSecurityPage (st_nor_flash_info_t * p_nor_flash_info);


#endif /* R_NOR_FLASH_RL78_IF_H */

/* End of File */
