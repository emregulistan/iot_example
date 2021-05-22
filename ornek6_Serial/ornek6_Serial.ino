// Seri porttan haberlesme ve led yakip sondurma
//********************************************************
void setup() 
{
  pinMode(D0, OUTPUT);    // D0 pinini çıkış yap
  pinMode(D1, OUTPUT);    // D1 pinini çıkış yap
  Serial.begin(9600);     // asenkron veri iletişimi, seri portu başlat, bps yani saniyede iletilecek olan bit sayısı 9600
  delay(2000);                      // 2sn bekleme
}
//********************************************************
void loop() 
{
  digitalWrite(D0, HIGH); // D0 pinini Lojik 1 yap
  digitalWrite(D1, HIGH); // D1 pinini Lojik 1 yap
  Serial.println("LED ler yaniyor");  // seri porttan bu bilgiyi gonder
  delay(500);             // 500ms bekle
  digitalWrite(D0, LOW);  // D0 pinini Lojik 0 yap
  digitalWrite(D1, LOW);  // D1 pinini Lojik 0 yap
  Serial.println("LED ler sonuyor");  // seri porttan bu bilgiyi gonder
  delay(500);             // 500ms bekle
}
