/*
 * AVR_ADC_REG.h
 *
 *  Created on: Dec 19, 2020
 *      Author: kh
 */

#ifndef AVR_ADC_REG_H_
#define AVR_ADC_REG_H_


#define ADMUX  *((volatile uint8_t*)0x27)
#define ADCSRA *((volatile uint8_t*)0x26)
#define ADCH *((volatile uint8_t*)0x25)
#define ADCL *((volatile uint8_t*)0x24)
#define SFIOR *((volatile uint8_t*)0x50)
#define SREG         *((volatile uint8_t*)0x5F)

#define ADMUX_REFS0  6
#define ADMUX_REFS1  7
#define ADMUX_ADLAR  5
#define ADMUX_MUX4  4
#define ADMUX_MUX3  3
#define ADMUX_MUX2  2
#define ADMUX_MUX1  1
#define ADMUX_MUX0  0


#define ADCSRA_ADEN  7
#define ADCSRA_ADSC  6
#define ADCSRA_ADATE  5
#define ADCSRA_ADIF  4
#define ADCSRA_ADIE  3
#define ADCSRA_ADPS2  2
#define ADCSRA_ADPS1  1
#define ADCSRA_ADPS0  0

#define SFIOR_ADTS0  5
#define SFIOR_ADTS1  6
#define SFIOR_ADTS2  7

#endif /* AVR_ADC_REG_H_ */
