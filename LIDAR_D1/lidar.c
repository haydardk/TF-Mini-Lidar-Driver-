#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "lidar.h"
#include  "stdint.h"

uint8_t lidar_buffer[];
double Lidar_Mesafe ; 
double Lidar_Guc ; 
uint8_t Dist_H , Dist_L , Strength_L , Strength_H , Lidar_Mode; 

void lidar_uart_setup(){
    PIO pio = pio1; // PIO PIN NUMARASINA GÖRE AYARLANACAK
    uint sm = 0;
    uint offset = pio_add_program(pio, &lidar_program);
    lidar_program_init(pio, sm, offset, PIO_RX_PIN, LIDAR_BAUD);
}

void lidar_configurate(){
    // BU FONKSİYON BLOĞU YALNIZCA BİR KEZ ÇALIŞTIRACAK
    /* Herhangi bir platform ile (STM32 ya da Pico) aşağıdaki mesajlar HEX kodu olarak UART 115200 baud rate ile lidara gönderilmeli 
        Distance Mode : 42 57 02 00 00 00 02 11 Short distance mode, applicable for 0-5m
    */
}

void lidar_process(uint8_t buffer[]){
    Dist_L = buffer[2];
    Dist_H = buffer[3];
    Lidar_Mesafe = (Dist_H << 8) | Dist_L; // MESAFE VERİSİ İŞLENİYOR

    Strength_L = buffer[4];
    Strength_H = buffer[5];
    Lidar_Guc = (Strength_H << 8) | Strength_L ; // SİNYAL GÜÇ VERİSİ İŞLENİYOR

    Lidar_Mode = buffer[6] // 02 Short(0-5m) - 07 Long (1-12m) 
}

void lidar_read_s(uint8_t buffer[]){
    buffer = lidar_program_gets(pio, sm);
}

void lidar_read_c(uint8_t buffer[]){
    int i;
    buffer[0] = lidar_program_getc(pio,sm);
    if (buffer[0]==0x59 ){
        for (i=1;i<9;i++){
            buffer[i] = liddar_program_getc(pio,sm);
            i++;
        }
    }else{
        lidar_read_c(buffer);
    }
}
    
