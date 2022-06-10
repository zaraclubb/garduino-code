
#include "DHT.h"




#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

//MOISTURE PIN DEFINITIONS
int moistureSensorPin = A0;    // select the input pin for the potentiometer
int moistureSensorValue = 0;  // variable to store the value coming from the sensor
int minMoistureSense;

//UV pin definitions
int UVOUT = A1; //Output from the sensor
int REF_3V3 = A2; //3.3V power on the Arduino board

//HUMIDITY PIN STUFF

  





void setup() {
  //MOISTURE
  // declare the ledPin as an OUTPUT:
  
   Serial.begin(9600);  
//UV SENSOR
  
 
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
 
  Serial.println("ML8511 UV example");

  //DHT

Serial.println(F("DHTxx test!"));

  dht.begin();
 
}

void loop() {
  //MOISTURE
  //read the value from the moisture sensor
  moistureSensorValue = analogRead(moistureSensorPin);    
  delay(1000);          
  Serial.print("moisture sensor = " );                       
  Serial.println(moistureSensorValue); 

  //UV SENSOR
int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;

  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level

  Serial.print("output: ");
  Serial.print(refLevel);

  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);

  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);

  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);

  Serial.println();

  delay(100);

  //DHT
  
// Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);



 Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
 


  
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

  
  

 
