#ifndef ALU_H
#define ALU_H

#include "Register.h"

#include <bits/stdc++.h>
using namespace std;

class ALU
{
public:
    static string floatToHex(float floatNum)
    {
        uint8_t sign = 0;
        uint8_t exponent = 0;
        uint8_t mantissa = 0;

        if (floatNum < 0)
        {
            sign = 1;
            floatNum = -floatNum;
        }

        if (floatNum == 0.0f)
        {
            exponent = 0;
            mantissa = 0;
        }
        else
        {
            int exponent_unbiased = static_cast<int>(floor(log2(floatNum)));
            int exponent_biased = exponent_unbiased + 3;

            if (exponent_biased >= 7)
            {
                exponent = 7;
                mantissa = 0;
            }
            else if (exponent_biased <= 0)
            {
                exponent = 0;
                mantissa = 0;
            }
            else
            {
                exponent = static_cast<uint8_t>(exponent_biased);
                float mantissa_fraction = floatNum / pow(2, exponent_unbiased) - 1.0f;
                mantissa = static_cast<uint8_t>(round(mantissa_fraction * 16));
                if (mantissa >= 16)
                {
                    mantissa = 15; // Clamp mantissa
                }
            }
        }

        uint8_t binary = (sign << 7) | (exponent << 4) | mantissa;
        stringstream ss;
        ss << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(binary);
        return ss.str();
    }
    static float hexToFloat(const string &hex)
    {
        unsigned int binary;
        stringstream ss;
        ss << hex << hex;
        ss >> binary;

        uint8_t sign = (binary >> 7) & 0x1;
        uint8_t exponent = (binary >> 4) & 0x7;
        uint8_t mantissa = binary & 0xF;

        float value = 0.0f;

        if (exponent == 0)
        {
            if (mantissa == 0)
            {
                value = 0.0f;
            }
            else
            {
                int exponent_unbiased = 1 - 3; 
                value = (static_cast<float>(mantissa) / 16.0f) * pow(2, exponent_unbiased);
            }
        }
        else if (exponent == 7)
        {
            if (mantissa == 0)
            {
                value = numeric_limits<float>::infinity();
            }
            else
            {
                value = numeric_limits<float>::quiet_NaN();
            }
        }
        else
        {
            int exponent_unbiased = static_cast<int>(exponent) - 3;
            float mantissa_fraction = static_cast<float>(mantissa) / 16.0f;
            value = (1.0f + mantissa_fraction) * pow(2, exponent_unbiased);
        }
        if (sign)
        {
            value = -value;
        }
        return value;
    }
    static int hexToDec(const string &hex)
    {
        return stoi(hex, nullptr, 16);
    }

    static string decToHex(int dec)
    {
        stringstream ss;
        ss << hex << dec;
        string result = ss.str();
        for (char &c : result)
        {
            if (isalpha(c))
            {
                c = toupper(c);
            }
        }
        return result;
    }

    static int add(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) + reg.getCell(idx2);
    }

    static int bitwiseOr(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) | reg.getCell(idx2);
    }

    static int bitwiseAnd(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) & reg.getCell(idx2);
    }

    static int bitwiseXor(int idx1, int idx2, Register &reg)
    {
        return reg.getCell(idx1) ^ reg.getCell(idx2);
    }

    static int rotateRight(int value, int steps)
    {
        return ((value >> steps) | (value << (16 - steps))) % 256;
    }
};
#endif