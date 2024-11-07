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


/*
    Тестирующая функция
*/
int main(){
    // test();
    // ifstream in("./files/file.txt");
    // Distribution newDist;
    // IDistribution& newElem = newDist;
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

    IDistribution& newDist1 = *(new Distribution());
    newDist1.load("./files/file.txt");

    Empiric dist = Empiric(100, newDist1, 4);
}