#include "webusb.h"

// ����������Ϣ
uint8_t MS_OS_20_DESCRIPTOR_SET[MS_OS_20_DESCRIPTOR_LENGTH] =
{
    // Microsoft OS 2.0 ����������ͷ
    0x0A, 0x00,                         // Descriptor size (10 bytes)
    0x00, 0x00,                         // MS OS 2.0 descriptor set header
    0x00, 0x00, 0x03, 0x06,             // Windows version (8.1) (0x06030000)
    MS_OS_20_DESCRIPTOR_LENGTH, 0x00,   // Size, MS OS 2.0 descriptor set

    // Microsoft OS 2.0 �����Ӽ���ͷ
    0x08, 0x00,                 // wLength
    0x01, 0x00,                 // wDescriptorType
    0x00,                       // ���������� 1
    0x00,                       // bReserved
    0XA8, 0X00,                 // Size, MS OS 2.0 configuration subset

    // Microsoft OS 2.0 �����Ӽ�ͷ
    0x08, 0x00,  // Descriptor size (8 bytes)
    0x02, 0x00,  // MS OS 2.0 function subset header
    0x01,        // ��2���ӿ�
    0x00,        // ��������Ϊ 0
    0xA0, 0x00,

    // Microsoft OS 2.0 ���� ID ������
    // ���� ID ���������� Windows ���豸�� WinUSB �����������
    0x14, 0x00,             // wLength  20
    0x03, 0x00,             // MS_OS_20_FEATURE_COMPATIBLE_ID
    'W',  'I',  'N',  'U',  'S',  'B',  0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    // Microsoft OS 2.0 ע�������������
    // ע������Է����豸�ӿ� GUID
    0x84, 0x00,             //wLength: 132
    0x04, 0x00,             // wDescriptorType: MS_OS_20_FEATURE_REG_PROPERTY: 0x04 (Table 9)
    0x07, 0x00,             //wPropertyDataType: REG_MULTI_SZ (Table 15)
    0x2a, 0x00,             //wPropertyNameLength:
    //bPropertyName: ��DeviceInterfaceGUID��
    'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00,
    'r', 0x00, 'f', 0x00, 'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00,
    0x00, 0x00,
    0x50, 0x00,             // wPropertyDataLength
    //bPropertyData: ��{975F44D9-0D08-43FD-8B3E-127CA8AFFF9D}��.
    '{', 0x00, '9', 0x00, 'd', 0x00, '7', 0x00, 'd', 0x00, 'e', 0x00, 'b', 0x00, 'b', 0x00, 'c', 0x00, '-', 0x00,
    'c', 0x00, '8', 0x00, '5', 0x00, 'd', 0x00, '-', 0x00, '1', 0x00, '1', 0x00, 'd', 0x00, '1', 0x00, '-', 0x00,
    '9', 0x00, 'e', 0x00, 'b', 0x00, '4', 0x00, '-', 0x00, '0', 0x00, '0', 0x00, '6', 0x00, '0', 0x00, '0', 0x00,
    '8', 0x00, 'c', 0x00, '3', 0x00, 'a', 0x00, '1', 0x00, '9', 0x00, 'a', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00
};

// ��ַ������
uint8_t USBD_WebUSBURLDescriptor[URL_DESCRIPTOR_LENGTH]=
{
    URL_DESCRIPTOR_LENGTH,                       // Size of this descriptor
    WEBUSB_URL_TYPE,            // bDescriptorType
    WEBUSB_URL_SCHEME_HTTPS,    // URL scheme prefix
    WEBUSB_URL_STRINGS          // ���ӵ�ַ UTF-8 ����� URL ����
};

