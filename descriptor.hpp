#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <iostream>

/**
 * @brief Абстрактный класс Дескриптор
*/
class Descriptor {
    public:
        virtual ~Descriptor() {;}

        virtual void print() const = 0;
        virtual void input() = 0;
        virtual std::string type() const = 0;
        virtual bool init() const = 0;
        virtual size_t size_of() const = 0;
};
#endif
