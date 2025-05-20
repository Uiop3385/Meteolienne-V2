void initPMIC() {
  if (!is_charging_initialized) {
    PMIC.setMinimumSystemVoltage(batteryEmptyVoltage);
    PMIC.setChargeVoltage(batteryFullVoltage);
    PMIC.setChargeCurrent(batteryCapacity / 2);
    if (PMIC.chargeStatus() != CHARGE_TERMINATION_DONE && PMIC.isBattConnected()) {
      PMIC.enableCharge();
    }
    is_charging_initialized = true;
  }
}

void updateBatteryCapacity() {
  if (PMIC.isBattConnected() && is_charging_initialized) {
    if (PMIC.chargeStatus() != NOT_CHARGING) {
      PMIC.disableCharge();
      delay(100);
    }
    rawADC = analogRead(ADC_BATTERY);
    voltADC = rawADC * (3.3 / 4095.0);
    voltBat = voltADC * (max_Source_voltage / 3.3);
    batterie = round((voltBat - batteryEmptyVoltage) * (100) / (batteryFullVoltage - batteryEmptyVoltage));
    if (PMIC.chargeStatus() == NOT_CHARGING && batterie < 90) {
      PMIC.enableCharge();
    }
  }
}

void manageCharge() {
  if (PMIC.isBattConnected() && is_charging_initialized) {
    if (!faultCheck()) {
      int status = PMIC.chargeStatus();
      if (status == CHARGE_TERMINATION_DONE) {
        PMIC.disableCharge();
      }
      else if (status == NOT_CHARGING && batterie < 95) {
        PMIC.enableCharge();
      }
    }
    else {
      commandPrompt = "Program execution halted. The device will reset itself in 60 seconds.";
      ArduinoCloud.update();
      delay(60000);
      // function from the CMSIS, as the MKR 1010 uses an ARM Cortex-M0+ microcontroller
      NVIC_SystemReset();
    }
  }
}

void faultOutput(String fault_message) {
  commandPrompt = fault_message;
  trig = true;
  ArduinoCloud.update();
}

bool faultCheck() {
  if (PMIC.isBattConnected() && is_charging_initialized) {
    trig = false;
    switch (PMIC.getChargeFault()) {
      case INPUT_OVER_VOLTAGE:
        faultOutput("A charging fault occurred: input over voltage fault (0x10)");
        break;
      case THERMAL_SHUTDOWN:
        faultOutput("A charging fault occurred: thermal shutdown triggered (0x20)");
        break;
      case CHARGE_SAFETY_TIME_EXPIRED:
        faultOutput("A charging fault occurred: safety time expiration fault (0x30)");
        break;
      default: break;
    }
    
    if (PMIC.isBatteryInOverVoltage()) {
      faultOutput("A battery fault occurred: battery over voltage fault");
    }
  
    switch (PMIC.hasBatteryTemperatureFault()) {
      case LOWER_THRESHOLD_TEMPERATURE_FAULT:
        faultOutput("A temperature fault occurred: battery temperature lower threshold exceeded (0x05)");
        break;
      case HIGHER_THRESHOLD_TEMPERATURE_FAULT:
        faultOutput("A temperature fault occurred: battery temperature higher threshold exceeded (0x06)");
        break;
      default: break;
    }
    return trig;
  }
}