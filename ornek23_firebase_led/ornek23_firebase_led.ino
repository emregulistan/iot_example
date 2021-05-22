//Firebase Realtime Database'den okudugmuzu sicaklik verisine gore ledi
//yakip sondurme
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MQTTClient.h>
#include <FirebaseArduino.h>

const char *ssid = "FENERBAHCE";      // baglanilacak olan wifi aginin adi  
const char *password = "aysem210beko";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "iot-1-15646-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "CBAs4SEyNYsnSoKP9Teri3dz1JSCPpW48CfNidVo" //gizli anahtar
//************************************************************

void setup() {
  pinMode(D0,OUTPUT);
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
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
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  Serial.println("Connecting Firebase Realtime Databese");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  digitalWrite(D0,LOW);   
}
//************************************************************
void loop() 
{
  float sicak = Firebase.getFloat("Sicaklik: ");
  Serial.print("Okunan sicaklik degeri: ");
  Serial.println(sicak);
  if(sicak < 24)
  {
    Serial.println("LED yaniyor");
    digitalWrite(D0,HIGH); 
  }
  else
  {
    Serial.println("LED sonuyor");
    digitalWrite(D0,LOW);
  }
  delay(5000);
  
}
