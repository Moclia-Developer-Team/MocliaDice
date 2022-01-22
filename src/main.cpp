#include <iostream>
#include "mirai.h"
#include "RollDiceUnit.h"

using namespace std;
using namespace Cyan;
using namespace Moclia;

int main()
{
#ifdef _WIN32
    system("chcp 65001");
    system("title MocliaDice");
#endif

    MiraiBot bot;
    calc calcul;
    tool dicetool;
    exp_t expr;
    SessionOptions opts = SessionOptions().FromJsonFile("./connect.json");

    while (true)
    {
        try
        {
            cout << "尝试连接Mirai-Api-Http" << endl;
            bot.Connect(opts);
            break;
        }
        catch (const std::exception &ex)
        {
            cout << ex.what() << endl;
        }
        MiraiBot::SleepSeconds(1);
    }

    cout << "成功连接，正在运行……" << endl;

    bot.On<GroupMessage>(
            [&](GroupMessage gm)
            {
               try
               {
                   string plain = gm.MessageChain.GetPlainText();
                   wstring wplain;
                   dicetool.sswConversion(plain,wplain);
                   if (wplain.find(L".r") == 0 || wplain.find(L"。r") == 0)
                   {
                       wplain = wplain.substr(2,strlen(plain.c_str()) - 1);
                       dicetool.sswConversion(wplain,expr.original);
                       calcul.expressionStandard(expr);
                       if (!expr.exception.empty())
                       {
                           gm.Reply(MessageChain().Plain("由于" + expr.reason + "," + gm.Sender.MemberName + "掷骰出现错误：" + expr.exception));
                           expr.clear();
                           return;
                       }
                       calcul.expressionCalculator(expr);
                       gm.Reply(MessageChain().Plain("由于" + expr.reason + "，" + gm.Sender.MemberName + "骰出了：" + expr.original + "=" + expr.finalResult));
                       return;
                   }
               }
               catch (const std::exception &ex)
               {
                   cout << ex.what() << endl;
               }
            });

    bot.On<FriendMessage>(
            [&](FriendMessage fm)
            {
                try
                {
                    string plain = fm.MessageChain.GetPlainText();
                    wstring wplain;
                    dicetool.sswConversion(plain,wplain);
                    if (wplain.find(L".r") == 0 || wplain.find(L"。r") == 0)
                    {
                        wplain = wplain.substr(2,strlen(plain.c_str()) - 1);
                        dicetool.sswConversion(wplain,expr.original);
                        calcul.expressionStandard(expr);
                        if (!expr.exception.empty())
                        {
                            fm.Reply(MessageChain().Plain("由于" + expr.reason + "," + fm.Sender.NickName + "掷骰出现错误：" + expr.exception));
                            expr.clear();
                            return;
                        }
                        calcul.expressionCalculator(expr);
                        fm.Reply(MessageChain().Plain("由于" + expr.reason + "，" + fm.Sender.NickName + "骰出了：" + expr.original + "=" + expr.finalResult));
                        return;
                    }
                }
                catch (const std::exception &ex)
                {
                    cout << ex.what() << endl;
                }
            });

    bot.On<NewFriendRequestEvent>(
            [&](NewFriendRequestEvent nf)
            {
                nf.Accept();
            });

    bot.On<LostConnection>(
            [&](LostConnection e)
            {
                cout << e.ErrorMessage << " (" << e.Code << ")" << endl;
                while (true)
                {
                    try
                    {
                        cout << "尝试连接 mirai-api-http..." << endl;
                        bot.Reconnect();
                        cout << "与 mirai-api-http 重新建立连接!" << endl;
                        break;
                    }
                    catch (const std::exception& ex)
                    {
                        cout << ex.what() << endl;
                    }
                    MiraiBot::SleepSeconds(1);
                }
            });

    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "exit")
        {
            // 程序结束前必须调用 Disconnect，否则 mirai-api-http 会内存泄漏。
            bot.Disconnect();
            break;
        }
    }

    return 0;
}
