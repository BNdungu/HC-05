#include <SoftwareSerial.h>

SoftwareSerial bt(16, 17);  
char c = ' ';                  
boolean newLine = true;             
void setup() {
    bt.begin(38400);  
    Serial.begin(115200);
}

void loop()
{
     
    if (bt.available())
    {
        c = bt.read();
        Serial.write(c);
    }
     
    if (Serial.available())
    {
        c = Serial.read();
        bt.write(c);   
 
        if (newLine) { Serial.print(">");  newLine = false; }
        Serial.write(c);
        if (c==10) newLine = true;    
    }
 
}                                                                                                                                     
