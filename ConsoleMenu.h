//
// Created by Sami Dahoux on 09/05/2018.
//

#ifndef MATHTOOLKIT_CONSOLEGUI_H
#define MATHTOOLKIT_CONSOLEGUI_H

#include <iostream>
#include <string>
#include <vector>
#include <curses.h>

class ConsoleMenu final {
public:
    ConsoleMenu(const std::vector<std::string>& choices, const std::string& title = "");
    ~ConsoleMenu();

    unsigned int launch();
    unsigned int choice();
protected:
    void print();
    void getChoiceFromCin();
private:
    std::string _title;
    std::vector<std::string> _choices;
    unsigned int _choice;
};


#endif //MATHTOOLKIT_CONSOLEGUI_H
