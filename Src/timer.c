#include "stm32f4xx.h"

#define TMR2_ON		(1U<<0)
#define CR1_CEN		(1U<<0)

void tim2_1hz(void){

	/*Activar (Conectar) el reloj para el temporizador*/
	RCC->APB1ENR |= TMR2_ON;

	/*Estableser el valor del prescalador*/
	TIM2->PSC=1600-1;/// Es escribe de esta manera porque se cuenta desde cero.

	/*El registro PSC es un prescalizador del reloj principal por lo que cualquier freciencia
	 *a la que este trabajando el reloj del sistema sera dividida el valor cargado en este registro. Esto ese:
	 *
	 *                    CLK_SYS  (Reloj del sistema)
	 * Prescalizador  =  ---------
	 *                      PSC    (Valor cargado en el registro PSC*/

	/*Valor de la recarga automatica*/
	TIM2->ARR=10000-1;

	/*El registro ARR es un contador (Progresivo o Regresivo) previo su valor de carga.
	 * Cuando este termina de contar activa una bandera*/

	/*Borrar el contador del temporizacor*/
	TIM2->CNT=0;//Borrar el valor acual del contador

	/*Este registro muesta el valor acual del contador*/

	/*Habilita el temporizador*/
	TIM2->CR1 |= CR1_CEN;//El registro CR1 es un registro de control
}
