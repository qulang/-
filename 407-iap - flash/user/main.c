#include "main.h"
u8 name[20][10];
u8 n=0;



__align(32) u8 buffers[70*1024] __attribute__ ((at(0X20001000)));     //���ջ���,���USART_REC_LEN���ֽ�.
typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.  

#define FLASH_APP1_ADDR		0x08040000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)


iapfun jump2app; 


void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ xianshi("kaishi\n",0);
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2app();									//��ת��APP.
		xianshi("shibai",0);
	}
	else xianshi("zhixingshibai\n",0);
}	

int main(void)
{
	u32 total,free;
	u8 i,k;
	u8 res=0;	
	u32 applen;
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
//	uart_init(84,115200);		//��ʼ�����ڲ�����Ϊ115200 
	KEY_Init();
 	LCD_Init();					//LCD��ʼ��
	LCD_Color(RED,GRED);  
	
					
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
	while(SD_Init())//��ⲻ��SD��
	{
		LCD_ShowString(30,150,16,"SD Card Error!");
	}
	exfuns_init();							//Ϊfatfs��ر��������ڴ�
	
	
	
	f_mount(fs[0],"0:",1); 					//����SD�� 
									    
	LCD_Clear(YELLOW);		//�����ʾ			  
	while(exf_getfree("0",&total,&free))	//�õ�SD������������ʣ������
	{
		LCD_ShowString(30,150,16,"SD Card Fatfs Error!");
		delay_ms(200);
	}	
	
	
	xianshi("SD Total Size:(MB)",total>>10);
	xianshi("SD Free Size:(MB)",free>>10);
	xianshi("read:",0);
	//xianshi(name[n],0);
	 mf_scan_files("0:");
	//xianshi("sd wenjianruxia:",n);
	for(i=0;i<n;i++)
	{
		xianshi(name[i],i);	
	}
	i=0;
	xianshi("wenjian:   ",i);
	while(1)
	{
	//	LCD_ShowNum(30+11*8,yy,i,3,16,1);
		k=KEY_Scan();
		if(k)
		{
			if(k==1) i++;
			if(k==2) i--;
			if(k==3) break;
			if(i<0) i=0;
			if(i>=n) i=n-1;
		}
//		LCD_ShowString(10+11*8,yy,16,"                                                       ");
		LCD_ShowString(10+11*8,yy,16,name[i]);	
		LCD_ShowString(10+11*8+strlen(name[i])*8,yy,16,"                                                       ");
		delay_ms(200);
	};
	xianshi("namew is:  ",0);
	LCD_ShowString(10+11*8,yy,16,"                                                       ");
	LCD_ShowString(10+11*8,yy,16,name[i]);
	res = mf_open(name[i],FA_READ | FA_WRITE);
	applen=mf_size();
	xianshi("wenjiandaxiao:",applen);
  mf_read(applen);
	xianshi("wancheg",0);

	INTX_DISABLE();//�ر������ж�
	
				xianshi("kaishi",0);
 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
				{	 
					iap_write_appbin(FLASH_APP1_ADDR,buffers,applen);//����FLASH����   
					xianshi("successed!!",0);
				
				}else 
				{
					xianshi("errr1",0);	   
				}
				
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
			{	 xianshi("zhixing",0);
				iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
			}else 
			{
				xianshi("errr2!",0);
				
			}				
				
				
				while(1);
	while(1);
}
