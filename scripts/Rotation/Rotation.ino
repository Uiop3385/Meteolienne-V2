int positionToSteps(int8_t pos) {
  return pos * (steps_per_revolution / 16);
}

int convertVoltageToPosition(int voltage) {
  int closest_index = 0;
  float min_difference = abs(voltage_values[0] - voltage);
  for (int i = 1; i < 16; i++) {
      float difference = abs(voltage_values[i] - voltage);
      if (difference < min_difference) {
          min_difference = difference;
          closest_index = i;
      }
  }
  return closest_index;
}

void updateRotation(int8_t wind_vane_position) {
  stepper.step(positionToSteps(wind_vane_position - current_position));
  setCurrentPosition(wind_vane_position);
}

void setCurrentPosition(int pos) {
  current_position = pos;
  direction = current_position;
}

/*
  Since Direction is READ_WRITE variable, onDirectionChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onDirectionChange()  {
  // Add your code here to act upon Direction change
  updateRotation(direction);
  setCurrentPosition(0);
}