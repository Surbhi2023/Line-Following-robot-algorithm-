// Define IR sensor pins
const int leftSensorPin = 2;
const int centerSensorPin = 3;
const int rightSensorPin = 4;

// Define motor control pins
const int leftMotorPin1 = 5;
const int leftMotorPin2 = 6;
const int rightMotorPin1 = 7;
const int rightMotorPin2 = 8;

// Define speed variables for motor control
int leftMotorSpeed = 200; // adjust as needed
int rightMotorSpeed = 200; // adjust as needed

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
}

void loop() {
  // Read sensor values
  int leftSensorValue = digitalRead(leftSensorPin);
  int centerSensorValue = digitalRead(centerSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // Debugging: print sensor values
  Serial.print("Left: ");
  Serial.print(leftSensorValue);
  Serial.print("  Center: ");
  Serial.print(centerSensorValue);
  Serial.print("  Right: ");
  Serial.println(rightSensorValue);

  // Line following logic
  if (leftSensorValue == LOW && centerSensorValue == HIGH && rightSensorValue == LOW) {
    moveForward();
  } else if (leftSensorValue == HIGH && centerSensorValue == LOW && rightSensorValue == LOW) {
    // Turn right 90 degrees
    turn(1, 1000); // Right turn
  } else if (leftSensorValue == LOW && centerSensorValue == LOW && rightSensorValue == HIGH) {
    // Turn left 90 degrees
    turn(0, 1000); // Left turn
  } else if (centerSensorValue == HIGH) {
    // Adjust center alignment
    adjustCenter();
  } else {
    stopMotors();
  }
}

// Function to move the robot forward
void moveForward() {
  analogWrite(leftMotorPin1, leftMotorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  analogWrite(rightMotorPin1, rightMotorSpeed);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to turn left or right
void turn(int direction, int delayTime) {
  if (direction == 0) { // Left turn
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else { // Right turn
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  delay(delayTime); // Adjust delay as needed for your robot to complete the turn
  stopMotors();
}

// Function to adjust center alignment
void adjustCenter() {
  analogWrite(leftMotorPin1, leftMotorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  analogWrite(rightMotorPin1, rightMotorSpeed / 2); // Reduce right motor speed for center adjustment
  digitalWrite(rightMotorPin2, LOW);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}
