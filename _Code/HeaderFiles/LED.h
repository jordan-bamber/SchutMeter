/*
 * File:	LED.h
 * Purpose:	Routines for the LEDs
 *
 * Notes:	
 *			
 */

//Preprocessor Directives
#ifndef LED_H
#define LED_H

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

/* Definitions */

/* Macros */
/* example
// LED macros
#define LED1_ON						LED1_GPIO_PORT->BSRRL = LED1_GPIO_PIN
#define LED1_OFF					LED1_GPIO_PORT->BSRRH = LED1_GPIO_PIN
#define LED2_ON						LED2_GPIO_PORT->BSRRL = LED2_GPIO_PIN
#define LED2_OFF					LED2_GPIO_PORT->BSRRH = LED2_GPIO_PIN
#define LED3_ON						LED3_GPIO_PORT->BSRRL = LED3_GPIO_PIN
#define LED3_OFF					LED3_GPIO_PORT->BSRRH = LED3_GPIO_PIN
#define LED4_ON						LED4_GPIO_PORT->BSRRL = LED4_GPIO_PIN
#define LED4_OFF					LED4_GPIO_PORT->BSRRH = LED4_GPIO_PIN
*/

/* Public functions */
void LEDInit(void);

/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */

#endif /* LED_H */