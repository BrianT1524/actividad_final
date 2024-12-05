#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

// Inicialización del RTC
void rtc_init(void);

// Establecimiento de la hora y fecha
void rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec);
void rtc_set_date(uint8_t day, uint8_t month, uint8_t year);

// Lectura de la hora y fecha
void rtc_get_time(uint8_t *hour, uint8_t *min, uint8_t *sec);
void rtc_get_date(uint8_t *day, uint8_t *month, uint8_t *year);

#endif // RTC_H_
