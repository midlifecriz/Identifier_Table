#ifndef VECTOR_HPP
#define VECTOR_HPP


#include "input.hpp"
#include <iostream>


/**
 * @brief Шаблонный класс - динамический массив, обеспечивающий добавление новых элементов в конец, вставку по индексу, удаление по индексу. Хранит в себе количество элементов size, емкость capacity и указатель на массив данных data
*/
template <typename T>
class Vector {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;

    public:
        class Iterator {
            private: 
                T* ptr_;
            public:
                Iterator() {;}

                Iterator(T* ptr) : ptr_(ptr) {;}

                T& operator *() { return *ptr_; }
                
                T* operator ->() { return ptr_; }

                Iterator& operator ++() {
                    ++ptr_;
                    return *this;
                }

                bool operator ==(const Iterator& other) const { return ptr_ == other.ptr_; }

                bool operator !=(const Iterator& other) const { return ptr_ != other.ptr_;}
        };
/**
 * @brief Пустой конструктор
*/
        Vector() : size_(0), capacity_(1) { data_ = new T[1]; }


/**
 * @brief Копирующий конструктор
 * @param other Копируемый вектор
*/

        Vector(const Vector& other) : size_(other.size_), capacity_(other.size_) {
            data_ = new T[size_];
            for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        }


/**
 * @brief Деструктор
*/
        ~Vector() { delete [] data_; }


/**
 * @brief Расширение выделенной памяти
*/
        void resize() {
            T* new_data = new T[capacity_ * 2];
            for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
            delete [] data_;
            capacity_ *= 2;
            data_ = new_data;
        }


/**
 * @brief Геттер
 * returns Количество элементов в массиве
*/
        size_t size() const { return size_; }


/**
 * @brief Геттер
 * @returns Количество выделенной памяти
*/
        size_t capacity() const { return capacity_; }


/**
 * @brief Геттер
 * @returns Указатель на данные
*/
        T* data() const { return data_; }

        bool empty() const { return size_ == 0; }


        bool full() const { return size_ == capacity_; }


/**
 * @brief Оператор "квадратные скобки"
 * @param index Индекс элмента массива
 * @returns Ссылка на элемент массива
*/
        T& operator [](size_t index) const { return *(data_ + index); }


/**
 * @brief Копирующий оператор "="
 * @param src Копируемый вектор
 * @returns Копия
*/
        Vector& operator =(const Vector& src) {
            size_ = src.size_;
            capacity_ = src.capacity_;
            delete [] data_;
            T* new_data = new T[src.capacity_];
            for (size_t i = 0; i < src.size_; ++i) new_data[i] = src.data_[i];
            data_ = new_data;
            return *this;
        }


/**
 * @brief Оператор "+="
 * @param x Добавляемый элемент
 * @returns Вектор
*/
        Iterator push_back(const T& x) {
            if (size_ == capacity_) (*this).resize();
            (*this).data_[size_++] = x;
            return Iterator(data_ + size_ - 1);
        }


/**
 * @brief Вставка элемента по индексу
 * @param x Элемент
 * @param index Индекс для вставки
 * @throws std::invalid_argument Если индекс выходит за пределы массива
*/
        Iterator insert(const T& x, size_t index) {
            if (index > size_) throw std::invalid_argument("INDEX OUT OF RANGE");
            if (size_ == 0) {
                this->push_back(x);
                return Iterator(data_);
            }

            if (size_ == capacity_) (*this).resize();

            for (size_t i = size_; i > index; i--)
                data_[i] = data_[i - 1];
            size_++;
            data_[index] = x;
            return Iterator(data_ + index);
        }


/**
 * @brief Удаление элемента по индексу
 * @param index Индекс удаляемого элемента
 * @throws std::invalid_argument Если индекс выходит за пределы массива
*/
        Iterator erase(size_t index) {
            if (index >= size_) throw std::invalid_argument("INDEX OUT OF RANGE");
            for (size_t i = index; i < size_ - 1; ++i) data_[i] = data_[i + 1];
            size_--;
            return Iterator(data_ + index);
        }

        
/**
 * @brief Оператор вывода
 * @param os Поток вывода
 * @param x Вектор
 * @returns Поток вывода
*/
        friend std::ostream& operator <<(std::ostream& os, const Vector& x) {
            for (size_t i = 0; i < x.size_; ++i) os << x.data_[i];
            os << std::endl;
            return os;
        }


/**
 * @brief Оператор ввода
 * @param is Поток ввода
 * @param x Вектор
 * @returns Поток ввода
*/
        friend std::istream& operator >>(std::istream& is, Vector& x) {
            delete [] x.data_;
            std::cout << "Input quantity of elements: " << std::endl;
            while (!tryInput(x.size_)) std::cout << "Repeat the input" << std::endl;
            x.data_ = new T[x.size_];
            x.capacity_ = x.size_;
            for (size_t i = 0; i < x.size_; ++i) is >> x.data_[i];
            return is;
        }
};


#endif

