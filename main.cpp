#include <iostream>
#include <Auxiliar.h>
using namespace std;

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

bool pruebaDesencript(char caracter, char bandera);
/*
Programa que simula el proceso de identificar la informacion verdadera o false,
recibe un numero (tipo char) y lo compara con la bandera.
return True si son iguales, false de lo contrario
*/

void tArduino(char byte);
/*
Transmision de un byte de un arduino a otro de forma serial
Del bit mas al menos significativo
*/

unsigned char rArduino(unsigned char lectura);
/*
Recibe un byte de manera serial
*/

void tBitArduino(unsigned char tBit);
/*
tBit-> bit (0b00 o 0b01)
Manda un bit a un arduino receptor
*/

void rBitArduino(unsigned char &rBit, unsigned char tBit);
/*
&rBit->Variable donde se guardara el bit por referencia
tBit ->Solo funciona como ejemplo de la simulacion
Recibe un bit por un puerto digital.
Espera señal de reloj para recibir dicho bit
*/

int main()
{
    unsigned char byte = 'a';
    unsigned char arr2[] = {134,48,63,13,32,165,94};
    serial74HC595(byte);
    pruebaDesencript(32, 32);
    tArduino(arr2[0]);
    byte = rArduino(arr2[0]);
    return 0;
}

void serial74HC595(unsigned char byte){
    unsigned char bit;
    unsigned char relojShift = 0;
    unsigned char relojStorage = 0;
    for (short i=1; i<=8; i++) {
        bit = byte & 0b01;
        //ya que tenemos el bit a transferir, le indicamos al circuito que lo reciba activando el reloj de dezplazamiento
        relojShift = 1;//Aqui el cirtuito guarda el bit
        relojShift = 0;//se cierra para el proximo ciclo
        byte = byte >> 1;
    }
    relojStorage = 1;//liberamos los bits al exterior guardados en la memoria de dezplazamiento
    relojStorage = 0;
}

bool pruebaDesencript(char caracter, char bandera){
    bool *bits = getBits(&caracter,1);
    bool *bitsBandera = getBits(&bandera,1);
    bool outXOR[8];
    for (short i=0;i<8;i++) {
        outXOR[i] = bits[i] ^ bitsBandera[i]; //Si todos los valores de outXOR son 0, los numeros son iguales
    }
    bool outOR;
    outOR = outXOR[0];
    for (short i=1;i<8;i++ ) {
        outOR = outOR | outXOR[i]; //Comparamos todos los output de XOR usando OR, asi si el resultado es 0, eso quiere decir que son iguales.
    }
    bool resultado = !outOR; //negamos el resultado que nos dio antes, asi 1 sera que son iguales, 0 son distintos
    return resultado;
}

void tArduino(char byte)
{
    unsigned char bit;
    unsigned char reloj = 0;
    for (short i=0; i<8; i++) {
        bit = byte & 0b10000000; //Mandaremos del mas significativo al menos significativo
        byte = byte << 1;
        if (bit == 0b10000000){
            cout << '1'; //bit = 0b01
        }
        else cout << '0'; //bit = 0b00
        reloj = 1; //Mandamos una señal para avisarle al arduino receptor que debe de recibir un bit
        reloj = 0;
        //Delay para dar tiempo a que la informacion que se mando se procese bien
    }
 }

unsigned char rArduino(unsigned char lectura)
{
    unsigned char byte = 0;
    unsigned char lecBit = 1;
    unsigned char reloj = 1;
    unsigned indx = 0;
    while (indx<8) {
        if (reloj == 0){

        }

        else if (reloj == 1){
            lecBit = lectura & 0b10000000; //Leemos el bit -> 0b01 o 0b00 que esta llegando por el puerto digital
            lectura = lectura << 1;
            if (lecBit == 0b10000000){
                lecBit = 1;
            }
            else lecBit = 0;
            byte = byte << 1;
            byte += lecBit;
            indx+=1;
        }
    }return byte;
}

void tBitArduino(unsigned char tBit)
{
    unsigned char reloj = 0;//El reloj siempre entrara estaando en 0
    //digitalWrite(data,tBit); //se manda bit
    reloj = 1;//digitalWrite(reloj,HIGH) Se manda señal para que el arduino receptor reciba el bit
    reloj = 0;//digitalWrite(reloj,LOW)
}

void rBitArduino(unsigned char &rBit, unsigned char tBit)
{
    unsigned char reloj = 0;
    while (reloj == 0){ //Se queda aqui hasta que recibe la señal de reloj
        reloj = 1; //digitalRead(reloj)
    }
    rBit = tBit; //digiralRead(data)
}
