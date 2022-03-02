// C++ code
void serial74HC595(unsigned char byte);
/*
Transfiere un byte de manera serial a un circuito integrado 74HC595 el cual lo paraleliza
Con esta funcion mandamos los bits del menos significativo al mas significativo, por lo cual en la memoria de ddezplazamieto del 74hc595 se guardaran
en ese mismo orden.
10100101 si mandamos esto, en el 74hc595 se guardaran en ese mismo orden.
A diferencia que si transfirieramos los bits del mas al menos significativo; eso significaria que en el 74hc595 se guardarian ene l orden contrario.
si mandamos 10000101 -> 10100001 en la memoria de dezplazamiento de guardan en orden invertido, el mas pasaria a ser el menos significativo. Hay que tener
esto muy presente si se mandan de esta manera
*/

//variables
unsigned char numPrint1 = 0b10011011;
unsigned char numPrint2 = 0b10000001;
unsigned char numPrint3 = 0b10101010;
unsigned char nums[3] = {numPrint1,numPrint2,numPrint3};

//configuracion de puertos
void setup()
{
  for (short i=2; i<=4; i++){
  	pinMode(i,OUTPUT);
  }
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}

void loop()
{
  for (short i=0;i<3;i++){
  	serial74HC595(nums[i]);
    delay(500);
    
  }
}

void serial74HC595(unsigned char byte){
    unsigned char bit;
    for (short i=1; i<=8; i++) {
        bit = byte & 0b01;
      	if (bit == 0){//mandamos el bit
        	digitalWrite(2, LOW);
        }
      	else {
        	digitalWrite(2, HIGH);
        }
        //ya que tenemos el bit a transferir, le indicamos al circuito que lo reciba activando el reloj de dezplazamiento
        digitalWrite(3,HIGH);//Aqui el cirtuito guarda el bit
        delay(1);
        digitalWrite(3,LOW);//se cierra para el proximo ciclo
        byte = byte >> 1;
    }
    digitalWrite(4,HIGH);//liberamos los bits al exterior guardados en la memoria de dezplazamiento
    digitalWrite(4,LOW);
}