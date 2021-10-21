// define the LEDs. For this exercise, we use the on-board LEDs
#define LED1 2
#define LED2 4
#define S_LED1_TURN_ON 1
#define S_LED1_IS_ON 2
#define S_LED1_TURN_OFF 3
#define S_LED1_IS_OFF 4
#define button1 P1_1
#define debounceDelay 500 //Debounce delay time, in milliseconds.
boolean LEDstate = HIGH; //ON/OFF state of LED
volatile boolean button1_flag = 0;
volatile long lastDebounceTime = 0;
volatile boolean pressed_event_flag = 0;
volatile boolean released_event_flag = 0;
int state_LED1 = S_LED1_TURN_ON;
long timer_LED1;
// delays in millisecond
int delay_LED1 = 500;
// the setup routine runs once when you press reset:
void setup() {
 // initialize the digital pin as an output.
pinMode(LED1, OUTPUT);
// button input and interrupt
pinMode(button1, INPUT_PULLUP);
attachInterrupt(button1, button1_event, CHANGE);
// initialize so that LED is are off
digitalWrite(LED1, LOW);
}
// the loop routine runs over and over again forever:
void loop() {
// led 1
switch (state_LED1) {
 case S_LED1_TURN_ON:
 // turn on LED1
digitalWrite(LED1, HIGH);
 // start the timer for LED1
 timer_LED1 = millis();
 // next state
 state_LED1 = S_LED1_IS_ON;
 break;
 case S_LED1_IS_ON:
 // next state
 if (millis() > timer_LED1 + delay_LED1)
 {
 state_LED1 = S_LED1_TURN_OFF;
 }
 break;
 case S_LED1_TURN_OFF:
 // ADD YOUR CODE HERE
 digitalWrite(LED1, LOW);
 // start the timer for LED1
 timer_LED1 = millis();
 // next state
 state_LED1 = S_LED1_IS_OFF;
 break;
 case S_LED1_IS_OFF:
 // ADD YOUR CODE HERE
 if (millis() > timer_LED1 + delay_LED1)
 {
 state_LED1 = S_LED1_TURN_ON;
 }
 break;
 default:
 // default statements
 break;
}
}
void button1_event()
{
boolean state = digitalRead(button1); //Determine if pressed or released.
 if(state) {
 if(!button1_flag) {
 if((millis() - lastDebounceTime) >debounceDelay) {
 button1_flag = 1;
 digitalWrite(LED1, LOW);
 lastDebounceTime = millis();
 pressed_event_flag = 1;
 }
 }
 }
 else {
 if(button1_flag) {
 if((millis() - lastDebounceTime) >debounceDelay) {
 button1_flag = 0;

lastDebounceTime = millis();
released_event_flag = 1;
 }
 }
 }
}