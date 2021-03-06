/**
  ******************************************************************************
  * @file    MS_core.h
  * @author  Paweł Rozenblut
  * @brief   Initialization and Program Data structure.
  *   
  ******************************************************************************
  */


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


/**
  * @brief Program_Data structure definiton, holding all the variables necessary 
  *        for realisation of the fan RPM control. 
  */

typedef struct Program_Data{
    uint32_t RPM_actual;        // Acutal/Current speed at which the fan is rotating
    uint32_t RPM_reference;     // Desired value of speed at which the fan is supposed to rotate.
    
    uint32_t PWM;               // Current value of PWM duty cycle (expressed as permille)

    uint8_t rx_buffer[16];      // Buffer for the received data.
    uint8_t tx_flag;            // Transmission flag, for desktopApp  interfacing purposes
    uint32_t HAL_PULSE_counter; // Amount of pulses generated by HAL sensor-based tachometer, in 1 s.

      

}Program_Data;

/**
  * @brief  Initialization of STM32 interfaces, and relevant data fields.
  * 
  * @attention Pay attention to the function body in the MS_core.c file.
  *  
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */

void initialize_STM32_interfaces(Program_Data* pd);

#endif
