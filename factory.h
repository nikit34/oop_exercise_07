#pragma once

#include "figures.h"


class Factory {
    public:

    Figure* FigureCreate(FigureType type) const {
        Figure* res;
        if(type == rec) {
            res = new rec;
        }
    }

}