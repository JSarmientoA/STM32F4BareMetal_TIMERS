#include <stdint.h>
#include <stdio.h> // Para poder usar printf()
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

#define GPIOAEN						(1U<<0)
#define PIN5						(1U<<5)//Poner un uno en la posicion 5
#define GPIOA_5						PIN5
int main(void){
/*Este progra es un temporizador de un segundo utilizando un prescalador que divide la frecuencia
 * del reloj rpincipal (16MHZ) erntre 1600 para optenr un reloj de 10KHZ, luego cada que ocurre un cilco de
 * este reloj se activa un contador de 10000 conteos y se conecta al puerto GPIOA5 porlo que se logra
 * una salida logica con una frecuenia de un(1) segundo.*/

	//1. Habilitar el acceso a reloj al GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//2. Configurar el PIN 5 como salida
	GPIOA -> MODER |=  (1U<<10);//poner un uno en la posicion dies |= es or igual
	GPIOA -> MODER &=~ (1U<<11);//poner un cero en la posicion once &=~ es and igual negado

	uart2_rx_tx_init();
	tim2_1hz();


	while(1){

		/*Espera a que se reestablesca la bandea UIF*/
		while(!(TIM2->SR & SR_UIF));
		/*El registro SR se utiliza para verificar el estado del TIMER.}
		 *La banderoa UIF se establese por hardware en unevento de actualización del TIMER
		 *Esta bandera se borra por software*/

		/*Borra la bandera UIF*/
		TIM2->SR &= ~SR_UIF;

		printf("Retardo de 0.5 segundos!! \n\r");
		GPIOA->ODR ^= GPIOA_5;//Donde ^=, es alternancia (XOR)

		//SystickDelayMS(1000);

	}
}
