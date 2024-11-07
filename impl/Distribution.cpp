#include "Distribution.h"
#include <cmath>

// Конструктор с чтением из файла
Distribution::Distribution(ifstream &stream) {
    float tempV;
    float tempU;
    float tempL;
    stream >> tempV >> tempU >> tempL;
    setV(tempV);
    setU(tempU);
    setL(tempL);
}

void Distribution::load(std::string path) {
    std::ifstream in;
    in.open(path);
    float tempV;
    float tempU;
    float tempL;
    in >> tempV >> tempU >> tempL;
    setV(tempV);
    setU(tempU);
    setL(tempL);
}

// Базовый конструктор для наследников
Distribution::Distribution() {}

// Моделирование случайных величин (массив)
double* Distribution::modelingPool(int size) {
    double* pool = new double[size];
    for (int i = 0; i < size; i++) {
        pool[i] = modeling();
    }
    return pool;
}

// Возврат характеристик
double* Distribution::getProperties() const {
    double* mas = properties();
    return mas;
}

void Distribution::showProperties() const {
    double* mas = properties();
    cout << "Mathematical expectation = " << mas[0] << endl;
    cout << "Dispersion = " << mas[1] << endl;
    cout << "Coefficient of asymmetry = " << mas[2] << endl;
    cout << "Coefficient of excess = " << mas[3] << endl;
}

// Сеттеры и геттеры
double Distribution::getV() const {
    return v;
}

double Distribution::getU() const {
    return u;
}

double Distribution::getL() const {
    return l;
}

void Distribution::setV(float v) {
    if (v < 0) {
        throw Exception("Значение формы должно быть неотрицательным");
    }
    this->v = v;
}

void Distribution::setU(float u) {
    this->u = u;
}

void Distribution::setL(float l) {
    if (l == 0) {
        throw Exception("Значение масштаба не должно быть 0");
    }
    this->l = l;
}

// Деструктор
Distribution::~Distribution() {}

// Конструктор с параметрами
Distribution::Distribution(float v, float u, float l) {
    setV(v);
    setU(u);
    setL(l);
}

double Distribution::math() const {
    return getU();
}

double Distribution::disp() const {
    double w = exp(2.0 / (getV() * getV())) * getL() * getL();
    return (w - 1.0) / 2.0;
}

double Distribution::y1() const {
    return 0.0;
}

double Distribution::y2() const {
    double w = exp(2.0 / (getV() * getV())) * getL() * getL();
    return (w * w + 2.0 * w - 3.0) / 2.0;
}

// Реализация приватного метода properties()
double* Distribution::properties() const {
    double* props = new double[4];
    props[0] = math();
    props[1] = disp();
    props[2] = y1();
    props[3] = y2();
    return props;
}

// Моделирование случайной величины
double Distribution::modeling() const {
    double r1;
    do {
        r1 = (double)rand() / RAND_MAX;
    } while (r1 == 0. || r1 == 1.);

    double r2;
    do {
        r2 = (double)rand() / RAND_MAX;
    } while (r2 == 0. || r2 == 1.);

    double z = sqrt(-2 * log(r1)) * cos(2 * M_PI * r2);
    double x = sinh(z / getV());
    return x;
}

// Плотность распределения
double Distribution::density(float x) const {
    double f;
    double answer = (x - getU()) / getL();
    double part1 = getV() / sqrt(2 * M_PI);
    double part2 = 1.0 / sqrt(answer * answer + 1.0);
    double part3 = exp(-0.5 * getV() * getV() * pow(log(answer + sqrt(answer * answer + 1.0)), 2));
    f = (part1 * part2 * part3) / getL();
    return f;
}


void Distribution::saveTofile(std::string path) const {
    std::ofstream out;
    out.open(path);
    if (out.is_open()) {
        out << getV() << endl;
        out << getU() << endl;
        out << getL();
    }
}
