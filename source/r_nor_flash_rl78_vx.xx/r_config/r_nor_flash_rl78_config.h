/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nor_flash_rl78_config.h
 * Version      : 1.00
 * Description  : NOR FLASH driver configuration header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/
#ifndef R_NOR_FLASH_RL78_CONFIG_H
#define R_NOR_FLASH_RL78_CONFIG_H

/**********************************************************************************************************************
 SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 *********************************************************************************************************************/
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
   Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define NOR_FLASH_CFG_PARAM_CHECKING_ENABLE  (BSP_CFG_PARAM_CHECKING_ENABLE)

/**********************************************************************************************************************
 ENABLE CHECKING OF THE WEL BIT.
 *********************************************************************************************************************/
/* Define the check of WEL bit after Write Enable command issue. */
/* 0 : Not check WEL bit. */
/* 1 : Check WEL bit. */
#define NOR_FLASH_CFG_WEL_CHK           (1)

/**********************************************************************************************************************
 SELECT THE FLASH MEMORY TYPE
 *********************************************************************************************************************/
/*  Please set one macro definition. */
/*      NOR_FLASH_TYPE_AT25SF   */
/*      NOR_FLASH_TYPE_AT25QF   */
/*      NOR_FLASH_TYPE_MX25L    */
/*      NOR_FLASH_TYPE_MX66L    */
/*      NOR_FLASH_TYPE_MX25R    */
#define NOR_FLASH_CFG_DEVICE            (NOR_FLASH_TYPE_AT25SF)

/**********************************************************************************************************************
 SELECT THE FLASH MEMORY SIZE
 *********************************************************************************************************************/
/*  Please set one macro definition. */
/*      NOR_FLASH_SIZE_4M       */
/*      NOR_FLASH_SIZE_8M       */
/*      NOR_FLASH_SIZE_16M      */
/*      NOR_FLASH_SIZE_32M      */
/*      NOR_FLASH_SIZE_64M      */
/*      NOR_FLASH_SIZE_128M     */
/*      NOR_FLASH_SIZE_256M     */
/*      NOR_FLASH_SIZE_512M     */
/*      NOR_FLASH_SIZE_1G       */
#define NOR_FLASH_CFG_SIZE              (NOR_FLASH_SIZE_64M)

/**********************************************************************************************************************
 PIN ASSIGNMENT
 *********************************************************************************************************************/
/* The macros to specify the ports used for SS#. 
   Default value 'X' is for reference only, If this default value is kept, then the code
   support for device port will be temporarily disabled until user assigns a value of port
   used for SS# according to a device. */
#define NOR_FLASH_CFG_CS_PORTNO         (0)         /* Port Number : FLASH SS#         */
#define NOR_FLASH_CFG_CS_BITNO          (6)         /* Bit Number  : FLASH SS#         */

/**********************************************************************************************************************
 DATA TRANSFER MODE
 *********************************************************************************************************************/
/*  Please set one macro definition. */
/*      NOR_FLASH_TRNS_CPU      */
/*      NOR_FLASH_TRNS_DTC      */
#define NOR_FLASH_CFG_MODE_TRNS         (NOR_FLASH_TRNS_CPU)

/**********************************************************************************************************************
 DEVICE DRIVER CHANEL NUMBER
 *********************************************************************************************************************/
/*  Please set one macro definition. */
/*      NOR_FLASH_DRVR_CH0 - NOR_FLASH_DRVR_CH7  */
#define NOR_FLASH_CFG_DRVR_CH           (NOR_FLASH_DRVR_CH3)

/**********************************************************************************************************************
 DTC ONLY : CONTROL DATA NUMBER OF DTC
 *********************************************************************************************************************/
/* Set the DTC control data number used for transmission and reception. */
#define NOR_FLASH_CFG_DTCD_NO           (0) /* DTC for transmission & reception   */


#endif /* R_NOR_FLASH_RL78_CONFIG_H */

/* End of File */
