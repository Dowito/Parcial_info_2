#include <iostream>
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

int main()
{
    unsigned char byte = 'a';
    serial74HC595(byte);
    cout << "Hello World!" << endl;
    return 0;
}

void serial74HC595(unsigned char byte){
    unsigned char bit;
    unsigned char relojShift;
    unsigned char relojStorage;
    string prueba; //para hacer prueba de como quedarian guardados en la memoria de dezplazamiento
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
