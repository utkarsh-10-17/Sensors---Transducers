#define MQ2pin A0
float sensorvalue;

void setup(){
  Serial.begin(9600);
  Serial.println("MQ2 Warming up!");
  delay(20000);
}

void loop()
{
  sensorvalue = analogRead(MQ2pin);
  Serial.print("sensor value ");
  Serial.println(sensorvalue);
  delay(2000);
}

