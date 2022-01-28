#pragma once

#define MOCLIA_LANG_ZH

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

namespace MocliaDice
{
    struct MocliaCExp
    {
        const char * original; // 输入和规范化后的原始表达式
        const char * iterationCalc; // 迭代计算中间过程
        const char * middleCalc; // 返回给用户的计算中间过程
        int64_t finalResult; // 最终计算得到的结果
        const char * reason; // 分离出来的理由
        const char * exception; // 表达式错误信息
    };

    struct MocliaExp
    {
        std::string original; // 输入和规范化后的原始表达式
        std::string iterationCalc; // 迭代计算中间过程
        std::string middleCalc; // 返回给用户的计算中间过程
        int64_t finalResult; // 最终计算得到的结果
        std::string reason; // 分离出来的理由
        std::string exception; // 表达式错误信息

        MocliaExp & operator=(const MocliaCExp &mce);
        void clear();
    };

    class tool
    {
    public:
        // string 转 wstring
        static void stws(std::string &str, std::wstring &wstr);
        // wstring 转 string
        static void wsts(std::wstring &wstr, std::string &str);
    };
}