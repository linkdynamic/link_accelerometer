//Define All the Pins
#define PIN_FLASH      0  //use for Hard Reset
#define LED1           5  // D1 GPIO5 another pin for 3.3v

//Sensor Part
//D5 (14) SCL  SCL
//D6 (12) MISO SDIO SDO
//D7 (13) MOSI SDA
//D8 (10) SD3   CS
#define ADXL345_CS    10  // SD3 GPIO10
#define ADXL345_SDO   12  // D6  GPIO12 #This is not used in the code but for records
#define ADXL345_SDA   13  // D7  GPIO13 #This is not used in the code but for records
#define ADXL345_SCL   14  // D5  GPIO14 #This is not used in the code but for records

//The circuit:
// SD card attached to SPI bus as follows:
// MOSI - pin 11 on Arduino Nodemcu D7
// MISO - pin 12 on Arduino Nodemcu D6
// SCK -  pin 13 on Arduino Nodemcu D5
// CS - depends on your SD card shield or module. Pin 4 Nodemcu D2



#define SD_CS   4 //Arduino Ethernet shield: pin 4
