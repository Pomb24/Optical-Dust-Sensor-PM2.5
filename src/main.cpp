#include <Arduino.h>
#include <BME280I2C.h>
#include <Wire.h>

BME280I2C bme;

void setup() {
  Serial.begin(115200);

  while(!Serial) {} // Wait

  Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}
void loop()
{
  {
    float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);
 
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? "C" :"F"));
    Serial.print("\t\tHumidity: ");
    Serial.print(hum);
    Serial.print("% RH");
    Serial.print("\t\tPressure: ");
    Serial.print(pres);
    Serial.println("Pa"); // expected hPa and Pa only
    
    delay(1000);
  }
  delay(500);
}
