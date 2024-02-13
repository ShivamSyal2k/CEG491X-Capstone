const int pingPin1 = 5;
long duration;
int distance;

void setup() {
  
  // put your setup code here, to run once:
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
  long duration1, inches1, cm1, duration2, inches2, cm2;
  // put your main code here, to run repeatedly:

  pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin1, LOW);


  pinMode(pingPin1, INPUT);
  duration1 = pulseIn(pingPin1, HIGH);

  // convert the time into a distance
  inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  forward(10);
  if(cm1 < 15) {
    stop(1000);
    backward(3000);
    stop(1000);
    pivotLeft(4000);
    stop(1000);
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

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
