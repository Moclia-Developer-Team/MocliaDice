#include "mirai.h"
#include "MocliaDiceCore.h"
#include "GeneralUnit.h"

using namespace std;
using namespace Cyan;
using namespace Moclia;

MocliaDice::MocliaExp mexp;
MocliaDice::MocliaCExp mcexp;

int main()
{
#ifdef _WIN32
    system("chcp 65001");
    system("title MocliaDice");
#endif

    MiraiBot bot;
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
                   cout << gm.ToString() << endl;
                   //wstring wplain;
                   //MocliaDice::tool::stws(plain,wplain); // 转换为wstring便于find和substr
//                   if (wplain.find(L".r") == 0 || wplain.find(L"。r") == 0)
//                   {
//                       wplain = wplain.substr(2,strlen(plain.c_str()) - 1);
//                       MocliaDice::tool::wsts(wplain,plain); //转回string方便处理
//                       mcexp.original = plain.c_str();
//                       classicDiceUnit((char*&)mcexp.original,(char*&)mcexp.middleCalc,(char*&)mcexp.reason,mcexp.finalResult,(char*&)mcexp.exception);
//                       mexp.original = mcexp.original;
//                       mexp.middleCalc = mcexp.middleCalc;
//                       mexp.reason = mcexp.reason;
//                       mexp.finalResult = mcexp.finalResult;
//                       mexp.exception = mcexp.exception;
//                       //mexp = mcexp;
////
////                       if (!mexp.exception.empty())
////                       {
////                           gm.Reply(MessageChain().Plain("由于" + mexp.reason + "," + gm.Sender.MemberName + "掷骰出现错误：" + mexp.exception));
////                           mexp.clear();
////                           return;
////                       }
//                       gm.Reply(MessageChain().Plain("由于" + mexp.reason + "，" + gm.Sender.MemberName + "骰出了：" + mexp.original + "=" + to_string(mexp.finalResult)));
//                       return;
//                   }

                   if (plain.find(".x") == 0)
                   {
                       plain = plain.substr(2,strlen(plain.c_str()) - 1);


                       /*Moclia::exp_t d3xp;
                       d3xp.original = plain;
                       Moclia::DX3::addDice(d3xp);
                       if (!d3xp.exception.empty())
                       {
                           gm.Reply(MessageChain().Plain(d3xp.exception));
                           return;
                       }
                       gm.Reply(MessageChain().Plain(d3xp.finalResult));*/

                       mcexp.original = plain.c_str();
                       string a;
                       a = "hello world";
                       cout << a << endl;
                       dx3AddDiceUnit((char*&)mcexp.original, (char*&)mcexp.iterationCalc, (char*&)mcexp.middleCalc, (char*&)mcexp.reason, mcexp.finalResult, (char*&)mcexp.exception);
                       mexp.original = mcexp.original;
                       mexp.iterationCalc = mcexp.iterationCalc;
                       mexp.middleCalc = mcexp.middleCalc;
                       mexp.reason = mcexp.reason;
                       mexp.finalResult = mcexp.finalResult;
                       mexp.exception = mcexp.exception;

                       if (!mexp.exception.empty())
                       {
                           MessageChain me = MessageChain().Plain(mcexp.exception);
                           cout << me.ToString() << endl;
                           gm.Reply(me);
                           return;
                       }
                       string sender = gm.Sender.MemberName;
                       string msg = "由于" + mexp.reason + "，" + "骰出了：" + mexp.original + "=" + mexp.middleCalc + "=" + to_string(mexp.finalResult) + "\0";
                       cout << msg << endl;
                       MessageChain mc = MessageChain().Plain(mexp.finalResult);
                       cout << mc.ToString() << endl;
                       gm.Reply(mc);
                       return;
                   }
               }
               catch (const std::exception &ex)
               {
                   cout << ex.what() << endl;
               }
               catch (...)
               {
                   cout << "未被捕获的异常" << endl;
               }
            });

    bot.On<FriendMessage>(
            [&](FriendMessage fm)
            {
                try
                {
                    string plain = fm.MessageChain.GetPlainText();
                    wstring wplain;
                    MocliaDice::tool::stws(plain,wplain); // 转换为wstring便于find和substr
                    if (wplain.find(L".r") == 0 || wplain.find(L"。r") == 0)
                    {
                        wplain = wplain.substr(2,strlen(plain.c_str()) - 1);
                        MocliaDice::tool::wsts(wplain,plain); //转回string方便处理
                        mcexp.original = plain.c_str();

                        classicDiceUnit((char*&)mcexp.original,(char*&)mcexp.middleCalc,(char*&)mcexp.reason,mcexp.finalResult,(char*&)mcexp.exception);

                        mexp = mcexp;

                        if (!mexp.exception.empty())
                        {
                            fm.Reply(MessageChain().Plain("由于" + mexp.reason + "," + fm.Sender.NickName + "掷骰出现错误：" + mexp.exception));
                            mexp.clear();
                            return;
                        }
                        fm.Reply(MessageChain().Plain("由于" + mexp.reason + "，" + fm.Sender.NickName + "骰出了：" + mexp.original + "=" + to_string(mexp.finalResult)));
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
