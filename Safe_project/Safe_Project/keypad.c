/*
 * keypad.c
 *
 * Created: 11/30/2023 6:31:24 PM
 *  Author: hp
 */ 
#define connected_port 'D'
#include "DIO_Module.h"

void keypadInitialization()
{
	char i ;
	//make first 4 pins output pins
	for (i = 0 ; i<4 ; i++)
	{
		setBitDirection(connected_port,(int)i , '1');
	}
	//make last 4 pins input pins and enable internal pull up
	for (i = 4 ; i<8 ; i++)
	{
		setBitDirection(connected_port,(int)i , '0');
		pullUpConnect(connected_port,(int)i , '1');
	}
}

unsigned char keypadRead()
{
	/*
	hardware ?? ?????
	{{'1','2','3','/'},
	{'4','5','6','c'},
	{'7','8','9','-'},
	{'*','0','=','+'}
    };
	software
	{{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}
     };
	
	*/
	char arr[4][4] ={{'7','8','9','/'},
					{'4','5','6','*'},
					{'1','2','3','-'},
					{'c','0','=','+'}
				    };
	char row , col , val = 'Z';			  
    for (row = 0 ; row < 4 ; row ++)
    {
		setBit(connected_port,0);
		setBit(connected_port,1);
		setBit(connected_port,2);
		setBit(connected_port,3);
		clearBit(connected_port,(int)row);
		for (col = 0 ; col < 4 ; col++)
		{
			if (readBit(connected_port,(col+4)) == 0)
			{
				val = arr[row][col];
				break;
			}
		}
		if (val != 'Z')
		{
			break;
		}	
    }
	return val;
}