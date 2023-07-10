/*!
    \file    hid_keyboard_itf.c
    \brief   standard HID keyboard interface driver

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
    \version 2022-06-10, V3.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "standard_hid_core.h"

typedef enum
{
    CHAR_A = 1,
    CHAR_B,
    CHAR_C
} key_char;

//��һ����ΪReportID:3���ֽ�2��0000 0xxx����λ�ֱ��ʾ�м䵥�����Ҽ��������������
//�ֽ�3Ϊx���ƶ����룬�ֽ�4Ϊy���ƶ����룬�ֽ�5Ϊ�����ƶ�ֵ �䷶ΧΪ-127~127
uint8_t buff_Mouse[5]={0x03,0x00,0x00,0x00,0x00};

//��ý�巢�����飬����HID�����������Ķ��壬��һ���ֽ�λReportID:2,
//�ڶ����ֽڴӸߵ��ͣ�ÿһλ�ֱ��Ӧ��
/*	      Bit ���� 
					0   ��������
					1   ������С
					2   ����
					3   ����/��ͣ
					4   ��ͣ
					5   ��һ��
					6   ��һ��
					7   �˳�����
*/
//����Ĳ�����HID����������ӣ��ο�HID Usage Tables��15��Consumer Page
//0x01����ʾ��������
uint8_t buff_Audio[2]={0x02,0x00};

//���̷�������
//�ֽ�1ΪReportID:1���ֽ�2Ϊ���ܼ��̣�ÿһλ��Ӧһ��������
/*  ����ϸ�Ĺ涨�ο��ĵ�Device Class Definition for HID��8.3��
					Bit Key 
					0 LEFT CTRL
					1 LEFT SHIFT
					2 LEFT ALT
					3 LEFT GUI 
					4 RIGHT CTRL
					5 RIGHT SHIFT
					6 RIGHT ALT
					7 RIGHT GUI
*/
//�ֽ�3�������ֽ�4-9��ʾ��ʾ������ֵ��
//ÿ���������ڵ�ֵ����HID Usage Tables�ĵ��еĵ�10�ڲ�ѯ
uint8_t buff_Key[9]={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


/* local function prototypes ('static') */
static void key_config(void);
static uint8_t key_state(void);
static void hid_key_data_send(usb_dev *udev);

hid_fop_handler fop_handler = {
    .hid_itf_config = key_config,
    .hid_itf_data_process = hid_key_data_send
};

/*!
    \brief      configure the keys
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void key_config (void)
{
//    /* keys configuration */
//    gd_eval_key_init(KEY_TAMPER, KEY_MODE_GPIO);
//    gd_eval_key_init(KEY_WAKEUP, KEY_MODE_GPIO);

//#ifdef GD32F30X_HD
//    gd_eval_key_init(KEY_USER1, KEY_MODE_GPIO);
//#else
//    gd_eval_key_init(KEY_USER, KEY_MODE_GPIO);
//#endif

//    gd_eval_key_init(KEY_TAMPER, KEY_MODE_EXTI);
}

/*!
    \brief      to get usb keyboard state
    \param[in]  none
    \param[out] none
    \retval     the char
*/
static uint8_t key_state (void)
{
//    /* have pressed tamper key */
//    if (!gd_eval_key_state_get(KEY_TAMPER)) {
//        return CHAR_A;
//    }

//    /* have pressed wakeup key */
//    if (!gd_eval_key_state_get(KEY_WAKEUP)) {
//        return CHAR_B;
//    }

//    /* have pressed user key */
//#ifdef GD32F30X_HD
//    if (!gd_eval_key_state_get(KEY_USER1)) {
//#else
//    if (!gd_eval_key_state_get(KEY_USER)) {
//#endif
//        return CHAR_C;
//    }

    /* no pressed any key */
    return 0U;
}

static uint16_t test = 0;
/*
 * buffer[0] - bit0: Left CTRL
 *           -bit1: Left SHIFT
 *           -bit2: Left ALT
 *           -bit3: Left GUI
 *           -bit4: Right CTRL
 *           -bit5: Right SHIFT
 *           -bit6: Right ALT
 *           -bit7: Right GUI 
 * buffer[1] - Padding = Always 0x00
 * buffer[2] - Key 1
 * buffer[3] - Key 2
 * buffer[4] - Key 3
 * buffer[5] - Key 4
 * buffer[6] - Key 5
 * buffer[7] - Key 6
 */
static void hid_key_data_send(usb_dev *udev)
{
    standard_hid_handler *hid = (standard_hid_handler *)udev->class_data[USBD_HID_INTERFACE];

    if (hid->prev_transfer_complete) {
//        switch (key_state()) {
//        case CHAR_A:
            hid->data[2] = 0x04U;
//            break;
//        case CHAR_B:
//            hid->data[2] = 0x05U;
//            break;
//        case CHAR_C:
//            hid->data[2] = 0x06U;
//            break;
//        default:
//            break;
//        }

//		buff_Mouse[1] = 2; //����һ�
//		//buff_Mouse[4] = 2; //����һ�
//		for(int i = 0;i < 5 ;i++)
//		{
//			hid->data[i] = buff_Mouse[i];
//		}
		
		
//		buff_Key[3] = 0x04u;
//		for(int i = 0;i < 9 ;i++)
//		{
//			hid->data[i] = buff_Key[i];
//		}

		buff_Audio[1] = 0x05u;
		for(int i = 0;i < 2 ;i++)
		{
			hid->data[i] = buff_Audio[i];
		}

		
        if (0U != hid->data[1] && (test == 0)) {
			test = 1;
            hid_report_send(udev, hid->data, 2);
			delay_1ms(2);
			hid->data[1] = 0;
			hid_report_send(udev, hid->data, 2);
        }
    }
}
