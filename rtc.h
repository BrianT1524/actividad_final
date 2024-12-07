#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include <avr/io.h>

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
} Time;

typedef struct {
	uint8_t day;
	uint8_t month;
	uint16_t year;
} Date;

void rtc_init(void);
void rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec);
void rtc_set_date(uint8_t day, uint8_t month, uint8_t year);
Time rtc_get_time(void);
Date rtc_get_date(void);
#endif // RTC_H_
