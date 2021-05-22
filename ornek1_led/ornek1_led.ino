// LED yakma Programi D0 ve D1 pinlerine bagli olan
// ledleri ters bir sekilde yakiyor
//********************************************************
void setup() 
{
  pinMode(D1,OUTPUT);     // D1 pinini cikis yap
  pinMode(D0,OUTPUT);     // D0 pinini cikis yap
}
//********************************************************
void loop() 
{
  digitalWrite(D1, LOW);  // D1 pinini lojik low a cektim
  digitalWrite(D0, HIGH); // D0 pinini lojik high a cektim
  delay(500);             // 500ms bekleme
  digitalWrite(D1, HIGH); // D1 pinini lojik high a yaptım
  digitalWrite(D0, LOW);  // D0 pinini lojik low a cektim
  delay(500);             // 500ms bekleme
}
