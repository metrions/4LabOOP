#ifndef EMPIRIC_H
#define EMPIRIC_H

#include <iostream>
#include "../IDistribution.h"
#include "./Distribution.h"
#include "./Mixture.h"
#include "../IPersistent.h"
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
/*
    Класс для основного распределения
*/
class Empiric : public IDistribution, public IPersistent {
private:
    int n; // объем выборки
    int k; // количество интервалов 
    double* data; // массив данных
    double* bins;
    double* fr;// массив относительных частот
    IDistribution& dist;
    
    void calculate_fr(int size);

public:
    double math() const; 
    double disp() const;
    double y1() const;
    double y2() const;
    Empiric(int n0, IDistribution& prim, int k0=0); // По основному

    // конструктор копирования и оператор присваивания 
    // для глубокого копирования
    Empiric(const Empiric& emp); 
    Empiric& operator=(const Empiric & emp);
    Empiric(std::string pool);

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
    // Загрузка из файла
    void load(std::string stream) override;

    double math_solve(double* mas, int size) const;
    double calculate_moment(const double* mas, int size, double math, int order) const;
    int getSize() const;
    double* getData() const;
    double* getBins() const;
    double* getFr() const;
    // Деструктор
    ~Empiric();
};

#endif
