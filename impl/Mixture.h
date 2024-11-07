#ifndef MIXTURE_H
#define MIXTURE_H

#include <iostream>
#include "../IDistribution.h"
#include "./Distribution.h"
#include <fstream>
#include <string>

using namespace std;
/*
    Класс для основного распределения
*/
class Mixture : public IDistribution {
private:
    Distribution distribution1;
    Distribution distribution2;
    float p;

    // Возвращает характеристики распределения
    double* properties() const;

protected:
    double math() const; 
    double disp() const;
    double y1() const;
    double y2() const;

public:
    Mixture(Distribution& dist1, Distribution& dist2, float p);
    // Конструктор с чтением из файла
    Mixture();

    // Моделирование случайной величины
    double modeling() const;
    double* modelingPool(int size);
    // Плотность
    double density(float x) const override;
    // Характеристики распределения
    double* getProperties() const final;

    void showProperties() const;

    Distribution component1();
    Distribution component2();

    // Запись в файл
    void saveTofile(std::string path) const override;
    // Загрузка из файла
    void load(std::string path) override;

    // Деструктор
    ~Mixture();
};

#endif
