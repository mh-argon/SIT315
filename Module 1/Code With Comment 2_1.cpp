
//Setting the variables BTN_PIN and LED_PIN to 2 and 13 as constants.
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

//Setting the state of buttonPrevState and ledState to low initially.
uint8_t buttonPrevState = LOW;
uint8_t ledState = LOW;

// the primary setup for the sketch.
void setup()
{
  // setting up BTN_PIN as a INPUT_PULLUP with internal pullup resistor.
  pinMode(BTN_PIN, INPUT_PULLUP);
  //Setting the LED_PIN as an output pin. In this casse pin 13.
  pinMode(LED_PIN, OUTPUT);
  //setting the serial communcation at a baud rate of 9600bps
  Serial.begin(9600);
}

void loop()
{
  // setting buttonState to read the output of the BTN_PIN.
  uint8_t buttonState = digitalRead(BTN_PIN);
  
  //Prints the buttonState, buttonPrevState, ledState, and a additional line.
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");
  
  
  // if there is a change from previous state, ledState is set to high. set LED_PIN to ledState. 
  if(buttonState != buttonPrevState)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  buttonPrevState = buttonState;
    
  //Delays the overall runtime by 500 milliseconds
  delay(500);
}