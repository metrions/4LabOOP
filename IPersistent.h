#ifndef IPERSISTENT_H
#define IPERSISTENT_H

#include <string>

/*
    Интерфейс с описанием функционала для классов распределений
*/
class IPersistent {
public:
    // Запись в файл
    virtual void saveTofile(std::string path) const = 0;
    
    // Загрузка из файла
    virtual void load(std::string path) = 0;
};



#endif