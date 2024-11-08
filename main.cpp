#include <iostream>
#include "./impl/Distribution.h"
#include <fstream>
#include <chrono>
#include "./impl/Mixture.h"
#include "./impl/Empiric.h"

using namespace std;

void test(){
    ifstream in("./files/file.txt");

    Distribution dist;
    // Подстановка к интерфейсу
    Distribution elem = dist;

    if (elem.getV() != 1.5 || elem.getU() != 0 || elem.getL() != 1) throw Exception("Неправильное чтение");

    // Геттеры и сеттеры
    elem.setL(12);
    elem.setU(102);
    elem.setV(11);
    if (elem.getL() != 12 || elem.getU() != 102 || elem.getV() != 11) {
        throw Exception("Incorrect implementation of setters and getters");
    }
    
    // Неправильные значения для сеттеров и геттеров
    try{
        elem.setL(0);
        cout << "Incorrect ejection for setter L";
    }
    catch(Exception exc){}

    try{
        elem.setV(-12);
        cout << "Incorrect outlier for setter V";
    }
    catch(Exception exc){}
    // Чтение из файла в файле (1, 2, 3)
    Distribution newDist(in);
    // Подстановка к интерфейсу
    IDistribution& newElem = newDist;

    // Запись в файл
    newElem.saveTofile("./files/newfile.txt");
    ifstream newFile("./files/newfile.txt");
    float value1;
    float value2;
    float value3;
    newFile >> value1;
    newFile >> value2;
    newFile >> value3;
    if (value1 != 1.5 || value2 != 1 || value3 != 1){
        throw new Exception("Wrong writing to file");
    }
    // Вывод значений
    newElem.getProperties();
}

void testMix(){
    // Тест правильности привязки Основного распределения к миксу
    std::ofstream out;
    out.open("./data.txt");
    Distribution newDist1;
    newDist1.load("./files/file.txt");
    Distribution newDist2;
    newDist2.load("./files/newfile.txt");
    Mixture mix(newDist1, newDist2, 0.4);

}

void testEmpire(){
    // Проверка на корректное копирование
    std::ofstream out;
    out.open("./data.txt");

    std::ofstream out2;
    out2.open("./data2.txt");

    int N = 1000;
    Distribution dist;
    dist.load("./files/file.txt");
    IDistribution& dists = dist;
    Empiric empiric1(1000, dists, 10);
    Empiric empiric2 = empiric1;
    if (&empiric2 == &empiric1){
        throw Exception("Wrong copy file");
    }
    double* data1 = empiric1.getData();
    double* data2 = empiric2.getData();
    for (int i=0; i<N; i++){
        if (data1[i] != data2[i]) throw Exception("Wrong copy file");
    }

    // Проверка на корректное чтение выборки
    Empiric emp = Empiric("./out.txt");
    emp.savePool("./saved.txt");

    // Эмпирическая на основе основном распределении
    Distribution dist5;
    dist5.load("./files/file.txt");
    Distribution dist52;
    dist52.load("./files/file.txt");

    Mixture mix = Mixture(dist5, dist52, 0.5);
    IDistribution& distsq = mix;
    Empiric empiric3(1000, distsq, 10);
    IDistribution& distNew = empiric3;
    Empiric empiric5(1000, empiric3, 10);
}

void destinityTime(int N){
    ifstream in("./files/file.txt");
    Distribution newDist(in);
    IDistribution& newElem = newDist;
    std::ofstream out;
    out.open("destinityTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newDist.density(1);
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Destinity Time = " << sum / N << endl;
}

void destinityTime_mix(int N){
    Distribution newDist1;
    newDist1.load("./files/file.txt");

    Distribution newDist2;
    newDist2.load("./files/newfile.txt");

    Mixture newDist(newDist1, newDist2, 0.4);
    std::ofstream out;
    out.open("destinityTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newDist.density(1);
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Destinity Time = " << sum / N << endl;
}

void destinityTime_empiric(int N){
    Distribution newDist1;
    newDist1.load("./files/file.txt");
    IDistribution& dist = newDist1;

    Empiric newDist(1000, dist, 0.4);
    std::ofstream out;
    out.open("destinityTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newDist.density(1);
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Destinity Time = " << sum / N << endl;
}

void propertiesTime(int N){
    ifstream in("./files/file.txt");
    Distribution newDist(in);
    IDistribution& newElem = newDist;
    std::ofstream out;
    out.open("propertiesTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newElem.getProperties();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Properties Time = " << sum / N << endl;
}

void propertiesTime_mix(int N){
    Distribution newDist1;
    newDist1.load("./files/file.txt");

    Distribution newDist2;
    newDist2.load("./files/newfile.txt");

    Mixture newElem(newDist1, newDist2, 0.4);
    std::ofstream out;
    out.open("propertiesTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newElem.getProperties();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Properties Time = " << sum / N << endl;
}

void propertiesTime_empiric(int N){
    Distribution newDist1;
    newDist1.load("./files/file.txt");
    IDistribution& dist = newDist1;

    Empiric newDist(1000, dist, 0.4);
    std::ofstream out;
    out.open("propertiesTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newDist.getProperties();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Properties Time = " << sum / N << endl;
}

void modelingTime(int N){
    ifstream in("./files/file.txt");
    Distribution newDist(in);
    IDistribution& newElem = newDist;
    std::ofstream out;
    out.open("modelingTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newElem.modeling();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Modeling Time = " << sum / N << endl;
}

void modelingTime_mix(int N){
    Distribution newDist1;
    newDist1.load("./files/file.txt");
    IDistribution& dist = newDist1;

    Empiric newDist(1000, dist, 0.4);
    std::ofstream out;
    out.open("modelingTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        newDist.modeling();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Modeling Time = " << sum / N << endl;
}

void modelingTime_empiric(int N){
    ifstream in("./files/file.txt");
    Distribution newDist1;
    newDist1.load("./files/file.txt");

    Distribution newDist2;
    newDist2.load("./files/newfile.txt");

    Mixture mix(newDist1, newDist2, 0.4);
    std::ofstream out;
    out.open("modelingTime.txt");
    float sum = 0;
    for (int i=0; i<N; i++){
        auto start = chrono::steady_clock::now();
        mix.modeling();
        auto end = chrono::steady_clock::now();
        auto diff = std::chrono::duration<double, std::milli>(end - start).count();
        sum += diff;
        out << diff << endl; //ms
    }
    cout << "Avarage Modeling Time = " << sum / N << endl;
}


/*
    Тестирующая функция
*/
int main(){
    // test();
    // std::ofstream out;
    // out.open("./data.txt");
    // Distribution newDist1;
    // newDist1.load("./files/file.txt");

    // Distribution newDist2;
    // newDist2.load("./files/newfile.txt");

    // Mixture mix(newDist1, newDist2, 0.4);
    
    // double* data = mix.modelingPool(1000);
    // for (int i=0; i<1000; i++){
    //     out << data[i] << " " << mix.density(data[i]) << endl;
    // }
    // std::ofstream out;
    // out.open("./data.txt");

    // std::ofstream out2;
    // out2.open("./data2.txt");

    // int N = 1000;
    // Distribution dist;
    // dist.load("./files/file.txt");
    // IDistribution& dists = dist;
    // Empiric empiric1(1000, dists, 10);
    // IDistribution& emp = empiric1;
    // Empiric empiric(1000, emp, 10);

    // empiric.savePool("out.txt");
    // empiric.loadPool("out.txt");
    // empiric.savePool("saved.txt");
    testEmpire();
    // double* data = empiric.modelingPool(N);
    // double* data2 = dist.modelingPool(N);
    // for (int i=0; i<1000; i++){
    //     out << data[i] << " " << empiric.density(data[i]) << endl;
    //     out2 << data2[i] << " " << dist.density(data2[i]) << endl;
    // }
    // IDistribution& emp = empiric;
    // Empiric fin = Empiric(1000, emp, 3);

    // destinityTime(N);
    // propertiesTime(N);

    // modelingTime(N);
    // newElem.setL(1);
    // newElem.setU(0);
    // newElem.setV(1.5);
    // newElem.saveTofile("./files/out");

    // Distribution newDist2;
    // IDistribution& newElem2 = newDist2;
    // newElem2.load("./files/out.txt");
    // cout << newElem2.getL() << endl;
    // cout << newElem2.getU() << endl;
    // cout << newElem2.getV() << endl;

    // IDistribution& newDist1 = *(new Distribution());
    // newDist1.load("./files/file.txt");

    // Empiric dist = Empiric(100, newDist1, 4);
}