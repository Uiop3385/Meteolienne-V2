#include <BQ24195.h>

bool trig;
bool is_charging_initialized = false;

void initPMIC();
void updateBatteryCapacity();
void manageCharge();
void faultOutput(String fault_message);
bool faultCheck();
