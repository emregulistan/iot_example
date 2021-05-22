//Firebase Realtime Databese'e DHT11den okudugumuz sicaklik verisi yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "ThingSpeak.h"
//*******************************************
const char *ssid = "DSMART_4DB33C";      // baglanilacak olan wifi aginin adi  
const char *password = "cEqyYrzx";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "iot-1-a954b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "GQ4SDF8beXv1O30SzP8OulVsk2kSJAFlGcPsYtPA" //gizli anahtar
#define SECRET_CH_ID 1279812 //Proje adinin altinda 
const char *SECRET_WRITE_APIKEY = "OBE5QF6HHJPT74EP"; //API Keys bolumunde
WiFiClient wifi_istemci;

int firebase_oku = 0;
//************************************************************
void setup() {
  
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

  
}
//************************************************************
void loop() 
{
   
   firebase_oku = Firebase.getInt("iot");
  
   if(Firebase.failed()){
    Serial.print("Hata kodu:");
    Serial.println(Firebase.error());
    return;
  }
  delay(5000);

 ThingSpeak.begin(wifi_istemci);

  int x = ThingSpeak.writeField(SECRET_CH_ID, 1, firebase_oku, SECRET_WRITE_APIKEY); 
  
  if(x == 200){
    Serial.println("Kanala veri yazildi");
  }
  else{
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
  }
  delay(3000); 

}
