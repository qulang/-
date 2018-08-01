#include<spi.h>
void spi_init()
{
	RCC->AHB1ENR|=1<<1;    	//使能PORTA时钟	   
	RCC->APB2ENR|=1<<12;   	//SPI1时钟使能 
	GPIO_Set(GPIOB,7<<3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PB3~5复用功能输出	
	GPIO_Set(GPIOB,PIN1|PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PA15复用功能输出	
	
  GPIO_AF_Set(GPIOB,3,5);	//PB3,AF5
 	GPIO_AF_Set(GPIOB,4,5);	//PB4,AF5
 	GPIO_AF_Set(GPIOB,5,5);	//PB5,AF5 
	GPIO_AF_Set(GPIOA,15,5);	//PB5,AF5 
	
	RCC->APB2RSTR|=1<<12;	//复位SPI1
	RCC->APB2RSTR&=~(1<<12);//停止复位SPI1
	SPI1->CR1=0;
	SPI1->CR2=0;
	SPI1->CR2|=1<<2;
	SPI1->CR1|=0<<10;			//全双工模式	
	SPI1->CR1|=0<<9;			//硬件nss管理
	SPI1->CR1|=1<<8;			 
	SPI1->CR1|=1<<2;			//SPI主机  
	SPI1->CR1|=0<<11;			//8位数据格式	
	SPI1->CR1|=1<<1;			//空闲模式下SCK为1 CPOL=1 
	SPI1->CR1|=1<<0;			//数据采样从第2个时间边沿开始,CPHA=1  
 	//对SPI1属于APB2的外设.时钟频率最大为84Mhz频率.
	SPI1->CR1|=7<<3;			//Fsck=Fpclk1/256
	SPI1->CR1|=0<<7;			//MSB First  
	SPI1->CR1|=1<<6;			//SPI启动 
	SPI1->I2SCFGR&=~(1<<11);//选择SPI模式
	SPI1_ReadWriteByte(0xff);//启动传输
}
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
	while((SPI1->SR&1<<1)==0);		//等待发送区空 
	SPI1->DR=TxData;	 	  		//发送一个byte  
	while((SPI1->SR&1<<0)==0);		//等待接收完一个byte  
 	return SPI1->DR;          		//返回收到的数据				    
}

	
	
	