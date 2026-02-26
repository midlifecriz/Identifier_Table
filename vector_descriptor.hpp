#ifndef VECTOR_DESCRIPTOR_HPP
#define VECTOR_DESCRIPTOR_HPP


#include "input.hpp"
#include "vector.hpp"
#include "descriptor.hpp"


/**
 * @brief Шаблонный класс - динамический массив, обеспечивающий добавление новых элементов в конец, вставку по индексу, удаление по индексу. Хранит в себе количество элементов size, емкость capacity и указатель на массив данных data
*/
template <typename T>
class VectorDescriptor : public Descriptor {
    private:
        Vector<T> data_;
    public:
/**
 * @brief Пустой конструктор
*/
        VectorDescriptor() {;}


/**
 * @brief Копирующий конструктор
 * @param other Копируемый вектор
*/

        VectorDescriptor(const VectorDescriptor& other) { data_ = other.data_; }


/**
 * @brief Деструктор
*/
        ~VectorDescriptor() {;}


/**
 * @brief Геттер
 * returns Количество элементов в массиве
*/
        size_t size() const { return data_.size(); }


/**
 * @brief Геттер
 * @returns Количество выделенной памяти
*/
        size_t capacity() const { return data_.capacity(); }


/**
 * @brief Оператор "квадратные скобки"
 * @param index Индекс элмента массива
 * @returns Ссылка на элемент массива
*/
        T& operator [](size_t index) const { return data_[index]; }


/**
 * @brief Копирующий оператор "="
 * @param src Копируемый вектор
 * @returns Копия
*/
        VectorDescriptor& operator =(const VectorDescriptor& src) {
            data_ = src.data_;
            return *this;
        }


/**
 * @brief Оператор "+="
 * @param x Добавляемый элемент
 * @returns Вектор
*/
/*
        Vector& operator +=(const T& x) {
            if (size == capacity) (*this).resize();
            (*this).data[size++] = x;
            return (*this);
        }
*/

/**
 * @brief Вставка элемента по индексу
 * @param x Элемент
 * @param index Индекс для вставки
*/
        void insert(const T& x, size_t index) { data_.insert(x, index); }


/**
 * @brief Удаление элемента по индексу
 * @param index Индекс удаляемого элемента
*/
        void erase(size_t index) { data_.erase(index); }


/**
 * @brief Вывод в консоль
*/
        void print() const override {
            std::cout << "size: " << data_.size() << ";" << " capacity: " << data_.capacity() << "; ";
            std::cout << data_;
            std::cout << std::endl;
        }


/**
 * @brief Ввод массива с клавиатуры
*/
        void input() override { std::cin >> data_; }


/**
 * @brief Геттер
 * @returns Тип дескриптора
*/
        std::string type() const override { return "vector"; }


/**
 * @brief Геттер
 * @returns Флаг заполненности массива
*/
        bool init() const override { return data_.full(); }
        

        size_t size_of() const override { return sizeof(*this); }

/**
 * @brief Оператор вывода
 * @param os Поток вывода
 * @param x Вектор
 * @returns Поток вывода
*/
        friend std::ostream& operator <<(std::ostream& os, const VectorDescriptor& x) {
            os << x.data_;
            os << std::endl;
            return os;
        }


/**
 * @brief Оператор ввода
 * @param is Поток ввода
 * @param x Вектор
 * @returns Поток ввода
*/
        friend std::istream& operator >>(std::istream& is, VectorDescriptor& x) {
            is >> x.data_;
            return is;
        }
};


#endif

