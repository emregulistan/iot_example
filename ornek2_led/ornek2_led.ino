// LED yakma Programi D0,D1,D2,D3 pinlerine bagli olan
//********************************************************
void setup() 
{
  pinMode(D0, OUTPUT);    // D0 pinini cikis yap
  pinMode(D1, OUTPUT);    // D1 pinini cikis yap
  pinMode(D2, OUTPUT);    // D2 pinini cikis yap
  pinMode(D3, OUTPUT);    // D3 pinini cikis yap
}
//********************************************************
void loop() 
{
  digitalWrite(D0, HIGH);   // D0 pinini lojik high a cektim
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D1, HIGH);
  delay(500);               // 500ms bekleme
  digitalWrite(D1, LOW);    // D0 pinini lojik low a cektim
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D0, LOW);
  delay(500);               // 500ms bekleme
}
