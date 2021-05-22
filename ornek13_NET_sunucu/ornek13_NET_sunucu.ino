// ESP modlununu evdeki ağa/telefon erisim noktasına bağlayıp, sunucu olarak çalıştırma
// port yonlendirme yaptık ev agindaki modeme baglanip, once bu kod bir kere calistirilip
// seri port ekranindan NodeMCU'nun ev agindan hangi IP adresini aldigina baktik. O IP
// adresini alip modemin ara yuzunden PORT FORWARDING secenegine gidip orada yonlendirme 
// islemini gerceklestirdik. Yonlendirilen port numarasini 80 girdik, sunucumuzu o porttan
// yayin yaptiriyoruz asagidaki kodlarda. Uzak bir pc den evin IP adresi tiklandigi an, ornegin
// 76.152.58.125 veya 76.152.58.125/80 ayni sey, bizim nodemcu Baglandiniz sayfasini gonderiyor.
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "************";    // baglanilacak olan wifi aginin adi  
const char *password = "********";    // baglanilacak olan wifi aginin sifresi

ESP8266WebServer sunucu(80);          // sunucu nesnesini olusturma
//************************************************************
void setup() {
  Serial.begin(9600);               // seri portu baslat
  delay(2000);                      // 2sn bekleme
  Serial.println("Wifi agına baglanıyor");

  WiFi.mode(WIFI_STA);             // istasyon modunda çalış
  WiFi.begin(ssid, password);       // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());      // wifi agindan alinan IP adresini yazdir.
  
  sunucu.on("/", anasayfa);         
  sunucu.begin();                       // sunucuyu baslat. Biri yukaridaki IP adresini tiklayinca gozukcek
  Serial.println("HTTP sunucusu basladi");
}
//************************************************************
void loop() {
  sunucu.handleClient();            // sunucuya baglanan istemcileri karsila
}
//************************************************************
void anasayfa() {
  sunucu.send(200, "text/html", "<h1>Baglandiniz</h1>");
}
