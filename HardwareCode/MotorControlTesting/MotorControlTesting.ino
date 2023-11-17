void setup() {
  // put your setup code here, to run once:
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
  digitalWrite(4, HIGH); //STBY, allows motors to drive

  forward(1000);
  stop(1000);
  backward(1000);
  stop(1000);
  turnLeft(1000);
  stop(1000);
  turnRight(1000);
  stop(1000);
  pivotLeft(1000);
  stop(1000);
  pivotRight(1000);
  stop(1000);
}


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
