#include "WiFiS3.h"


//#define trigPin2 9
//#define echoPin2 2

const int TRIG_PIN = 9;
const int ECHO_PIN = 2;

long duration;
int distance;

String connection_status = "Connected";


char ssid[] = "Ileri";        // your network SSID (name)
char pass[] = "Ileri1234";        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0; 
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Access Point Web Server");

  //setup pins second sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //Motor 1 Control
  pinMode(11, OUTPUT);  // PWM A
  pinMode(12, OUTPUT);  // AI1
  pinMode(13, OUTPUT);  // AI2

  //Motor 2 Control
  pinMode(10, OUTPUT);  // PWM B
  pinMode(7, OUTPUT);   // BI1
  pinMode(8, OUTPUT);   // BI2


  // check for the WiFi module:
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
  //status = WiFi.begin(ssid, pass);
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
}

void loop(){
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
            //client.print("<div>");

            client.print("<div style=\"text-align:center;background-color:#DBF9FC;height:100vh;width:100vw;>");
            client.print("<h1>GCN</h1>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:600px;width:600px;font-size:20vw;\"> <a style= \"color:white;text-decoration:none;\" href=\"/F\">GCN Controls</a> <br></button>");
            //actual buttons below
            client.print("<button style=\"border-radius:15px;margin:20px;height:200px;width:300px;font-size:15vw;\"> <a style= \"margin-bottom:10px;color:white;text-decoration:none;\" href=\"/F\">&#8679</a> <br></button>");
            client.print("<div>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:200px;width:300px;font-size:15vw;\"> <a style= \"margin-bottom:10px;color:white;text-decoration:none;\" href=\"/L\">&#8678</a> <br></button>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:200px;width:300px;font-size:15vw;\"> <a style= \"margin-bottom:10px;color:white;text-decoration:none;\" href=\"/R\">&#8680</a> <br></button>");
            client.print("</div>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:200px;width:300px;font-size:15vw;\"> <a style= \"margin-bottom:10px;color:white;text-decoration:none;\" href=\"/B\">&#8681</a><br></button>");
            client.print("<div>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:auto;width:auto;font-size:15vw;padding:10px;\"> <a style= \"color:white;text-decoration:none;\" href=\"/S\">Stop</a> <br></button>");
            client.print("<button style=\"border-radius:15px;margin:20px;height:auto;width:auto;background-color:red;font-size:15vw;color:white;padding:10px;\"> <a style= \"color:white;text-decoration:none;\" href=\"/D\">Disconnect</a> <br></button>");
            client.print(connection_status);
            client.print("</div>");
            client.print("</div>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /F")) {
          connection_status = "Connected";
          forward(5000);
        }
        if (currentLine.endsWith("GET /B")) {
          connection_status = "Connected";
          backward(5000);
        }
        if (currentLine.endsWith("GET /R")) {
          connection_status = "Connected";
          pivotRight(2000);
        }
        if (currentLine.endsWith("GET /L")) {
          connection_status = "Connected";
          pivotLeft(2000);
        }
        if (currentLine.endsWith("GET /S")) {
          connection_status = "Connected";
          stop(5000);
        }
        if (currentLine.startsWith("GET /D")) {
          connection_status = "Disconnected";
          disconnect();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
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
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}

void forward(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10, 255);

  delay(forHowLong);
}


void backward(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(10, 255);

  delay(forHowLong);
}


void turnLeft(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10, 255);

  delay(forHowLong);
}


void turnRight(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(10, 255);

  delay(forHowLong);
}


void pivotLeft(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(10, 255);

  delay(forHowLong);
}

void pivotRight(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10, 255);

  delay(forHowLong);
}

void stop(int forHowLong) {
  digitalWrite(4, HIGH);  //STBY, allows motors to drive
  //Motor 1
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  analogWrite(11, 255);
  //Motor 2
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(10, 255);

  delay(forHowLong);
}
////You are here
void disconnect(){
  delay(3000);
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
