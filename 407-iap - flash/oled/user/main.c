#include "sys.h"
#include "delay.h"
#include "spi.h"
#include "oled.h"
int main(void )
{
	SDIO->ICR=0xc0037f;
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化 
	RCC->AHB1ENR|=0xff; 
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PA15复用功能输出	
	PEout(3);
	PEout(4);
	
	spi_init();
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,0,"1234567890");
	OLED_ShowString(0,20,"1234567890");
	OLED_Refresh_Gram();	
	while(1) // 死循环
	   {
			
				 	
	   } 
	
}

