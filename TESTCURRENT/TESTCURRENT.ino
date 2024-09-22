// Constants for the ACS712 sensor
const int sensorPin = A0; // Pin where the sensor is connected
const float referenceVoltage = 5.0; // Reference voltage of Arduino
const int sensorZero = 512; // Midpoint of 10-bit ADC (for 5V reference)
const float sensitivity = 0.185; // Sensitivity for ACS712 5A version (in V/A)

const int IN1 = 13;
const int IN2 = 12;
const int ENB = 11;
float pcurrent = 1.5;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
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
      motor(350);  // Set motor speed to 50 (clockwise)
      Serial.println("Clockwise with speed of 250");
    } 
    else if (command == '2') {
      //startTime = millis();  // Record start time
      motor(-350);  // Set motor speed to 50 (clockwise)
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
    pcurrent = current;
}

void motor(int speed) {
  analogWrite(ENB, abs(speed));
   // Set speed using PWM
  if (speed > 0) { 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else if (speed < 0) {
    analogWrite(ENB, abs(speed)); 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}


