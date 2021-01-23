/**
  ******************************************************************************
  * @file    MS_UART_trns.c
  * @author  Paweł Rozenblut
  * @brief   Bodies of the functions realisng data transmission/receiving.
  *   
  ******************************************************************************
  */


#include "MS_UART_trns.h"
#include "MS_core.h"

void transmit_data_packet(Program_Data* pd)
{
  HAL_UART_Transmit(&huart3, (uint8_t*)&(pd->tx_flag), 1, 1000);

  uint8_t a[4] = {0,};

	memcpy(a, &(pd->RPM_actual), sizeof(pd->RPM_actual));
	HAL_UART_Transmit(&huart3, (uint8_t*)a, 4, 1000);

  memcpy(a, &(pd->RPM_reference), sizeof(pd->RPM_reference));
	HAL_UART_Transmit(&huart3, (uint8_t*)a, 4, 1000);

}


void deparse_received_data(Program_Data* pd)
{
    pd->RPM_reference = pd->rx_buffer[12] | (pd->rx_buffer[13] << 8) | (pd->rx_buffer[14] << 16) | (pd->rx_buffer[15] << 24);
}

