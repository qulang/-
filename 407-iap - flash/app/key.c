#include "key.h"
#include "delay.h" 
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<5;     //使能PORTE时钟
	GPIO_Set(GPIOF,PIN6|PIN7|PIN8|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//PE2~4设置上拉输入
} 

void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_F,6,FTIR); 		//下降沿触发
	Ex_NVIC_Config(GPIO_F,8,FTIR); 		//下降沿触发
	Ex_NVIC_Config(GPIO_F,9,FTIR); 		//下降沿触发
	MY_NVIC_Init(3,2,EXTI9_5_IRQn,2);		//抢占3，子优先级2，组2
	
}


u8 KEY_Scan()
{	 
	
	if((KEYUP==0||KEYDN==0||KEYOK==0))
	{
		delay_ms(10);//去抖动 
		if(KEYUP==0)return 1;
		else if(KEYDN==0)return 2;
		else if(KEYOK==0)return 3;
	} 	    
 	return 0;// 无按键按下
}

void EXTI9_5_IRQHandler()
{
	delay_ms(10);	//消抖
	


}
