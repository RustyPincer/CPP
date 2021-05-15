#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "radiation.h"

class Plant
{
    public:
        virtual void survive(Radiation* r) = 0;
        virtual int alphaNeed() = 0;
        virtual std::string type() const = 0;
        virtual bool alive() =0;
        std::string getName() const {return _name;}
        int getNutrient() const {return _nutrient;}

    protected:
        std::string _name;
        int _nutrient;
        bool _alive;
        Plant(std::string name, int n) : _name(name), _nutrient(n) {}

};

class Puffancs : public Plant
{
public:
    void survive(Radiation* r) override;
    int alphaNeed() override;
    std::string type() const override;
    bool alive() override;
    Puffancs(std::string name, int n) : Plant(name, n) {}

};

class Deltafa : public Plant
{
public:
    void survive(Radiation* r) override;
    int alphaNeed() override;
    std::string type() const override;
    bool alive() override;
    Deltafa(std::string name, int n) : Plant(name, n) {}
};

class Parabokor : public Plant
{
public:
    void survive(Radiation* r) override;
    int alphaNeed() override;
    std::string type() const override;
    bool alive() override;
    Parabokor(std::string name, int n) : Plant(name, n) {}
};

#endif // PLANT_H
