#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define KEY_1_IO		PAin(4)
#define KEY_2_IO		PAin(8)	
#define KEY_3_IO		PBin(3)	
#define KEY_4_IO		PBin(4)
#define KEY_5_IO		PBin(5)
#define KEY_6_IO		PAin(15)	
#define KEY_7_IO		PBin(6)	
#define KEY_8_IO		PBin(7)	

#define KEY_1_MASK		0x01
#define KEY_2_MASK		0x02
#define KEY_3_MASK		0x04
#define KEY_4_MASK		0x08
#define KEY_5_MASK		0x10
#define KEY_6_MASK		0x20
#define KEY_7_MASK		0x40
#define KEY_8_MASK		0x80

extern uint8_t KeyValue;
extern int16_t logic_channel[];	

void Key_Init(void);
void Key_Scan(void);
void Key_Deal(void);

#endif

