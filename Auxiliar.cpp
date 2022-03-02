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
