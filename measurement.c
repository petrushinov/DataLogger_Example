/* 
 * File:   measurement.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

//#include <libpic30.h> 
#include "mcc_generated_files/adc1.h"

int16_t ADC1_get_value(uint8_t channel){
  
   return (int16_t) ADC1_GetConversion(channel);
   
}


