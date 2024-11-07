#include "Mixture.h"
#include <cmath>

Mixture::Mixture(Distribution& dist1, Distribution& dist2, float p) {
    distribution1 = dist1;
    distribution2 = dist2;
    this->p = p;
}

// Возврат первого распределения
Distribution Mixture::component1(){
    return distribution1;
}

// Возврат второго распределения
Distribution Mixture::component2(){
    return distribution2;
}

// Доделать
void Mixture::load(std::string path) {
    std::ifstream in;
    in.open(path);
    float tempV1;
    float tempU1;
    float tempL1;
    in >> tempV1 >> tempU1 >> tempL1;
    component1().setV(tempV1);
    component1().setL(tempL1);
    component1().setU(tempU1);
    float tempV2;
    float tempU2;
    float tempL2;
    in >> tempV2 >> tempU2 >> tempL2;
    component2().setV(tempV2);
    component2().setL(tempL2);
    component2().setU(tempU2);

}

// Базовый конструктор для наследников
// Доделать
Mixture::Mixture() {}

// Моделирование случайных величин (массив)
double* Mixture::modelingPool(int size) {
    double* pool = new double[size];
    for (int i = 0; i < size; i++) {
        pool[i] = modeling();
    }
    return pool;
}

// Возврат характеристик
double* Mixture::getProperties() const {
    double* mas = properties();
    return mas;
}

void Mixture::showProperties() const {
    double* mas = properties();
    cout << "Mathematical expectation = " << mas[0] << endl;
    cout << "Dispersion = " << mas[1] << endl;
    cout << "Coefficient of asymmetry = " << mas[2] << endl;
    cout << "Coefficient of excess = " << mas[3] << endl;
}

// Деструктор
Mixture::~Mixture() {
    
}


double Mixture::math() const {
    double math1 = distribution1.math();
    double math2 = distribution2.math();
    return p * math1 + math2 * (1-p);
}

double Mixture::disp() const {
    double* props1 = distribution1.properties();
    double* props2 = distribution2.properties();
    double mathValue = math();

    double dispValue = p * (props1[0] * props1[0] + props1[1]) + (1 - p) * (props2[0] * props2[0] + 
    props2[1]) - mathValue * mathValue;
    delete[] props1;
    delete[] props2;
    return dispValue;
}

double Mixture::y1() const {
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

double Mixture::y2() const {
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
double* Mixture::properties() const {
    double* props = new double[4];
    props[0] = math();
    props[1] = disp();
    props[2] = y1();
    props[3] = y2();
    return props;
}

// Моделирование случайной величины
double Mixture::modeling() const {
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
double Mixture::density(float x) const {
    return (1-p) * distribution1.density(x) + p * distribution2.density(x);
}

// Доделать
void Mixture::saveTofile(std::string path) const {
    std::ofstream out;
    out.open(path);
    if (out.is_open()) {
        out << distribution1.getV() << endl;
        out << distribution1.getU() << endl;
        out << distribution1.getL() << endl;
        out << distribution2.getV() << endl;
        out << distribution2.getU() << endl;
        out << distribution2.getL() << endl;
    }
}
