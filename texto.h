#ifndef STRING_H
    #define STRING_H
    #include <string>
#endif

#ifndef VECTOR_H
    #define VECTOR_H
    #include <vector>
#endif

#ifndef CSTRING_H
    #define CSTRING_H
    #include <cstring>
#endif

#ifndef LIST_H
    #define LIST_H
    #include <list>
#endif

#ifndef MAP_H
    #define MAP_H
    #include <map>
#endif

#ifndef IOSTREAM_H
    #define IOSTREAM_H
    #include <iostream>
#endif

#ifndef FSTREAM_H
    #define FSTREAM_H
    #include <fstream>
#endif

#ifndef BITSET_H
    #define BITSET_H
    #include <bitset>
#endif

#ifndef IOMANIP_H
    #define IOMANIP_H
    #include <iomanip>
#endif

#ifndef CSTDIO_H
    #define CSTDIO_H
    #include <cstdio>
#endif

#ifndef TEXTO_H
#define TEXTO_H

using namespace std;

class Texto
{
public:
    string text;

    size_t countWord(string word);
    size_t countCharacter(char character);
    map<char, size_t> countAllCharacters();
    map<string, size_t> countAllWords();
    list<string> split(char character);
    static bool isBigEndian();
    static bool isEmail( const string email );

    bool isCellPhone( const string cell );
    bool isCURP( const string CURP );
    bool isRFC( const string RFC );
    map<long, size_t> countAllNumericStrings(); // cuanta todas las palabras que representan a un numero entero separadas por espacios en blanco
    vector<long> getAllNumericStrings();         // registra todas las palabras que pueden ser convertidas a un numero entero valido y retorna la lista
    void detectEnconding();
};

#endif // TEXTO_H
