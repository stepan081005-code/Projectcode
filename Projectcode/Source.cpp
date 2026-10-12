#include <iostream>
#include <vector>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "ƒобро пожаловать в игру!!!\n—егодн€ 01.06.2026. ¬ы просыпаетесь на кровати в спальне\n";

    struct next
    {
        string room;
        string room2;
        string room3;
    };

    struct house
    {
        int nam;
        string room;
        vector<next> nextroom;
        vector<string> back;

    };

    struct player
    {
        string room;
        string hands;
        string back;
        string items;

    };


    vector<house> myrooms = {
    {0," спальн€  ",{{" прихожа€ "}},{""}},
    {1," прихожа€ ",{{" спальн€2 "},{" коридор "}},{" спальн€ \n"}},
    {2," спальн€2 ",{{" балкон "}},{"прихожа€"}},
    {3," коридор  ",{{" кухн€   "},{" туалет " }, { " ванна€ " }},{ " прихожа€ \n"}},
    {4," кухн€    ",{},{" коридор \n"}},
    {5," туалет   ",{},{" коридор \n"}},
    {6," ванна€   ",{},{" коридор \n"}},
    {7," балкон   ",{},{" спальн€2 \n"}}
    };

    //for (const house& item : myrooms) {
    //    cout << item.nam;
    //    cout << item.room;
    //    for (const next& room : item.nextroom) {
    //        cout << " можно перейти в: ";
    //        cout << room.room;
    //        cout << room.room2;
    //        cout << room.room3;
    //    }
    //    for (const string& room : item.back) {
    //        cout << " можно вернутьс€ в: ";
    //        cout << room;
    //        if (room == "")
    //            cout << "некуда\n";
    //        }
    //}

}