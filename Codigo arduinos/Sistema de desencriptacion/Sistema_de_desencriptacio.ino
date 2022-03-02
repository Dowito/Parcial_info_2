// C++ code

char bit;
char num = 0b01000000;
void setup()
{
  for (short i = 2;i<=10;i++)
  {
  	pinMode(i, OUTPUT);
  }
}

void loop()
{
  	digitalWrite(2, 0);
	digitalWrite(3, 1);
	digitalWrite(4, 0);
	digitalWrite(5, 1);
	digitalWrite(6, 0);
	digitalWrite(7, 1);
	digitalWrite(8, 0);
	digitalWrite(9, 1);
  /*for (short i = 9;i>=2;i--)
  {
  	bit = num & 0b01;
  	digitalWrite(i, bit);
    num >> 1;
  }
  lectura = digitalRead(11);
  digitalWrite(10, lectura);
  num = 0b01000000;*/
}