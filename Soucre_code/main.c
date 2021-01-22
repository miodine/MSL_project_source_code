/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"stdio.h"
#include "arm_math.h"
#include "math.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint32_t ref_RPM[900] = {
		#include "../../MATLAB/PWM_RPM_REFERENCE.csv"
};

uint32_t ref_PWM[900]={0,};
uint32_t sought_PWM= 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

 uint32_t counter=0;
 uint32_t rpm =0;
 char buffer [50];
 uint8_t rx_buffer[16];
 uint32_t pwm_input =1000;

uint32_t RPM_to_be_set=6000;



 uint32_t motor_input_voltage_to_PWM(float32_t voltage)
  {
 	return (uint32_t)(1000 - (voltage*1000/5));
  }

  float32_t RPM_to_voltage(uint32_t RPM)
  {
 	 return (float32_t)(RPM/600.0);
  }

  uint32_t RPM_to_PWM(uint32_t RPM)
  {
 	 float32_t V = RPM_to_voltage(RPM);
 	 return motor_input_voltage_to_PWM(V);
  }

  //RPM = aPWM + b, where:  a = -8.3707 b= 8332.9

   uint32_t set_PWM_from_RPM(uint32_t RPM)
   {
  	 uint32_t PWM = 0;

  	 if(RPM < 240) return 1000;
  	 if(RPM > 8000) return 0;

  	 return (uint32_t)(((float)RPM - 8332.9)/(-8.3707));

   }


   uint32_t compensate(uint32_t u, uint32_t y, uint32_t curr_PWM)
   {
   	if(y > (u+40))
   	{
   		if(curr_PWM < 1000) return curr_PWM += 1;
   	}

   	else if(y < (u-40))
   	{
   		if(curr_PWM > 0) return curr_PWM -= 1;
   	}
   	return curr_PWM;
   }






float32_t system_input_voltage = 1;
uint32_t object_input_voltage = 0;
uint32_t pwm_adjusted = 0;

arm_pid_instance_f32 pid;

uint32_t pwm_actual =0;

		uint32_t x = 0;

		uint32_t pwm_to_set=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	for(int i=0;i<900;i++)
	{
		ref_PWM[i]=900-i;
	}



	float32_t Kp=0.0000467209359865134;
	float32_t Ki=0.00004672093598651341;
    float32_t Kd=0.00001168023399662835;

    pid.Kp=1;
    pid.Ki=0;
    pid.Kd=0;




    arm_pid_init_f32(&pid,0);




  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM14_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	/* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

 pwm_to_set=set_PWM_from_RPM(RPM_to_be_set);
 //sought_PWM = find_PWM(ref_RPM,ref_PWM,6660,900);
 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm_to_set);
 HAL_UART_Receive_IT(&huart3, rx_buffer, 16);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback ( uint16_t GPIO_Pin )
{
	if(GPIO_Pin == TACH_Pin)
	{
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		counter++;
	}

	if(GPIO_Pin == USER_Btn_Pin)
	{
		//1000 PWM == 0 V  0 PWM == 5V
		//8000 PWM == 1 V ?????
		//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 800); //1V fan +V input
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim-> Instance ==TIM6)
	{
		rpm = counter*1*60/2;
		counter=0;
		 pwm_actual =__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);

		 x = compensate(RPM_to_be_set, rpm, pwm_actual);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, x);



		uint8_t a[4] = {0,};
			memcpy(a, &rpm, sizeof(rpm));
			uint8_t flag_ = 68;
			HAL_UART_Transmit(&huart3, (uint8_t*)&flag_, 1, 1000);
			HAL_UART_Transmit(&huart3, (uint8_t*)a, 4, 1000);



	}


	/*if(htim-> Instance == TIM7)
		{

			sprintf(buffer, "%d \r\n", rpm);
			HAL_UART_Transmit(&huart3, (uint8_t*)buffer, strlen(buffer), 1000);
	       if (pwm_input >0)
	       {
	    	   pwm_input=pwm_input-10;
	    	   __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm_input);
	       }
		}*/

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{

		RPM_to_be_set = rx_buffer[12] | (rx_buffer[13] << 8) | (rx_buffer[14] << 16) | (rx_buffer[15] << 24);
		pwm_to_set = set_PWM_from_RPM(RPM_to_be_set);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm_to_set);
		 HAL_UART_Receive_IT(&huart3, rx_buffer, 16);

	}
}









/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
