// A0 pininden analog okuma yapan program
//********************************************************
void setup() 
{
  pinMode(D0, OUTPUT);    // D0 pinini cikis yap
}
//********************************************************
void loop() 
{
  if(analogRead(A0)>500)    // analog sinyali oku, degeri 500den buyuk mu?
    digitalWrite(D0,HIGH);  // evet buyuk LEDi yak
  else
    digitalWrite(D0,LOW);   // hayir kucuk LEDi SONDUR
}
