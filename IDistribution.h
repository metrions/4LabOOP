#ifndef IDISTRIBUTION_H
#define IDISTRIBUTION_H

#include <string>

/*
    Интерфейс с описанием функционала для классов распределений
*/
class IDistribution {
public:
    // Случайная величина
    virtual double modeling() const = 0;
    // Пул значений
    virtual double* modelingPool(int size) = 0;
    // Плотность
    virtual double density(float x) const = 0;
    // Возврат значений
    virtual double* getProperties() const = 0;
    // Вывод характеристик
    virtual void showProperties() const = 0;
};

#endif