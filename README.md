# What I want to achieve

I want to replace DummySensor.h header with I2CArduino.h. This mDot node will act as a slave for reading data transfered from the Arduino i2c bus. The arduino will read from some sensors and generate a string ready to be transfered on the bus.

## Arduino testing simple SKETCH

```
#include <DHT.h>
#include <Wire.h>
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 10
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

// Para pasar float (son 4 bytes) a byte
const byte mDotAddress = 2;
const byte dataCount = 1;
typedef union {
 float floatData;
 byte  rawData [dataCount * sizeof (float)];
} myData;
unsigned long lastSerialPrint = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  // Comenzamos el sensor DHT
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  // Leemos la humedad relativa
  myData h;
  h.floatData = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  myData t;
  t.floatData = dht.readTemperature();
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h.floatData) || isnan(t.floatData)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  Serial.print("Humedad: ");
  Serial.print(h.floatData);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t.floatData);
  Serial.println(" *C ");

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("/Humedad:");        // sends 9 bytes
  for (int i=0; i<4; i++) {
    Wire.write(h.rawData[i]); // Print the hex representation of the float
  }
  Wire.write("/Temperatura:"); // 13 bytes
  for (int i=0; i<4; i++) {
    Wire.write(t.rawData[i]); // Print the hex representation of the float
  }
  Wire.endTransmission();

}
```
