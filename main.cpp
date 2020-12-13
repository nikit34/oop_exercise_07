#include <iostream>
#include <string>
#include "editor.h"



void create(std::string& cmd, Editor &editor) {
    if (editor.exist()) {
        std::cout << "Save old document? Yes/No ";
        std::cin >> cmd;
        if (cmd == "Yes" || cmd == "Y") {
            std::string filename;
            std::cout << "Enter name of file: ";
            std::cin >> filename;
            try {
                editor.SaveDocument(filename);
            } catch (std::runtime_error &err) {
                std::cout << err.what() << std::endl;
            }
        }
    }
    std::cout << "Enter name of new project" << std::endl;
    std::cin >> cmd;
    editor.CreateDocument(cmd);
    std::cout << "Document " << cmd << " is created" << std::endl;
}

void save(Editor &editor) {
    if (!editor.DocumentExist())
        throw std::runtime_error("Document does not exist");

    std::string filename;
    std::cin >> filename;

    try {
        editor.SaveDocument(filename);
        std::cout << "Document save in file " << filename << std::endl;
    } catch (std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
}

void load(Editor &editor) {
    std::string cmd;
    std::string filename;
    if (editor.DocumentExist()) {
        std::cout << "Save old document? Yes/No ";
        std::cin >> cmd;
        if (cmd == "Yes") {
            std::cout << "Enter name of file ";
            std::cin >> filename;
            try {
                editor.SaveDocument(filename);
            } catch (std::runtime_error& err) {
                std::cout << err.what() << std::endl;
            }
        }
    }
    std::cout << "Enter name of file to upload: ";
    std::cin >> filename;
    try {
        editor.LoadDocument(filename);
        std::cout << "Document loaded from file " << filename << std::endl;
    } catch (std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }
}

void add(Editor &editor) {
    if (!editor.DocumentExist())
        throw std::runtime_error("Document does not exist");
    std::string type;
    std::cout << "Enter shape type: \n\t- rec \n\t- trap \n\t- rhomb\n";
    std::cin >> type;

    Vertex *vertices = new Vertex[4];
    if (type == "rec") {
        std::cout << "Enter coordinates separated by space\n";
        for (int i = 0; i < 4; ++i) {
            std::cin >> vertices[i];
        }
        try {
            editor.InsertPrimitive(rec, vertices);
            delete [] vertices;
            vertices = nullptr;
        } catch (std::logic_error &err) {
            std::cout << err.what() << std::endl;
            delete [] vertices;
            vertices = nullptr;
            return;
        }
        std::cout << "Primitive is added" << std::endl;
    }
    else if (type == "trap") {
        std::cout << "Enter the coordinates separated by space: ";
        for (int i = 0; i < 4; i++) {
            std::cin >> vertices[i];
        }
        try {
            editor.InsertPrimitive(Trapeze, vertices);
            delete [] vertices;
            vertices = nullptr;
        } catch (std::logic_error &err) {
            std::cout << err.what() << std::endl;
            delete [] vertices;
            vertices = nullptr;
            return;
        }
        std::cout << "Primitive is added"  << std::endl;
    }
    else if (type == "rhomb") {
        std::cout << "Enter the coordinates separated by a space: ";
        for (int i = 0; i < 4; i++) {
            std::cin >> vertices[i];
        }
        try {
            editor.InsertPrimitive(Rhomb, vertices);
            delete [] vertices;
            vertices = nullptr;
        } catch (std::logic_error &err) {
            std::cout << err.what() << std::endl;
            delete [] vertices;
            vertices = nullptr;
            return;
        }
        std::cout << "Primitive is added" << std::endl;
    }
    else {
        std::cout << "Primitive isn't added" << std::endl;
        return;
    }
}

void remove(Editor &editor) {
    if (!editor.DocumentExist())
        std::cout << "Document does not exist" << std::endl;
    int id;
    std::cin >> id;
    if (id <= 0) {
        std::cout << "Invalid id" << std::endl;
        return;
    }
    try {
        editor.RemovePrimitive(id);
    } catch (std::exception &e) {
        std::cout << "Invalid id" << std::endl;
        return;
    }
    std::cout << "Remove primitive at id: " << id << std::endl;
}

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

int main() {
    Editor editor;
    uint16_t cmd = 1;

    while(cmd != 9) {
        if (cmd == 1) {
            menu();
        }
        else if (cmd == 2) {
            create(editor);
        }
        else if (cmd == 3) {
            try {
                load(editor);
            } catch (std::runtime_error &err) {
                std::cout << err.what() << "\n\n";
            }
        }
        else if (cmd == 4) {
            try {
                save(editor);
            } catch (std::runtime_error &err) {
            }
        }
        else if (cmd == 5) {
            try {
                add(editor);
            } catch (std::runtime_error &err) {
                std::cout << err.what() << "\n\n";
            }
        }
        else if (cmd == 6) {
            try {
                remove(editor);
            } catch (std::exception &err) {
                std::cout << err.what() << std::endl;
            }
        }
        else if (cmd == 7) {
            try {
                editor.Undo();
                std::cout << "OK\n";
            } catch (std::logic_error &err) {
                std::cout << err.what() << "\n\n";
            }
        }
        else if (cmd == 8) {
            if (!editor.DocumentExist()) {
                std::cout << "Document does not exist" << "\n\n";
                continue;
            }
            editor.PrintDocument();
        }
        else if(cmd == "Exit"){
            return 0;
        } else {
            std::cout << "You did not choose an action\n";
        }
        std::cin >> cmd;
        std::cout << std::endl;
    }
    return 0;
}