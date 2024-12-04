#include <iostream>
#include "./impl/Distribution.h"
#include <fstream>
#include <chrono>
#include "./impl/Mixture.h"
#include "./impl/Empiric.h"

using namespace std;

void test_save(){
    std::ofstream out;
    out.open("./data.txt");
    Distribution newDist1;
    newDist1.load("./files/newfile.txt");
    Distribution newDist2;
    newDist2.load("./files/newfile2.txt");
    Mixture<Distribution, Distribution> mix2 = Mixture(newDist2, newDist2, 0.1);

    Mixture<Distribution, Mixture<Distribution, Distribution>> mix(newDist1, mix2, 0);
    mix.load("./files/file.txt");
    cout << mix.density(0) << endl;
    mix.saveTofile("./files/out.txt");
    if (mix.component1().getV() != 3 || mix.component1().getU() != 0 || mix.component1().getL() != 1) throw Exception("bad save");
}

void save_data(std::string path, double* data, IDistribution& dist, int n){
    std::ofstream out(path);
    for (int i=0; i<n-1; i++){
        out << data[i] << " " << dist.density(data[i]) << endl;
    }
    out << data[n-1] << " " << dist.density(data[n-1]);
    out.close();
}

// Тест для Эмпирической на основе Основного
void test_empiric_dist(){
    std::ifstream in("./files/newfile.txt");
    Distribution dist(in);
    IDistribution& iDist = dist;
    Empiric empiric(1000, iDist, 10);
    save_data("./files/out_empiric_dist.txt", empiric.getData(), empiric, 1000);
    save_data("./files/pool_dist.txt", dist.modelingPool(1000), dist, 1000);
}
// Тест для Эмпирической на основе Смеси
void test_empiric_mix(){
    Distribution newDist1;
    newDist1.load("./files/newfile.txt");
    Distribution newDist2;
    newDist2.load("./files/newfile.txt");
    Mixture mix2 = Mixture(newDist2, newDist2, 0.1);

    Mixture<Distribution, Mixture<Distribution, Distribution>> mix(newDist1, mix2, 0);
    IDistribution& iDist = mix;

    Empiric empiric(1000, iDist, 10);
    save_data("./files/out_empiric_mix.txt", empiric.getData(), empiric, 1000);
    save_data("./files/pool_mix.txt", mix.modelingPool(1000), mix, 1000);
}
// Тест для Эмпирической на основе Эмпирической
void test_empiric_empiric(){
    std::ifstream in("./files/newfile.txt");
    Distribution dist(in);
    IDistribution& iDist = dist;
    Empiric empiric(1000, iDist, 10);
    IDistribution& dist2 = empiric;
    Empiric empiric2(1000, empiric, 10);
    save_data("./files/out_empiric_empiric.txt", empiric2.getData(), empiric2, 1000);
    save_data("./files/pool_empiric.txt", empiric.modelingPool(1000), empiric, 1000);
}

void test_mix(){
    Distribution newDist1;
    Distribution newDist2;
    Mixture mix2 = Mixture(newDist2, newDist2, 0.1);

    Distribution dist(newDist1);

    Mixture<Distribution, Mixture<Distribution, Distribution>> mix(dist, mix2, 0.3);
    save_data("./files/test_mix.txt", mix.modelingPool(1000), mix, 1000);
    save_data("./files/test_mix_mix.txt", mix2.modelingPool(1000), mix2, 1000);
    save_data("./files/test_mix_dist1.txt", dist.modelingPool(1000), dist, 1000);
    save_data("./files/test_mix_dist2.txt", newDist2.modelingPool(1000), newDist2, 1000);
}

/*
    Тестирующая функция
*/
int main(){
    test_empiric_dist();
    test_save();

}