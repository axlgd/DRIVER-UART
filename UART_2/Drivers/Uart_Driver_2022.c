 // FileName:        Uart_Driver_2022.c
 // Dependencies:	 Uart_Driver_2022.h
 // Processor:       32-bit Xtensa LX6
 // Board:           ESP32 DEVKIT V1 (30 pins)
 // Program version: Espressif IDE
 // Company:         Espressif Systems
 // Description:     Funciones de control de HW a través de estructuras.
 // Authors:         Anahí González Holguín
 //					 Axel Gay Díaz
 //					 Carlos González Vázquez
 //					 Carlos López Lara
 // Updated:         12/2022

#pragma once

 //Librerías necesarias
#include <stdio.h>
#include <stdlib.h>
#include "C:\UART_2\Drivers\Uart_Driver_2022.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

/**************************************************************************
* Function: uart_config
* Preconditions: Ninguna.
* Overview: Accede a los registros por medio de una estructura para configurar la UART.
* Input: Ninguno.
* Output: Ninguno.
*
*****************************************************************************/

//	En este caso está configurada para:
void uart_config(void)
{
	uart_config_t uart_config = {
        .baud_rate = BAUD_RATE, //Baud Rate 115 200
        .data_bits = DATA_BITS, //8 bits de datos
        .parity    = PARITY,	//Sin paridad
        .stop_bits = STOP_BITS,	//1 bit de paro
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    //Instalación del driver para la UART
    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    //Confirmación de la configuración de la UART con la estructura antes definida
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
    //SETTER de los pines RXD, TXD y el número de puerto de la UART.
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));
}

/**************************************************************************
* Function: uart_read
* Preconditions: data, len.
* Overview: Permite recibir información vía UART desde otra terminal.
* Input: *data. Dirección de memoria de la variable "data", el arreglo dentro
* de memoria dinámica que guarda lo que se recibe de la UART.
* Output: int len. Entero que guarda el índice del arreglo data donde se guardó la
* información que recibió la UART.
*****************************************************************************/

int uart_read(uint8_t *data)
{
	int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_RATE_MS);
	return len;
}

/**************************************************************************
* Function: uart_write
* Preconditions: data, len.
* Overview: Permite e scribir en la terminal.
* Input:
* *data. Dirección de memoria de la variable "data", el arreglo dentro
* de memoria dinámica que guarda lo que se recibe de la UART.
* int len. Entero que guarda el índice del arreglo data donde se guardó la
* información que recibió la UART.
* Output: Ninguna.
*****************************************************************************/

void uart_write(uint8_t *data, int len)
{
	uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) data, len);
	       if (len) {
	            data[len] = '\0';
	            ESP_LOGI(TAG, "Recv str: %s", (char *) data);
	        }
}

