#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <iostream>
#include "../IDistribution.h"
#include "../Exception.h"
#include <fstream>
#include <string>
#include "../IPersistent.h"

using namespace std;
/*
    Класс для основного распределения
*/
class Distribution : public IDistribution, public IPersistent {
private:
    float v;  // Форма
    float u;  // Сдвиг
    float l;  // Масштаб

public:
    double math() const; 
    double disp() const;
    double y1() const;
    double y2() const;
    // Конструктор с чтением из файла
    Distribution(ifstream &stream);
    Distribution();
    // Базовый конструктор
    Distribution(float v, float u, float l);

    // Моделирование случайной величины
    double modeling() const;
    double* modelingPool(int size);
    // Плотность
    double density(float x) const override;
    // Характеристики распределения
    double* getProperties() const final;

    void showProperties() const;

    // Возвращает характеристики распределения
    double* properties() const;

    // Сеттеры и геттеры
    double getV() const;
    double getU() const ;
    double getL() const ;
    void setV(float v) ;
    void setU(float u) ;
    void setL(float l) ;

    // Запись в файл
    void saveTofile(std::string path) const override;
    void saveTofile(std::ofstream& out);
    // Загрузка из файла
    void load(std::string stream) override;
    void load(std::ifstream& in);

    // Деструктор
    ~Distribution();
};

#endif
