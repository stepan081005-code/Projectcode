#include <iostream>
#include <vector>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Добро пожаловать в игру!!!\nСегодня 01.06.2026. Вы просыпаетесь на кровати в спальне, ваша цель открыть сейф\n";

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
        vector<string> items;


    };

    struct player
    {
        string room;
        string hands;
        string back;
        vector<string> items;

    };


    vector<house> myrooms = {
    { 0," спальня  ",{ { " прихожая " } },{ "" } },
    { 1," прихожая ",{ { " зал " },{ " коридор " } },{ " спальня \n" } },
    { 2," зал ",{ { " балкон " } },{ " прихожая \n" } },
    { 3," коридор  ",{ { " кухня   " },{ " туалет " },{ " ванная " } },{ " прихожая \n" } },
    { 4," кухня    ",{},{ " коридор \n" } },
    { 5," туалет   ",{},{ " коридор \n" } },
    { 6," ванная   ",{},{ " коридор \n" } },
    { 7," балкон   ",{},{ " зал \n" } }

    };

    int current = 0;
    const house& r = myrooms[current];
    cout << "\n=== Вы в комнате: [" << r.nam << "] " << r.room << " ===\n";

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
    //        cout << " можно вернуться в: ";
    //        cout << room;
    //        if (room == "")
    //            cout << "некуда\n";
    //    }
    //}
    // =====================================================
     // === ДОПИСАННЫЙ КОД — навигация между комнатами    ===
     // =====================================================

     // Функция очистки строки от пробелов и переносов для корректного сравнения
    auto normalize = [](string s) -> string {
        string res;
        for (char c : s)
            if (c != ' ' && c != '\n' && c != '\t' && c != '\r')
                res += c;
        return res;
        };

    myrooms[0].items = { "сейф" };          // === НОВОЕ: сейф в спальне ===
    myrooms[2].items = { "фонарик" };
    myrooms[4].items = { "записка с кодом" };
    myrooms[6].items = { "ключ от сейфа" };
    myrooms[7].items = { "бинокль" };


    player hero;
    hero.room = myrooms[0].room;

    int cur = 0;   // текущая комната игрока
    cout << "\n\n========================================\n";
    cout << "        НАЧАЛО ИГРЫ — НАВИГАЦИЯ\n";
    cout << "========================================\n";
    cout << "Вводите номер комнаты для перехода,\n";
    cout << "номер предмета (от 10) чтобы взять его,\n";
    cout << "99 — открыть рюкзак, -1 — выход.\n";

    while (true)
    {
        const house& cr = myrooms[cur];
        cout << "\n>>> Вы в комнате: [" << cr.nam << "]" << cr.room << "<<<\n";

        // Собираем все доступные направления из nextroom и back
        vector<int> dests;

        auto tryAdd = [&](const string& destName) {
            string nd = normalize(destName);
            if (nd.empty()) return;
            for (const auto& h : myrooms) {
                if (normalize(h.room) == nd) {
                    bool dup = false;
                    for (int d : dests)
                        if (d == h.nam) { dup = true; break; }
                    if (!dup) dests.push_back(h.nam);
                }
            }
            };

        for (const auto& nr : cr.nextroom) {
            tryAdd(nr.room);
            tryAdd(nr.room2);
            tryAdd(nr.room3);
        }
        for (const string& b : cr.back) {
            tryAdd(b);
        }

        // Показываем доступные комнаты
        if (dests.empty()) {
            cout << "  Отсюда некуда идти.\n";
        }
        else {
            cout << "  Доступные направления:\n";
            for (int d : dests)
                cout << "    [" << d << "]" << myrooms[d].room << "\n";
        }

        // === Показываем предметы в текущей комнате ===
        if (!cr.items.empty()) {
            cout << "  Предметы в комнате:\n";
            for (size_t i = 0; i < cr.items.size(); ++i) {
                cout << "    [" << (10 + i) << "] Взять: " << cr.items[i] << "\n";
            }
        }
        cout << "    [99] Посмотреть инвентарь (рюкзак)\n";

        // Читаем выбор игрока
        cout << "  Ваш выбор: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Введите число!\n";
            continue;
        }
        if (choice == -1) {
            cout << "Выход из игры. До свидания!\n";
            break;
        }

        // === Обработка взятия предмета ===
        if (choice >= 10 && choice < 10 + (int)cr.items.size()) {
            int itemIndex = choice - 10;
            string taken = cr.items[itemIndex];

            // === НОВОЕ: Особая обработка сейфа ===
            if (taken == "сейф") {
                bool hasKey = false, hasCode = false;
                for (const string& it : hero.items) {
                    if (it == "ключ от сейфа") hasKey = true;
                    if (it == "записка с кодом") hasCode = true;
                }

                if (!hasKey && !hasCode) {
                    cout << "  >> Сейф заперт! У вас нет ключа и нет кода.\n";
                    cout << "  >> Нужно найти ключ от сейфа и записку с кодом.\n";
                }
                else if (!hasKey) {
                    cout << "  >> У вас есть код, но нет ключа от сейфа!\n";
                    cout << "  >> Поищите ключ в другой комнате.\n";
                }
                else if (!hasCode) {
                    cout << "  >> У вас есть ключ, но вы не знаете код!\n";
                    cout << "  >> Поищите записку с кодом в другой комнате.\n";
                }
                else {
                    cout << "\n==================================================\n";
                    cout << " Вы вставили ключ, набрали код... ЩЕЛК!\n";
                    cout << " Сейф открыт! Внутри — золотые слитки!\n";
                    cout << " ПОБЕДА! Поздравляем с прохождением игры!\n";
                    cout << "==================================================\n";
                    break;
                }
                continue; // сейф остаётся в комнате
            }

            hero.items.push_back(taken);
            myrooms[cur].items.erase(myrooms[cur].items.begin() + itemIndex);

            cout << "  >> Вы подобрали: [" << taken << "]!\n";
            continue;
        }

        // === Просмотр инвентаря ===
        if (choice == 99) {
            cout << "\n  --- ВАШ РЮКЗАК ---\n";
            if (hero.items.empty()) {
                cout << "  (рюкзак пуст)\n";
            }
            else {
                for (size_t i = 0; i < hero.items.size(); ++i) {
                    cout << "  " << (i + 1) << ". " << hero.items[i] << "\n";
                }
            }
            cout << "  ------------------\n";
            continue;
        }

        // Проверяем, можно ли туда перейти
        bool ok = false;
        for (int d : dests)
            if (d == choice) { ok = true; break; }

        if (ok) {
            cur = choice;
            hero.room = myrooms[cur].room;
            cout << "  Вы перешли в комнату [" << cur << "]" << myrooms[cur].room << "\n";
        }
        else {
            cout << "  Нельзя туда попасть из этой комнаты!\n";
        }
    }

    return 0;
}