#include <SoftwareSerial.h>

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

SoftwareSerial BTSerial(10, 11); // RX | TX
int  LED = 13; // LED on pin 13
int KEY = 9;  //Define BT KEY pin
    
void setup() {
    pinMode(KEY,OUTPUT);    
    digitalWrite(KEY,HIGH);  //Set KEY output high
    BTSerial.begin(9600);
    BTSerial.println("AT+NAMESUNRISE");    //rename BT device
    BTSerial.end();          //end serial comms to BT device
    digitalWrite(KEY,LOW);   //Clear KEY pin
    delay(100);              //Wait 100ms to make sure BT device has exited AT mode
    BTSerial.begin(9600);  //Reconnect as serial modem at new baud
    pinMode(LED, OUTPUT);
}

char Comp(char* This) {
    while (BTSerial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = BTSerial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}

void loop()
{
    if (Comp("WAKE")==0) {
        BTSerial.write("WAKE COMMAND RECEIVED\n");
        digitalWrite(LED, HIGH);    // if it's a 1 (one) turn LED on
    }
    if (Comp("OFF")==0) {
        BTSerial.write("OFF COMMAND RECEIVED\n");
        digitalWrite(LED, LOW);    // if it's a 1 (one) turn LED on
    }
}
