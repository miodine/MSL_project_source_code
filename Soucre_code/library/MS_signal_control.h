#ifndef MS_SIGNAL
#define MS_SIGNAL
#include "MS_core.h"

void compensate_error(Program_Data* pd);

void set_PWM_from_RPM(Program_Data* pd);

void set_reference_RPM(Program_Data* pd, uint32_t new_RPM_ref);

void get_RPM_actual(Program_Data* pd);

void increment_counter_at_tacho_ev(Program_Data* pd);

void update_PWM_duty(Program_Data* pd);

void read_PWM_duty(Program_Data* pd);

#endif
