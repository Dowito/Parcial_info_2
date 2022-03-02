//https://www.tinkercad.com/things/c23zoX6GXdb

#define data 2
#define reloj 3
#define storage 4
#define estado 5

char *getBits(char *cad, unsigned long long tamCad);

//variables
char numPrint1 = 0b10011011; //155
char numPrint2 = 0b10000001; //129
char numPrint3 = 0b00001010; //clave=10
char numPrint4 = 0b10101010; //170
char numPrint5 = 0b10011011; //155
char numPrint6 = 0b01010010; //numero par 82
char tArrBytes[] = {numPrint1,numPrint2,numPrint3,numPrint4,numPrint5,numPrint6};
unsigned long long tam = sizeof(tArrBytes);
char *tArrBits = getBits(tArrBytes,tam);
unsigned long long indx = 0;

//configuracion de puertos
void setup()
{
  Serial.begin(9600);
  pinMode(data, OUTPUT);
  pinMode(reloj, OUTPUT);
  pinMode(storage, OUTPUT);
  pinMode(estado, OUTPUT);
  
  /*for (unsigned long long i = 0;i<tam*8;i++){
    Serial.print(bool(tArrBits[i]));//prueba
  }*/
  digitalWrite(reloj,0);
  digitalWrite(storage,0);
  digitalWrite(estado,0);
  delay(100);
}

void loop()
{   
  if(indx<tam*8){
  	digitalWrite(data,tArrBits[indx]);
    digitalWrite(reloj,1);
    delay(1); //delay para que el otro arduino pueda leer la señal correctamente
    digitalWrite(reloj,0);
    indx++;
    delay(1); //Delay para que el otro arduino se prepare para recibir el proximo dato
    if(indx%8 == 0) {
    	digitalWrite(storage,1);
        delay(1); //delay para que lea la señal correctamente
    	digitalWrite(storage,0);
      	delay(1); //delay necesario para que la señal del circuito se procese y le de tiempo al otro arduino de leerla y de prepararce para recibir el proximo dato
    }
  }
  if(indx==(tam*8)){ //le avisa al otro arduino que ya se transmitieron todos los datos
  	digitalWrite(estado,1);
  }
}

char *getBits(char *cad, unsigned long long tamCad)
{
    //unsigned long long tamCad = lenCad(cad);
    char *arrBits = new char [8*tamCad]; //Los bits totales seran 8*tamCad
    //Transformar cada char de cad en bits y guardarlos desde el mas al menos significativo
    unsigned long long indxBits = 0;
    char bit;//Se guardaran dia bit a bit
    char copyChar;
    for (unsigned long long indxCad = 0; indxCad<tamCad; indxCad++) {
        copyChar = cad[indxCad]; //copia del Caracter al que le sacaremos los bits
        for (short i = 0; i<8; i++) {
            bit = copyChar & 0b01; //se saca el bit menos significativo
            arrBits[indxBits+(7-i)] = bit; //Se iran guardando de esta manera {8,7,6,5,4,3,2,1} ya que vamos sacando dia bit menos significativo y tenemos que guarlos en el arrBits en ese mismo orden
            copyChar = copyChar>>1; //Corrimiento de bit hacia la derecha.
        }
        indxBits+=8;//Saltamos al siguiente bloque
    }
    return arrBits;
}