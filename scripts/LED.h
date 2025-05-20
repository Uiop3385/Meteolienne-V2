#include <utility/wifi_drv.h>

struct RGB {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct Gradient {
  uint8_t red;
  uint8_t green;
};

RGB cloudColorToRGB(CloudColoredLight led);
Gradient getGradientAtPercentage(int percent);
void turnOffLED();
RGB gradientToRGB(Gradient gradient);
void setLED(RGB rgb);
void updateLED();