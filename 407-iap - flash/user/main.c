#include "main.h"
u8 name[20][10];
u8 n=0;



__align(32) u8 buffers[70*1024] __attribute__ ((at(0X20001000)));     //接收缓冲,最大USART_REC_LEN个字节.
typedef  void (*iapfun)(void);				//定义一个函数类型的参数.  

#define FLASH_APP1_ADDR		0x08040000  	//第一个应用程序起始地址(存放在FLASH)


iapfun jump2app; 


void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ xianshi("kaishi\n",0);
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(vu32*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
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
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
//	uart_init(84,115200);		//初始化串口波特率为115200 
	KEY_Init();
 	LCD_Init();					//LCD初始化
	LCD_Color(RED,GRED);  
	
					
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	
	while(SD_Init())//检测不到SD卡
	{
		LCD_ShowString(30,150,16,"SD Card Error!");
	}
	exfuns_init();							//为fatfs相关变量申请内存
	
	
	
	f_mount(fs[0],"0:",1); 					//挂载SD卡 
									    
	LCD_Clear(YELLOW);		//清除显示			  
	while(exf_getfree("0",&total,&free))	//得到SD卡的总容量和剩余容量
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

	INTX_DISABLE();//关闭所有中断
	
				xianshi("kaishi",0);
 				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
				{	 
					iap_write_appbin(FLASH_APP1_ADDR,buffers,applen);//更新FLASH代码   
					xianshi("successed!!",0);
				
				}else 
				{
					xianshi("errr1",0);	   
				}
				
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
			{	 xianshi("zhixing",0);
				iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
			}else 
			{
				xianshi("errr2!",0);
				
			}				
				
				
				while(1);
	while(1);
}
