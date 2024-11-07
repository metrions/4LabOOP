#include "Empiric.h"
#include <cmath>


Empiric::Empiric(int n0, IDistribution& prim, int k0) : n(n0), k(k0), dist(prim) {
    data = prim.modelingPool(n0);
    this->n = n0;
    this->k = k0;
    calculate_fr(n);
}

Empiric::Empiric(const Empiric& emp) : n(emp.n), k(emp.k), dist(emp.dist) {
    double* dataNew =  new double[emp.getSize()];
    double* frNew =  new double[emp.getSize()];
    double* dataCopy = emp.getData();
    double* frCopy = emp.getFr();
    for (int i=0; i<emp.getSize(); i++){
        dataNew[i] = dataCopy[i];
        frNew[i] = frCopy[i];
    }
    delete[] data;
    delete[] fr;
    data = dataNew;
    fr = frNew;
}

Empiric& Empiric::operator=(const Empiric & emp){
    // проверка на присваивание самому себе
    if(this==&emp) return *this;
    // если размеры изменяются, то перераспределяем память
    if(n!=emp.n){ 
        delete [] data;
        n=emp.n;
        data=new double[n]; 
    }
    if(k!=emp.k){ 
        delete [] fr;
        k=emp.k;
        fr=new double[k]; 
        delete [] bins;
        bins=new double[k]; 
    }
    double* empData = emp.getData();
    for (int i=0; i<n; i++){
        data[i] = empData[i];
    }
    double* empBins = emp.getBins();
    double* empFr = emp.getFr();
    for (int i=0; i<n; i++){
        bins[i] = empBins[i];
        fr[i] = empFr[i];
    }
    return *this;

}

// Деструктор
Empiric::~Empiric() {
    delete[] data;
    delete[] bins;
    delete[] fr;
}

// Моделирование случайных величин (массив)
double* Empiric::modelingPool(int size) {
    double* pool = new double[size];
    for (int i = 0; i < size; i++) {
        pool[i] = modeling();
    }
    return pool;
}

// Возврат характеристик
double* Empiric::getProperties() const {
    double* mas = properties();
    return mas;
}

void Empiric::showProperties() const {
    double* mas = properties();
    cout << "Mathematical expectation = " << mas[0] << endl;
    cout << "Dispersion = " << mas[1] << endl;
    cout << "Coefficient of asymmetry = " << mas[2] << endl;
    cout << "Coefficient of excess = " << mas[3] << endl;
}

void Empiric::calculate_fr(int size) {
    fr = new double[k];
    bins = new double[k];
    double min = 99999999, max = -99999999;
    for (int i = 0; i < size; i++) {
        if (data[i] > max) max = data[i];
        if (data[i] < min) min = data[i];
    }
    max += (max - min) * 1e-6;
    cout << "max = " << max << ", min = " << min << endl;
    double delta = (max - min) / k;
    for (int i = 0; i < size; i++) {
        int m = int((data[i] - min) / delta);
        if (m == k) m--; // Защита от выхода за пределы массива
        fr[m]++;
    }
    for (int i = 0; i < k; i++) {
        bins[i] = min + (max - min) / delta * i;
        fr[i] = fr[i] / (size * delta);
    }
}

int Empiric::getSize() const {
    return n;
}

double* Empiric::getData() const{
    return data;
}

double* Empiric::getFr() const {
    return fr;
}

double* Empiric::getBins() const {
    return bins;
}

void Empiric::load(std::string stream) {
    
}

double Empiric::math() const {
    return math_solve(data, n);
}

// Вычисление мат ожидания
double Empiric::math_solve(double* mas, int size) const{
    double math = 0;
    for (int i =0; i< size; i++){
        math += mas[i];
    }
    return math / ((double) size);
}

// Вычисление моментов
double Empiric::calculate_moment(const double* mas, int size, double math, int order) const {
    double sum = 0;
    double* newArray = new double[size];
    for (int i = 0; i < size; ++i) {
        newArray[i] = std::pow(mas[i] - math, order);
    }
    return math_solve(newArray, size);
}

double Empiric::disp() const {
    return calculate_moment(data, n, math(), 2);
}

double Empiric::y1() const {
    return calculate_moment(data, n, math(), 3) / std::pow(disp(), 1.5);
}

double Empiric::y2() const {
    return calculate_moment(data, n, math(), 4) / std::pow(disp(), 2) - 3.0;
}

// Реализация приватного метода properties()
double* Empiric::properties() const {
    double* props = new double[4];
    props[0] = math();
    props[1] = disp();
    props[2] = y1();
    props[3] = y2();
    return props;
}

// Моделирование случайной величины
double Empiric::modeling() const {
    return dist.modeling();
}

// Плотность распределения
double Empiric::density(float x) const {
    for (int i=0; i<k-1; i++){
        if (x >= bins[i] && x < bins[i+1]) return fr[i];
    }
    if (x < bins[0] || x > bins[k-1]) return 0;
}


void Empiric::saveTofile(std::string path) const {
    std::ofstream out;
    out.open(path);
    if (out.is_open()) {

    }
}
