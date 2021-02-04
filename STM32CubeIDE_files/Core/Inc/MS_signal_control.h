/**
  ******************************************************************************
  * @file    MS_signal_control.h
  * @author  Paweł Rozenblut
  * @brief   Header file containing prototypes of the functions realising  
  *          all the control logic of the fan, update of the PWM duty cycle 
  *          and readout/conversion of the RPM values.
  *   
  ******************************************************************************
  */



#ifndef MS_SIGNAL
#define MS_SIGNAL
#include "MS_core.h"


/**
  * @brief  Update PWM duty cycle, if desired RPM is not within the control error 
  *         range envelope (compensation is being triggered at +/- 0.5% of the total range of 0 RPM to 8000 RPM).
  * @param  pd: pointer to the Program_Data type structure, containing current PWM value set, readout
  *         of the reference RPM (system's input) and actual RPM (system's regulation error).
  *         The function corrects the PWM to be set, if the value currently set is too low, 
  *         or too high.
  * @retval None
  */

void compensate_error(Program_Data* pd);

/**
  * @brief  Obtain the value of PWM duty cycle to be set, from reference RPM. 
  *         If desired RPM is within the appropriate control range, the  
  *         function interpolates the PWM to be set, from the following dependency:
  *         PWM  = (RPM - 8332.9)/(-8.3707)).  
  *         
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void set_PWM_from_RPM(Program_Data* pd);


/**
  * @brief  Set new reference value of fan's RPM. 
  *  
  * @param  pd: pointer to the Program_Data type structure. 
  * @param new_RPM_ref: New RPM value to be set. 
  * 
  * @retval None
  */
void set_reference_RPM(Program_Data* pd, uint32_t new_RPM_ref);


/**
  * @brief  Get the current value of RPM, and reset the counter measuring HAL sensor ticks
  *         in the duration of one second.
  * @attention Should be triggered every second elapsed.
  *  
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void get_RPM_actual(Program_Data* pd);


/**
  * @brief  Increment HAL tick counter, for latter computation of RPM.
  * @attention STM32 Timer must be compliant with the default configuration
  *             provided, that is: (TIM3, with TIM_CHANNEL_2 used to generate PWM, 
  *             clock frequency = 12kHz, CLCK max = 10,000.)
  *   
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void increment_counter_at_tacho_ev(Program_Data* pd);

/**
  * @brief  Set new value of PWM, to PWM-generating timer.
  * @attention STM32 Timer must be compliant with the default configuration
  *             provided, that is: (TIM3, with TIM_CHANNEL_2 used to generate PWM, 
  *             clock frequency = 12kHz, CLCK register max = 1000.)
  * 
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void update_PWM_duty(Program_Data* pd);


/**
  * @brief  Obtain the PWM value, from the PWM-generating timer.
  * @attention STM32 Timer must be compliant with the default configuration
  *             provided, that is: (TIM3, with TIM_CHANNEL_2 used to generate PWM, 
  *             clock frequency = 12kHz, CLCK register max = 1000.)
  * 
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void read_PWM_duty(Program_Data* pd);

/**
  * @brief  Control reference RPM through rotary encoder.
  * 
  * @attention Place it in the encoder's clock falling edge detection callback.
  *  
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */
void encoder_RPM_update(Program_Data* pd);

#endif
