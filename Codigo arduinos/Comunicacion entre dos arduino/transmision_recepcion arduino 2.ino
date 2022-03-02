#define reloj 2
#define data 3
#define dTime 1

char rBit;
char rArrBits[1000]; //donde se guardaran todos los bits leidos
unsigned long long cont = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop()
{
  if (digitalRead(reloj) == 1){
    rBit = digitalRead(data);
    rArrBits[cont] = rBit;
    Serial.print(bool(rBit));
    cont++;
    if(cont%8==0) Serial.print('-');
    delay(dTime);
  }
}