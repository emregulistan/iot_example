// ESP modlununu istasyon, station olarak ayarla, diğer ESP sunucusuna baglanma
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "********";      // baglanilacak olan wifi aginin sifresi

const char *sunucu = "78.179.117.60";   // ornek13_NET_sunucu programinin bagli oldugu agin IP adresi
String yol="";
//************************************************************
void setup() {
  Serial.begin(9600);   //seri portu baslat
  delay(2000);                      // 2sn bekleme
  Serial.println("Wifi agına baglanıyor");

  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());      // wifi agindan alinan IP adresini yazdir.
}
//************************************************************
void loop() 
{
  WiFiClient istemci;               // istemci nesnesini olustur
  if (!istemci.connect(sunucu, 80)) // isemci nesnesi sunucuya 80 portundan baglandi mi?
  {
    Serial.println("Sunucuya baglanamadi");
    delay(500);
    return;                         // loop un basina git
  } 
  
  // sunucuya baglandi, http protokolunu olustur, sayfayi istemek icin           
  yol="GET /";
  yol+= " HTTP/1.1\r\n";
  yol+="Host: ";
  yol+=sunucu;
  yol+="\r\n";
  yol+="Connection: close\r\n\r\n";

  istemci.print(yol);               // anasayfa istegini gonder
  //*************** 3sn lik istemci kontrolu*****************
  unsigned long simdiki_zaman = 0;
  simdiki_zaman = millis();             // millis fonksiyonu o anki zamanı aldı simdiki_zaman değişkenine atadı. örneğin simdiki_zaman=4000
  
  while(!istemci.available())           // istemciye bilgi gelmemis mi?
  {                                     // gelmemis bekleme
      if(millis()-simdiki_zaman>3000)   // örneğin yeniden o anki zamanı al. 4001-4000=1>3000?
      { 
        istemci.stop();                 // örneğin yeniden o anki zamanı al. 7001-4000=3001>3000. 3 sn doldu
        return;                         // istemci durduruldu loop basina don
      }
  }
  //********************************************************
  while (istemci.available())           // istemciye bilgi gelmis mi?
  {                                     // geldigi surece satir satir veri oku
    String line = istemci.readStringUntil('\r');  // gelen veriyi satır satır oku
    Serial.println(line);               // okudugunu seri porttan gonder
  }
  Serial.println("............................");
}
