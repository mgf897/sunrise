#include <SoftwareSerial.h>

char INBYTE;
int  LED = 13; // LED on pin 13
SoftwareSerial BTSerial(10, 11); // RX | TX
int KEY = 9;  //Define BT KEY pin

void setup() {
  // put your setup code here, to run once:
  pinMode(KEY,OUTPUT);    
  digitalWrite(KEY,HIGH);  //Set KEY output high
  delay(100);              //Wait 100ms to make sure BT device has entered AT mode
  BTSerial.begin(38400);   //Initialise serial at default AT command speed
  BTSerial.println("AT+NAME=SUNRISE");    //rename BT device
  BTSerial.println("AT+UART=115200,1,0"); //Set 115200 baud
  BTSerial.end();          //end serial comms to BT device
  digitalWrite(KEY,LOW);   //Clear KEY pin
  delay(100);              //Wait 100ms to make sure BT device has exited AT mode
  BTSerial.begin(9600);  //Reconnect as serial modem at new baud
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available()>0){
    INBYTE = BTSerial.read();      // read next available byte
    if( INBYTE == '0' ){
      digitalWrite(LED, LOW);      // if it's a 0 (zero) tun LED off
      BTSerial.println("LED OFF");
    }
    if( INBYTE == '1' ){
      digitalWrite(LED, HIGH);    // if it's a 1 (one) turn LED on
      BTSerial.println("LED ON");
    }
    delay(50);
  }
}
