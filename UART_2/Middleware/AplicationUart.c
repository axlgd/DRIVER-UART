 // FileName:        AplicationUart.c
 // Dependencies:	 AplicationUart.h
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
#include "C:\UART_2\Middleware\AplicationUart.h"
#include <unistd.h>
#include <TIME.H>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"


/**************************************************************************
* Function: sistema_init
* Preconditions:
* Overview: Imprime que ha iniciado el programa.
* Input: Ninguna.
* Output: Ninguna.
*****************************************************************************/

void sistema_init(void)
{
	char cadena[] = "El programa ha iniciado\n\r Presione una tecla para iniciar";
	uint8_t longitud;
	longitud = sizeof(cadena);
	uart_write(&cadena, longitud);
}

/**************************************************************************
* Function: imprimir_menu
* Preconditions:
* Overview: Imprime el menú de la aplicación
* Input: uint8_t estado_luces, uint8_t estado_persianas, uint8_t estado_alarma
* Output: Ninguna.
*****************************************************************************/

void imprimir_menu(void)
{
	char luces[] = "1.Prender/Apagar luces";
	    uint8_t longitud_luces;
	    longitud_luces = sizeof(luces);
	    uart_write(&luces, longitud_luces);
	char persianas[] = "2.Subir/Bajar persianas";
			uint8_t longitud_persianas;
			longitud_persianas = sizeof(persianas);
			uart_write(&persianas, longitud_persianas);
	char alarma[] = "3.Prender/Apagar alarma";
				uint8_t longitud_alarma;
				longitud_alarma = sizeof(alarma);
				uart_write(&alarma, longitud_alarma);
	char apagar[] = "4.Apagar el sistema";
					uint8_t longitud_apagar;
					longitud_apagar = sizeof(apagar);
					uart_write(&apagar, longitud_apagar);
	char opcion[] = "Presione el boton de menu:";
						uint8_t longitud_opcion;
						longitud_opcion = sizeof(opcion);
						uart_write(&opcion, longitud_opcion);
}

/**************************************************************************
* Function: imprimir_estado
* Preconditions:
* Overview: Imprime el estado de cada componente del sistema.
* Input: uint8_t estado_luces, uint8_t estado_persianas, uint8_t estado_alarma
* Output: Ninguna.
*****************************************************************************/

void imprimir_estado(uint8_t estado_luces, uint8_t estado_persianas, uint8_t estado_alarma)
{
	char Micasa[] = "Mi casa";
	uint8_t longitud_micasa;
	longitud_micasa = sizeof(Micasa);
	uart_write(&Micasa, longitud_micasa);

	if(estado_luces == 0)
	{
		char luces_off[] = "Luces: OFF";
		uint8_t longitud_luces_off;
		longitud_luces_off = sizeof(luces_off);
		uart_write(&luces_off, longitud_luces_off);
	}else
	{
		char luces_on[] = "Luces: ON";
		uint8_t longitud_luces_on;
		longitud_luces_on = sizeof(luces_on);
		uart_write(&luces_on, longitud_luces_on);
	}
	if(estado_persianas == 0)
	{
		char persianas_down[] = "Persianas: CLOSE";
		uint8_t longitud_persianas_down;
		longitud_persianas_down = sizeof(persianas_down);
		uart_write(&persianas_down, longitud_persianas_down);
	}else
	{
		char persianas_open[] = "Persianas: OPEN";
		uint8_t longitud_persianas_open;
		longitud_persianas_open = sizeof(persianas_open);
		uart_write(&persianas_open, longitud_persianas_open);
	}


	if(estado_alarma == 0)
	{
		char alarma_off[] = "Alarma: Off";
		uint8_t longitud_alarma_off;
		longitud_alarma_off = sizeof(alarma_off);
		uart_write(&alarma_off, longitud_alarma_off);
	}else
	{
		char alarma_on[] = "Alarma: On";
		uint8_t longitud_alarma_on;
		longitud_alarma_on = sizeof(alarma_on);
		uart_write(&alarma_on, longitud_alarma_on);
	}


}
