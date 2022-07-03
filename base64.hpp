#include <iostream>
#include <string>
#include <cmath>

// «адаем массив символов, чтобы работать в будущем, константно, потому что мен€ть его не будем, а использовать будем всегда. 
const char AlphabetBase64[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', //   0 -   9
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', //  10 -  19
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', //  20 -  29
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', //  30 -  39
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', //  40 -  49
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', //  50 -  59
    '8', '9', '+', '/'                                //  60 -  63
};


// ѕринимает строку и переводит ее в формат Base64.
std::string Encode(std::string inputString)
{
    int size;
    size = inputString.size();
    int* arrayDec = new int[size];
    int* arrayBin = new int[size];

    // «аполн€ем массив ASCII кодов, одна €чейка - один символ.
    for (int i = 0; i < size; i++)
    {
        arrayDec[i] = (int)inputString[i];
    }

    // ѕереводит из кода ASCII в двоичный.
    for (int i = 0; i < size; i++)
    {
        int number = arrayDec[i], bin = 0, d = 1;
        while (number)
        {
            bin += (number % 2) * d;
            number = number / 2;
            d = d * 10;
        }
        arrayBin[i] = bin;
    }

    // —трока, котора€ будет состо€ть из всех бинарных кодов, которые мы создали.
    std::string binCode = "";
    // ƒобавл€ем нули перед каждым бинарным кодом, если он меньше 10000000, потому что двоичный код ASCII должен быть 8-ми битным.
    for (int i = 0; i < size; i++)
    {
        std::string code = std::to_string(arrayBin[i]);
        if (arrayBin[i] < 1)
            binCode += "00000000";
        else if (arrayBin[i] < 10)
            binCode += "0000000";
        else if (arrayBin[i] < 100)
            binCode += "000000";
        else if (arrayBin[i] < 1000)
            binCode += "00000";
        else if (arrayBin[i] < 10000)
            binCode += "0000";
        else if (arrayBin[i] < 100000)
            binCode += "000";
        else if (arrayBin[i] < 1000000)
            binCode += "00";
        else if (arrayBin[i] < 10000000)
            binCode += "0";

        binCode += code;
    }

    // —оздаем переменные, чтобы работать дальше.
    int sizeBINcode = ceil(binCode.size() / 6.0);
    int* arrayBase64code = new int[sizeBINcode];
    int marker = 0;

    // ƒвочиный код ASCII 8-ми битный, а у Base64 6-ти битный, поэтому производим некии манипул€ции.
    for (int i = 0; i < sizeBINcode; i++)
    {
        std::string partBin = "";

        // ѕроверка на выход за границы строки, если все нормально, то считываем 6 бит, иначе также считываем, а затем добавл€ем нужные нули, чтобы было 6 бит.
        if (marker + 6 <= binCode.size())
        {
            for (int j = marker; j < marker + 6; j++)
            {
                partBin += binCode[j];
            }
        }
        else
        {
            for (int j = marker; j < binCode.size(); j++)
            {
                partBin += binCode[j];
            }

            for (int j = 0; j < (sizeBINcode * 6) - binCode.size(); j++)
            {
                partBin += "0";
            }
        }

        // 1-ца в двоичном коде - это степень двойки, поэтому считаем и закидываем в массив посимвольно.
        int code = 0;
        for (int j = 0; j < 6; j++)
        {
            if (partBin[j] == '1')
            {
                code += pow(2, 5 - j);
            }
        }

        arrayBase64code[i] = code;
        // ћаркер на 6, потому что Base64 6-ти разр€дный.
        marker += 6;
    }

    // —оздаем переменную дл€ вывода результата.
    std::string result = "";
    for (int i = 0; i < sizeBINcode; i++)
    {
        result += AlphabetBase64[arrayBase64code[i]];
    }

    return result;
}

// ѕринимает строку(желательно формата Base64) и переводит ее в привычный нам вид(ASCII).
std::string Decode(std::string inputString)
{
    int size = inputString.size();
    int* arrayNumbers = new int[size];

    // «аполн€ем массив посимвольно из строки кодом Base64.
    for (int i = 0; i < inputString.size(); i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (inputString[i] == AlphabetBase64[j])
            {
                arrayNumbers[i] = j;
            }
        }
    }

    int* arrayBin = new int[size];

    // ѕереводим в двоичный код.
    for (int i = 0; i < size; i++)
    {
        int number = arrayNumbers[i], bin = 0, d = 1;
        while (number)
        {
            bin += (number % 2) * d;
            number = number / 2;
            d = d * 10;
        }
        arrayBin[i] = bin;
    }

    // —трока, котора€ будет состо€ть из всех бинарных кодов, которые мы создали. ѕри необходимости добавл€ем нули, перед каждым кодом.
    std::string binCode = "";
    for (int i = 0; i < size; i++)
    {
        std::string code = std::to_string(arrayBin[i]);
        if (arrayBin[i] < 10)
            binCode += "00000";
        else if (arrayBin[i] < 100)
            binCode += "0000";
        else if (arrayBin[i] < 1000)
            binCode += "000";
        else if (arrayBin[i] < 10000)
            binCode += "00";
        else if (arrayBin[i] < 100000)
            binCode += "0";

        binCode += code;
    }

    // ѕеременные дл€ завершающей работы.
    int sizeBINcode = ceil(binCode.size() / 8.0);
    int* arrayBase64code = new int[sizeBINcode];
    int marker = 0;

    // ѕроизводим некие манипул€ции, чтобы получить результат.
    for (int i = 0; i < sizeBINcode; i++)
    {
        std::string partBin = "";

        // ѕроверка на границу строки + считывание 8 бит, если их меньше, то добавл€ем в конец нули.
        if (marker + 8 <= binCode.size())
        {
            for (int j = marker; j < marker + 8; j++)
            {
                partBin += binCode[j];
            }
        }
        else
        {
            for (int j = marker; j < binCode.size(); j++)
            {
                partBin += binCode[j];
            }

            for (int j = 0; j < (sizeBINcode * 8) - binCode.size(); j++)
            {
                partBin += "0";
            }
        }

        int code = 0;

        // —тепень двойки.
        for (int j = 0; j < 8; j++)
        {
            if (partBin[j] == '1')
            {
                code += pow(2, 7 - j);
            }
        }

        arrayBase64code[i] = code;

        // Base64 8-ми битный, поэтому маркер увеличиваетс€ на 8.
        marker += 8;
    }

    // «аписываем посимвольно результат.
    std::string result = "";
    for (int i = 0; i < sizeBINcode; i++)
    {
        result += (char)arrayBase64code[i];
    }

    return result;
}
