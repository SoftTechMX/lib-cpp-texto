#include "Texto.h"

size_t Texto::countWord(string word)
{
    size_t count = 0;
    size_t last_pos = 0;

    while ((last_pos = this->text.find(word, last_pos)) != string::npos)
    {
        ++last_pos;
        ++count;
    }
    return count;
}

size_t Texto::countCharacter(char character)
{
    size_t count = 0;

    for (size_t i = 0; i < this->text.size(); ++i)
    {
        if (this->text[i] == character)
        {
            ++count;
        }
    }
    return count;
}

map<char, size_t> Texto::countAllCharacters()
{
    map<char, size_t> listaDeConteo;
    pair< map<char, size_t>::iterator, bool> valorInsertado;

    // Por cada letra
    for (size_t i = 0; i < this->text.size(); i++)
    {
        // Intentamos insertar la palabra con el valor de 1
        valorInsertado = listaDeConteo.insert(pair<char, size_t>(this->text[i], 1));

        // si el valor de retorno es falso quiere decir que esa palabra ya existe
        if (valorInsertado.second == false)
        {
            // entonces incrementamos en 1 el contador
            valorInsertado.first->second++;
        }
    }

    return listaDeConteo;
}

map< string, size_t> Texto::countAllWords()
{
    map<string, size_t> listaDeConteo;
    list<string> listaDePalabras = this->split(' ');
    pair< map<string, size_t>::iterator, bool> valorInsertado;

    // Por cada palabra en el texto
    for (auto palabra = listaDePalabras.begin(); palabra != listaDePalabras.end(); palabra++)
    {
        // Intentamos insertar la palabra con el valor de 1
        valorInsertado = listaDeConteo.insert(pair<string, size_t>(*palabra, 1));

        // si el valor de retorno es falso quiere decir que esa palabra ya existe
        if (valorInsertado.second == false)
        {
            // entonces incrementamos en 1 el contador
            valorInsertado.first->second++;
        }
    }

    return listaDeConteo;
}

list<string> Texto::split(char character)
{
    list<string> WordsList;     // lista de string que contiene las palabras separadas por el token especificado como argumento
    size_t szWordBegin = 0;     // Indice del inicio  de la palabra que se va a agregar en la lista, cambia en cada itineracion
    size_t szWordEnd = 0;       // Indice del final   de la palabra que se va a agregar en la lista, cambia en cada itineracion
    size_t szWordSize = 0;      // Tamano de la Palabra a agregar en la lista de palabras, cambia en cada itineracion
    string sWord;

    while ((szWordEnd = this->text.find(character, szWordBegin)) != string::npos)
    {
        szWordSize = szWordEnd - szWordBegin;
        sWord = this->text.substr(szWordBegin, szWordSize);
        szWordBegin = szWordEnd + 1;                                   // Actualizamos el indice de donde debe buscar
        WordsList.push_back(sWord);
    }

    sWord = this->text.substr(szWordBegin);
    WordsList.push_back(sWord);

    return WordsList;
}

bool Texto::isBigEndian()
{
    union {
        uint32_t i;
        char c[4];
    } bint = { 0x01020304 };

    return bint.c[0] == 1;
}

bool Texto::isEmail( const string email )
{
    string dominio;
    size_t indiceDelArroba = email.find("@");
    string dominios[] = {
        "gmail.com",
        "outlook.com"
        "hotmail.com"
        "live.com"
    };

    // SI CONTIENE EL ARROBA @
    if( indiceDelArroba != string::npos )
    {
        // EXTRAEMOS EL DOMINIO DEL CORREO
        dominio = email.substr( indiceDelArroba + 1 );

        // VERIFICAMOS SI EL DOMINIO DEL CORREO ESTA EN ALGUN DOMNIO VALIDO
        for(string dominioValido : dominios)
        {
            if( dominioValido.find(dominio) != string::npos )
                return true;
        }

        // PENDIENTE VALIDAR LOS ESPACIOS EN BALNCO Y CARACTERES ESPECIALES
    }
    else
    {
        // NO TIENE ARROBA POR LO TANTO NO ES UN EMAIL VALIDO
        return false;
    }

    // SI NO PASA NINGUNA PRUEBA ES UN CORREO INVALIDO
    return false;
}





void Texto::detectEnconding() {
    const size_t BIT_8 = 7;
    const size_t BIT_7 = 6;
    const size_t BIT_6 = 5;
    const size_t BIT_5 = 4;
    const size_t BIT_4 = 3;

    const bool ONE = true;
    const bool CERO = false;

    ifstream inputStream;
    size_t inputStreamSize;

    inputStream.open("txt.pdf", ios::in | ios::binary);
    if (inputStream.is_open()) {

        inputStream.seekg(0, ios_base::end);
        inputStreamSize = inputStream.tellg();
        inputStream.seekg(0, ios_base::beg);

        char* buffer = new char[inputStreamSize];
        inputStream.read(buffer, inputStreamSize);
        inputStream.close();

        cout << "Tamano del buffer: " << inputStreamSize << endl;
        cout << "Buffer: " << buffer << endl;

        int contador = 0;
        for (size_t i = 0; i < inputStreamSize; i++) {
            contador++;
            //readChar(buffer[i]);
            bitset<8> byte1(buffer[i]);

            if (byte1.test(BIT_8) == CERO) {                // 0xxx xxxx
                cout << buffer[i] << " -- ASCII 1 byte" << endl;
            }
            else {
                if (byte1.test(BIT_8) == ONE &&             // 110x xxxx
                    byte1.test(BIT_7) == ONE &&
                    byte1.test(BIT_6) == CERO) {
                    cout << buffer[i] << buffer[i + 1] << "-- UTF-8 2 bytes" << endl;
                    i++;
                }
                else {
                    if (byte1.test(BIT_8) == ONE &&         // 1110 xxxx
                        byte1.test(BIT_7) == ONE &&
                        byte1.test(BIT_6) == ONE &&
                        byte1.test(BIT_6) == CERO) {
                        cout << buffer[i] << buffer[i + 1] << buffer[i + 2] << "-- UTF-16 3  bytes" << endl;
                        i += 2;
                    }
                    else {
                        if (byte1.test(BIT_8) == ONE &&     // 1111 0xxx
                            byte1.test(BIT_7) == ONE &&
                            byte1.test(BIT_6) == ONE &&
                            byte1.test(BIT_5) == ONE &&
                            byte1.test(BIT_4) == CERO) {
                            cout << buffer[i] << buffer[i + 1] << buffer[i + 2] << buffer[i + 3] << "-- UNICODE  4 bytes" << endl;
                            i += 3;
                        }
                    }
                }
            }
        }
        cout << "Ciclos en for: " << contador << endl;
        delete[] buffer;
    }
}

vector<long> Texto::getAllNumericStrings()
{
    vector<long> numeros;
    long numero;
    size_t i = 0, f;

    while( (f = this->text.find(",", i)) != string::npos )
    {
        numero = stoi( this->text.substr(i,f-i) );
        numeros.push_back(numero);
        i = f+1;
    }

    numero = stoi( this->text.substr(i, this->text.size()-i) );
    numeros.push_back(numero);

    return numeros;
}


map<long, size_t> Texto::countAllNumericStrings()
{
    map<long, size_t> listaDeConteo;

    list<string> listaDePalabras = this->split(' ');
    pair< map<long, size_t>::iterator, bool> valorInsertado;

    int tmp_numero;

    // Por cada palabra en el texto
    for (auto palabra = listaDePalabras.begin(); palabra != listaDePalabras.end(); palabra++)
    {
        // Intentamos insertar la palabra con el valor de 1
        tmp_numero = stoi(palabra->c_str());
        valorInsertado = listaDeConteo.insert(pair<long, size_t>(tmp_numero, 1));

        // si el valor de retorno es falso quiere decir que esa palabra ya existe
        if (valorInsertado.second == false)
        {
            // entonces incrementamos en 1 el contador
            valorInsertado.first->second++;
        }
    }

    return listaDeConteo;
}




/**
 *  @brief  Funcion encargada de validar si una cadena es un telefono valido
 *  @return verdadero si es un telefono valido de lo contrario retorna falso
 */
bool Texto::isCellPhone( string cell ){
    // Si tiene este formato 868-353-4291
    if(cell.size() == 12 && cell[7] == '-' && cell[3] == '-')
    {
        for( size_t i=0; i < cell.size(); ++i ){
            if( !isdigit(cell[i]) ){
                if( i == 4 || i == 8)
                    continue;
                else
                    return false;
            }
            return true;
        }
    }
    if( cell.size() == 10 ){
        for( size_t i=0; i < cell.size(); ++i ){
            if( !isdigit(cell[i]) ){
                    return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * Valida el formato de una cadena para ver si es una CURP valida.
 *
 *                                            Sexo
 *                                          'H' o 'M'
 *                                              ^
 *                                             /_\
 *                       Fecha de Nacimiento    |
 *                           1994/11/21         |   Estado
 *                                ^             |     ^
 *                               /_\            |    /_\
 *                     ___________|___________  |  ___|___
 *                    |                       | | |       |
 *    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *    | S | E | A | J | 9 | 4 | 1 | 1 | 2 | 1 | H | T | S | G | G | S | 0 | 4 |
 *    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *      |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| 16| 17|
 *    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
 * @return verdadero si tiene el formato correcto y falso si no lo tiene
 */
bool Texto::isCURP(string CURP){

    // La CURP constan de 18 caracteres alfanumericos
    if( CURP.size() != 18 )
        return false;

    // 10 indica el genero
    if( CURP[10] != 'M' && CURP[10] != 'H')
        return false;

    // 4-9 Contiene la Fecha de Nacimiento
    for(size_t i = 4; i <= 9; ++i){
        if( !isdigit( CURP[i]) )
            return false;
    }

    return true;
}


/**
 * @brief Verifica si una cadena tiene el formato de un RFC
 * @return si el rfc tiene el formato Correcto retorna true de lo contrario false
 */
bool Texto::isRFC(string RFC){
    if( RFC.size() != 13)
        return false;
    return true;
}
