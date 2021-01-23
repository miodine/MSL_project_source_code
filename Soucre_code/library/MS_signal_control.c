#include "MS_signal_control.h"


void compensate_error(Program_Data* pd)
{
   	if(pd->RPM_actual > (pd->RPM_reference+40))
   	{
   		if(pd->PWM < 1000)
        {
            pd->PWM  += 1;
        } 
   	}

   	else if(pd->RPM_actual < (pd->RPM_reference-40))
   	{
   		if(pd->PWM  > 0)
        {
            pd->PWM  -= 1;
        } 
   	}
}

void set_PWM_from_RPM(Program_Data* pd)
{
  	if(pd->RPM_reference < 240) 
    {
        pd->PWM = 1000;
        return;
    } 
       
    if(pd->RPM_reference > 8000)
    {
        pd->PWM = 0;
        return;
    } 
  	
    pd->PWM  = (uint32_t)(((float)pd->RPM_reference - 8332.9)/(-8.3707));
}

void set_reference_RPM(Program_Data* pd, uint32_t new_RPM_ref)
{
    pd->RPM_reference = new_RPM_ref;
}

void get_RPM_actual(Program_Data* pd)
{
    pd->RPM_actual = pd->HAL_PULSE_counter*1*60/2;
	pd->HAL_PULSE_counter=0;
}

void increment_counter_at_tacho_ev(Program_Data* pd)
{
    pd->HAL_PULSE_counter++;
}


void update_PWM_duty(Program_Data* pd)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pd->PWM);
}

void read_PWM_duty(Program_Data* pd)
{
    pd->PWM = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);
}

