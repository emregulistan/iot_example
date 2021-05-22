// ESP modlununu istasyon, station olarak ayarla, nete baglanip tarih bilgisini cekme
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "************";    // baglanilacak olan wifi aginin adi  
const char *password = "********";    // baglanilacak olan wifi aginin sifresi

const char *sunucu = "time.is";         // time.is sitesine baglanilacak
String yol="";
String tarih="";
//************************************************************
void setup() {
  Serial.begin(9600);         //seri portu baslat
  delay(1500);                // 1500 ms = 1.5sn
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
  String path="/Kütahya,_Kütahya";      // time.is sitesinde kutahya sayfasina gitmek icin
  WiFiClient istemci;                   // istemci nesnesini olustur
  if (!istemci.connect(sunucu, 80))     // isemci nesnesi sunucuya 80 portundan baglandi mi?
  {
    Serial.println("Sunucuya baglanamadi");
    delay(500);
    return;                              // loop un basina git
  }     

  // sunucuya baglandi, http protokolunu olustur, sayfayi istemek icin                     
  yol="GET ";
  yol+=path;
  yol+= " HTTP/1.1\r\n";
  yol+="Host: ";
  yol+=sunucu;
  yol+="\r\n";
  yol+="Connection: close\r\n\r\n";

  istemci.print(yol);                   // sayfa istegini gonder
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
  {
    String line = istemci.readStringUntil('\r');  // gelen veriyi satır satır oku
    
    // Serial.println(line);             // okudugunu seri porttan gonder
    
    // ***** ilk once ustteki satir yorum degilken calistirildi,seri portta gelen bilgiye
    // ***** baktik, Date: ile baslayan kisim sonrası tarih bilgisi geliyormus, o yuzden 
    // ***** asagida Date sonrasi bilgiyi cekmek icin string islemleri yapacagiz.
    
    //------------- String filtreleme işlemi için 1. yol  ----------
    int var_mi=line.indexOf("Date:");   // okunan satirda Date: indexini al
    if(var_mi!= -1)                     // index -1 ise Date yok demektir.
    {                                   // Date: var ise, substring islemini yap
      //------------- String filtreleme işlemi için 1. yol  ----------
      // ***** 7 bilgisi-> "Date: " burada 6 karakter var 7. karakterden itibaren al
      // ***** 23 bilgisi-> "Date: Thu, 26 Nov 2020" burada 22 karakter var 23. karaktere kadar al
      
      tarih=line.substring(7,23);
      
      //------------- String filtreleme işlemi için 2. yol -----------
      // ***** 6 bilgisi-> "Date: " burada 6 karakter var 
      // ***** 22 bilgisi-> "Date: Thu, 26 Nov 2020" burada 22 karakter var
      
      //for(int i=(var_mi+6);i<(var_mi+22);i++)   
      //  tarih+=line[i]; 
    }
  }
  Serial.print("Tarih: ");
  Serial.println(tarih);
  tarih="";                            // 2.yol kullanılırsa diye içeriğini temizle
  Serial.println("............................");
}
