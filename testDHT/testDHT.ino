#include "DHT.h"
//----------------------------------------------

#define DHTPIN D3 //--> Arduino pin connected to DHT11 Pin Out   
#define DHTTYPE DHT11 //--> The type of DHT sensor used  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(100);
  
  //----------------------------------------------Starting up the DHT11 Sensor
  Serial.println("Start DHT11");
  dht.begin();
  delay(100);
  Serial.println();
  //----------------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------------Get or update Temperature and Humidity Values
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //----------------------------------------------

  //----------------------------------------------Check if any reads failed and exit early (to try again).
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read Data from DHT sensor!");
    delay(500);
    return;
  }
  //----------------------------------------------

  //----------------------------------------------Printing Temperature and Humidity Values to Serial Monitor
  Serial.print("Temperature : ");
  Serial.print(h);
  Serial.print(" | Humidity : ");
  Serial.println(t);
  delay(2000);
  //----------------------------------------------
}
//=========================================================================================
