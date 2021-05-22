// A0 pininden analog okuma yapan program
// okunan degere gore D0 pinindeki led in 
// aydinlik siddetini degistir
//********************************************************
void setup() 
{
  pinMode(D0, OUTPUT);    // D0 pinini cikis yap
}
//********************************************************
void loop() 
{  
  analogWrite(D0,analogRead(A0));   // D0 a PWM sinyali yolla analogwrite ile
}
