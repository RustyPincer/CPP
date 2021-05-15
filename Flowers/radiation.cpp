#include "radiation.h"

Neutral* Neutral::_instance = nullptr;
Neutral* Neutral::instance()
{
    if(_instance == nullptr) {
        _instance = new Neutral();
    }
    return _instance;
}

Alpha* Alpha::_instance = nullptr;
Alpha* Alpha::instance()
{
    if(_instance == nullptr) {
        _instance = new Alpha();
    }
    return _instance;
}

Delta* Delta::_instance = nullptr;
Delta* Delta::instance()
{
    if(_instance == nullptr) {
        _instance = new Delta();
    }
    return _instance;
}

void Neutral::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

void Alpha::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

void Delta::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

std::string Neutral::type() const
{
    return "Neutral";
}

std::string Alpha::type() const
{
    return "Alpha";
}

std::string Delta::type() const
{
    return "Delta";
}
