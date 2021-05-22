//ESP modulu Thingspeak.com sitesine sicaklik gonderecek
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <dht11.h>
#define DHT11PIN D1

const char *ssid = "CASPER_Network";
const char *password = "aysem210beko"; //min 8 char

#define SECRET_CH_ID 1276093
const char *SECRET_WRITE_APIKEY = "NS1FVI90EYRXD2CY";

float sicaklik = 0.0, nem = 0.0;
dht11 DHT11;
WiFiClient wifi_istemci;
//****************************************************

void setup() {
 
  Serial.begin(9600); //seri portu baslat
  delay(1500); //1500ms = 1.5sn 
  Serial.println("Wifi agina baglaniyor");
  
  //1)Wifi baglanma adimi
  WiFi.mode(WIFI_STA);  //istasyon modunda calis
  WiFi.begin(ssid, password); //SSID'si yukarida belirtilmis olan wifi a baglan
  
  while (WiFi.status() != WL_CONNECTED) //baglanti kontrol
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());
  
   ThingSpeak.begin(wifi_istemci);
}
//**********************************************
void loop() {

  sicaklik_olc();
  ThingSpeak.setField(1, sicaklik);
  ThingSpeak.setField(2, nem);
  ThingSpeak.setField(3, 45);
  
  int x = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY); //alan1'e sicaklik yaz
  if(x == 200){
    Serial.println("Kanala veri yazildi");
  }
  else{
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
  }
  delay(18000);
  
}
//**********************************************
/*SICAKLIK OLCUMU*/
void sicaklik_olc()
{
  DHT11.read(DHT11PIN);
  sicaklik = DHT11.temperature;
  nem = DHT11.humidity;
  delay(200);
}
