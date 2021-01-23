#ifndef MS_CORE_H
#define MS_CORE_H

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include"stdio.h"
#include "arm_math.h"
#include "math.h"




typedef struct Program_Data{
    uint32_t RPM_actual; //replace "rpm" withit
    uint32_t RPM_reference; //replace "RPM_to_be_set"
    
    uint32_t PWM; //replace pwm_actual and  withit

    
    uint8_t rx_buffer[16];
    uint8_t tx_flag;
    uint32_t HAL_PULSE_counter;

}Program_Data;

void initialize_STM32_interfaces(Program_Data* pd);

#endif
