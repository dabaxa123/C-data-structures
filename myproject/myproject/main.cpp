#include <iostream>
#include "list.h"
#include "clasebi.h"

int main() {
    // ვქმნით priority_queue-ს Employee ტიპისთვის
    // Employee არის base class, ხოლო CIO, tester, frontend და სხვები არიან შვილობილი კლასები
    priority_queue<Employee> list;

    // თანამშრომლების დამატება სიაში
    // push ფუნქცია თვითონ დაალაგებს ხელფასის მიხედვით კლებადობით
    list.push(new CIO(234, "nika", 5000, 30));
    list.push(new tester(123, "inako", 1000, 12, "Senior"));
    list.push(new frontend(123, "saba", 1000, 12, "Senior", "Angular"));
    list.push(new backend(456, "artaka", 1200, 11, "Junior", ".Net"));
    list.push(new DevOps(654, "ramazi", 1000, 8, "Senior"));

    std::cout << "yvela tanamshromeli xelfasis mixedvit:\n";
    list.display_all();

    std::cout << "\ntqveni sasurveli tanamshromeli:\n";
    list.display("inako");

    std::string name = "saba";

    // ვეძებთ თანამშრომელს სახელით
    int idx = list.search(name);

    if (idx != -1)
        std::cout << "\n" << name << " vipovet indexze: " << idx << "\n";
    else
        std::cout << "\n" << name << " ver vipovet\n";

    // თანამშრომლის წაშლა სახელით
    list.Delete("nika");

    std::cout << "\nnikas gatavisuflebis shemdeg:\n";
    list.display_all();

    std::cout << "\nnikas modzebna washilis shemdeg:\n";
    list.display("nika");

    return 0;
}