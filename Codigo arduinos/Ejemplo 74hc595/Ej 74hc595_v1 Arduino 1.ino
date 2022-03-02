// C++ code
//
void setup()
{
  for (short i = 2; i<=4; i++){
  	pinMode(i, OUTPUT);
  }
}

void loop()
{
  for (short i = 2; i<=4; i++){
  	digitalWrite(i, 1);
  }
}