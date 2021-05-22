// ESP modlununu erisim noktasi olarak ayarla ve uzerinde WEB sunucu calistir
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP8266";       // olusturulan wifi aginin adi
const char *password = "12345678";  // olusturulan wifi aginin sifresi

ESP8266WebServer sunucu(80);        // sunucu nesnensini olusturup, 80 portunu kullan
//************************************************************
void setup() {
  Serial.begin(9600);               // seri portu baslat
  delay(2000);                      // 2sn bekleme
  Serial.println("Erisim noktasi baslatiliyor...");
  WiFi.softAP(ssid, password);      // soft access point i baslat

  IPAddress myIP = WiFi.softAPIP(); // acces point in IP adresini goster
  Serial.print("AP IP address: ");  // acces point in IP adresini goster
  Serial.println(myIP);             // acces point in IP adresini goster
  
  sunucu.on("/", anasayfa);         // 192.168.x.x adresi ki bu yukarida cikan adres
                                    // tiklaninca anasyfa foksiyonunu calistir
  
  sunucu.begin();                   // sunucuyu baslat
  Serial.println("HTTP sunucusu basladi");
}
//************************************************************
void loop() {
  sunucu.handleClient();            // sunucuya baglanan istemcileri karsila
}
//************************************************************
void anasayfa() 
{ // anasayfa tiklaninca Baglandiniz yazisi gonderiliyor                
  sunucu.send(200, "text/html", "<h1>Baglandiniz</h1>");
}
