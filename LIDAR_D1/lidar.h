#define LIDAR_BAUD 115200
#define HARD_UART_INST uart2 // AYARLANACAK
#define PIO_RX_PIN 3 // AYARLANACAK

#define SHORT_MODE_MESSAGE 4257020000000211

/*Byte0-1 Byte2 Byte3 Byte4 Byte5 Byte6 Byte7 Byte8
0x59 59 Dist_L Dist_H Strength_L Strength_H Mode 0x00 CheckSum*/

/*Mode, distance mode, represented respectively by 02 (short distance) and 07 (long distance),
automatically switchable by default*/
/*42 57 02 00 00 00 02 11 Short distance mode, applicable for 0-5m
42 57 02 00 00 00 07 11 Long distance mode, applicable for 1-12m */

void lidar_uart_setup(void);
void lidar_configurate(void);
void lidar_process(uint8_t buffer[]);
void lidar_read_c(uint8_t buffer[]);
void lidar_read_s(uint8_t buffer[]);

