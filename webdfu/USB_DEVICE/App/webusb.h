#ifndef __WEBUSB_H
#define __WEBUSB_H

#include "main.h"

#define USBD_LPM_ENABLED  1 // 支持bos描述符

#define WL_REQUEST_WEBUSB    (0x22)  // WebUSB 供应商代码
#define WL_REQUEST_WINUSB    (0x21)  // WinUSB 供应商代码
#define MS_OS_20_DESCRIPTOR_LENGTH (0xB2) // 描述符集总长度
#define BOS_DESCRIPTOR_LENGTH 0x39

#define URL_DESCRIPTOR_LENGTH 0x2C

#define WEBUSB_REQUEST_GET_URL    (0x02) /* WebUSB Request Codes */
#define WINUSB_REQUEST_DESCRIPTOR (0x07)

#define WEBUSB_URL_TYPE                         0x03

/* bScheme in URL descriptor */
#define WEBUSB_URL_SCHEME_HTTP                  0x00
#define WEBUSB_URL_SCHEME_HTTPS                 0x01

// 设备链接网址
#define WEBUSB_URL_STRINGS  \
'd','e','v','a','n','l','a','i','.','g','i','t','h','u','b','.','i','o','/','w','e','b','d','f','u','/','d','f','u','-','u','t','i','l'



extern uint8_t MS_OS_20_DESCRIPTOR_SET[MS_OS_20_DESCRIPTOR_LENGTH];
extern uint8_t USBD_WebUSBURLDescriptor[URL_DESCRIPTOR_LENGTH];
#endif