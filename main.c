#include <avr/io.h>
#include <util/delay.h>
#include "rtc.h"
#include "lcd_i2c.h"



int main(void) {
    uint8_t hour, minute, second;
    uint8_t day, month, year;

    // Inicialización de los módulos
    lcd_i2c_init();  // Inicializa el LCD
    rtc_init();  // Inicializa el RTC

    while (1) {
        // Obtener la hora actual del RTC
        rtc_get_time(&hour, &minute, &second);
        rtc_get_date(&day, &month, &year);

        // Limpia el LCD y muestra la hora y fecha
        lcd_i2c_clr();
        lcd_i2c_col_row(0, 0);  // Posiciona el cursor en la primera línea
        lcd_i2c_write_string("Hora: ");
        lcd_i2c_write_int(hour,2);
        lcd_i2c_write_string(":");
        lcd_i2c_write_int(minute,2);
        lcd_i2c_write_string(":");
        lcd_i2c_write_int(second,2);

        lcd_i2c_col_row(0, 1);  // Posiciona el cursor en la segunda línea
        lcd_i2c_write_string("Fecha: ");
        lcd_i2c_write_int(day,2);
        lcd_i2c_write_string("/");
        lcd_i2c_write_int(month,2);
        lcd_i2c_write_string("/");
        lcd_i2c_write_int(year % 100,4);  // Solo mostrar los dos últimos dígitos del año

        _delay_ms(1000);  // Actualiza cada segundo
    }

    return 0;
}
