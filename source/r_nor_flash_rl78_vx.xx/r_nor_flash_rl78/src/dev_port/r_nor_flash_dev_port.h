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
 * File Name    : r_nor_flash_dev_port.h
 * Version      : 1.00
 * Description  : NOR FLASH driver device port header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "platform.h"


#ifndef R_NOR_FLASH_DEV_PORT_H
#define R_NOR_FLASH_DEV_PORT_H


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/*----------- Definitions of port control ------------*/
#define NOR_FLASH_HI      (0x01U)                 /* Port "H" */
#define NOR_FLASH_LOW     (0x00U)                 /* Port "L" */

/* ---- CS ---- */
#if   (0 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  0
#elif (1 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  1
#elif (2 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  2
#elif (3 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  3
#elif (4 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  4
#elif (5 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  5
#elif (6 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  6
#elif (7 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  7
#elif (8 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  8
#elif (9 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  9
#elif (10 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  10
#elif (11 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  11
#elif (12 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  12
#elif (13 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  13
#elif (14 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  14
#elif (15 == NOR_FLASH_CFG_CS_PORTNO)
    #define NOR_FLASH_CS_PORTNO_SFR  15
#endif

#if   (0 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   0
#elif (1 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   1
#elif (2 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   2
#elif (3 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   3
#elif (4 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   4
#elif (5 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   5
#elif (6 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   6
#elif (7 == NOR_FLASH_CFG_CS_BITNO)
    #define NOR_FLASH_CS_BITNO_SFR   7
#endif


/* **** Definitions of string conversion to access I/O registers **** */
#define SFR1_PMXX( x,y )        PM ## x ## _bit.no ## y             /* String "PMx_bit.noy" */
#define SFR2_PMXX( x,y )        SFR1_PMXX( x , y )
#define SFR1_PXX( x,y )         P ## x ## _bit.no ## y              /* String "Px_bit.noy" */
#define SFR2_PXX( x,y )         SFR1_PXX( x , y )


/* **** Definitions of I/O registers of ports used for CS **** */
/* ---- Registers of the port used as CS ---- */
#define NOR_FLASH_PMXX_CS       (SFR2_PMXX( NOR_FLASH_CS_PORTNO_SFR , NOR_FLASH_CS_BITNO_SFR ))
#define NOR_FLASH_PXX_CS        (SFR2_PXX( NOR_FLASH_CS_PORTNO_SFR , NOR_FLASH_CS_BITNO_SFR ))

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/


#endif /* R_NOR_FLASH_DEV_PORT_H */

/* End of File */
