#ifndef _KEY_H
#define _KEY_H

#include  "gd32f30x.h"

#define KEYn                             1U

#define COL	8				// 列
#define ROW 16				// 行


#define KEY_PRESSED 0   // 按键按下状态

#define FILTER_VALUE 10

// 行 输出
static uint32_t KEY_PORT[ROW] = {GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,
								 GPIOC,GPIOC,GPIOC,GPIOC,
								 GPIOA,GPIOA,GPIOA,GPIOA};
static uint32_t KEY_PIN[ROW] = {GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_10,GPIO_PIN_11,GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15,
								GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_8,GPIO_PIN_9,
								GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11};

// 列  输入
static uint32_t COL_KEY_PORT[COL] = {GPIOA,GPIOA,GPIOA,GPIOA,GPIOA,GPIOC,GPIOC,GPIOB};
static uint32_t COL_KEY_PIN[COL] = {GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_0};

// 定义按键结构体
typedef struct {
    uint8_t state;      // 按键状态：按下为 KEY_PRESSED，弹起为 ~KEY_PRESSED
    uint8_t cnt;        // 按键计数器
    uint8_t filter;     // 滤波值
} KeyTypeDef;

typedef enum 
{
    KEY_USER = 0,
	KEY_27,
	KEY_28,
	KEY_29,
	KEY_30,
	KEY_31,
	KEY_32,
	KEY_33,
	KEY_34,
	KEY_35,
	KEY_36,
	KEY_37,
	KEY_38,
	KEY_39,
	KEY_40,
	KEY_41,
	KEY_42,
	KEY_43,
	KEY_44
} key_col_enum;

typedef enum 
{
    KEY_Test= 0,
	KEY_17,
	KEY_20,
	KEY_21,
	KEY_22,
	KEY_23,
	KEY_24,
	KEY_25,
	KEY_26
} key_row_enum;

typedef enum 
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1
} keymode_typedef_enum;
/* exported types */

extern uint8_t readBuffer[COL * ROW];
extern uint8_t sendBuffer[COL * ROW];

/* user push-button */
#define USER_KEY_PIN                     GPIO_PIN_15
#define USER_KEY_GPIO_PORT               GPIOB
#define USER_KEY_GPIO_CLK                RCU_GPIOB
#define USER_KEY_EXTI_LINE               EXTI_15
#define USER_KEY_EXTI_PORT_SOURCE        GPIO_PORT_SOURCE_GPIOB
#define USER_KEY_EXTI_PIN_SOURCE         GPIO_PIN_SOURCE_15
#define USER_KEY_EXTI_IRQn               EXTI10_15_IRQn

/* configure key */
void gd_key_init();
void KEY_MATRIX_Scan(uint16_t *data,uint16_t *isFnPress);
///* return the selected key state */
uint8_t gd_key_state_get(uint8_t key);
uint8_t key_filter(uint8_t key_id);
#endif
