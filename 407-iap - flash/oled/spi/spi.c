#include<spi.h>
void spi_init()
{
	RCC->AHB1ENR|=1<<1;    	//ʹ��PORTAʱ��	   
	RCC->APB2ENR|=1<<12;   	//SPI1ʱ��ʹ�� 
	GPIO_Set(GPIOB,7<<3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB3~5���ù������	
	GPIO_Set(GPIOB,PIN1|PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PA15���ù������	
	
  GPIO_AF_Set(GPIOB,3,5);	//PB3,AF5
 	GPIO_AF_Set(GPIOB,4,5);	//PB4,AF5
 	GPIO_AF_Set(GPIOB,5,5);	//PB5,AF5 
	GPIO_AF_Set(GPIOA,15,5);	//PB5,AF5 
	
	RCC->APB2RSTR|=1<<12;	//��λSPI1
	RCC->APB2RSTR&=~(1<<12);//ֹͣ��λSPI1
	SPI1->CR1=0;
	SPI1->CR2=0;
	SPI1->CR2|=1<<2;
	SPI1->CR1|=0<<10;			//ȫ˫��ģʽ	
	SPI1->CR1|=0<<9;			//Ӳ��nss����
	SPI1->CR1|=1<<8;			 
	SPI1->CR1|=1<<2;			//SPI����  
	SPI1->CR1|=0<<11;			//8λ���ݸ�ʽ	
	SPI1->CR1|=1<<1;			//����ģʽ��SCKΪ1 CPOL=1 
	SPI1->CR1|=1<<0;			//���ݲ����ӵ�2��ʱ����ؿ�ʼ,CPHA=1  
 	//��SPI1����APB2������.ʱ��Ƶ�����Ϊ84MhzƵ��.
	SPI1->CR1|=7<<3;			//Fsck=Fpclk1/256
	SPI1->CR1|=0<<7;			//MSB First  
	SPI1->CR1|=1<<6;			//SPI���� 
	SPI1->I2SCFGR&=~(1<<11);//ѡ��SPIģʽ
	SPI1_ReadWriteByte(0xff);//��������
}
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
	while((SPI1->SR&1<<1)==0);		//�ȴ��������� 
	SPI1->DR=TxData;	 	  		//����һ��byte  
	while((SPI1->SR&1<<0)==0);		//�ȴ�������һ��byte  
 	return SPI1->DR;          		//�����յ�������				    
}

	
	
	