#pragma once

#include <fstream>
#include <list>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <utility>
#include "figures.h"
#include "factory.h"



class Document {
public:
    Document() : id(1), name(""), buffer(0), factory() {};
    Document(std::string name) : id(1), name(name), buffer(0), factory() {};

    ~Document() = default;

    void Rename(const std::string &new_name) {
        this->name = new_name;
    }

    void Save(const std::string &filename) {
        SerialiseImpl(filename);
    }

    void Load(const std::string &filename) {
        DeserializeImpl(filename);
    }

    void Print() {
        std::for_each(this->buffer.begin(), this->buffer.end(), [](std::shared_ptr<Figure> shape) {
            shape->Print(std::cout) << std::endl;
        });
    }

    void RemovePrimitive(int id) {
        auto it = std::find_if(this->buffer.begin(), this->buffer.end(),
                [id](std::shared_ptr<Figure> shape) -> bool {
            return id == shape->getId();
        });

        if (it == this->buffer.end())
            throw std::logic_error("Figure with this id doesn't exist");

        this->buffer.erase(it);
    }

    void InsertPrimitive(FigureType type, std::pair<double, double> *vertices) {
        switch (type) {
            case rec:
                this->buffer.push_back(factory.FigureCreate(rec, vertices, id));
                break;
            case rhomb:
                this->buffer.push_back(factory.FigureCreate(rhomb, vertices, id));
                break;
            case trap:
                this->buffer.push_back(factory.FigureCreate(trap, vertices, id));
                break;
        }
        ++this->id;
    }

private:
    int id;
    std::string name;
    std::list<std::shared_ptr<Figure>> buffer;
    Factory factory;

    friend class InsertCommand;
    friend class RemoveCommand;

    void SerialiseImpl(const std::string &filename) const {
        std::ofstream os(filename, std::ios::binary | std::ios::out);
        if(!os)
            throw std::runtime_error("File is not opened");

        size_t len_name = this->name.size();
        os.write((char *) &len_name, sizeof(len_name));
        os.write((char *) this->name.c_str(), len_name);
        for (const auto &shape : this->buffer)
            shape->Serialize(os);
    }

    void DeserializeImpl(const std::string &filename) {
        std::ifstream is(filename, std::ios::binary | std::ios::in);
        if(!is)
            throw std::runtime_error("File is not opened");

        size_t len_name;
        is.read((char *) &len_name, sizeof(len_name));

        char *clear_name = new char[len_name + 1];
        clear_name[len_name] = 0;
        is.read(clear_name, len_name);
        this->name = std::string(clear_name);
        delete [] clear_name;

        FigureType type;
        while (true) {
            is.read((char *) &type, sizeof(type));
            if (is.eof())
                break;
            switch (type) {
                case rec:
                    this->buffer.push_back(factory.FigureCreate(rec));
                    break;
                case rhomb:
                    this->buffer.push_back(factory.FigureCreate(rhomb));
                    break;
                case trap:
                    this->buffer.push_back(factory.FigureCreate(trap));
                    break;
            }
            this->buffer.back()->Deserialize(is);
        }
        this->id = this->buffer.size();
    }

    std::shared_ptr<Figure> GetFigure(int id) {
        for (auto it = this->buffer.begin(); it != this->buffer.end(); ++it)
            if (id == (*it)->getId())
                return *it;
        return nullptr;
    }

    int getPos(int id) {
        int i = 0;
        for (auto it = this->buffer.begin(); it != this->buffer.end(); ++it) {
            if (id == (*it)->getId())
                return i;
            ++i;
        }
        return -1;
    }

    void InsertPrimitive(int pos, std::shared_ptr<Figure> figure) {
        auto it = this->buffer.begin();
        std::advance(it, pos);
        this->buffer.insert(it, figure);
    }

    void RemoveLastPrimitive() {
        if (this->buffer.empty())
            throw std::logic_error("Document is empty");
        this->buffer.pop_back();
    }

};
