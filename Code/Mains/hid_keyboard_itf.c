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

//第一个字为ReportID:3，字节2的0000 0xxx后三位分别表示中间单击，右键单击，左键单机
//字节3为x轴移动距离，字节4为y轴移动距离，字节5为滚轮移动值 其范围为-127~127
uint8_t buff_Mouse[5]={0x03,0x00,0x00,0x00,0x00};

//多媒体发送数组，根据HID报告描述符的定义，第一个字节位ReportID:2,
//第二个字节从高到低，每一位分别对应：
/*	      Bit 功能 
					0   音量升高
					1   音量减小
					2   静音
					3   播放/暂停
					4   暂停
					5   下一首
					6   上一首
					7   退出播放
*/
//更多的操作在HID描述符中添加，参考HID Usage Tables的15节Consumer Page
//0x01即表示音量升高
uint8_t buff_Audio[2]={0x02,0x00};

//键盘发送数据
//字节1为ReportID:1，字节2为功能键盘，每一位对应一个按键，
/*  更详细的规定参考文档Device Class Definition for HID的8.3节
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
//字节3保留，字节4-9表示表示按键键值，
//每个按键对于的值可在HID Usage Tables文档中的第10节查询
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

//		buff_Mouse[1] = 2; //鼠标右击
//		//buff_Mouse[4] = 2; //鼠标右击
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
