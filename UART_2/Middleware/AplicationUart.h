 // FileName:        AplicationUart.h
 // Dependencies:	 Uart_Driver_2022.h, Uart_Driver_2022.c
 // Processor:       32-bit Xtensa LX6
 // Board:           ESP32 DEVKIT V1 (30 pins)
 // Program version: Espressif IDE
 // Company:         Espressif Systems
 // Description:     Funciones de control de HW a través de los drivers.
 // Authors:         Anahí González Holguín
 //					 Axel Gay Díaz
 //					 Carlos González Vázquez
 //					 Carlos López Lara
 // Updated:         12/2022

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "C:\UART_2\Drivers\Uart_Driver_2022.h"
#include "C:\UART_2\Drivers\Uart_Driver_2022.c"
#include <unistd.h>
#include <TIME.H>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

//Definiciones para el código de aplicación
#define On		1
#define Off		0
#define Open	1
#define Close	0

/**************************************************************************
* Function: sistema_init
* Preconditions:
* Overview: Imprime que ha iniciado el programa.
* Input: Ninguna.
* Output: Ninguna.
*****************************************************************************/
extern void sistema_init(void);

/**************************************************************************
* Function: imprimir_menu
* Preconditions:
* Overview: Imprime el menú de la aplicación
* Input: Ninguna.
* Output: Ninguna.
*****************************************************************************/
extern void imprimir_menu(void);

/**************************************************************************
* Function: imprimir_estado
* Preconditions:
* Overview: Imprime el estado de cada componente del sistema.
* Input: uint8_t estado_luces, uint8_t estado_persianas, uint8_t estado_alarma
* Output: Ninguna.
*****************************************************************************/
extern void imprimir_estado(uint8_t estado_luces, uint8_t estado_persianas, uint8_t estado_alarma);

