
//=========================================================================================Arduino Data Logger Micro SD Card
//----------------------------------------------Includes Libraries
#include "RTClib.h"

#include "DHT.h"

#include <SD.h>
#include <SPI.h>
//----------------------------------------------
File myFile; //--> File Initialization
RTC_DS1307 rtc; //--> Initialize RTC_DS1307

#define DHTPIN 2 //--> Arduino pin connected to DHT11 Pin Out   
#define DHTTYPE DHT11 //--> The type of DHT sensor used  
DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = 4; //--> chipSelect (CS) Pin

unsigned long previousMillis = 0; //--> will store last time was updated
const long interval = 1000; //--> interval (1000 = 1 second)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //----------------------------------------------Initializing Micro SD Card
  Serial.println("Initializing Micro SD Card...");
  delay(100);

  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    while (1);
  }

  Serial.println("Successfully Initializing Micro SD Card");
  Serial.println();
  delay(100);
  //----------------------------------------------

  Serial.println("Initializing RTC DS1307...");
  delay(100);

  //----------------------------------------------Initializing RTC DS1307
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //----------------------------------------------

  Serial.println("Successfully Initializing the RTC DS1307");
  Serial.println();

  Serial.println("Starting to run RTC DS1307...");
  delay(100);
  Serial.println("Setting the Date and Time...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); //--> Set Date and Time manually
  delay(100);
  Serial.println("Successfully Setting Date and Time");
  Serial.println();

  //----------------------------------------------Checks whether the DS1307 RTC can be run or not
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> If that doesn't work, use this line of code outside of "if (! rtc.isrunning())"
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //----------------------------------------------

  //----------------------------------------------Set the Date and Time on the DS1307 RTC
  // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
  //Serial.println("Setting the Date and Time...");
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Use this line of code if it doesn't work in "if (! rtc.isrunning())"
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  //delay(100);
  //Serial.println("Successfully Setting Date and Time");
  //Serial.println();
  // If the time and date are successfully set, then deactivate the code line (make the code a comment), then re-upload the code.
  // if not done then the time and date will return to the beginning when it was set when arduino is reset or restarted.
  //----------------------------------------------

  Serial.println("Successfully running RTC DS1307");
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
  //___________________________________________________________________________________Millis to update the Date, Time, Temperature and Humidity
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    DateTime now = rtc.now(); //--> Get or update the Date and Time

    //----------------------------------------------Get or update Temperature and Humidity Values
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    int h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    //----------------------------------------------

    //----------------------------------------------Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read Data from DHT sensor!");
      delay(500);
      return;
    }
    //----------------------------------------------

    //___________________________________________________________________________________Conditions for writing data to a Micro SD Card
    // Data Date, Time, Temperature and Humidity will be written to the Micro SD Card if Seconds are worth 0,5,10,15,20 and so on
    if (now.second() %5 == 0) {
      Serial.println("----");
      //----------------------------------------------Printing Date and Time to Serial Monitor
      Serial.print(now.day(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.year(), DEC);
      Serial.print(" ");   
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.println();
      //----------------------------------------------

      //----------------------------------------------Printing Temperature and Humidity Values to Serial Monitor
      Serial.print("Temperature : ");
      Serial.print(h);
      Serial.print(" | Humidity : ");
      Serial.println(t);
      Serial.println();
      //----------------------------------------------
    
      //___________________________________________________________________________________Write to Micro SD Card
      //----------------------------------------------Opening files that have been specified on the Micro SD Card
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      myFile = SD.open("DH.txt", FILE_WRITE);
      //----------------------------------------------
    
      //----------------------------------------------Writing Data to the specified file on the Micro SD Card
      // if the file opened okay, write to it:
      if (myFile) {
        Serial.println("Writing to DHT11Log.txt...");
        
        //----------------------------------------------Writing Date Data to Micro SD Card
        myFile.print(now.day());
        myFile.print("-");
        myFile.print(now.month());
        myFile.print("-");
        myFile.print(now.year());
        //----------------------------------------------
        
        myFile.print(","); //--> Write the delimiter between the data in the form of a comma character to the Micro SD Card

        //----------------------------------------------Writing Time Data to Micro SD Card
        myFile.print(now.hour());
        myFile.print(":");
        myFile.print(now.minute());
        myFile.print(":");
        myFile.print(now.second());
        //----------------------------------------------
    
        myFile.print(","); //--> Write the delimiter between the data in the form of a comma character to the Micro SD Card
        
        myFile.print(t); //--> Writing Temperature Data to Micro SD Card
    
        myFile.print(","); //--> Write the delimiter between the data in the form of a comma character to the Micro SD Card
    
        myFile.println(h); //--> Writing Humidity Data to Micro SD Card
          
        myFile.close(); //--> close the file
        
        Serial.println("Successfully writing Data to Micro SD Card");
        Serial.println("----");
        Serial.println();

      } else {      
        Serial.println("Error opening DHT11Log.txt"); //--> if the file didn't open, print an error
      }
      //----------------------------------------------
      //___________________________________________________________________________________
    }
    //___________________________________________________________________________________
  }
  //___________________________________________________________________________________
}
//=========================================================================================