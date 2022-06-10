
#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int ledpin =13;
int soilpin = 1;
int buzzer = 12;
int val =0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(ledpin, OUTPUT);
  pinMode(soilpin, INPUT);
  pinMode(buzzer , OUTPUT);
  pinMode(A0, INPUT);//ldr sensor
  dht.begin();
  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  
  Serial.println("");
  val=analogRead(soilpin);
  int ldr = analogRead(A0);
  int ldrmap = map(ldr,0,1023,0,100);
  int soil_moisture=map(val,0,1023,0,100);
  
  
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

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
  Serial.print(" Soil Moisture: ");
  Serial.print(soil_moisture);
  Serial.println("%");
  Serial.print(" sunlight: ");
  Serial.print(ldrmap);
  Serial.print("%");
  Serial.println("");
  if(soil_moisture < 60){
    Serial.println(" Warning!! wet soil");
    digitalWrite(ledpin,HIGH);
  }
  else if(soil_moisture > 90){
    Serial.println(" Warning!! dry soil");
    digitalWrite(ledpin,HIGH);
  }
  else{ 
    digitalWrite(ledpin,LOW);
  }
}
