#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>

// * Ethernet shield attached to pins 10, 11, 12, 13

// CHANGE!!!!
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x21, 0x62 };
byte ip[] = { 172,16,66,221 };


Server server(8089);

// 5 relays:  2 for each motor (on/off,reverse) + 1 for an external LED lamp

const int roll1MainPin = 2;
const int roll1ReversePin = 3;
const int roll2MainPin = 4;
const int roll2ReversePin = 5;
const int ledLampPin = 6;

// max time to keep output enabled
const long timeout = 40000;
long roll1Start = 0;
long roll2Start = 0;

void setup()
{
  delay(1000);
  Serial.begin(9600);

  pinMode(roll1MainPin, OUTPUT);
  pinMode(roll1ReversePin, OUTPUT);
  pinMode(roll2MainPin, OUTPUT);
  pinMode(roll2ReversePin, OUTPUT);
  pinMode(ledLampPin, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Ethernet.begin(mac, ip);
  delay(200); // wait for ethernet
  server.begin(); 
  delay(200); // wait for ethernet
  Serial.print("start");
}

void loop()
{
  unsigned long currentMillis = millis();
  String readString = "";  
  
  // motor stops automatically. This is only to reset relays

  if (roll1Start > 0 && currentMillis - roll1Start > timeout) {
    Serial.println("roll1 timeout");
    roll_stop(roll1MainPin, roll1ReversePin);
    roll1Start = 0;
  }
  if (roll2Start > 0 && currentMillis - roll2Start > timeout) {
    Serial.println("roll2 timeout");
    roll_stop(roll2MainPin, roll2ReversePin);
    roll2Start = 0;
  }

  // the server loop

  Client client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        
        char c = client.read();
        Serial.print(c);
        
        //read char by char HTTP request
        if (readString.length() < 100) {        
          readString.concat(c);
        }

        if (c == '\n') {
          // line completed
          Serial.print(readString);
          
          if(readString.indexOf("-") == 5) {
            // example:  /roll1-open roll2-close led-on led-off
            
            if (handleCommand(readString)) {
              client.println("HTTP/1.1 200 OK");
            } else {
              client.println("HTTP/1.1 404 Not Found");
            }

          } else {
            // no valid url request
            client.println("HTTP/1.1 400 Bad Request");
          }
          client.println("Content-Type: text");
          client.println();          
          break;
        }
      }
    }
    delay(1);     // give the web browser time to receive the data
    client.stop();     // close the connection:
  }
}

boolean handleCommand(String readString) {
  unsigned long currentMillis = millis();
  int len = readString.lastIndexOf(" ");
  int dashPos = readString.lastIndexOf("-");
              
  // get actuator
  String actuator = readString.substring(6, dashPos);
  Serial.println("act: " + actuator);
  
  // get command
  String command = readString.substring(dashPos + 1, len);            
  Serial.println("cmd: " + command);
  
  if (actuator == "roll1") {
    if (roll1Start > 0) {
        Serial.println("roll1 stop");
        roll_stop(roll1MainPin, roll1ReversePin);      
        roll1Start = 0;
    } else {
      if (command == "close") {
        Serial.println("roll1 close");
        roll_close(roll1MainPin, roll1ReversePin);
        roll1Start = currentMillis;
      } else {            
        Serial.println("roll1 open");
        roll_open(roll1MainPin, roll1ReversePin);
        roll1Start = currentMillis;
      }
    }
  }               
  
  else if (actuator == "roll2") {
    if (roll2Start > 0) {
        Serial.println("roll2 stop");
        roll_stop(roll2MainPin, roll2ReversePin);      
        roll2Start = 0;
    } else {
      if (command == "close") {
        Serial.println("roll2 close");
        roll_close(roll2MainPin, roll2ReversePin);
        roll2Start = currentMillis;
      } else {                
        Serial.println("roll2 open");
        roll_open(roll2MainPin, roll2ReversePin);
        roll2Start = currentMillis;
      }
    }
  }  
      
  else if (actuator == "led") {
    if (command == "on") {
      Serial.println("led on");
      digitalWrite(ledLampPin, HIGH);
    } else {                
      Serial.println("led off");      
      digitalWrite(ledLampPin, LOW);
    }              
  } 
  else {
    return false;
  }
  return true;
} // handleCommand




// TODO: refactore

void roll_close(int mainPin, int reversePin) {
  digitalWrite(mainPin, HIGH);
}

void roll_open(int mainPin, int reversePin) {
  digitalWrite(reversePin, HIGH);
  delay(5);
  digitalWrite(mainPin, HIGH);
}

void roll_stop(int mainPin, int reversePin) {
  digitalWrite(mainPin, LOW);
  digitalWrite(reversePin, LOW);                
}

