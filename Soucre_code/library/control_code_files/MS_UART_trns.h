/**
  ******************************************************************************
  * @file    MS_UART_trns.h
  * @author  Paweł Rozenblut
  * @brief   Function prototypes realising UART communiction.
  *   
  ******************************************************************************
  */


#ifndef MS_TRANS_H
#define MS_TRANS_H

#include "MS_core.h"

/**
  * @brief  Deparse received data packet; expected format: 96-bits of nothing, and 32-bits of new RPM value to be set.
  *         This "nothing" was meant to convey the PID tuning, but in this version - we decided to go with
  *         some simpler error compensation algorithm.
  * 
  * @attention Use USART3 interface, enable Receive IT mode, as shown in initialize_STM32_interfaces() function
  *            and call the HAL Receive IT in the very same way in appropriate callback 
  *            again, after calling this function
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */

void deparse_received_data(Program_Data* pd);

/**
  * @brief  Transmit data packet with current reference velocity, structure of the packet:
  *         8-bit transmit flag, 32-bit current RPM readout, 32-bit reference RPM echo.
  *    
  * @attention Use USART3 interface. 
  *  
  * @param  pd: pointer to the Program_Data type structure. 
  * 
  * @retval None
  */

void transmit_data_packet(Program_Data* pd);


#endif
