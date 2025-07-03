#include<Q2HX711.h>

const byte MPS_OUT_pin = 2;
const byte MPS_SCK_pin = 3;
int avg_size = 10;

Q2HX711 MPS20N0040D(MPS_OUT_pin, MPS_SCK_pin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float avg_value = 0.0;
  for (int ii=0; ii<avg_size; ii++){
    avg_value += MPS20N0040D.read();
    delay (50);
  }
  avg_value /= avg_size;
  Serial.println(avg_value,0);

}
