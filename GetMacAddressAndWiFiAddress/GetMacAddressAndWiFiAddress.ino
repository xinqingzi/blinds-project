#include <WiFiS3.h>

const char* ssid = "Kellie";
const char* password = "b38cVncktTadtZrvEFoV";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial communication is working.");
  WiFi.begin(ssid, password);

  while( WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the MAC address
  uint8_t mac[6];  // Array to store the MAC address
  WiFi.macAddress(mac);  // Get the MAC address

  Serial.print("MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(mac[i], HEX);  // Print each byte in hexadecimal
    if (i < 5) Serial.print(":");  // Add a colon between bytes
  }
  Serial.println();

  // Print the local IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
