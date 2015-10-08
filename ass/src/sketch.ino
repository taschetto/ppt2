#define CMD_SIZE 4

int ledA = 13;
int ledB = 12;
int ledC = 11;
int ledD = 10;

void turnLed(int led, int value) {
  int ledPin = 0;
  switch(led) {
    case 0x00: ledPin = ledA; break;
    case 0x01: ledPin = ledB; break;
    case 0x02: ledPin = ledC; break;
    case 0x03: ledPin = ledD; break;
    default:   ledPin = 0;    break;
  }
  if (ledPin == 0) return;

  if (value == 0x01) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

void blink(int ledPin, int times)
{
  int previousValue = digitalRead(ledPin);
  digitalWrite(ledPin, LOW);
  delay(1000);
  for (int i = 0; i < times; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(800);
  }
  delay(1000);
  digitalWrite(ledPin, previousValue);
}

void showCount(int button, int times)
{
  int ledPin = 0;
  switch(button) {
    case 0x00: ledPin = ledA; break;
    case 0x01: ledPin = ledB; break;
    case 0x02: ledPin = ledC; break;
    default:   ledPin = 0;    break;
  }

  blink(ledPin, times);
}

void runCommand(int* bytes) {
  switch(bytes[0])
  {
    case 0x00: // comando para controlar leds
      turnLed(bytes[1], bytes[2]);
      break;
    case 0x01: // comando para piscar leds de acordo com contagem de cliques 
      showCount(bytes[1], bytes[2]);
      break;
    default:
      break;
  }
}

void setup() {                
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int inBytes[CMD_SIZE] = { 0 };
  int ledPin = 0;

  while (Serial.available() < CMD_SIZE) {}

  for (int i = 0; i < CMD_SIZE; i++)
    inBytes[i] = Serial.read();

  runCommand(inBytes);
}

