#define gate 34
#define btn 35
#define onboardLED 30
#define lo 11
#define threshold 30  // 3V3, 8b ADC System would be 46, ESP32-C3 SuperMini should using mili volt thing and make it 600mV
/* these are CH552 pin.
   for ESP32C3 SuperMini: gate 0, btn 1, LED 8 */

bool toggle = false;
uint16_t mins[2] = {30, 60*2}; // the loop duration.
                               // default: {30, 60*2} = 30min / 2hr. for testiŋ: {1, 4};

void delayMin(uint16_t min)
{
  unsigned long endTime = millis() + (min * 60000UL);
                      // for testiŋ: (min * 1000UL); to make it seconds rather than minutes 
  while (millis() < endTime) {
    delay(50); 
    if (digitalRead(btn) == LOW) {
      while(digitalRead(btn) == LOW); 
      return; 
    }
    if((analogRead(lo) >= threshold) && toggle) {
      digitalWrite(onboardLED, !(digitalRead(onboardLED)));
      delay(50);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(gate, OUTPUT);
  digitalWrite(gate, HIGH);
  pinMode(btn, INPUT_PULLUP);
  pinMode(onboardLED, OUTPUT);
  pinMode(lo, INPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(gate, toggle);
  digitalWrite(onboardLED, !toggle);
  delayMin(mins[toggle]);
  toggle = !toggle;
}
