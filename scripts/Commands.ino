String macToString(byte mac[]) {
  String result = "";
  for (int i = 0; i < 6; i++) {
    if (mac[i] < 16) {
      result += "0";
    }
    result += String(mac[i], HEX);
    if (i < 5) {
      result += ":";
    }
  }
  return result;
}

String echoCommand(const String args[], size_t argCount) {
  String result = "";
  for (size_t i = 0; i < argCount; i++) {
      result += args[i] + " ";
  }
  result.trim(); // Modify result in place
  return result;
}

String infoCommand(const String args[], size_t argCount) {
  if (argCount == 0) {
      return "No arguments provided";
  } else {
      String response = "Arguments: ";
      for (size_t i = 0; i < argCount; i++) {
          response += args[i] + " ";
      }
      response.trim();
      return response;
  }
}

String locateCommand(const String args[], size_t argCount) {
  queryPosition();
  return "Location queried, check serial monitor.";
}

String positionCalibrateCommand(const String args[], size_t argCount) {
  int8_t target_position = constrain(args[0].toInt(), 0, 15);
  updateRotation(target_position);
  return "Calibrated to position " + String(current_position) + ".";
}

String stepCalibrateCommand(const String args[], size_t argCount) {
  int16_t steps = constrain(args[0].toInt(), 0, 15);
  stepper.step(steps);
  setCurrentPosition(0);
  return "Calibrated by " + String(steps) + " steps.";
}

String resetCommand(const String args[], size_t argCount) {
  NVIC_SystemReset();
  return "Reset.";
}

String sleepNowCommand(const String args[], size_t argCount) {
  uint8_t duration = (argCount == 1) ? constrain(args[0].toInt(), 1, 120) : 0;
  sleepRoutine(duration);
  return "Went to sleep.";
}

String wifiLpmConfigurationCommand(const String args[], size_t argCount) {
  if (constrain(args[0].toInt(), 0, 1) == 0) {
    WiFi.noLowPowerMode();
    return "Low Power Mode has been disabled.";
  } else {
    WiFi.lowPowerMode();
    return "Low Power Mode has been enabled.";
  }
}

String wifiScanNetworksCommand(const String args[], size_t argCount) {
  int numNetworks = WiFi.scanNetworks();
  String result = "List of available networks:\n";

  if (numNetworks == 0) {
    result = "No networks found.";
  } else {
    for (int i = 0; i < numNetworks; i++) {
      result += "ID: " + String(i);
      result += ", SSID: " + String(WiFi.SSID(i));
      result += ", RSSI: " + String(WiFi.RSSI(i)) + " dBm\n";
    }
  }
  return result;
}

String wifiPingCommand(const String args[], size_t argCount) {
  String hostname = args[0];
  int ping = WiFi.ping(hostname);
  if (ping >= 0) {
    return "Successfully pinged "+hostname+" in "+String(ping)+"ms!";
  } else {
    return "Something went wrong. Error code: "+String(ping);
  }
}

String wifiGetDebugInfoCommand(const String args[], size_t argCount) {
  String response = "Wifi debugging information log:\n";
  response.concat("Network SSID: "+String(WiFi.SSID())+"\n");
  response.concat("Network signal strength (RSSI): "+String(WiFi.RSSI())+"\n");
  response.concat("Encryption used: "+String(WiFi.encryptionType())+"\n");
  response.concat("Connection status: "+String(WiFi.status())+"\n");
  response.concat("Wifi firmware version: "+String(WiFi.firmwareVersion())+"\n");
  response.concat("Local IP address: "+String(WiFi.localIP())+"\n");
  response.concat("Subnet mask: "+String(WiFi.subnetMask())+"\n");
  response.concat("Gateway: "+String(WiFi.gatewayIP())+"\n");
  response.concat("Primary DNS: "+String(WiFi.dnsIP())+"\n");
  response.concat("Secondary DNS: "+String(WiFi.dnsIP(1))+"\n");
  byte mac[6];
  WiFi.macAddress(mac);
  response.concat("Local MAC address: "+macToString(mac)+"\n");
  byte bssid[6];
  WiFi.BSSID(bssid);
  response.concat("Router MAC address (BSSID): "+macToString(bssid));
  return response;
}

String wifiGetReasonCodeCommand(const String args[], size_t argCount) {
  return "Deauthentication reason code: "+String(WiFi.reasonCode());
}

String demoSpinCommand(const String args[], size_t argCount) {
  updateRotation(15);
  updateRotation(-15);
  return "Spin demo executed successfully!";
}

String demoLedBuiltinCommand(const String args[], size_t argCount) {
  static bool state = LOW;
  state = !state;
  digitalWrite(LED_BUILTIN, state);
  return "Built-in LED state updated!";
}