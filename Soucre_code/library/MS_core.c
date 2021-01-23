#include "MS_core.h"
#include "MS_signal_control.h"

void initialize_STM32_interfaces(Program_Data* pd)
{

    HAL_TIM_Base_Start_IT(&htim6);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_UART_Receive_IT(&huart3, pd->rx_buffer, 16);

    pd->tx_flag = 68;
    pd->HAL_PULSE_counter = 0;

    set_reference_RPM(pd, 0);
    set_PWM_from_RPM(pd);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pd->PWM);
}
