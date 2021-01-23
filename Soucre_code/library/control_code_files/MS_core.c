/**
  ******************************************************************************
  * @file    MS_core.c
  * @author  Paweł Rozenblut
  * @brief   MS_core.h appendix - initialization function
  *   
  ******************************************************************************
  */





#include "MS_core.h"
#include "MS_signal_control.h"




void initialize_STM32_interfaces(Program_Data* pd)
{

    HAL_TIM_Base_Start_IT(&htim6);            // Period 1s 
    HAL_TIM_Base_Start_IT(&htim7);            // Extra timer
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // Frequency 12kHz
    HAL_UART_Receive_IT(&huart3, pd->rx_buffer, 16); 

    pd->tx_flag = 68;
    pd->HAL_PULSE_counter = 0;

    set_reference_RPM(pd, 0);
    set_PWM_from_RPM(pd);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pd->PWM);
}
