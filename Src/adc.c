
#include "stm32f4xx.h"
#include "adc.h"
#define ADC1EN		  (1U<<8)
//#define ADC1_IN18
#define GPIOAEN		  (1U<<0)
#define ADC_CH1		  (1U<<0)
#define ADC_SEQ_LEN_1 0X00
#define CR2_ADON	  (1U<<0)
#define CR2_SWSTART   (1U<<30)
#define SR_EOC        (1U<<1)
#define CRE_CONT 	  (1U<<1)

void pa1_adc_int(void){

	/*********Configuracion del puerto GPIOA**********/

	/*Habilitacion reloj pierto GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/*Estableser PA1 en modo analogico, registro MODER*/
	GPIOA->MODER |= (1U<<2);//Bit 0 del registro MODER en el periferico GPIOA en 1.
	GPIOA->MODER |= (1U<<3);//Bit 1 del registro MODER en el periferico GPIOA en 1.

	/**********Configuracion del ADC*************/

	/*Configuración de parametros ADC*/

	/*Habilitacion reloj ADC */
	RCC->APB2ENR |= ADC1EN;

	/*Inico secuencia de conversion*/
	ADC1->SQR3 = ADC_CH1;
	/*Las posiciones del registro SQRn establesen el orden de la secuen del ADC.
	 * Ej:
	 * Si se van autilizar lo cnales CH6, CH2 y CH0 y se desea empesar con la secuencia CH6-CH2-CH0 se etuliza la posicion SQRn_1(CH6)
	 * SQRn_2(CH2) y SQRn_1(CH0) donde n espesifica si es el 1, 2 y 3*/

	/*Longitud secuencia de conversion*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	/*Esta  longitud se reriere a la cantidad de canales que se estan utilizando para la conversion, se se utiliza un canal
	 * la longitud de la secuencia es 1 si se utilizan 5 la longitud de la secuencia es 5*/

	/*Activacion ADC*/
	ADC1->CR2 |= CR2_ADON;

}

void inicio_conversion(void){
	/*Activa la conversion continua*/
	ADC1->CR2 |= (1U<<1);
	/*Inicia la conversion*/
	ADC1->CR2 |= CR2_SWSTART;

}

uint32_t leer_conversion(void){
	/*Esperar a que se conplete la conversion*/
	while(!(ADC1->SR & SR_EOC)){};

	/*Leer los datos de la conversion*/
	return (ADC1->DR);

}
