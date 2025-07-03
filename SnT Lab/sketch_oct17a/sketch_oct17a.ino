#define ntc_pin A0
#define nominal_resistance 10000
#define nominal_temperature 25
#define beta 3950
#define sampling 5
#define Rref 10000
int samples=0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t i;
  float average;
  samples=0;
  for (i=0;i<sampling;i++){
    samples+= analogRead(ntc_pin);
    delay(10);
  }
  average=0;
  average=samples/sampling;
  Serial.print("ADC Readings ");
  Serial.println(average);
  average= 1023/average -1;
  average= Rref/average;
  Serial.print("Thermistor Resistance ");
  Serial.println(average);
  float temperature;
  temperature= average/nominal_resistance;
  temperature=log(temperature);
  temperature/=beta;
  temperature+=1.0/(nominal_temperature +273.15);
  temperature=1.0/temperature;
  temperature-=273.15;
  Serial.print("Temperature is ");
  Serial.print(temperature);
  Serial.println(" Degree C ");
  Serial.println("===================================================");
  delay(2000);
}
