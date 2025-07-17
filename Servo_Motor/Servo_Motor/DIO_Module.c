/*
 * DIO_Module.c
 *
 * Created: 10/8/2023 12:07:52 AM
 *  Author: Ahmed
 */ 

/*
 * DIO_Module.c
 *
 * Created: 10/8/2023 12:07:52 AM
 *  Author: Ahmed
 */
#define DDRA  *((volatile unsigned char*)(0x3A))
#define DDRB  *((volatile unsigned char*)(0x37))
#define DDRC  *((volatile unsigned char*)(0x34))
#define DDRD  *((volatile unsigned char*)(0x31))

#define PORTA *((volatile unsigned char*)(0x3B))
#define PORTB *((volatile unsigned char*)(0x38))
#define PORTC *((volatile unsigned char*)(0x35))
#define PORTD *((volatile unsigned char*)(0x32))

#define PINA *((volatile unsigned char*)(0x39))
#define PINB *((volatile unsigned char*)(0x36))
#define PINC *((volatile unsigned char*)(0x33))
#define PIND *((volatile unsigned char*)(0x30))


void setBitDirection(char port , int bitNumber , char direction)
{
	if (direction == '1')
	{
		direction = 1;
	}else direction = 0;
	
	switch(port)
	{
		case 'A':
		case 'a':
			if (direction)
			{
				DDRA |= (1<<bitNumber);
			}
			else
			{
				DDRA &= ~(1<<bitNumber);
			}
			break;
			
		case 'B':
		case 'b':
			if (direction)
			{
				DDRB |= (1<<bitNumber);
			} 
			else
			{
				DDRB &= ~(1<<bitNumber);
			}
			break;
			
		case 'C':
		case 'c':
			if (direction)
			{
				DDRC |= (1<<bitNumber);
			} 
			else
			{
				 DDRC &= ~(1<<bitNumber);
			}
			break;
			
		case 'D':
		case 'd':
			if (direction)
			{
				 DDRD |= (1<<bitNumber);
			} 
			else
			{
				DDRD &= ~(1<<bitNumber);
			}
			break;
	}
}

void setBortDirection(char port , char direction)
{
	if (direction == '1')
	{
		direction = 0xff;
	}
	else
	{
		direction = 0;
	}
	switch(port)
	{
		case 'A':
		case 'a':
		DDRA = direction;
		break;
		
		case 'B':
		case 'b':
		DDRB = direction;
		break;
		
		case 'C':
		case 'c':
		DDRC = direction;
		break;
		
		case 'D':
		case 'd':
		DDRD = direction;
		break;
		default:
		break;
	}
}

void setBit(char port , int bitNumber)
{
	
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA |= (1<<bitNumber);
		break;
			
		case 'B':
		case 'b':
			PORTB |= (1<<bitNumber);
		break;
			
		case 'C':
		case 'c':
			PORTC |= (1<<bitNumber);
		break;
		
		case 'D':
		case 'd':
			PORTD |= (1<<bitNumber);
		break;
	}
}

void writePort(char port , char value)
{
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA = value;
		break;
		
		case 'B':
		case 'b':
			PORTB = value;
		break;
		
		case 'C':
		case 'c':
			PORTC = value;
		break;
		
		case 'D':
		case 'd':
			PORTD = value;
		break;
		default:
		break;
	}
}

void writeLow_4pins(char port, char value)
{
	value &= 0x0F;
	
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA &=0xF0;
			PORTA |=value;
		break;
		
		case 'B':
		case 'b':
			PORTB &=0xF0;
			PORTB |=value;
		break;
		
		case 'C':
		case 'c':
			PORTC &=0xF0;
			PORTC |=value;
		break;
		
		case 'D':
		case 'd':
			PORTD &=0xF0;
			PORTD |=value;
		break;
		
		default:
		break;
	}
}

void writeHigh_4pins(unsigned char port,unsigned char value)
{
	value = value << 4;
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA &= 0x0F;
			PORTA |= value;
		break;
		
		case 'B':
		case 'b':
			PORTB &= 0x0F;
			PORTB |= value;
		break;
		
		case 'C':
		case 'c':
			PORTC &= 0x0F;
			PORTC |= value;
		break;
		
		case 'D':
		case 'd':
			PORTD &= 0x0F;
			PORTD |= value;
		break;
		
		default:
		break;
	}
}

void clearBit(char port , int bitNumber)
{
	
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA &= ~(1<<bitNumber);
		break;
		
		case 'B':
		case 'b':
			PORTB &= ~(1<<bitNumber);
		break;
		
		case 'C':
		case 'c':
			PORTC &= ~(1<<bitNumber);
		break;
		
		case 'D':
		case 'd':
			PORTD &= ~(1<<bitNumber);
		break;
	}
}

void clearPort(char port)
{
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA = 0;
		break;
		
		case 'B':
		case 'b':
			PORTB = 0;
		break;
		
		case 'C':
		case 'c':
			PORTC = 0;
		break;
		
		case 'D':
		case 'd':
			PORTD = 0;
		break;
		default:
		break;
	}
	
}

void toggelBit(char port , int bitNumber)
{
	
	switch(port)
	{
		case 'A':
		case 'a':
			PORTA ^= (1<<bitNumber);
		break;
		
		case 'B':
		case 'b':
			PORTB ^= (1<<bitNumber);
		break;
		
		case 'C':
		case 'c':
			PORTC ^= (1<<bitNumber);
		break; 
		
		case 'D':
		case 'd':
			PORTD ^= (1<<bitNumber);
		break;
	
	}
}

void toggelPort(char port)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA ^= 1;
		break;
		
		case 'B':
		case 'b':
		PORTB ^= 1;
		break;
		
		case 'C':
		case 'c':
		PORTC ^= 1;
		break;
		
		case 'D':
		case 'd':
		PORTD ^= 1;
		break;
		default:
		break;
	}
}

unsigned char readBit(char port , int bitNumber)
{
	unsigned char pin;
	switch(port)
	{
		case 'A':
		case 'a':
			pin = (PINA & (1<<bitNumber))>>bitNumber;
		break;
		
		case 'B':
		case 'b':
			pin =  (PINB &(1<<bitNumber))>>bitNumber;
		break;
		
		case 'C':
		case 'c':
			pin  = (PINC & (1<<bitNumber))>>bitNumber;
		break;
		
		case 'D':
		case 'd':
			pin =  (PIND & (1<<bitNumber))>>bitNumber;
		break;
		
		default:
			return 0;
	}
	return pin;
}

unsigned char readPort (char port)
{
	unsigned char pins = 0;
	switch(port)
	{
		case 'A':
		case 'a':
		pins = PINA;
		break;
		
		case 'B':
		case 'b':
		pins = PINB;
		break;
		
		case 'C':
		case 'c':
		pins = PINC;
		break;
		
		case 'D':
		case 'd':
		pins = PIND;
		break;
		default:
		break;
	}
	return pins;
	
}

void pullUpConnect(char port , int bitNumber , char enable)
{
	if (enable == '1')
	{
		enable = 1;
	}
	else
	{
		enable = 0;
	}
	switch(port)
	{
		case 'A':
		case 'a':
			if (enable)
			{
				PORTA |= (1<<bitNumber);
			}
			else
			{
				PORTA &= ~(1<<bitNumber);
			}
		break;
		
		case 'B':
		case 'b':
			if (enable)
			{
				PORTB |= (1<<bitNumber);
			}
			else
			{
				PORTB &= ~(1<<bitNumber);
			}
		break;
		
		case 'C':
		case 'c':
			if (enable)
			{
				PORTC |= (1<<bitNumber);
			}
			else
			{
				PORTC &= ~(1<<bitNumber);
			}
		break;
		
		case 'D':
		case 'd':
			if (enable)
			{
				PORTD |= (1<<bitNumber);
			}
			else
			{
				PORTD &= ~(1<<bitNumber);
			}	
		break;
		
	}
}
