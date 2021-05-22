 // ESP modlununu erisim noktasi olarak ayarla ve uzerinde WEB sunucu calistir
#include <dht11.h>          // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN D1         // DHT11PIN olarak Dijital 1'yi belirliyoruz.
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP8266";       // olusturulan wifi aginin adi
const char *password = "12345678";  // olusturulan wifi aginin sifresi

float sicaklik=0.0, nem=0.0;

dht11 DHT11;                    // DHT11 nesnesi olusturuluyor
ESP8266WebServer sunucu(80);    // sunucu nesnensini olusturup, 80 portunu kullan
//************************************************************
void setup() {
  pinMode(D0,OUTPUT);               // led portunu cikis yap
  Serial.begin(9600);               // seri portu baslat
  delay(2000);                      // 2sn bekleme
  Serial.println("Erisim noktasi baslatiliyor...");
  WiFi.softAP(ssid, password);      // soft access point i baslat

  IPAddress myIP = WiFi.softAPIP(); // acces point in IP adresini goster
  Serial.print("AP IP address: ");  // acces point in IP adresini goster
  Serial.println(myIP);             // acces point in IP adresini goster
  
  sunucu.on("/", anasayfa);         // 192.168.4.1 adresi ki bu yukarida cikan adres
                                    // tiklaninca anasyfa foksiyonunu calistir

  sunucu.on("/ledyak",led_yak);     // 192.168.4.1/ledyak adresi tiklaninca led_yak fonskiyonunu cagir
  sunucu.on("/ledson",led_son);     // 192.168.4.1/ledson adresi tiklaninca led_son fonskiyonunu cagir
  
  sunucu.begin();                   // sunucuyu baslat
  Serial.println("HTTP sunucusu basladi");
  
  digitalWrite(D0, LOW);            // baslangic durumu led sonuk
}
//************************************************************
void loop() {
  sunucu.handleClient();            // sunucuya baglanan istemcileri karsila
}
//************************************************************
void anasayfa() 
{ // html sayfa hazirlaniyor, istemcilere gonderiliyor
  sicaklik_olc();               // sicakligi olc, html sayfasina ekle asagida
  String sayfa="<!doctype html>";
  sayfa+="<html>";
  sayfa+="<head>";
  sayfa+="<title> Sekme Basligi </title>";
  sayfa+="</head>";
  sayfa+="<body>";
  sayfa+="<h1> Sicaklik degeri "+ String(sicaklik) + "</h1>";
  sayfa+="<h1> Nem degeri "+ String(nem) + "</h1>";
  sayfa+="</body>";
  sayfa+="</html>";
  sunucu.send(200, "text/html", sayfa);
}
//************************************************************
void led_yak() 
{ // html sayfa hazirlaniyor, istemcilere gonderiliyor
  sunucu.send(200, "text/html", "<h1>LED yandi</h1>");
  digitalWrite(D0,HIGH);    // ledi yak
}
//************************************************************
void led_son() 
{ // html sayfa hazirlaniyor, istemcilere gonderiliyor
  sunucu.send(200, "text/html", "<h1>LED sondu</h1>");
  digitalWrite(D0,LOW);     // ledi sondur
}
//**************** sicaklik olcumu ********************
void sicaklik_olc()
{
  DHT11.read(DHT11PIN);       // sicaklik sensorunu oku
  sicaklik=DHT11.temperature; // sicaklik degerini sicaklik degiskenine ata
  nem=DHT11.humidity;         // nem degerini nem degiskenine ata
  delay(200);                 // 200ms bekle
}
