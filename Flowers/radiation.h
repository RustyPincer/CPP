#ifndef RADIATION_H
#define RADIATION_H

#include <string>

class Radiation
{
    public:
        virtual std::string type() const = 0;

    protected:
};

class Neutral : public Radiation
{
public:
    static Neutral* instance();
    static void destroy();
    std::string type() const override;
public:
    Neutral(){}
private:
    static Neutral* _instance;
};

class Alpha : public Radiation
{
public:
    static Alpha* instance();
    static void destroy();
    std::string type() const override;
public:
    Alpha(){}
private:
    static Alpha* _instance;
};

class Delta : public Radiation
{
public:
    static Delta* instance();
    static void destroy();
    std::string type() const override;
public:
    Delta(){}
private:
    static Delta* _instance;
};

#endif // RADIATION_H
