// Buton okuma programi, buton durumuna gore led yak
// veya sondur yapıyor
//********************************************************
void setup() 
{
  pinMode(D0, OUTPUT);      // D0 pinini cikis yap
  pinMode(D1, OUTPUT);      // D1 pinini cikis yap
  pinMode(D7, INPUT);       // D7 pinini giris yap
}
//********************************************************
void loop() 
{
  if(digitalRead(D7)==LOW)    // D7 pull-up yapilmis buton var, butona basıldı mi?
  {
    digitalWrite (D0, HIGH);  // evet basildi, ledleri yak
    digitalWrite (D1, HIGH);
  }
  else
  {
    digitalWrite (D0, LOW);   // hayir basilmadi, ledleri sondur
    digitalWrite (D1, LOW);
  }  
}
