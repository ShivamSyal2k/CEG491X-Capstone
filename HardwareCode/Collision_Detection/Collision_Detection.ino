const int TRIG_PIN = 5;
const int ECHO_PIN = 9;
long duration;
int distance;

void setup() {
  
  // put your setup code here, to run once:

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  pinMode(4, OUTPUT); // STBY

  //Motor 1 Control
  pinMode(11, OUTPUT); // PWM A
  pinMode(12, OUTPUT); // AI1
  pinMode(13, OUTPUT); // AI2

  //Motor 2 Control
  pinMode(10, OUTPUT); // PWM B
  pinMode(7, OUTPUT); // BI1
  pinMode(8, OUTPUT); // BI2
}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  forward(10);
  if(distance < 15) {
    stop(1000);
    backward(5000);
  }

}











//motors
  // digitalWrite(4, HIGH); //STBY, allows motors to drive
  // forward(2000);
  // stop(1000);
  // pivotLeft(2000);
  // stop(1000);
  // pivotRight(2000);
  // stop(1000);
  // backward(2000);
  // stop(1000);
  // pivotRight(2000);
  // stop(1000);

  // stop(1000);
  // forward(1000);
  // stop(1000);
  // backward(1000);
  // stop(1000);
  // turnLeft(1000);
  // stop(1000);
  // turnRight(1000);
  // stop(1000);
  // pivotLeft(1000);
  // stop(1000);
  // pivotRight(1000);
  // stop(1000);
//}


void forward(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10 , 255);

  delay(forHowLong);
}


void backward(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(10 , 255);

  delay(forHowLong);
}


void turnLeft(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10 , 255);

  delay(forHowLong);
}


void turnRight(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(10 , 255);

  delay(forHowLong);
}


void pivotLeft(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(10 , 255);

  delay(forHowLong);
}

void pivotRight(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10 , 255);

  delay(forHowLong);
}

void stop(int forHowLong){
  digitalWrite(4, HIGH); //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(10 , 255);

  delay(forHowLong);
}
