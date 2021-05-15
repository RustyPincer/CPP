#include <iostream>
#include "radiation.h"
#include "plant.h"
#include <vector>
#include <fstream>

using namespace std;

void create(const string &fileName, vector<Plant*> &plants, int &days, Radiation* &r)
{
    r = new Neutral();

    ifstream f(fileName);
    if(f.fail())
    {
        cout << "Wrong file name!\n";
        exit(1);
    }

    unsigned int n;
    f >> n;
    plants.resize(n);
    for( unsigned int i = 0; i < n; ++i )
    {
        string name;
        char ch;
        int nutrient;
        f >> name >> ch >> nutrient;
        switch(ch)
        {
            case 'p' :
                plants[i] = new Puffancs(name,nutrient);
                plants[i]->alive();
                break;
            case 'd' :
                plants[i] = new Deltafa(name,nutrient);
                plants[i]->alive();
                break;
            case 'b' :
                plants[i] = new Parabokor(name,nutrient);
                plants[i]->alive();
                break;
        }
    }

    f >> days;
}

int dailyChange(vector<Plant*> &plants, Radiation* dailyRad)
{
    int alphaNeed = 0;
    if(plants.size() > 0){
        for(int i = 0; i < plants.size(); i++){
            plants[i]->survive(dailyRad);
            alphaNeed += plants[i]->alphaNeed();
        }
    }
    return alphaNeed;
}

void destroyRad(){
    Neutral::destroy();
    Alpha::destroy();
    Delta::destroy();
}

void nextRad(Radiation* &r, int alphaNeed)
{
    if(alphaNeed >= 3){
        r = new Alpha();
    } else if (alphaNeed <= -3){
        r = new Delta();
    } else {
        r = new Neutral();
    }
}

bool strongest(vector<Plant*> &plants, Plant* &strongestPlant)
{
    if(plants.size() > 0){
        bool l = false;
        int maxNut = 0;
        for(int i = 0; i < plants.size(); i++){
            if(l && plants[i]->alive()){
                if(plants[i]->getNutrient() > maxNut){
                    maxNut = plants[i]->getNutrient();
                    strongestPlant = plants[i];
                }
            } else if (!l && plants[i]->alive()){
                maxNut = plants[i]->getNutrient();
                strongestPlant = plants[i];
                l = true;
            }
        }
        return l;
    }

}

template <typename Item>
void destroy(vector<Item*> &vec)
{
    for(unsigned int i = 0; i < vec.size(); ++i)
        delete vec[i];
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    Radiation* r;
    vector<Plant*> plants;
    int days;
    Plant* strongestPlant;

    create("inputs/input.txt", plants, days, r);


    for(int i = 1; i <= days; i ++){
        cout << "DAY" << i << endl;
        cout << "Actual radiation is " << r->type() << ", and the daily changes are: " << endl;
        nextRad(r, dailyChange(plants, r));

        for(int i = 0; i < plants.size(); i++){
            if(plants[i]->alive()){
                cout << plants[i]->getName() << " is a " << plants[i]->type() << " and it has " << plants[i]->getNutrient() << " nutrient." << endl;
            } else {
                cout << plants[i]->getName() << " is dead." << endl;
            }
        }
        cout << endl;
    }

    if(strongest(plants, strongestPlant)){
        cout << strongestPlant->getName() << " is the strongest plant." << endl;
    }else {
        cout << "There is no plant alive." << endl;
    }

    destroy(plants);
    destroyRad();


    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("no plants", "inp1.txt")
{
    Radiation* r;
    vector<Plant*> plants;
    int days;
    Plant* strongestPlant;

    create("inputs/inp1.txt", plants, days, r);
    for(int i = 1; i <= days; i ++){
        nextRad(r, dailyChange(plants, r));
    }

    CHECK(!strongest(plants, strongestPlant));
    CHECK(r->type() == "Neutral");

    destroy(plants);
    destroyRad();
}

TEST_CASE("no days", "inp2.txt")
{
    Radiation* r;
    vector<Plant*> plants;
    int days;
    Plant* strongestPlant;

    create("inputs/inp2.txt", plants, days, r);
    for(int i = 1; i <= days; i ++){
        nextRad(r, dailyChange(plants, r));
    }

    CHECK(strongest(plants, strongestPlant));
    CHECK(strongestPlant->getName() == "Falank");
    CHECK(r->type() == "Neutral");

    destroy(plants);
    destroyRad();
}

TEST_CASE("1 plant, 1 day", "inp3-8.txt")
{
    Radiation* r;
    vector<Plant*> plants;
    int days;
    Plant* strongestPlant;

    SECTION("Puffancs")
    {
        create("inputs/inp3.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(!strongest(plants, strongestPlant));
        CHECK(r->type() == "Neutral");
        destroy(plants);
        destroyRad();

        create("inputs/inp4.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Falank");
        CHECK(strongestPlant->getNutrient() == 6);
        CHECK(r->type() == "Alpha");
        destroy(plants);
        destroyRad();
    }

    SECTION("Deltafa")
    {
        create("inputs/inp5.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(!strongest(plants, strongestPlant));
        CHECK(r->type() == "Neutral");
        destroy(plants);
        destroyRad();

        create("inputs/inp6.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Sudar");
        CHECK(strongestPlant->getNutrient() == 3);
        CHECK(r->type() == "Delta");
        destroy(plants);
        destroyRad();
    }

    SECTION("Parabokor")
    {
        create("inputs/inp7.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(!strongest(plants, strongestPlant));
        CHECK(r->type() == "Neutral");
        destroy(plants);
        destroyRad();

        create("inputs/inp8.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Kopcos");
        CHECK(strongestPlant->getNutrient() == 2);
        CHECK(r->type() == "Neutral");
        destroy(plants);
        destroyRad();
    }
}

TEST_CASE("More plants", "inp9-12.txt")
{
    Radiation* r;
    vector<Plant*> plants;
    int days;
    Plant* strongestPlant;

    SECTION("1 Puffancs, 1 Deltafa, 1 Parabokor")
    {
        create("inputs/inp9.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Falank");
        CHECK(strongestPlant->getNutrient() == 6);
        CHECK(r->type() == "Alpha");
        destroy(plants);
        destroyRad();
    }

    SECTION("1 Puffancs, 4 Deltafa under 5 nutrient")
    {
        create("inputs/inp10.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Falank");
        CHECK(strongestPlant->getNutrient() == 6);
        CHECK(r->type() == "Delta");
        destroy(plants);
        destroyRad();
    }

    SECTION("1 Puffancs, 3 Deltafa under 5 nutrient, second day 1 Deltafa dies")
    {
        create("inputs/inp11.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Falank");
        CHECK(strongestPlant->getNutrient() == 5);
        CHECK(r->type() == "Neutral");
        destroy(plants);
        destroyRad();
    }

    SECTION("1 Puffancs, 3 Deltafa under 5 nutrient, second day 2 Deltafa die")
    {
        create("inputs/inp12.txt", plants, days, r);
        for(int i = 1; i <= days; i ++){
            nextRad(r, dailyChange(plants, r));
        }
        CHECK(strongest(plants, strongestPlant));
        CHECK(strongestPlant->getName() == "Falank");
        CHECK(strongestPlant->getNutrient() == 5);
        CHECK(r->type() == "Alpha");
        destroy(plants);
        destroyRad();
    }
}

#endif
