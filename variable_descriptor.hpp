#ifndef VARIABLE_DESCRIPTOR_H
#define VARIABLE_DESCRIPTOR_H

#include <iostream>
#include "descriptor.hpp"
#include "input.hpp"


/**
 * @brief Шаблонный класс Простая переменная, хранит в себе значение и флаг инициализации
*/

template <typename T>
class VariableDescriptor : public Descriptor {
    private:
        T value_;
        bool init_ = false;

    public:
/**
 * @brief Пустой конструктор
*/
        VariableDescriptor() {;}


/**
 * @brief Инициализирующий конструктор
 * param x Значение
*/
        VariableDescriptor(T x) : value_(x), init_(true) {;}


/**
 * @brief Деструктор
*/
        ~VariableDescriptor() override {;}


/**
 * @brief Вывод переменной в консоль
*/
        void print() const override {
            std::cout << "init: " << init_ << "; ";
            if (init_) std::cout << "value: " << value_;
        }


/**
 * @brief Геттер
 * @returns Значение переменной
*/
        T value() const { return value_; }


/**
 * @brief Геттер
 * returns Тип дескриптора
*/
        std::string type() const override { return "variable"; }


/**
 * @brief Геттер
 * returns Флаг инициализации
*/
        bool init() const override { return init_; }


        size_t size_of() const override { return sizeof(*this); }

/** 
 * @brief Оператор копирования
 * @param x Копируемая переменная
 * @returns Ссылка на копию
*/
        VariableDescriptor& operator =(const VariableDescriptor& x) {
            value_ = x.value_;
            init_ = true;
            return *this;
        }


/**
 * @brief Оператор присваивания
 * @param x Значение
 * @returns Ссылка на проинициализированную переменную
*/
        VariableDescriptor& operator =(const T x) {
            value_ = x;
            init_ = true;
            return *this;
        }


/**
 * @brief Ввод переменной из консоли
*/
        void input() override {
            std::cout << "Input value:" << std::endl;
            std::cin >> value_;
            init_ = true;
        }


/**
 * @brief Оператор вывода
 * @param os Поток вывода
 * @param x Переменная
 * @returns Поток вывода
*/
        friend std::ostream& operator <<(std::ostream& os, const VariableDescriptor& x) {
            os << x.value_;
            return os;
        }


/**
 * @brief Оператор ввода
 * @param Поток ввода
 * @param Переменная
 * @returns Поток ввода
*/
        friend std::istream& operator >>(std::istream& is, VariableDescriptor& x) {
            std::cout << "Input value: " << std::endl;
            is >> x.value_;
            x.init_ = true;
            return is;
        }
};

#endif

