/*
 * Adc.h
 *
 * Created: 09.09.2014 15:58:00
 *  Author: majapo
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_start(uint8_t channel);
uint8_t ADC_read(void);



#endif /* ADC_H_ */