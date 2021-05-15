#include "plant.h"

std::string Puffancs::type() const
{
    return "Puffancs";
}

bool Puffancs::alive()
{
    _alive = _nutrient > 0 && _nutrient < 11;
    return _alive;
}

std::string Deltafa::type() const
{
    return "Deltafa";
}

bool Deltafa::alive()
{
    _alive = _nutrient > 0;
    return _alive;
}

std::string Parabokor::type() const
{
    return "Parabokor";
}

bool Parabokor::alive()
{
    _alive = _nutrient > 0;
    return _alive;
}

void Puffancs::survive(Radiation* r)
{
    if (alive()){
        if (r->type() == "Alpha"){
            _nutrient += 2;
        } else if (r->type() == "Delta"){
            _nutrient -= 2;
        } else {
            _nutrient -= 1;
        }
    }
}

int Puffancs::alphaNeed()
{
    if (alive()){
        return 10;
    }
    return 0;
}

void Deltafa::survive(Radiation* r)
{
    if (alive()){
        if (r->type() == "Alpha"){
            _nutrient -= 3;
        } else if (r->type() == "Delta"){
            _nutrient += 4;
        } else {
            _nutrient -= 1;
        }
    }
}

int Deltafa::alphaNeed()
{
    if (alive()){
        if(_nutrient < 5){
            return -4;
        } else if(_nutrient < 11){
            return -1;
        }
        return 0;
    }
}

void Parabokor::survive(Radiation* r)
{
    if (alive()){
        if (r->type() == "Alpha"){
            _nutrient += 1;
        } else if (r->type() == "Delta"){
            _nutrient += 1;
        } else {
            _nutrient -= 1;
        }
    }
}

int Parabokor::alphaNeed()
{
    return 0;
}
