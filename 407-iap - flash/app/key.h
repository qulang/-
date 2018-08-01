#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 


#define KEYUP 		PFin(8)   	//PE4
#define KEYDN 		PFin(6)		//PE3 
#define KEYOK 		PFin(9)		//P32
//#define WK_UP 	PAin(0)		//PA0 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	  2	//KEY1按下
#define KEY2_PRES	  3	//KEY2按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP)

void KEY_Init(void);	//IO初始化
u8 KEY_Scan();  		//按键扫描函数					    
#endif
