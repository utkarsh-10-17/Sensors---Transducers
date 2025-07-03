const int ledPin = 13; // Pin number for the LED
const int buttonPin = 2; // Pin number for the push button
void setup()
{
pinMode(ledPin, OUTPUT); // Set the LED pin as an output
pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as aninput with pull-up resistor
digitalWrite(ledPin, LOW); // Turn off the LED initially
Serial.begin(9600); // Initialize Serial communication
}
void loop()
{
int buttonState = digitalRead(buttonPin); // Read the button state
if (buttonState == LOW) { // Button is pressed (LOW)
digitalWrite(ledPin, HIGH); // Turn on the LED
Serial.println("LED ON");
} else {
digitalWrite(ledPin, LOW); // Turn off the LED
Serial.println("LED OFF");
}
delay(100); // Add a small delay for stability
}