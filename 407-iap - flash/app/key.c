#include "key.h"
#include "delay.h" 
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<5;     //ʹ��PORTEʱ��
	GPIO_Set(GPIOF,PIN6|PIN7|PIN8|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//PE2~4������������
} 

void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_F,6,FTIR); 		//�½��ش���
	Ex_NVIC_Config(GPIO_F,8,FTIR); 		//�½��ش���
	Ex_NVIC_Config(GPIO_F,9,FTIR); 		//�½��ش���
	MY_NVIC_Init(3,2,EXTI9_5_IRQn,2);		//��ռ3�������ȼ�2����2
	
}


u8 KEY_Scan()
{	 
	
	if((KEYUP==0||KEYDN==0||KEYOK==0))
	{
		delay_ms(10);//ȥ���� 
		if(KEYUP==0)return 1;
		else if(KEYDN==0)return 2;
		else if(KEYOK==0)return 3;
	} 	    
 	return 0;// �ް�������
}

void EXTI9_5_IRQHandler()
{
	delay_ms(10);	//����
	


}
