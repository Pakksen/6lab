#include <iostream>
#include <string>
#include <cmath>

// ������ ������ ��������, ����� �������� � �������, ����������, ������ ��� ������ ��� �� �����, � ������������ ����� ������. 
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


// ��������� ������ � ��������� �� � ������ Base64.
std::string Encode(std::string inputString)
{
    int size;
    size = inputString.size();
    int* arrayDec = new int[size];
    int* arrayBin = new int[size];

    // ��������� ������ ASCII �����, ���� ������ - ���� ������.
    for (int i = 0; i < size; i++)
    {
        arrayDec[i] = (int)inputString[i];
    }

    // ��������� �� ���� ASCII � ��������.
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

    // ������, ������� ����� �������� �� ���� �������� �����, ������� �� �������.
    std::string binCode = "";
    // ��������� ���� ����� ������ �������� �����, ���� �� ������ 10000000, ������ ��� �������� ��� ASCII ������ ���� 8-�� ������.
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

    // ������� ����������, ����� �������� ������.
    int sizeBINcode = ceil(binCode.size() / 6.0);
    int* arrayBase64code = new int[sizeBINcode];
    int marker = 0;

    // �������� ��� ASCII 8-�� ������, � � Base64 6-�� ������, ������� ���������� ����� �����������.
    for (int i = 0; i < sizeBINcode; i++)
    {
        std::string partBin = "";

        // �������� �� ����� �� ������� ������, ���� ��� ���������, �� ��������� 6 ���, ����� ����� ���������, � ����� ��������� ������ ����, ����� ���� 6 ���.
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

        // 1-�� � �������� ���� - ��� ������� ������, ������� ������� � ���������� � ������ �����������.
        int code = 0;
        for (int j = 0; j < 6; j++)
        {
            if (partBin[j] == '1')
            {
                code += pow(2, 5 - j);
            }
        }

        arrayBase64code[i] = code;
        // ������ �� 6, ������ ��� Base64 6-�� ���������.
        marker += 6;
    }

    // ������� ���������� ��� ������ ����������.
    std::string result = "";
    for (int i = 0; i < sizeBINcode; i++)
    {
        result += AlphabetBase64[arrayBase64code[i]];
    }

    return result;
}

// ��������� ������(���������� ������� Base64) � ��������� �� � ��������� ��� ���(ASCII).
std::string Decode(std::string inputString)
{
    int size = inputString.size();
    int* arrayNumbers = new int[size];

    // ��������� ������ ����������� �� ������ ����� Base64.
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

    // ��������� � �������� ���.
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

    // ������, ������� ����� �������� �� ���� �������� �����, ������� �� �������. ��� ������������� ��������� ����, ����� ������ �����.
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

    // ���������� ��� ����������� ������.
    int sizeBINcode = ceil(binCode.size() / 8.0);
    int* arrayBase64code = new int[sizeBINcode];
    int marker = 0;

    // ���������� ����� �����������, ����� �������� ���������.
    for (int i = 0; i < sizeBINcode; i++)
    {
        std::string partBin = "";

        // �������� �� ������� ������ + ���������� 8 ���, ���� �� ������, �� ��������� � ����� ����.
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

        // ������� ������.
        for (int j = 0; j < 8; j++)
        {
            if (partBin[j] == '1')
            {
                code += pow(2, 7 - j);
            }
        }

        arrayBase64code[i] = code;

        // Base64 8-�� ������, ������� ������ ������������� �� 8.
        marker += 8;
    }

    // ���������� ����������� ���������.
    std::string result = "";
    for (int i = 0; i < sizeBINcode; i++)
    {
        result += (char)arrayBase64code[i];
    }

    return result;
}
