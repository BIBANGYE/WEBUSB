/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_dfu_if.c
  * @brief          : Usb device for Download Firmware Update.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_dfu_if.h"

#define FLASH_DESC_STR      "@Internal Flash   /0x08000000/256*02Kgd,"

/** @defgroup USBD_DFU_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static uint16_t MEM_If_Init_FS(void);
static uint16_t MEM_If_Erase_FS(uint32_t Add);
static uint16_t MEM_If_Write_FS(uint8_t *src, uint8_t *dest, uint32_t Len);
static uint8_t *MEM_If_Read_FS(uint8_t *src, uint8_t *dest, uint32_t Len);
static uint16_t MEM_If_DeInit_FS(void);
static uint16_t MEM_If_GetStatus_FS(uint32_t Add, uint8_t Cmd, uint8_t *buffer);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

#if defined ( __ICCARM__ ) /* IAR Compiler */
    #pragma data_alignment=4
#endif
__ALIGN_BEGIN USBD_DFU_MediaTypeDef USBD_DFU_fops_FS __ALIGN_END =
{
    (uint8_t*)FLASH_DESC_STR,
    MEM_If_Init_FS,
    MEM_If_DeInit_FS,
    MEM_If_Erase_FS,
    MEM_If_Write_FS,
    MEM_If_Read_FS,
    MEM_If_GetStatus_FS
};

/* Private functions ---------------------------------------------------------*/
/**
Flash初始化，将Flash解锁，并将所有的标志位清零，以便后续的写入动作
  * @brief  Memory initialization routine.
  * @retval USBD_OK if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Init_FS(void)
{
    /* USER CODE BEGIN 0 */
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
    return (USBD_OK);
    /* USER CODE END 0 */
}

/**
Flash取消初始化，将Flash重新上锁，禁止对Flash的操作
  * @brief  De-Initializes Memory
  * @retval USBD_OK if operation is successful, MAL_FAIL else
  */
uint16_t MEM_If_DeInit_FS(void)
{
    /* USER CODE BEGIN 1 */
    HAL_FLASH_Lock();
    return (USBD_OK);
    /* USER CODE END 1 */
}

/**
  * @brief  Erase sector.Flash擦除
  * @param  Add: Address of sector to be erased.
  * @retval 0 if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Erase_FS(uint32_t Add)
{
    /* USER CODE BEGIN 2 */
    uint32_t PageError;
    /* Variable contains Flash operation status */
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef eraseinitstruct;

    eraseinitstruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseinitstruct.PageAddress = Add;
    eraseinitstruct.NbPages = 1U;
    status = HAL_FLASHEx_Erase(&eraseinitstruct, &PageError);

    if(status != HAL_OK)
    {
        return (USBD_FAIL);
    }

    return (USBD_OK);
    /* USER CODE END 2 */
}

/**
  * @brief  Memory write routine.Flash写入，将USB接收到的Flash数据写入到Flash中
  * @param  src: Pointer to the source buffer. Address to be written to.
  * @param  dest: Pointer to the destination buffer.
  * @param  Len: Number of data to be written (in bytes).
  * @retval USBD_OK if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Write_FS(uint8_t *src, uint8_t *dest, uint32_t Len)
{
    /* USER CODE BEGIN 3 */
    uint32_t i = 0;

    for(i = 0; i < Len; i += 4)
    {
        /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
        * be done by byte */
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)(dest + i), *(uint32_t *)(src + i)) == HAL_OK)
        {
            /* Check the written value */
            if(*(uint32_t *)(src + i) != *(uint32_t *)(dest + i))
            {
                /* Flash content doesn't match SRAM content */
                return (USBD_FAIL);
            }
        }
        else
        {
            /* Error occurred while writing data in Flash memory */
            return (USBD_FAIL);
        }
    }

    return (USBD_OK);
    /* USER CODE END 3 */
}

/**
  * @brief  Memory read routine.Flash读取，读取指定地址的数据到目标数组中，并返回数组地址
  * @param  src: Pointer to the source buffer. Address to be written to.
  * @param  dest: Pointer to the destination buffer.
  * @param  Len: Number of data to be read (in bytes).
  * @retval Pointer to the physical address where data should be read.
  */
uint8_t *MEM_If_Read_FS(uint8_t *src, uint8_t *dest, uint32_t Len)
{
    /* Return a valid address to avoid HardFault */
    /* USER CODE BEGIN 4 */
    uint32_t i = 0;
    uint8_t *psrc = src;

//    for(i = 0; i < Len; i++)
//    {
//        dest[i] = *psrc++;
//    }
    return (uint8_t*)(psrc);
}

/**
  * @brief  Get status routine 获取Flash状态
  * @param  Add: Address to be read from
  * @param  Cmd: Number of data to be read (in bytes)
  * @param  buffer: used for returning the time necessary for a program or an erase operation
  * @retval USBD_OK if operation is successful
  */
uint16_t MEM_If_GetStatus_FS(uint32_t Add, uint8_t Cmd, uint8_t *buffer)
{
    /* USER CODE BEGIN 5 */
    //擦除及写入时间应该按文档改写
    uint16_t FLASH_PROGRAM_TIME = 50;
    uint16_t FLASH_ERASE_TIME = 50;

    printf("cmd = %d\r\n",Cmd);
    switch(Cmd)
    {
        case DFU_MEDIA_PROGRAM:
            printf("DFU_MEDIA_PROGRAM\r\n");
            buffer[1] = (uint8_t)FLASH_PROGRAM_TIME;
            buffer[2] = (uint8_t)(FLASH_PROGRAM_TIME << 8);
            buffer[3] = 0;
            break;

        case DFU_MEDIA_ERASE:
        default:
            printf("DFU_MEDIA_ERASE\r\n");
            buffer[1] = (uint8_t)FLASH_ERASE_TIME;
            buffer[2] = (uint8_t)(FLASH_ERASE_TIME << 8);
            buffer[3] = 0;
            break;
    }
    return (USBD_OK);
    /* USER CODE END 5 */
}