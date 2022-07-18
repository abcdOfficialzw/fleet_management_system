#define sensorPin A0
int threshold = 25;
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(sensorPin);

  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0); //reading  * (vref/1024.0)

  // Convert the voltage into the temperature in degree Celsius:
  float temperature = voltage / 10;

  // Prit the temperature in the Serial Monitor:
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");
  

 if(temperature > threshold){
      digitalWrite(13, HIGH); //turn on the fan
      Serial.println("Fan is now on!");
    }
 else{
    digitalWrite(13, LOW);
    Serial.println("Fan turned off!");
  }

  delay(1000);// wait a second between readings
}