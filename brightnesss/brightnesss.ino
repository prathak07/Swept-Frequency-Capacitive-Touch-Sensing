int potPin=0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int val=analogRead(potPin);
  Serial.println(val);
  delay(50);
}

