//Firebase Realtime Databese'e DHT11den okudugumuz sicaklik verisi yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<dht11.h>
#define DHT11PIN D1

dht11 DHT11;
float sicaklik=0.0;
//*******************************************
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
  sicaklik_oku_yaz(); //Firebase'e sicaklik yaz
  float turn_on = Firebase.getFloat("TurnOn"); 
  if(sicaklik < turn_on)
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
//**********
void sicaklik_oku_yaz()
{
  DHT11.read(DHT11PIN);
  sicaklik=DHT11.temperature;
  Firebase.setFloat("Sicaklik",sicaklik);

  if(Firebase.failed()){
    Serial.print("Hata kodu:");
    Serial.println(Firebase.error());
    return;
  }
}
