#include "key.h"

/* private variables */
static rcu_periph_enum KEY_CLK[KEYn] = {USER_KEY_GPIO_CLK};

static exti_line_enum KEY_EXTI_LINE[KEYn] = {USER_KEY_EXTI_LINE};

static uint8_t KEY_PORT_SOURCE[KEYn] = {USER_KEY_EXTI_PORT_SOURCE};
static uint8_t KEY_PIN_SOURCE[KEYn] = {USER_KEY_EXTI_PIN_SOURCE};

static uint8_t KEY_IRQn[KEYn] = {USER_KEY_EXTI_IRQn};

KeyTypeDef keys_f[COL];

enum KeyCode_t
{
	/*------------------------- HID report data -------------------------*/
	LEFT_CTRL = -8,LEFT_SHIFT = -7,LEFT_ALT = -6,LEFT_GUI = -5,
	RIGHT_CTRL = -4,RIGHT_SHIFT = -3,RIGHT_ALT = -2,RIGHT_GUI = -1,

	RESERVED = 0,ERROR_ROLL_OVER,POST_FAIL,ERROR_UNDEFINED,
	A,B,C,D,E,F,G,H,I,J,K,L,M,
	N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	NUM_1/*1!*/,NUM_2/*2@*/,NUM_3/*3#*/,NUM_4/*4$*/,NUM_5/*5%*/,
	NUM_6/*6^*/,NUM_7/*7&*/,NUM_8/*8**/,NUM_9/*9(*/,NUM_0/*0)*/,
	ENTER,ESC,BACKSPACE,TAB,SPACE,
	MINUS/*-_*/,EQUAL/*=+*/,LEFT_U_BRACE/*[{*/,RIGHT_U_BRACE/*]}*/,
	BACKSLASH/*\|*/,NONE_US/**/,SEMI_COLON/*;:*/,QUOTE/*'"*/,
	GRAVE_ACCENT/*`~*/,COMMA/*,<*/,PERIOD/*.>*/,SLASH/*/?*/,
	CAP_LOCK,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
	PRINT,SCROLL_LOCK,PAUSE,INSERT,HOME,PAGE_UP,DELETE,END,PAGE_DOWN,
	RIGHT_ARROW,LEFT_ARROW,DOWN_ARROW,UP_ARROW,PAD_NUM_LOCK,
	PAD_SLASH,PAD_ASTERISK,PAD_MINUS,PAD_PLUS,PAD_ENTER,
	PAD_NUM_1,PAD_NUM_2,PAD_NUM_3,PAD_NUM_4,PAD_NUM_5,
	PAD_NUM_6,PAD_NUM_7,PAD_NUM_8,PAD_NUM_9,PAD_NUM_0,
	PAD_PERIOD , NONUS_BACKSLASH,APPLICATION,POWER,PAD_EQUAL,
	F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24, EXECUTE,
	HELP,MENU,SELECT,STOP,AGAIN,UNDO,CUT,COPY,PASTE,FIND,MUTE,VOLUME_UP,VOLUME_DOWN,
	FN = 1000
	/*------------------------- HID report data -------------------------*/
};
	
int16_t keyMap[COL][ROW] = 
{
	{F6,A,GRAVE_ACCENT,Y,P,7,G,B},
	{F7,S,MINUS,U,LEFT_U_BRACE,8,H,N},
	{F8,D,EQUAL,O,RIGHT_U_BRACE,9,QUOTE,M},
	{F9,F,5,I,BACKSLASH,0,-1,COMMA},
	{F10,TAB,6,LEFT_ARROW,RIGHT_ARROW,UP_ARROW,-1,DOWN_ARROW},
	{F11,Q,J,-1,-1,DELETE,-1,-1},
	{F12,W,K,-1,-1,-1,-1,CAP_LOCK},
	{-1,E,L,-1,-1,-1,-1,MENU},
	{-1,R,SEMI_COLON,BACKSPACE,-1,-1,-1,-1},
	{-1,T,PERIOD,-1,RIGHT_ALT,-1,-1,-1},
	{Z,SPACE,SLASH,-1,-1,-1,-1,FN},
	{X,F1,1,-1,-1,RIGHT_GUI,-1,-1},
	{C,F2,2,RIGHT_GUI,-1,-1,-1,-1},
	{V,F3,3,-1,LEFT_ALT,-1,-1,-1},
	{ENTER,F4,4,-1,-1,-1,-1,-1},
	{ESC,F5,-1,-1,-1,-1,LEFT_CTRL}
};

int16_t keyIO[COL][ROW] = 
{
	{F6,A,GRAVE_ACCENT,Y,P,7,G,B},
	{F7,S,MINUS,U,LEFT_U_BRACE,8,H,N},
	{F8,D,EQUAL,O,RIGHT_U_BRACE,9,QUOTE,M},
	{F9,F,5,I,BACKSLASH,0,-1,COMMA},
	{F10,TAB,6,LEFT_ARROW,RIGHT_ARROW,UP_ARROW,-1,DOWN_ARROW},
	{F11,Q,J,-1,-1,DELETE,-1,-1},
	{F12,W,K,-1,-1,-1,-1,CAP_LOCK},
	{-1,E,L,-1,-1,-1,-1,MENU},
	{-1,R,SEMI_COLON,BACKSPACE,-1,-1,-1,-1},
	{-1,T,PERIOD,-1,RIGHT_ALT,-1,-1,-1},
	{Z,SPACE,SLASH,-1,-1,-1,-1,FN},
	{X,F1,1,-1,-1,RIGHT_GUI,-1,-1},
	{C,F2,2,RIGHT_GUI,-1,-1,-1,-1},
	{V,F3,3,-1,LEFT_ALT,-1,-1,-1},
	{ENTER,F4,4,-1,-1,-1,-1,-1},
	{ESC,F5,-1,-1,-1,-1,LEFT_CTRL}
};

/*!
    \brief      configure key
    \param[in]  key_num: specify the key to be configured
      \arg        KEY_TAMPER: tamper key
      \arg        KEY_WAKEUP: wakeup key
      \arg        KEY_USER: user key
    \param[in]  key_mode: specify button mode
      \arg        KEY_MODE_GPIO: key will be used as simple IO
      \arg        KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
    \param[out] none
    \retval     none
*/
void gd_key_init()
{
    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_AF);
	

    /* configure button pin as input */	
	{
		// 输入
		gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_3);
		gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
		gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
		gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
		gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
		
		gpio_init(GPIOC,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
		gpio_init(GPIOC,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
		
		gpio_init(GPIOB,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_0);
	}
	
	{
		// 输出 键盘
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_1);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_2);		
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_12);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_13);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_14);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_15);
		
		gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
		gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
		gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_8);
		gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
		
		gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_8);
		gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
		gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
		gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
		
		// LED
		gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_12);
		gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_3);
	}
	
	{
		// pwm
		gpio_init(GPIOB,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
	}
	

	{
		// PB8 外部中断
		/* enable and set key EXTI interrupt to the lowest priority */
		nvic_irq_enable(EXTI5_9_IRQn, 2U, 0U);

		/* connect key EXTI line to key GPIO pin */
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_8);

		/* configure key EXTI line */
		exti_init(EXTI_8, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
		exti_interrupt_flag_clear(EXTI_8);
	} 

	{
		// 初始化所有按键结构体
		for (int i = 0; i < COL; i++) 
		{
			keys_f[i].state = ~KEY_PRESSED;
			keys_f[i].cnt = 0;
			keys_f[i].filter = 0;
		}
	}
}

/******************************************************************************
 * 函  数： Activate_ROW
 * 功  能： 按键矩阵行电压变化
 * 参  数： 无
 ******************************************************************************/ 
void Activate_ROW(uint8_t row, uint8_t status)
{	
	gpio_bit_write(KEY_PORT[row],KEY_PIN[row],status ? SET : RESET);
}

/******************************************************************************
 * 函  数： Activate_ROW
 * 功  能： 按键矩阵全部行电压一起变化
 * 参  数： 无
 ******************************************************************************/ 
void Activate_ALL_ROW(uint8_t status)
{
	int row;
	for (row = 0; row < ROW; row++) 		
		Activate_ROW(row, status);
}

// col输出高/低电平，检测raw电平
void KEY_MATRIX_Scan(uint16_t *data,uint16_t *isFnPress)
{
	uint8_t row = 0,col = 0,index = 0;
	//所有行电平置零复位
	Activate_ALL_ROW(0);
	for(row = 0; row < ROW; row++)
	{ 
		Activate_ROW(row, 1);
		delay_1ms(1);
		for(col = 0; col < COL; col++)
		{
			//检测到高电平
			if(gpio_input_bit_get(COL_KEY_PORT[col],COL_KEY_PIN[col]) == 1)
			{
				if(key_filter(col))
				{
					data[index] = (row << 8) + col;
				}
			}
		}
		Activate_ROW(row, 0);
	}
	//所有行电平置零复位
	Activate_ALL_ROW(0);
}

/*!
    \brief      return the selected key state
    \param[in]  key: specify the key to be checked
      \arg        KEY_TAMPER: tamper key
      \arg        KEY_WAKEUP: wakeup key
      \arg        KEY_USER: user key
    \param[out] none
    \retval     the key's GPIO pin value
*/
uint8_t gd_key_state_get(uint8_t key)
{
    return gpio_input_bit_get(KEY_PORT[key], KEY_PIN[key]);
}

uint8_t key_filter(uint8_t key_id)
{
    uint8_t new_state = gd_key_state_get(key_id);    // 读取按键状态
    if (new_state == keys_f[key_id].state) 			// 如果状态未改变
	{         
        if (keys_f[key_id].cnt < 255) 
		{
            keys_f[key_id].cnt++;                     // 计数器加1
        }
    } 
	else 
	{                                        // 如果状态发生改变
        keys_f[key_id].state = new_state;             // 更新按键状态
        keys_f[key_id].cnt = 0;                       // 重置计数器
    }
	
    if (keys_f[key_id].cnt >= FILTER_VALUE) 		// 如果计数器达到滤波值
	{         
        keys_f[key_id].filter = keys_f[key_id].state;   // 使用当前状态作为滤波结果
    }
    return keys_f[key_id].filter;                     // 返回滤波后的结果
}
