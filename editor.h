#pragma once

#include <stack>
#include "document.h"
#include "command.h"



class Editor {
public:
    Editor() : doc(nullptr), history() {};

    void CreateDocument(const std::string &name) {
        this->doc = std::make_shared<Document>(name);
    }

    void InsertPrimitive(FigureType type, std::pair<double, double> *vertices) {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new InsertCommand(type, vertices));
        command->SetDocument(this->doc);
        command->Execute();
        this->history.push(command);
    }

    void RemovePrimitive(int id) {
        try {
            std::shared_ptr<Command> command = std::shared_ptr<Command>(new RemoveCommand(id));
            command->SetDocument(this->doc);
            command->Execute();
            this->history.push(command);
        } catch (std::exception &err) {
            std::cout << err.what() << std::endl;
            throw;
        }
    }

    void SaveDocument(const std::string &filename) {
        this->doc->Save(filename);
    }

    void LoadDocument(const std::string &filename) {
        this->doc = std::make_shared<Document>(filename);
        this->doc->Load(filename);
    }

    void Undo() {
        if (this->history.empty())
            throw std::logic_error("empty");

        std::shared_ptr<Command> lastCommand = this->history.top();
        lastCommand->UnExecute();
        this->history.pop();
    }

    void PrintDocument() {
        this->doc->Print();
    }

    bool DocumentExist() {
        return this->doc != nullptr;
    }

    ~Editor() = default;

private:
    std::shared_ptr<Document> doc;
    std::stack<std::shared_ptr<Command>> history;
};
