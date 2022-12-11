 // FileName:		 main.c
 // Dependencies:	 Uart_Driver_2022.h, Uart_Driver_2022.c, AplicationUart.h, AplicationUart.c
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

//Librerías necesarias
#include <stdio.h>
#include <stdlib.h>
#include "C:\UART_2\Drivers\Uart_Driver_2022.h"
#include "C:\UART_2\Drivers\Uart_Driver_2022.c"
#include "C:\UART_2\Middleware\AplicationUart.h"
#include "C:\UART_2\Middleware\AplicationUart.c"
#include <unistd.h>
#include <TIME.H>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

//Variables para manejo del estado de los elementos del sistema
uint8_t estado_luces = Off;
uint8_t estado_persianas = Close;
uint8_t estado_alarma = Off;
uint8_t estado_sistema = On;

//Variables para pooling
bool flag = 0;
bool flag1 = 0;
bool flag2 = 0;

//Variables para funciones uart_read y uart_write
int len;

//Variable para contador de las veces que se presionó el botón de menú.
int cont = 0;

/**************************************************************************
* Function: echo_task
* Preconditions:
* Overview: main del programa
* Input: Ninguna
* Output: Ninguna
*****************************************************************************/

static void echo_task(void *arg)
{

    uart_config(); //Configura la UART
    //Configuramos el pin 5 como salida y resistencia pulldown
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    gpio_set_direction(5,GPIO_MODE_INPUT);
    gpio_pulldown_en(5);

    //Inicializamos el sistema
    sistema_init();
	sleep(30);

	while(flag1==0) //Mientras no llegue algo a la terminal
	{
		for(int j=0;j<10;j++)
		{
			len = uart_read(&data); //Lee la UART desde otra terminal
			uart_write(&data, len); //Escribe en la UART lo que recibió desde otra terminal
			sleep(10);
			if(data[len] != 0) //Checa si llegó algo de la terminal
			{
				flag1 = 1;
			}
		}
	}


    while(estado_sistema) //Revisa la bandera
    {
    	sleep(10);
    	//Imprime el estado actual del sistema
    	imprimir_estado(estado_luces, estado_persianas, estado_alarma);
    	sleep(30);

    	//Imprime el menú
    	imprimir_menu();
    	sleep(30);

    	//Bandera que indica que no se ha presionado un botón
		while (flag==0) {
			for(int k=0;k<10;k++)
			{
				if(gpio_get_level(5)==0) //Si se presiona el botón menú
				{
					sleep(10);
					cont = cont + 1;	//Aumenta el contador

					//Manda mensaje a la terminal
					char contad[] = "Se ha presionado el boton";
					uint8_t cont;
					cont = sizeof(contad);
					uart_write(&contad, cont);
					flag=1;
				}
				sleep(3);
			}
		}
		sleep(10);

		while(flag == 1) //Cuando se presiona el botón:
		{
			if (cont == 1) //Si se presionó por primera vez
			{
				// Apaga/Enciende las luces
				if(estado_luces == On)
				{
					estado_luces = Off;
				}else
				{
					estado_luces = On;
				}
			}

			if (cont == 2) //Si se presionó por segunda vez
			{
				// Abre/Cierra las persianas
				if(estado_persianas == Open )
				{
					estado_persianas = Close;
				}else
				{
					estado_persianas = Open;
				}

			}

			if (cont == 3) //Si se presionó por tercera vez
			{
				// Apaga/Prende la alarma
				if(estado_alarma == On)
				{
					estado_alarma = Off;
				}else
				{
					estado_alarma = On;
				}
			}

			if (cont == 4) //Si se presionó por cuarta vez
			{
				//Termina el programa
				estado_sistema = Off;

				char off[] = "Se ha terminado el programa"; //Manda mensaje a la terminal
				uint8_t of;
				of = sizeof(off);
				uart_write(&off, of);
				cont = 0;
				sleep(30);
			}

			flag = 0; //Regresa la bandera del botón a 0, para volver a revisar si se presiona
		}
    }
}

/**************************************************************************
* Function: app_main
* Preconditions:
* Overview: Administra la task
* Input: Ninguna
* Output: Ninguna
*****************************************************************************/
void app_main(void)
{
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}


