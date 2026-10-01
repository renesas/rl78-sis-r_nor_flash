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
 * File Name    : r_nor_flash_at_type_sub.h
 * Version      : 1.00
 * Description  : NOR FLASH driver memory type header file
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 22.03.2024 1.00     Created
 *********************************************************************************************************************/
#ifndef R_NOR_FLASH_AT_TYPE_SUB_H
#define R_NOR_FLASH_AT_TYPE_SUB_H


/**********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/*-------- Definitions of Command size ---------*/
#define NOR_FLASH_AT_CMD_SIZE           (1U)        /* Command size(Byte)                       */
#define NOR_FLASH_AT_STSREG1_SIZE       (1U)        /* Status register 1 size(Byte)             */
#define NOR_FLASH_AT_STSREG2_SIZE       (1U)        /* Status register 2 size(Byte)             */
#define NOR_FLASH_AT_STSREG3_SIZE       (1U)        /* Status register 3 size(Byte)             */
#define NOR_FLASH_AT_WSTSREG1_SIZE      (1U)        /* Status register 1 size (bytes) for Write */
#define NOR_FLASH_AT_WSTSREG2_SIZE      (1U)        /* Status register 2 size (bytes) for Write */
#define NOR_FLASH_AT_WSTSREG3_SIZE      (1U)        /* Status register 3 size (bytes) for Write */
#define NOR_FLASH_AT_IDDATA_SIZE        (3U)        /* ID data size (bytes)                     */

/*-------- Definitions of device information ---------*/
#if (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_4M)
    #define NOR_FLASH_AT_MEM_SIZE       (524288UL)          /* 500kByte (4Mbit)                     */
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_8M)
    #define NOR_FLASH_AT_MEM_SIZE       (1048576UL)         /* 1MByte (8Mbit)                       */
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_16M)
    #define NOR_FLASH_AT_MEM_SIZE       (2097152UL)         /* 2MByte (16Mbit)                      */
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_32M)
    #define NOR_FLASH_AT_MEM_SIZE       (4194304UL)         /* 4MByte (32Mbit)                      */
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_64M)
    #define NOR_FLASH_AT_MEM_SIZE       (8388608UL)         /* 8MByte (64Mbit)                      */
#elif (NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25QF) && (NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_64M)
    #define NOR_FLASH_AT_MEM_SIZE       (8388608UL)         /* 8MByte (64Mbit)                      */
#else
    #error "Unsupported NOR FLASH SIZE"
#endif  /* NOR_FLASH_CFG_DEVICE == NOR_FLASH_TYPE_AT25SF && NOR_FLASH_CFG_SIZE == NOR_FLASH_SIZE_4M */

#define NOR_FLASH_AT_B4K_ADDR           (0xfffff000UL)          /* 4KB Block address setting            */
#define NOR_FLASH_AT_B32K_ADDR          (0xffff8000UL)          /* 32KB Block address setting           */
#define NOR_FLASH_AT_B64K_ADDR          (0xffff0000UL)          /* 64KB Block address setting           */
#define NOR_FLASH_AT_SCUR_ADDR          (0x00003000UL)          /* Mask three pages address setting     */
#define NOR_FLASH_AT_PAGE_SIZE          (256UL)                 /* Page size when writing               */
#define NOR_FLASH_AT_ADDR_SIZE          (NOR_FLASH_ADDR_3BYTES) /* Address size (bytes)                 */
#define NOR_FLASH_AT_WP_WHOLE_MEM       (0x07U)                 /* Whole memory WP setting              */

/*------- Definitions of Status Register 1 value -------*/
#define NOR_FLASH_AT_REG1_SRP0          (0x80U)                 /* Status Register Protection bit 0     */
#define NOR_FLASH_AT_REG1_WEL           (0x02U)                 /* Write Enable Latch Bit               */
#define NOR_FLASH_AT_REG1_WIP           (0x01U)                 /* Write In Progress Bit                */
#define NOR_FLASH_AT_REG1_BPMASK        (0x1cU)                 /* Block Protect Bit Mask               */

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/


/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
/* r_nor_flash_at_type_sub.c */
/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_init_port
 * Description  : Initialize the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void                 r_nor_flash_at_init_port (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_reset_port
 * Description  : Reset the port.
 * Arguments    : None
 * Return Value : None
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
void                 r_nor_flash_at_reset_port (void);

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
e_nor_flash_status_t r_nor_flash_at_write_disable (void);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg1
 * Description  : Reads status from the status register 1 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 1 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg1 (uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg2
 * Description  : Reads status from the status register 2 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 2 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg2 (uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_read_stsreg3
 * Description  : Reads status from the status register 3 and stores to the read status storage buffer(p_status).
 * Arguments    : uint8_t          * p_status           ;   Read status register 3 storage buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                     ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                    ;   Hardware error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_read_stsreg3 (uint8_t * p_status);

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
e_nor_flash_status_t r_nor_flash_at_set_write_protect (uint8_t wpsts);

/**********************************************************************************************************************
 * Function Name: r_nor_flash_at_write_stsreg1
 * Description  : Writes status from the write status storage buffer to the status register 1.
 * Arguments    : uint8_t     * p_reg               ;   Status register 1 setting data buffer (1 byte)
 * Return Value : NOR_FLASH_SUCCESS                 ;   Successful operation
 *              : NOR_FLASH_ERR_HARD                ;   Hardware error
 *              : NOR_FLASH_ERR_WEL_CHK             ;   WEL Check error
 *---------------------------------------------------------------------------------------------------------------------
 * Notes        : None
 *********************************************************************************************************************/
e_nor_flash_status_t r_nor_flash_at_write_stsreg1 (uint8_t * p_reg);

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
e_nor_flash_status_t r_nor_flash_at_write_stsreg2 (uint8_t * p_reg);

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
e_nor_flash_status_t r_nor_flash_at_write_stsreg3 (uint8_t * p_reg);

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
e_nor_flash_status_t r_nor_flash_at_read (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_at_read_scurreg_page (st_nor_flash_info_t * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_at_write_page (st_nor_flash_info_t  * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_at_write_scurreg_page (st_nor_flash_info_t  * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_at_erase (st_nor_flash_erase_info_t * p_nor_flash_erase_info);

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
e_nor_flash_status_t r_nor_flash_at_rdid (uint8_t * p_data);

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
e_nor_flash_status_t r_nor_flash_at_check_busy (e_nor_flash_check_busy_t mode);

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
void                 r_nor_flash_at_get_memory_info (st_nor_flash_mem_info_t * p_nor_flash_mem_info);

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
e_nor_flash_status_t r_nor_flash_at_check_cnt (st_nor_flash_info_t  * p_nor_flash_info);

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
e_nor_flash_status_t r_nor_flash_at_check_scurreg_cnt (st_nor_flash_info_t * p_nor_flash_info);

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
uint16_t             r_nor_flash_at_page_calc (st_nor_flash_info_t  * p_nor_flash_info);


#endif /* R_NOR_FLASH_AT_TYPE_SUB_H */

/* End of File */
