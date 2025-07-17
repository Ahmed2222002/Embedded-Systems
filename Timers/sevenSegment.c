/*
 * sevenSegment.c
 *
 * Created: 10/20/2023 7:33:36 AM
 *  Author: Ahmed Hussien
 */ 
/*
sevenSegmentType = 1 : this mean that connected to 8-pins of any port and the type is common cathode
sevenSegmentType = 2 : this mean that connected to 8-pins of any port and the type is common Anode
sevenSegmentType = 3 : this mean that connected to first 4-pins of any port (you need to connect BCD to seven segment decoder)
sevenSegmentType = 4 : this mean that connected to last 4-pins of any port (you need to connect BCD to seven segment decoder)

Any other value will generate warning
*/
#define sevenSegmentType 1
#include "DIO_Module.h"
void sevenSegmentInitialize(char port)
{
	#if (sevenSegmentType  == 1 || sevenSegmentType == 2)
		setBortDirection(port,'1');
	#elif (sevenSegmentType == 3)
		for(char i = 0 ; i < 4 ; i++)
		{
			setBitDirection(port,i,'1');
		}
	#elif (sevenSegmentType == 4)
		for(char i = 4 ; i < 8 ; i++)
		{
			setBitDirection(port,i,'1');
		}
		
	#else
	#warning "Unexpected value for macro sevensegment type please check it in sevenSegment.c file"
	#endif
}

void sevenSegmentWrite(char port , char number)
{
	#if (sevenSegmentType == 1)
		number = number > 9 ? 9:number;
		char numbers [10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f};
		writePort(port , numbers[(int)number]);
		
	#elif (sevenSegmentType == 2)
		number = number > 9 ? 9:number;
		char numbers [10] = {~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x47,~0x7f,~0x6f};
		writePort(port , numbers[(int)number]);
		
	#elif (sevenSegmentType == 3)
		writeLow_4pins(port,number);
		
		
	#elif (sevenSegmentType == 4)
		writeHigh_4pins(port,number);
	#else
	#warning "Unexpected value for macro sevensegment type please check it in sevenSegment.c file"
		
	#endif
}