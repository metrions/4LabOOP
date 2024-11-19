#ifndef MIXTURE_H
#define MIXTURE_H

#include <iostream>
#include "../IDistribution.h"
#include "./Distribution.h"
#include "../IPersistent.h"
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
/*
    Класс для основного распределения
*/
template<class Distribution1, class Distribution2> 
class Mixture : public IDistribution, public IPersistent {
private:
    Distribution1& distribution1;
    Distribution2& distribution2;
    float p;

public:
    Mixture(Distribution1& dist1, Distribution2& dist2, float p);
    // Моделирование случайной величины
    double modeling() const;
    double* modelingPool(int size);
    // Плотность
    double density(float x) const override;
    // Характеристики распределения
    double* getProperties() const final;
    // Возвращает характеристики распределения
    double* properties() const;

    double math() const; 
    double disp() const;
    double y1() const;
    double y2() const;

    void showProperties() const;

    Distribution1 component1();
    Distribution2 component2();

    // Запись в файл
    void saveTofile(std::string path) const override;
    void saveTofile(std::ofstream& out) const;
    // Загрузка из файла
    void load(std::string path) override;
    void load(std::ifstream& in);

    // Деструктор
    ~Mixture();
};

template <class Distribution1, class Distribution2>
Mixture<Distribution1, Distribution2>::Mixture(Distribution1 &dist1, Distribution2 &dist2, float p)
    : distribution1(dist1), distribution2(dist2), p(p) {}

// Возврат первого распределения
template<class Distribution1, class Distribution2>
Distribution1 Mixture<Distribution1, Distribution2>::component1(){
    return distribution1;
}

// Возврат второго распределения
template<class Distribution1, class Distribution2>
Distribution2 Mixture<Distribution1, Distribution2>::component2(){
    return distribution2;
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::load(std::string path) {
    std::ifstream in;
    in.open(path);
    float pValue;
    in >> p;
    distribution1.load(in);
    distribution2.load(in);
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::load(std::ifstream& in){
    float pValue;
    in >> p;
    distribution1.load(in);
    distribution2.load(in);
}

// Моделирование случайных величин (массив)
template<class Distribution1, class Distribution2>
double* Mixture<Distribution1, Distribution2>::modelingPool(int size) {
    double* pool = new double[size];
    for (int i = 0; i < size; i++) {
        pool[i] = modeling();
    }
    return pool;
}

// Возврат характеристик
template<class Distribution1, class Distribution2>
double* Mixture<Distribution1, Distribution2>::getProperties() const {
    double* mas = properties();
    return mas;
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::showProperties() const {
    double* mas = properties();
    cout << "Mathematical expectation = " << mas[0] << endl;
    cout << "Dispersion = " << mas[1] << endl;
    cout << "Coefficient of asymmetry = " << mas[2] << endl;
    cout << "Coefficient of excess = " << mas[3] << endl;
}

// Деструктор
template<class Distribution1, class Distribution2>
Mixture<Distribution1, Distribution2>::~Mixture() {
    
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::math() const {
    double math1 = distribution1.math();
    double math2 = distribution2.math();
    return math1 * p + math2 * (1.0-p);
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::disp() const {
    double* props1 = distribution1.properties();
    double* props2 = distribution2.properties();
    double mathValue = math();
    cout << props1[0] << endl;
    cout << props1[1] << endl;
    cout << props2[0] << endl;
    cout << props2[1] << endl;

    double dispValue = p * (props1[0] * props1[0] + props1[1]) + (1 - p) * (props2[0] * props2[0] + 
    props2[1]) - mathValue * mathValue;
    // cout << dispValue << endl;
    delete[] props1;
    delete[] props2;
    return dispValue;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::y1() const {
    double* props1 = distribution1.properties();
    double* props2 = distribution2.properties();
    double mathValue = math();
    double dispValue = disp();

    double y1 = 1 / pow(dispValue, 1.5) * (p * (pow(props1[0] - mathValue, 3) + 3 * (props1[0] - mathValue) * 
    props1[1] + pow(props1[1], 1.5) * props1[2])) +
    ((1 - p) * (pow(props2[0] - mathValue, 3) + 3 * (props2[0] - mathValue) * props2[1] + pow(props2[1], 
    1.5) * props2[2]));
    delete[] props1;
    delete[] props2;
    return y1;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::y2() const {
    double* props1 = distribution1.properties();
    double* props2 = distribution2.properties();
    double mathValue = math();
    double dispValue = disp();

    double y2 = (p * (pow(props1[0] - mathValue, 4) + 6 * pow(props1[0] - mathValue, 2)) * props1[1] + 4 * 
    (props1[0] - mathValue) * pow(props1[1], 1.5) + props1[2] + pow(props1[1], 2) * (props1[3] + 3)) +
    ((1 - p) * (pow(props2[0] - mathValue, 4) + 6 * pow(props2[0] - mathValue, 2)) * props2[1] + 4 * 
    (props2[0] - mathValue) * pow(props2[1], 1.5) + props2[2] + pow(props2[1], 2) * (props2[3] + 3));
    delete[] props1;
    delete[] props2;
    return y2;
}

// Реализация приватного метода properties()
template<class Distribution1, class Distribution2>
double* Mixture<Distribution1, Distribution2>::properties() const {
    double* props = new double[4];
    props[0] = math();
    props[1] = disp();
    props[2] = y1();
    props[3] = y2();
    return props;
}

// Моделирование случайной величины
template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::modeling() const {
    double r; 
    double x;
    do r=(double)rand()/RAND_MAX; 
    while(r==0.||r==1.);
    if (r > p){
        x = distribution1.modeling();
    }
    else {
        x = distribution2.modeling();
    }
    return x;
}

// Плотность распределения
template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::density(float x) const {
    return (1-p) * distribution1.density(x) + p * distribution2.density(x);
}

// Доделать
template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::saveTofile(std::string path) const {
    std::ofstream out;
    out.open(path);
    saveTofile(out);
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::saveTofile(std::ofstream& out) const {
    out << p << endl;
    distribution1.saveTofile(out);
    distribution2.saveTofile(out);
}



#endif
