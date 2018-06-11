//
// Created by Sami Dahoux on 09/05/2018.
//

#include "ConsoleMenu.h"

using namespace std;

ConsoleMenu::ConsoleMenu(const std::vector<std::string> &choices, const std::string& title) :
        _choices(choices), _title(title), _choice(0)
{}

ConsoleMenu::~ConsoleMenu() {}

unsigned int ConsoleMenu::launch() {
    print();
    getChoiceFromCin();
    return _choice;
}

void ConsoleMenu::print() {
    cout << endl << endl << "***" << _title << "***" << endl << endl;
    for (int k = 0; k < _choices.size(); ++k) {
        cout << (k + 1) << "- " << _choices[k] << endl;
    }
}

unsigned int ConsoleMenu::choice() {
    return _choice;
}

void ConsoleMenu::getChoiceFromCin() {
    do {
        cout << "Make a choice : ";
        cin >> _choice;
    } while(_choice == 0 || _choice > _choices.size());
}




