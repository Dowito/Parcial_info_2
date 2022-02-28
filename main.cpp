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

int main()
{
    unsigned char byte = 'a';
    serial74HC595(byte);
    pruebaDesencript(32, 32);
    cout << "Hello World!" << endl;
    return 0;
}

void serial74HC595(unsigned char byte){
    unsigned char bit;
    unsigned char relojShift;
    unsigned char relojStorage;
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
