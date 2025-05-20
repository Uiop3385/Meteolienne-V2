void updateEnvironmentalSensor() {
  temperature = environment.getTemperature(TEMP_C);
  pression = environment.getAtmospherePressure(HPA);
  humidite = environment.getHumidity();
  luminosite = environment.getLuminousIntensity();
  altitude = environment.getElevation();
  uv = environment.getUltravioletIntensity();
}

void updateAQSensor() {
  int co2_read = analogRead(aq_sensor_pin);
  co2 = map(co2_read, 0, 4096, 0, 100);
}

String queryPosition() {
  WiFiSSLClient client;
  int HTTPS_PORT = 443;
  String HTTP_METHOD = "GET";
  String response;
  char HOST_NAME[] = "eu-api.ipdata.co/";
  String PATH_NAME = String(WiFi.gatewayIP()) + String("?api-key=") + String(SECRET_GEOLOCATION_API_KEY) + String("&fields=latitude,longitude");

  if (client.connectSSL(HOST_NAME, HTTPS_PORT)) {
    Serial.println("Connected to server");
    
    client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        response += c;
        Serial.print(c);
      }
    }

    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {
    Serial.println("connection failed");
  }
}

void updatePosition() {
  String response = queryPosition();
  JsonDocument coordinates;
  DeserializationError error = deserializeJson(coordinates, response);
  if (error) {
    Serial.println("An error occurred during deserialization: "+String(error.c_str()));
  } else {
    float latitude = coordinates["latitude"] | 0.0f;
    float longitude = coordinates["longitude"] | 0.0f;
    String error_message = coordinates["message"] | "";
    if (latitude == 0.0 && longitude == 0.0) {
      Serial.println("An error occurred: "+error_message);
    }
    else {
      position = Location(latitude, longitude);
    }
  }
}