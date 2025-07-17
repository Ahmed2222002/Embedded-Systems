/*
 * timer2_driver.h
 *
 * Created: 2/3/2024 4:43:30 PM
 *  Author: hp
 */ 


#ifndef TIMER2_DRIVER_H_
#define TIMER2_DRIVER_H_

void timer2_RTC_config();
void timer2_overflow_init_interrupt(void);
void timer2_ctc_init(char OCR2_value,unsigned char prescaler,char external_clk_source);

void timer2_wave_CTC_mode(char OCR2_value,unsigned char prescaler,char external_clk_source);

/*
	----------------------------------------------------------------
	----------------------------------------------------------------
	--------        COM1:0 = 2 non inverting mode	   -------------
	
	-------- signal frequency = Freq (MC)  / 256 * precaler --------
			 
	--------       OCR2_value = Duty cycle * 256		   ----------
	----------------------------------------------------------------
	----------------------------------------------------------------
*/
void timer2_fast_PWM (char OCR2_value,unsigned char prescaler,char external_clk_source);

/*
	----------------------------------------------------------------
	----------------------------------------------------------------
	--------        COM1:0 = 2 	   -------------
	
	-------- signal frequency = Freq (MC)  / 510 * precaler --------
			 
	--------       OCR2_value = Duty cycle * 255		   ----------
	----------------------------------------------------------------
	----------------------------------------------------------------
*/
void timer2_phase_correct (char OCR2_value,unsigned char prescaler,char external_clk_source);





#endif /* TIMER2_DRIVER_H_ */