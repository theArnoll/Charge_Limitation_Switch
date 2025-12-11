#define gate 33
#define btn 35

bool toggle = false;
uint16_t mins[2] = {60, 60*4}; // {1, 4};

void delayMin(uint16_t min)
{
  unsigned long endTime = millis() + (min * 60000UL);//(min * 1000UL);
  while (millis() < endTime) {
    delay(50); 
    if (digitalRead(btn) == LOW) {
      while(digitalRead(btn) == LOW); 
      return; 
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(gate, OUTPUT);
  digitalWrite(gate, HIGH);
  pinMode(btn, INPUT_PULLUP);
  pinMode(30, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(gate, toggle);
  digitalWrite(30, !toggle);
  delayMin(mins[toggle]);
  toggle = !toggle;
}
