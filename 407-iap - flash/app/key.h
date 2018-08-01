#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 


#define KEYUP 		PFin(8)   	//PE4
#define KEYDN 		PFin(6)		//PE3 
#define KEYOK 		PFin(9)		//P32
//#define WK_UP 	PAin(0)		//PA0 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES	  3	//KEY2����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP)

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan();  		//����ɨ�躯��					    
#endif
