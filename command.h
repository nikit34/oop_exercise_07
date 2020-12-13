#pragma once

#include <stack>
#include "document.h"



class Command {
public:
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
    virtual ~Command() = default;

    void SetDocument(std::shared_ptr<Document> doc) {
        this->doc = doc;
    }
protected:
    std::shared_ptr<Document> doc;
};

class InsertCommand : public Command {
public:
    InsertCommand(FigureType type, std::pair<double, double> *vertices) :
            type{type}, vertices{vertices} {};

    void Execute() override {
        this->doc->InsertPrimitive(this->type, this->vertices);
    }

    void UnExecute() override {
        this->doc->RemoveLastPrimitive();
    }

private:
    FigureType type;
    std::pair<double, double> *vertices;
};


class RemoveCommand : public Command {
public:
    RemoveCommand(int id) : id(id), pos(0), figure(nullptr) {};

    void Execute() override {
        this->figure = this->doc->GetFigure(this->id);
        if (this->figure == nullptr) {
            return;
        }
        this->pos = this->doc->getPos(this->id);
        if (this->pos == 0) {
            return;
        }
        this->doc->RemovePrimitive(this->id);
    }

    void UnExecute() override {
        this->doc->InsertPrimitive(this->pos, this->figure);
    }

private:
    int id;
    int pos;
    std::shared_ptr<Figure> figure;
};