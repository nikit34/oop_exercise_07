#include <iostream>
#include <string>
#include "editor.h"



void menu() {
    std::cout << "1 - menu" << std::endl;
    std::cout << "2 - create new file" << std::endl;
    std::cout << "3 - load" << std::endl;
    std::cout << "4 - save [name]" << std::endl;
    std::cout << "5 - add [type]" << std::endl;
    std::cout << "6 - remove [id]" << std::endl;
    std::cout << "7 - undo" << std::endl;
    std::cout << "8 - print" << std::endl;
    std::cout << "9 - exit" << std::endl;
}

void create(std::string& cmd, Editor &editor) {
    if (editor.exist()) {
        std::cout << "Save old document or don't save? Yes/No\n";
        std::cin >> cmd;
        if (cmd == "Yes") {
            std::string filename;
            std::cout << "Enter name of file\n";
            std::cin >> filename;
            try {
                editor.SaveDocument(filename);
                std::cout << "Document save in file " << filename << "\n";
            } catch (std::runtime_error &err) {
                std::cout << err.what() << "\n";
            }
        }
    }
    std::cout << "Enter name of new project\n";
    std::cin >> cmd;
    editor.CreateDocument(cmd);
    std::cout << "Document " << cmd << " is created\n";
}