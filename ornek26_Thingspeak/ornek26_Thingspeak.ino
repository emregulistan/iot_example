//ESP modulu Thingspeak.com sitesine veri gonderecek
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char *ssid = "CASPER_Network";
const char *password = "aysem210beko"; //min 8 char

#define SECRET_CH_ID 1276093
const char *SECRET_WRITE_APIKEY = "NS1FVI90EYRXD2CY";
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
  float deger = 34.5;
  int x = ThingSpeak.writeField(SECRET_CH_ID, 1, deger, SECRET_WRITE_APIKEY); //alan1'e 34.5 yaz
  if(x == 200){
    Serial.println("Kanala veri yazildi");
  }
  else{
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
  }
  delay(18000); //thingspeak sitesi 15 saniyede bir guncelleme yapiyor o yuzden 18sn bekle
}
//**********************************************
