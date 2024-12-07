#include "rtc.h"
#include "i2c.h"
#include <stdarg.h>

#define DS1307_ADDRESS 0x68  


static uint8_t bcd_to_bin(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}


static uint8_t bin_to_bcd(uint8_t bin) {
    return ((bin / 10) << 4) | (bin % 10);
}

void rtc_init(void) {
    init_i2c(); 

}

void rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec) {
    start();
    write_i2c(DS1307_ADDRESS << 1 | 0);  
    write_i2c(0x00);  
    write_i2c(bin_to_bcd(sec));  
    write_i2c(bin_to_bcd(min));  
    write_i2c(bin_to_bcd(hour));  
    stop();
}

void rtc_set_date(uint8_t day, uint8_t month, uint8_t year) {
    start();
    write_i2c(DS1307_ADDRESS << 1);
    write_i2c(0x04);  
    write_i2c(bin_to_bcd(day));
    write_i2c(bin_to_bcd(month));
    write_i2c(bin_to_bcd(year %100));
    stop();
}

Time rtc_get_time(void) {
	Time time;
	start();
	write_i2c(DS1307_ADDRESS << 1);
	write_i2c(0x00); 
	start();
	write_i2c((DS1307_ADDRESS << 1) | 1); 
	time.seconds = bcd_to_bin(i2c_read_ack());
	time.minutes = bcd_to_bin(i2c_read_ack());
	time.hours = bcd_to_bin(i2c_read_nack());
	stop();
	return time;
}

Date rtc_get_date(void) {
	Date date;
	start();
	write_i2c(DS1307_ADDRESS << 1);
	write_i2c(0x04); 
	start();
	write_i2c((DS1307_ADDRESS << 1) | 1); 
	date.day = bcd_to_bin(i2c_read_ack());
	date.month = bcd_to_bin(i2c_read_ack());
	date.year = 2000 + bcd_to_bin(i2c_read_nack());
	stop();
	return date;
}
