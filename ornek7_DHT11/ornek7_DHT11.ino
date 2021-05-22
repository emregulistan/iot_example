// DHT11 sensorunu okuma, seri porttan haberlesme 
//********************************************************
#include <dht11.h>  // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN D1 // DHT11PIN olarak Dijital 1'yi belirliyoruz.

dht11 DHT11;        // DHT11 nesnesini olusturuyoruz
//********************************************************
void setup()
{
  Serial.begin(9600); // Seri iletişimi başlatıyoruz.
  delay(2000);        // 2sn bekleme
  Serial.println("DHT11 Test Programi");  // seri porttan bilgilendirme
}
//********************************************************
void loop()
{
  DHT11.read(DHT11PIN);   // sensoru oku
  
  // Sensörden gelen verileri serial monitörde yazdırıyoruz.
  Serial.print("Nem (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)DHT11.temperature, 2);

  // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
  delay(2000);
  
}
