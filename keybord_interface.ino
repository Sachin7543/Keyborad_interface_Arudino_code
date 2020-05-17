#include <PS2Keyboard.h>
// Macro declaration
#define led_Pin1 7
#define led_Pin2 6
#define led_Pin3 5
#define led_Pin4 4
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define Delete 79
#define OFF    0
#define Start 7
#define Stop 4
#define UP_arrow 11
#define Down_arrow 10

// variable declaration
int ledState = LOW;
unsigned long previous_value = 0;
long interval = 0;
int value = 0;
int LED_select = 0;
/* female USB PIN  interface With Arduino 
 *  vcc :-  5v
 *  Data(-) :- PIN 2
 *  Data(+) :- PIN 3
 *  GND :- GND
 */
// keyborad data reading pin
const int DataPin = 2;
const int IRQpin =  3;
PS2Keyboard keyboard;
void LED_state(void);             // function protocal declaration
void turnOffLed(int led_pin);
int LED_intial = 0;
char c ;
void setup() {
  keyboard.begin(DataPin, IRQpin, PS2Keymap_US);

  // LED intialize to LOW
  for ( LED_intial = Start; LED_intial >= Stop ; LED_intial--)
  {
    pinMode(LED_intial, OUTPUT);
    digitalWrite(LED_intial, LOW);
  }
  // Serial monitor intialization
  Serial.begin(9600);
  Serial.println("<===============**********************============>");
  Serial.println("Author:- Sachin Patil\nTitle:- Controlling LED blinking Without using delay and For LOOP interface With USB keyborad");
  Serial.println("NOTE:- USE EXTERNAL KEYBORD TO OPERATE THIS");
  Serial.println("<===========Welcome to LED Application============>");
  Serial.println("Please Follow below commands:\nPress 1 to glow 1st LED\nPress 2 to glow 2nd LED\nPress 3 to glow 3rd LED\nPress 4 to glow 4th LED");
  Serial.println("Press 0 to stop recently glowing LED\nPress \"delete\" to Stop all LED's\nPress \"up_arrow\" to increase blinking speed\nPress \"down_arrow\" to decrease blinking speed ");
  Serial.println("<=================================================>");

}

void loop() {

  // reading the value in miliseconds
  unsigned long current_value = millis();

  // checking keyboard is availble or not
  if (keyboard.available() > 0)
  {
    // read serial data through keyborad
    c = keyboard.read();
    if (c != 11 || c != 10 )
    {
      value = c - 48;
    }
    Serial.println("You Entered: " + (String)value);
    if ( value == LED1 || value == LED2 || value == LED3 || value == LED4) // select the LED according to the input
    {

      LED_select = value;
      Serial.println("You Selected LED: " + (String)LED_select);
    }
    // checking the value and true set all LED as LOW
    if  ( value == Delete)
    {
      Serial.println(value);
      for ( LED_intial = Start; LED_intial >= Stop ; LED_intial--)
      {
        digitalWrite(LED_intial, LOW);
        LED_select = 0;
      }
      Serial.println("Turned off all LED's");
    }
  }
  // checking value and increment or decrement the time interval
  if ( c == UP_arrow )
  {
    interval = interval + 80;
    Serial.println("Led " + (String)LED_select + " running at speed" + (String)interval);
    c = 0;
  }
  else if ( c == Down_arrow && interval >= 0)
  {
    interval = interval - 80;
    Serial.println("Led " + (String)LED_select + " running at speed" + (String)interval);
    c = 0;
  }

  // checking the current time and interval time
  if (current_value - previous_value >= interval)
  {
    previous_value = current_value;
    //calling the LED according to the LED set
    switch (LED_select)
    {
      case LED1:
        LED_state();
        digitalWrite(led_Pin1, ledState);
        if ( value == OFF) {
         turnOffLed(led_Pin1);
        }
        break;
      case LED2:
        LED_state();
        digitalWrite(led_Pin2, ledState);
        if ( value == OFF) {
          turnOffLed(led_Pin2);
        }
        break;
      case LED3:
        LED_state();
        digitalWrite(led_Pin3, ledState);
        if ( value == OFF) {
          turnOffLed(led_Pin3);
        }
        break;
      case LED4:
        LED_state();
        digitalWrite(led_Pin4, ledState);
        if ( value == OFF) {
          turnOffLed(led_Pin4);
        }
        break;
    }
  }
}
void LED_state(void)
{
  if (ledState == LOW)
  {
    ledState = HIGH;
  }
  else
  {
    ledState = LOW;
  }
}
void turnOffLed(int led_pin)
{
  digitalWrite(led_pin, LOW);
  Serial.println("turned off LED: " + (String)LED_select);
   LED_select = 0;

}

