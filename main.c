#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd_i2c.h"
#include "i2c.h"
#include "rtc.h"


int main(void)
{
	
	init_i2c();
	lcd_i2c_init();
	rtc_init();	
	lcd_i2c_clr();
	rtc_set_date(7, 12, 24); 
    rtc_set_time(16, 26, 0);   
	
    
    while (1) 
	{
		Time time = rtc_get_time();
		Date date = rtc_get_date();
		
		lcd_i2c_col_row(3, 1);
		lcd_i2c_printf("Hora - ");
		lcd_i2c_printf("%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
		
		lcd_i2c_col_row(2, 2);
		lcd_i2c_printf("Fecha - ");
		lcd_i2c_printf("%02d/%02d/%04d", date.day, date.month, date.year);

		_delay_ms(1000); 
    }
	
}
