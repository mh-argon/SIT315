// C++ code
//

const byte LED_PIN = 13;
const byte METER_PIN = A4;
// setting the meter values.
int meterReading = 0;
int meterState = 0;

void setup()
{
  // setting up the pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  setTimerFromPotentiometer();
  
  
  //startTimer();
}

void loop()
{ 
  // improve performance and readability
  delay(500);
  // check for updated values
  setTimerFromPotentiometer();
}

// function for setting the timer based on the object
void setTimerFromPotentiometer()
{
  // sets meterReading to the Potentiometer analog read.
  meterReading = analogRead(METER_PIN);
  // 
  if (meterState != meterReading)
  {
    // sets the meterState to current
    meterState = meterReading;
    // reading value from between 0 and 10
    meterReading = map(meterReading, 0, 1023, 1, 10);
    // set the timer value
    double times_per_second = (double) meterReading;
    // set the timer
    startTimer(times_per_second);
    Serial.println("setting timer to " + String(times_per_second) +  " times per second.");
  }
}

void startTimer(double timerFrequency) 
{
  noInterrupts();
  uint16_t timer_compare = 16000000 / (1024 * timerFrequency) - 1;
  // Clear configurations and resets
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  // CTC setup where it counts up to OCR1A value
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TCCR1B |= (1 << CS10);
  OCR1A = timer_compare;
  TIMSK1 = (1 << OCIE1A);
  sei();
  interrupts();
}


ISR(TIMER1_COMPA_vect){
   digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}

