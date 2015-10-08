#define CMD_SIZE 4
#define LED_A 13
#define LED_B 12
#define LED_C 11
#define LED_D 10

void turnLed(int led, int value) {
  int ledPin = 0;
  switch(led) {
    case 0x00: ledPin = LED_A; break;
    case 0x01: ledPin = LED_B; break;
    case 0x02: ledPin = LED_C; break;
    case 0x03: ledPin = LED_D; break;
    default: break;
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
    case 0x00: ledPin = LED_A; break;
    case 0x01: ledPin = LED_B; break;
    case 0x02: ledPin = LED_C; break;
    default: break;
  }
  if (ledPin == 0) return;
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
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int inBytes[CMD_SIZE] = { 0 };
  while (Serial.available() < CMD_SIZE) {}
  for (int i = 0; i < CMD_SIZE; i++)
    inBytes[i] = Serial.read();
  runCommand(inBytes);
}

