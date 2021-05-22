
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

/* Set these to your desired credentials. */
const char *ssid = "CASPER_Network";
const char *password = "aysem210beko"; //min 8 char

const char *sunucu = "maker.ifttt.com"; 
String yol = "";
//****************************************************
void setup() {

  pinMode(D7, INPUT);
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
}
//**********************************************
void loop() {

  String path="/trigger/buton/with/key/k98llcNjFztMrEpcMnd5fNYK122OKH9OCj-S81VEkmd";
  //2)Sunucu baglanma adimi
  WiFiClient istemci;
  if(!istemci.connect(sunucu,80))
  {
    Serial.println("Sunucuya baglanamadi");
    delay(500);
    return;  //baglanmadiysa 500ms beklet return ile tekrar ayni islemi yap
  }

  //3)http protokolu
  yol = "GET /";
  yol+=path;
  yol+= " HTTP/1.1|r\n";  //satir sonu (\r)
  yol+= "Host: ";
  yol+= sunucu;
  yol+= "\r\n";
  yol+= "Connection: close\r\n\r\n";

  istemci.print(yol);
  //*******3sn lik istemci kontrolu************
  unsigned long simdiki_zaman = 0;
  simdiki_zaman = millis();//millis fonksiyonu o anki zamani aldi simdiki_zaman a atadi ör:4000
  while(!istemci.available())
  {
    if(millis() - simdiki_zaman > 3000) //yeniden o anki zamani al ör:4001-4000 > 3000?
    {
     istemci.stop();    //or:yeniden o zamanki degeri al.  7001-4000>3000 3sn doldu
     return;
    }  
  }
   
  //*******************************************
  while(istemci.available())
  {   
      String line = istemci.readStringUntil('\r'); //gelen veriyi satir satir oku
      Serial.println(line);
        
  }
    delay(10000);
    Serial.println(".......................");
}
