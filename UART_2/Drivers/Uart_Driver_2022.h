 // FileName:        Uart_Driver_2022.h
 // Dependencies:
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

//Liberías necesarias
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"


//CONFIGURACIÓN PARA SELECCIONAR PINES DE LA ESP Y CARACTERÍSTICAS DE LA UART
#define ECHO_TEST_TXD (GPIO_NUM_17)			//PIN TXD
#define ECHO_TEST_RXD (GPIO_NUM_16)			//PIN RXD
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      (CONFIG_EXAMPLE_UART_PORT_NUM) //NUMERO DE PUERTO DE UART
#define ECHO_UART_BAUD_RATE     (CONFIG_EXAMPLE_UART_BAUD_RATE) //BAUD RATE
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)

//Redefiniciones del driver
#define	TX_PIN (ECHO_TEST_TXD)
#define	RX_PIN (ECHO_TEST_RXD)


#define UART_PORT	(ECHO_UART_PORT_NUM)
#define BAUD_RATE	(ECHO_UART_BAUD_RATE)
#define DATA_BITS	(UART_DATA_8_BITS) // BITS DE DATOS
#define PARITY		(UART_PARITY_DISABLE) // PARIDAD
#define STOP_BITS	(UART_STOP_BITS_1) //BITS DE PARO


static const char *TAG = "UART TEST";

#define BUF_SIZE (1024)

/**************************************************************************
* Function: uart_config
* Preconditions: Ninguna.
* Overview: Accede a los registros por medio de una estructura para configurar la UART.
* Input: Ninguno.
* Output: Ninguno.
*
*****************************************************************************/
extern void uart_config(void);

/**************************************************************************
* Function: uart_read
* Preconditions: data, len.
* Overview: Permite recibir información vía UART desde otra terminal.
* Input: *data. Dirección de memoria de la variable "data", el arreglo dentro
* de memoria dinámica que guarda lo que se recibe de la UART.
* Output: int len. Entero que guarda el índice del arreglo data donde se guardó la
* información que recibió la UART.
*****************************************************************************/
extern int uart_read(uint8_t *data);

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
extern void uart_write(uint8_t *data, int len);

