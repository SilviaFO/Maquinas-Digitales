//Mandar estas lecturas por BT Serial
//Cada 100ms
#include "FS.h"
#include "SD.h"
#include "SPI.h"


//Loguear la info del sensor barometrico y LDR
#define LED_PIN 33
#define LDR_PIN 35

#include <Adafruit_BMP085.h>//Importar biblioteca

#include "BluetoothSerial.h"

const char *pin = "1234"; 

String device_name = "ESP32-BT-Slave";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial SerialBT; //Objeto BT
Adafruit_BMP085 bmp; //Objeto bmp
char payload[80];

File readings;

void setup() {

  
  Serial.begin(9600);
  SerialBT.begin("Chips"); //Bluetooth device name
  Serial.printf("Bluetooth configurado");
  
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
  if (!bmp.begin(


  )) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(9600);
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
}

void loop() {
  //Hacer el payload de lecturas de sensores
  float pressure = bmp.readPressure();
  float temperature = bmp.readTemperature();
  int luminosity = analogRead(LDR_PIN);

    
    sprintf(payload, "%6.2f, %3.2f, %d", pressure, temperature, luminosity);


  digitalWrite(LED_PIN,HIGH);
    
    readings = SD.open("/lecturas_sensor.csv",FILE_APPEND);
    readings.println(payload);
    readings.close();
    SerialBT.println(payload);
    Serial.println(payload);
  digitalWrite(LED_PIN,LOW);
    delay(500);

}
