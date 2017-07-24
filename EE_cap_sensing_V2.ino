#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_6_7 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup()                    
{
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

   pinMode(13, OUTPUT);
}

void loop()                    
{
  
    long start = millis();
    long total1 =  cs_2_3.capacitiveSensor(30);
    long total2 =  cs_4_5.capacitiveSensor(30);
    long total3 =  cs_6_7.capacitiveSensor(30);

    //Serial.print(millis() - start);        // check on performance in milliseconds
    //Serial.print("\t");                    // tab character for debug windown spacing

    Serial.println(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.println(total2);                  // print sensor output 2
    //Serial.print("\t");
    Serial.println(total3);                // print sensor output 3

    delay(70);                             // arbitrary delay to limit data to serial port 

  if(total1 > 450 || total2 > 450 || total3 > 350 )
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  }  
  else{
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  }   
}
