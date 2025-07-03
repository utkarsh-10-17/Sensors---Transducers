#define D0 8
unsigned long last_event = 0;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(D0,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int output = digitalRead(D0);
if(output == HIGH)
{
  if(millis() - last_event >100)
  {
    counter += 1;
    Serial.print(counter);
    Serial.print("     ");
    Serial.print("sound Detected! ");
  }
  last_event = millis();
}
}
