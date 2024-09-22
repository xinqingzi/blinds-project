// Constants for the ACS712 sensor
const int sensorPin = A0; // Pin where the sensor is connected
const float referenceVoltage = 5.0; // Reference voltage of Arduino
const int sensorZero = 512; // Midpoint of 10-bit ADC (for 5V reference)
const float sensitivity = 0.185; // Sensitivity for ACS712 5A version (in V/A)

const int IN1 = 13;  // going up
const int IN2 = 12;
const int ENB = 11;
const int IN3 = 7;   // going down
const int IN4 = 8;
const int ENA = 9;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  // Convert the analog value to voltage
  float voltage = (sensorValue / 1023.0) * referenceVoltage;
  // Convert voltage to current
  // (Assuming the sensor output is centered around Vcc/2 when no current is flowing)
  float current = (voltage - (referenceVoltage / 2.0)) / sensitivity;
  
  // Print the current value to the serial monitor
  Serial.print("Current: ");
  Serial.println(current);
  Serial.println(" A");
  // delay(1000); // Delay for 1 second
  if(abs(current) > 2){ //1. control the current, set a max allowance to prevent hotness on the device. 2. Also serves as a indicator that the blinds reach to the top limit.
    motor(0);
  }
  //else if (abs(current) < 1){
    //motor(0);
  //}
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      //startTime = millis();  // Record start time
      motor(350);  // Set motor speed to 350 (clockwise)
      Serial.println("Clockwise with speed of 250");
    } 
    else if (command == '2') {
      //startTime = millis();  // Record start time
      motor(-100);  // Set motor speed to 100 (clockwise)
      Serial.println("counterclockwise with speed of 250");
    }
    else if (command == '0') {
      motor(0);   // Stop the motor
      //unsigned long elapsedTime = millis1
      //() - startTime;
      Serial.print("Motor stopped. Elapsed time: ");
      //Serial.print(elapsedTime);
      //Serial.println(" ms");
    }
  }
}

void motor(int speed) {
  analogWrite(ENB, abs(speed));
  if (speed > 0) { 
    analogWrite(ENB, abs(speed));   // Set speed using PWM
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else if (speed < 0) {
    analogWrite(ENA, abs(speed));    // Set speed using PWM
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}


