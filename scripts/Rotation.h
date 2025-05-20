#include <Stepper.h>

const uint16_t steps_per_revolution = 2048;
const byte wind_vane_pin = A1;
const int voltage_values[16] = {3144, 1944, 2148, 476, 528, 380, 1000, 704, 1464, 1280, 2712, 2620, 3544, 3260, 3404, 2920};
const byte stepper_pins[4] = {1, 3, 2, 4};
int8_t current_position = 0;
Stepper stepper(steps_per_revolution, stepper_pins[0], stepper_pins[1], stepper_pins[2], stepper_pins[3]);

int positionToSteps(int8_t pos);
int convertVoltageToPosition(int voltage);
void updateRotation(int8_t wind_vane_position);
void setCurrentPosition(int pos);