#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void dht_setup(){
    dht.begin();
};

float dht_temp(){
  return dht.readTemperature();
};

float humidity_read() {
  return  dht.readHumidity();
};
