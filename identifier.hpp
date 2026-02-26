#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <iostream>
#include <string>
#include "descriptor.hpp"


/**
 * @brief Класс Идентификатор, хранит в себе имя длиной не более 8 символов и указатель на дескриптор
*/
class Identifier {
    private:
        std::string name;
        Descriptor* descriptor;
    public:
/**
 * @brief Пустой конструктор
*/
        Identifier();


/**
 * @brief Инициализирующий конструктор 
 * @param x Имя идентификатора
 * @throws std::invalid_argument Если имя длиной более 8 символов
**/
        Identifier(std::string& x);


/**
 * @brief Инициализирующий конструктор
 * @param x Имя идентификатора
 * @param y Указатель на дескриптор
 * throws std::invalid_argument Если имя длиной более 8 символов
*/
        Identifier(std::string& x, Descriptor* y);

/**
 * @brief Сеттер
 * @param x Имя идентификатора
 * @param desc Указатель на дескриптор
 * @throws std::invalid_argument Если имя длиной более 8 символов
*/
        void set_parameters(std::string& x, Descriptor* desc);


/**
 * @brief Геттер
 * @returns Имя идентификатора
*/
        std::string get_name() const;


        size_t size_of() const;


/**
 * @brief Геттер
 * @returns Указатель на дескриптор
*/
        Descriptor* get_descriptor() const;

/**
 * @brief Сеттер
 * @param x Имя идентификатора
 * @throws std::invalid_argument Если имя длиной более 8 символов
*/
        void set_name(std::string& x);

/**
 * @brief Сеттер
 * @param x Указатель на дескриптор
*/
        void set_descriptor(Descriptor* x);

/**
 * @brief Копирующий оператор "="
 * @param src Копируемый идентификатор
 * @returns Копия
*/
        Identifier& operator =(Identifier& src);

/**
 * @brief Оператор сравнения ">"
 * @param x Правый операнд
 * @returns True, если имя левого операнда больше имени правого, false в ином случае
*/
        bool operator >(Identifier& x) const;

/**
 * @brief Оператор сравнения "==" 
 * @param x Правый операнд
 * @returns True, если имена одинаковы, иначе false
*/
        bool operator ==(const Identifier& x) const;

/*
 * @brief Оператор вывода
 * @param os Поток вывода
 * @param x Идентификатор
 * @returns Поток вывода
*/
        friend std::ostream& operator <<(std::ostream& os, const Identifier& x);
  
/**
 * @brief Оператор ввода
 * @param is Поток ввода
 * @param x Идентификатор
 * @returns Поток ввода
*/
        friend std::istream& operator >>(std::istream& is, Identifier& x);
};

#endif

