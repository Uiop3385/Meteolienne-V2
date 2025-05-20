#include <DFRobot_RTU.h>
#include <DFRobot_EnvironmentalSensor.h>
#include <ArduinoJson.h>

#define MODESWITCH /*UART:*/0 /*I2C: 0*/
DFRobot_EnvironmentalSensor environment(/*addr = */SEN050X_DEFAULT_DEVICE_ADDRESS, /*pWire = */&Wire);

const byte aq_sensor_pin = A2;

void updateEnvironmentalSensor();
void updateAQSensor();
void updatePosition();