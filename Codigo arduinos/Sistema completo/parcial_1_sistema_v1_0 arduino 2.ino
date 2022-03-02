//https://www.tinkercad.com/things/c23zoX6GXdb

#include <LiquidCrystal.h>
#define data 6
#define reloj 7
#define storage 8
#define rVali 9
#define estado 10

char *bits2Byte(bool *arrBits, unsigned long long tamArrBits);
/*
arrBits->arreglo bits.
tamBits->tamaño de arrBits
Agrupa 8 bits para formar 1 byte del mas al menos significativo por cada bloque.
Retorna una cadena de caracteres formado por los bytes resultantes.
*/

unsigned char *desencriptacion(char *arrBytes, bool *arrVali, unsigned long long tam);
/*
arrBytes->Arreglo de bytes encriptados
arrVali->Arreglo de boleano necesario para la clasificacion de la informacion
tam->tamaño de arrBytes/arrVali
returna un arreglo con la informacion desencriptada
*/

bool vali;
bool info;
bool arrInfo[128]={'\0'}; //buffer para guardar la info
bool arrVali[128]={'\0'}; //buffer para guardar las validaicones entrantes
char *arrBytes; //Se asignara por memoria dinamica, y su tamaño sera igual a la cantidad de datos leidos
unsigned long long k = 0; //indice de arrInfo ->La cantidad de datos que se leyeron
unsigned long long i = 0; //indice de arrVali ->La cantidad de bytes procesados.
//LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // initialize the library with the numbers of the interface pins

void setup() {
  Serial.begin(9600);
  pinMode(data,INPUT);
  pinMode(reloj,INPUT);
  pinMode(storage,INPUT);
  pinMode(rVali,INPUT);
  //LCD
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("Datos: ");
}

void loop() {
  if (digitalRead(reloj)){//Señal que me dice cuando leer un bit en camino
  	info = digitalRead(data);
    arrInfo[k] = info;
    Serial.print(bool(arrInfo[k]));
    k++;
    delay(1);
  }
  if (digitalRead(storage)==1){ //señal que me dice cuando se clasifica un byte y que me prepare para leerlo
    delay(1); //esperando a que se procese la señal
  	vali = digitalRead(rVali);
    arrVali[i] = vali;
    Serial.println(bool(arrVali[i]));
    i++;
  }  
  if (digitalRead(estado)==1){ //señal que me dice cuando se terminaron de transmitir todos los datos
    Serial.println("Procesando la informacion...");
    delay(100);
    arrBytes = bits2Byte(arrInfo, k);
    for (unsigned long long j = 0;j<i;j++){
    	Serial.print(byte(arrBytes[j]));
        Serial.print('-');
      	Serial.println(arrVali[j]);
  	}
    unsigned char *infoDeco = desencriptacion(arrBytes, arrVali, i);
    Serial.print("Los datos decodificados son: ");
    for (unsigned long long i=0; infoDeco[i] != '\0';i++ ) {
        Serial.print((unsigned int)(infoDeco[i]));
      	Serial.print(' ');
    }
    Serial.println();
    delay(100);
    
    while(true){ //parte del LCD
    	for (unsigned long long i=0; infoDeco[i] != '\0';i++ ) {
        	lcd.setCursor(0, 1);
  			lcd.print((unsigned int)(infoDeco[i]));
          	delay(500);
    	}
    }  
  }
}

char *bits2Byte(bool *arrBits, unsigned long long tamArrBits)
{
    char *arrBytes = new char [(tamArrBits/8)];
    unsigned long long indxBits=0, indxBytes=0;
    char byte = 0;
    while(indxBits<tamArrBits){ //se recorre todo arrbits
        for (short i=0; i<8; i++) { //Proceso para agrupar bits en un byte desde el mas al menor significativo
            byte = byte | (arrBits[indxBits] << (7-i));//se hace un corrimiento de bits y se usa OR. Esto es equivalente a multiplicar por 0b0X*2^(7-i) y luego sumar.
            indxBits++;
        }
        arrBytes[indxBytes] = byte;//El byte obtenido se almacena
        indxBytes++;
        byte = 0;
    }
    return arrBytes;
}

unsigned char *desencriptacion(char *arrBytes, bool *arrVali, unsigned long long tam)
{
    //Los datos válidos son los dos siguientes a la clave, sólo cuando el tercer dato después de la clave es par.
    unsigned char buffer[tam];
    unsigned long long indx=0;
    for (unsigned long long i=0; i<tam; i++) {
        if(arrVali[i]){
            if (i+3>=tam);//si se sale del arreglo
            else if(arrBytes[i+3]%2==0 | arrBytes[i+3]>0){
                buffer[indx] = arrBytes[i+1];
                indx++;
                buffer[indx] = arrBytes[i+2];
                indx++;
            }
        }
    }
    unsigned char *arrDeco = new unsigned char [indx+1] {'\0'};
    for (unsigned long long i=0; i<indx; i++) {
        arrDeco[i] = buffer[i];
    }

    return arrDeco;
}