
/*
 * timer0_driver.h
 *
 * Created: 2/3/2024 6:52:57 AM
 *  Author: hp
 */ 
void timer0_ctc_init(char OCR0_value,unsigned char prescaler);

void timer0_wave_CTC_mode(char OCR0_value,unsigned char prescaler);

/*
	----------------------------------------------------------------
	----------------------------------------------------------------
	--------        COM1:0 = 2 non inverting mode	   -------------
	
	-------- signal frequency = Freq (MC)  / 256 * precaler --------
			 
	--------       OCR0_value = Duty cycle * 256		   ----------
	----------------------------------------------------------------
	----------------------------------------------------------------
*/
void timer0_fast_PWM (char OCR0_value,unsigned char prescaler);

/*
	----------------------------------------------------------------
	----------------------------------------------------------------
	--------        COM1:0 = 2 	   -------------
	
	-------- signal frequency = Freq (MC)  / 510 * precaler --------
			 
	--------       OCR0_value = Duty cycle * 255		   ----------
	----------------------------------------------------------------
	----------------------------------------------------------------
*/
void timer0_phase_correct (char OCR0_value,unsigned char prescaler);
