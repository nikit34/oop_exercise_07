#pragma once

#include "figures.h"


class Factory {
public:
    std::shared_ptr<Figure> FigureCreate(FigureType type) const {
        std::shared_ptr<Figure> res;
        if (type == rec) {
            res = std::make_shared<rec>();
        } else if (type == rhomb) {
            res = std::make_shared<rhomb>();
        } else if (type == trap) {
            res = std::make_shared<trap>();
        }
        return res;
    }

    std::shared_ptr<Figure> FigureCreate(FigureType type, std::pair<double, double> *vertices, int id) const {
        std::shared_ptr<Figure> res;
        if (type == rec) {
            res = std::make_shared<Rectangle>(vertices[0], vertices[1], vertices[2], vertices[3], id);
        } else if (type == rhomb) {
            res = std::make_shared<Rhombus>(vertices[0], vertices[1], vertices[2], vertices[3], id);
        } else if (type == trap) {
            res = std::make_shared<Trapezoid>(vertices[0], vertices[1], vertices[2], vertices[3], id);
        }

        return res;
    }
};