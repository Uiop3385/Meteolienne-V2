RGB cloudColorToRGB(CloudColoredLight led) {
  RGB rgb;
  led.getValue().getRGB(rgb.red, rgb.green, rgb.blue);
  return rgb;
}

Gradient getGradientAtPercentage(int percent) {
  Gradient gradient;
  if (percent <= 50) {
    gradient.red = 255;
    gradient.green = map(percent, 0, 50, 0, 255);
  }
  else if (percent > 50) {
    gradient.red = map(percent, 51, 100, 255, 0);
    gradient.green = 255;
  }
  gradient.red = constrain(gradient.red, 0, 255);
  gradient.green = constrain(gradient.green, 0, 255);
  return gradient;
}

void turnOffLED() {
  WiFiDrv::analogWrite(25, 0);
  WiFiDrv::analogWrite(26, 0);
  WiFiDrv::analogWrite(27, 0);
}

RGB gradientToRGB(Gradient gradient) {
  RGB rgb;
  rgb.red = gradient.red;
  rgb.green = gradient.green;
  rgb.blue = 0;
  return rgb;
}

void setLED(RGB rgb) {
  WiFiDrv::analogWrite(25, rgb.red);
  WiFiDrv::analogWrite(26, rgb.green);
  WiFiDrv::analogWrite(27, rgb.blue);
}

void updateLED() {
  switch (ledDisplayOption) {
  case 0: // 0 = OFF
    turnOffLED();
    break;
  case 1: // 1 = BATTERIE
    setLED(gradientToRGB(getGradientAtPercentage(batterie)));
    break;
  case 2: // 2 = HUMIDITÉ
    setLED(gradientToRGB(getGradientAtPercentage(humidite)));
    break;
  case 3: // 3 = QUALITÉ DE L'AIR
    setLED(gradientToRGB(getGradientAtPercentage(co2)));
    break;
  default: break;
  }
}

/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange() {
  if (ledDisplayOption == 4) {
    if (led.getSwitch()) {
      setLED(cloudColorToRGB(led));
    } else {turnOffLED();}
  }
}

/*
  Since LedDisplayOption is READ_WRITE variable, onLedDisplayOptionChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedDisplayOptionChange() {
  updateLED();
}