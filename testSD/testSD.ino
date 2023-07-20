#include <SD.h>
#include <SPI.h>
//----------------------------------------------


const int chipSelect = 4; //--> chipSelect (CS) Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("Initializing Micro SD card...");
  Serial.println();

  //----------------------------------------------

  Serial.println();
  Serial.print("Micro SD card type : ");

  //----------------------------------------------Print any type of Micro SD card
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
    case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
    case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
    default:
    Serial.println("SD card type unknown !!!"); 
  }
  //----------------------------------------------

  //----------------------------------------------Conditions for finding the type of file system Micro SD Card
  if (!volume.init(card)) {
    Serial.println("Couldn't find the FAT16 / FAT32 file system !!!");
    Serial.println("Make sure the card has been formatted on the FAT16 / FAT32 file system.");
    while (1);
  }
  //----------------------------------------------

  //----------------------------------------------Prints the FAT type of Micro SD card and its sizes.
  uint32_t volumesize;
  
  Serial.println();
  Serial.print("Volume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();

  volumesize *= 512;   
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);

  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.print("Volume size (Gbytes): ");
  float vsg = volumesize;
  float VG  = vsg / 1024;
  Serial.println(VG);
  //----------------------------------------------

  //----------------------------------------------Printing Files on the Micro SD Card
  Serial.println();
  Serial.println("Files found on the Micro SD card (name, date and size in bytes) : ");

  root.openRoot(volume);

  root.ls(LS_R | LS_DATE | LS_SIZE);
  //----------------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
}