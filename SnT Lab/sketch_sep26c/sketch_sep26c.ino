int IRSensor = 7;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("Serial Working");
pinMode(IRSensor,INPUT);
pinMode(LED_BUILTIN,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorStatus = digitalRead(IRSensor);
  if(sensorStatus == 1)
  {
    digitalWrite(LED_BUILTIN,LOW);
    Serial.println("motion detected!");
    }
    else{
      digitalWrite(LED_BUILTIN,HIGH);
      Serial.println("MOTIN eNDED!");
    }

}
