
/*
=======================
FLEET MANAGEMENT SYSTEM
=======================

A fleet management system that monitors:
  1. Engine Temperature
  2. Cargo hold temperature
  3. Fuel Level
  4. GPS location of the truck
The system sends a message to the controller via a whatsApp text message
it also displays lights on the dashboard to alert the driver.

How to set up the system:
  A. Connecting the Engine Temperature sensor:
    1. connect the + => 5v and - => GND
    2. connect the Vout => A0 ***

  B. Connecting Fuel level sensor:
    1. connect the + and -(outside legs) any which way
    2. connect the Vout => A1 ***
    
  B. Connecting the Cargo Temperature Sensor
    1. connect the + => 5v and - => GND
    2. connect the Vout => A2 ***
  
  

  E. Connecting Engine Temperature warning light
    1. Connect - to GND through ressistor
    2. Connect + to port [8]
    ***be sure not to connect the resistor and both terminals of
    *the bulb in the same line
    
  F. Connecting Fuel level light
  *** green light => temperature levels OK
  *** amber light => temperature levels not owkay
  * 
    1. Connect - to GND through ressistor
    2. Connect + to port [5]
    ***be sure not to connect the resistor and both terminals of
    *the bulb in the same line
    *
  D. Connecting Cargo hold Temperature warning light
    1. Connect - to GND through ressistor
    2. Connect + of green light  to port [7]
    3. Connect + of amber light to port [2]
    ***be sure not to connect the resistor and both terminals of
    *the bulb in the same line
   

*/

#define sensorPin A0 //Engine sensor Vout
#define sensorPin3 A1 // Fuel sensor Vout
#define sensorPin2 A2 //Cargo sensor Vout
int engineTemperatureThreshold = 22; //Engine Temperature ranges from 75 - 100 C
int engineTemperatureThresholdMax = 25;
int cargoTemperatureThreshold = 18; // Cargo Temperature ranges 

void blink(){
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(100);
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(100);
    
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT); // Reg cargo Light
  pinMode(7, OUTPUT); // Green Cargo light
  pinMode(8, OUTPUT); //Engine Temperature light
  pinMode(5, OUTPUT); //Fuel light
  
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int engineTemp = analogRead(sensorPin);
  int cargoTemp = analogRead(sensorPin2);
  int fuelSensorInput = analogRead(sensorPin3);
  //
  int fuel = map(fuelSensorInput, 0, 1023, 0, 255);
  int fuel_level = 255 - fuel; //define the fuel level(when sensor output is 255 tank is empty) to switch on light
  analogWrite(5, fuel_level);
  
  

  // Convert the reading into voltage:
  float engineSensorVoltage = engineTemp * (5000 / 1024.0);
  float cargoSensorVoltage = cargoTemp * (5000 / 1024.0);

  // Convert the voltage into the temperature in degree Celsius:
  float engineTemperature = engineSensorVoltage / 10;
  float cargoTemperature = cargoSensorVoltage / 10;

  //send serial output to Raspberry pi
  Serial.print(engineTemperature);
  Serial.print(",");
  Serial.print(cargoTemperature);
  Serial.print(",");
  Serial.println(fuel);  
    

  
  /*
  // Print the Engine Temperature
  Serial.print("Engine Temperature: ");
  Serial.print(engineTemperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");

  // Print the Engine Temperature
  Serial.println("===============");
  Serial.print("Cargo Temperature: ");
  Serial.print(cargoTemperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");
*/
  
  
  //Turn on Light if Engine too hot
  if(engineTemperature >= engineTemperatureThresholdMax){
    // Blink the red LED if the engine temperature is way too fire🥵 🥵
    blink();
  }else if(engineTemperature > engineTemperatureThreshold){
    digitalWrite(8, HIGH);
    
  }else{
    digitalWrite(8, LOW);
  }

  //Turn on light if Cargo room temperature unsuitable for cargo
  if(cargoTemperature > cargoTemperatureThreshold){
    digitalWrite(7, LOW);
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
    digitalWrite(7, HIGH);
  }
  
  delay(5000);
}
