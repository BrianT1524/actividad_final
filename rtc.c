#include "rtc.h"
#include "i2c.h"

#define DS1307_ADDRESS 0x68  // Dirección I2C del DS1307

// Función para convertir de formato BCD a binario
static uint8_t bcd_to_bin(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// Función para convertir de binario a BCD
static uint8_t bin_to_bcd(uint8_t bin) {
    return ((bin / 10) << 4) | (bin % 10);
}

void rtc_init(void) {
    init_i2c();  // Asegúrate de que el bus I2C esté inicializado
}

void rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec) {
    start();
    write_i2c(DS1307_ADDRESS << 1 | 0);  // Escribir dirección con bit de escritura
    write_i2c(0x00);  // Dirección del registro de segundos
    write_i2c(bin_to_bcd(sec));  // Configurar segundos
    write_i2c(bin_to_bcd(min));  // Configurar minutos
    write_i2c(bin_to_bcd(hour));  // Configurar hora
    stop();
}

void rtc_set_date(uint8_t day, uint8_t month, uint8_t year) {
    start();
    write_i2c(DS1307_ADDRESS << 1 | 0);
    write_i2c(0x04);  // Dirección del registro de día
    write_i2c(bin_to_bcd(day));
    write_i2c(bin_to_bcd(month));
    write_i2c(bin_to_bcd(year));
    stop();
}

void rtc_get_time(uint8_t *hour, uint8_t *min, uint8_t *sec) {
    start();
    write_i2c(DS1307_ADDRESS << 1 | 0);
    write_i2c(0x00);  // Dirección del registro de segundos
    start();
    write_i2c(DS1307_ADDRESS << 1 | 1);  // Modo de lectura
    *sec = bcd_to_bin(read_i2c() & 0x7F);  // Leer segundos y convertir de BCD a binario
    *min = bcd_to_bin(read_i2c() & 0x7F);  // Leer minutos
    *hour = bcd_to_bin(read_i2c() & 0x3F);  // Leer hora (formato 24 horas)
    stop();
}

void rtc_get_date(uint8_t *day, uint8_t *month, uint8_t *year) {
    start();
    write_i2c(DS1307_ADDRESS << 1 | 0);
    write_i2c(0x04);  // Dirección del registro de día
    start();
    write_i2c(DS1307_ADDRESS << 1 | 1);
    *day = bcd_to_bin(read_i2c());
    *month = bcd_to_bin(read_i2c());
    *year = bcd_to_bin(read_i2c());
    stop();
}
