#include <CapacitiveSensor.h>

byte RedLED = 11; 
byte BluLED = 9;
byte GrnLED = 8;  

CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_5 = CapacitiveSensor(2,5);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_6_7 = CapacitiveSensor(2,7);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
int iterations = 0;
int ledr = 0;
int ledg = 0;
int ledb = 0;

int cap1 = 10; 
int cap2 = 10;
int cap3 = 10;



unsigned long time;

void setup()                    
{
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

   pinMode(13, OUTPUT);
   pinMode (10, OUTPUT); 
   pinMode (RedLED, OUTPUT);
   pinMode (BluLED, OUTPUT);
   pinMode (GrnLED, OUTPUT);
}

void loop()                    
{
    iterations ++;

    long start = millis();
    long total1 =  cs_2_3.capacitiveSensor(30);
    long total2 =  cs_4_5.capacitiveSensor(30);
    long total3 =  cs_6_7.capacitiveSensor(30);
    
    //Serial.print(millis() - start);        // check on performance in milliseconds
    //Serial.print("\t");                    // tab character for debug windown spacing
    time = millis();
  
    Serial.print("cap 1 is ");
    Serial.println(total1);                  // print sensor output 1
    
    
    
    if((total1/cap1 <= 1.1) && (total1/cap1 >= .9 ))
    {
      cap1 += total1;
    }

    Serial.print("cap 2 is " );
    Serial.println(total2);                  // print sensor output 2
    if((total2/cap2 <= 1.1) && (total2/cap2 >= .9 ))
    {
      cap2 += total1;
    }
    
    Serial.print("cap 3 is " );
    Serial.println(total3);                // print sensor output 3

    if((total3/cap3 <= 1.1) && (total3/cap3 >= .9 ))
    {
      cap3 += total3;
    }

    Serial.println("   ");
    delay(550);        

    // arbitrary delay to limit data to serial port 

//compare total1 to the avg of cap 1, total2 to avg of cap 2, and total3 to avg of cap3

//light LED based on %diff from baseline
double avg1 = cap1/iterations;
double avg2 = cap2/iterations;
double avg3 = cap3/iterations;


double percentDiff1 = total1/avg1;
double percentDiff2 = total2/avg2;
double percentDiff3 = total3/avg3;

if(percentDiff1 > percentDiff2 && percentDiff1 > percentDiff3 )
  {
   ledr = 255;
   ledg = 0;
   ledb = 0;
   
  }  
  else if(percentDiff2 > percentDiff1 && percentDiff2 > percentDiff3)
  {
   ledg = 255;
   ledr = 0;
   ledb = 0;
   
  }  
  else if(percentDiff3 > percentDiff2 && percentDiff3 > percentDiff1)
  {
   
    ledb = 255;
    ledg = 0;
    ledr = 0;
    
  }  


  Serial.println(ledr);
  Serial.println(ledg);
  Serial.println(ledb);

 digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

    digitalWrite(10,HIGH); // Enable the circuit
    analogWrite(RedLED, ledr); 
    analogWrite(GrnLED, ledg); 
    analogWrite(BluLED, ledb);

}
