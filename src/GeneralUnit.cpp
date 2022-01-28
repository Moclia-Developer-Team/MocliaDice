#include "GeneralUnit.h"

namespace MocliaDice
{
    void tool::wsts(std::wstring &wstr, std::string &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        str = converter.to_bytes(wstr);
        return;
    }

    void tool::stws(std::string &str, std::wstring &wstr)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        wstr = converter.from_bytes(str);
        return;
    }

    MocliaExp& MocliaExp::operator=(const MocliaCExp &mce)
    {
        original = mce.original;
        if (mce.iterationCalc != nullptr)
        {
            iterationCalc = mce.iterationCalc;
        }
        middleCalc = mce.middleCalc;
        finalResult = mce.finalResult;
        reason = mce.reason;
        if (mce.exception != nullptr || mce.exception != "")
        {
            exception = mce.exception;
        }
    }

    void MocliaExp::clear()
    {
        original.clear();
        iterationCalc.clear();
        middleCalc.clear();
        finalResult = 0;
        reason.clear();
        exception.clear();
    }
}