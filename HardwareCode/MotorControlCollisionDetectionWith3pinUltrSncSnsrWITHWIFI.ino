#include "WiFiS3.h"
char ssid[] = "iPhone";        // your network SSID (name)
char pass[] = "abcd1234";        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int pingPin1 = 5;
long duration;
int distance;
bool flag;

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



void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://%22/");
  Serial.println(ip);
}

void setup() {
  //APP CODE
  Serial.println("Access Point Web Server");

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  WiFi.config(IPAddress(192,48,56,2));

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP("arduino", pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();

  //MOTORS CODE
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
  flag = false;
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

  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
              // the content of the HTTP response follows the header:
            client.print("<p style=\"font-size:7vw;\"> <a href=\"/F\">Forward</a> <br></p>");
            client.print("<p style=\"font-size:7vw;\"> <a href=\"/B\">Back</a><br></p>");
            client.print("<p style=\"font-size:7vw;\"> <a href=\"/S\">Stop</a> <br></p>");
            client.print("<p style=\"font-size:7vw;\"> <a href=\"/L\">Left</a> <br></p>");
            client.print("<p style=\"font-size:7vw;\"> <a href=\"/S\">Right</a> <br></p>");
            client.println();
            break;

          }
        }
      }
    }
    if (currentLine.endsWith("GET /S" )) {
         forward(10);
        if(cm1 < 15) {
            stop(1000);
            backward(3000);
            stop(1000);
            pivotLeft(4000);
            stop(1000);
        }
   }else{
    if (currentLine.endsWith("GET /F")) {
          forward(10000);
        }
        if (currentLine.endsWith("GET /B")) {
          backward(10000);
        }
        if (currentLine.endsWith("GET /S")) {
          stop(5000);
        }
        if (currentLine.endsWith("GET /L")) {
          pivotLeft(5000);
        }
        if (currentLine.endsWith("GET /R")) {
          pivotRight(5000);
        }

   }
  }



  
}






