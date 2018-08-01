#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "spi.h"

//-----------------OLED???迆?“辰?---------------- 


#define OLED_RS     PBout(1)   //DC --dc
#define OLED_RST		PBout(0)   //RST--res
//cs?????車米?

#define OLED_CMD  0	//D∩?邦芍?
#define OLED_DATA 1	//D∩那y?Y


//OLED????車?o‘那y
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   				   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p);	 
#endif  
	 
