#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <vector>
#include "vector.hpp"


/**
 * @brief Шаблонный класс - упорядоченная таблица. Обеспечивает операции поиска, вставки и удалениы элемента.
*/
template <typename T>
class Table {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;

        size_t binary_search(T& x) {
            if (size_ == 0) return 0;
            size_t left = 0;
            size_t right = size_;
            size_t mid = 0;

            while (left < right) {
                mid = left + (right - left)/2;
                if (data_[mid] == x) return mid;
                else if (x > data_[mid]) left = mid + 1;
                else right = mid;
            }
            return left;
        }


        void resize() {
            T* new_data = new T[capacity_ * 2];
            for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
            delete [] data_;
            capacity_ *= 2;
            data_ = new_data;
        }


    public:
/**
 * @brief Класс Итератор для доступа к элементам таблицы
*/
        class Iterator {
            private:
                T* ptr_;
            public:
                Iterator() {;}

                Iterator(T* ptr) : ptr_(ptr) {;}

                T& operator *() { return *ptr_; }

                T* operator ->() { return ptr_; }

                T* pointer() { return ptr_; }

                Iterator& operator =(const Iterator& other) {
                    (*this).ptr_ = other.ptr_;
                    return *this;
                }

                Iterator& operator ++() {
                    ++(ptr_);
                    return *this;
                } 

                Iterator operator ++(int) {
                    Iterator tmp(*this);
                    (ptr_)++;
                    return tmp;
                }

                bool operator !=(const Iterator& other) const { return ptr_ != other.ptr_; }

                bool operator ==(const Iterator& other) const { return ptr_ == other.ptr_; }
        };

/**
 * @brief Пустой конструктор
*/
        Table() : size_(0), capacity_(1) { data_ = new T[1]; }


/**
 * @brief Копирующий конструктор
 * @param other Копируемая таблица
*/
        Table(const Table<T>& other) : size_(other.size_), capacity_(other.size_) {
            data_ = new T[other.size_];
            for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        }

/**
 * @brief Деструктор
*/
        ~Table() { delete [] data_; }


/**
 * @brief Геттер
 * @returns Количество элементов в таблице
*/
        size_t size() const { return size_; }


/**
 * @brief Геттер
 * @returns Максимальное количество элементов в таблице
*/
        size_t max_size() const { return std::numeric_limits<size_t>::max(); }


/**
 * @brief Геттер
 * @returns Указатель на данные
*/
        T* data() const { return data_; }


/**
 * @brief Вставка элемента в таблицу с сохранением упорядоченности
 * @param x Элемент для вставки
 * @returns Итератор
 * @throws std::invalid_argument При попытке вставки элемента, который уже содержится в таблице
*/
        Iterator insert(T& x) {
            if (size_ == 0) {
                (*this)[size_++] = x;
                return Iterator(data_);
            }

            size_t index = (*this).binary_search(x);
            if (index < size_ && (*this)[index] == x) throw std::invalid_argument("DUPLICATE");
            if (size_ == capacity_) this->resize();

            for (size_t i = size_; i > index; i--)
                data_[i] = data_[i - 1];
            size_++;
            data_[index] = x;
            return Iterator(data_ + index);
        }


/**
 * @brief Поиск элемента в таблице
 * @param x Элемент
 * @returns Итератор
 * @throws std::invalid_argument Если элемент не найден
*/
        Iterator find(T& x) {
            size_t i = (*this).binary_search(x);
            if ((*this)[i] == x) return Iterator(data_ + i);
            else throw std::invalid_argument("ELEMENT WAS NOT FOUND");
        }


/**
* @brief Удаление элемента из таблицы
* @param pos Итератор на элемент для удаления
* @returns Итератор на элемент после удаленного
*/
    Iterator erase(Iterator pos) noexcept {
        if (pos == this->end()) return this->end();

        Iterator next = pos;
        ++next;

        for (Iterator it = pos; it != this->end(); ++it) {
            if ((next) != this->end()) {
                *it = *next;
                ++next;
            } else {
                break;
            }
        }
        size_--;
        return pos;
    }


/**
* @brief Удаление диапазона элементов из таблицы
* @param first Итератор на начало диапазона
* @param last Итератор на конец диапазона (не включительно)
* @returns Итератор на элемент после диапазона
*/
    Iterator erase(Iterator first, Iterator last) noexcept {
        if (first == last) return first;

        size_t erased = 0;
        Iterator it = first;
        while (it != last){
            erased++;
            it++;
        }
        Iterator new_start = last;

        while (new_start != end()) {
           *first = *new_start;
            first++;
            new_start++;
        }

        size_ -= erased;
        return first;

    }

/**
* @brief Удаление всех элементов из таблицы
*/
    void clear() noexcept {
        size_ = 0;
    }


/**
 * @brief Изменение или вставка элемента
 * @param x Элемент
 * @returns Итератор на элемент
*/
        Iterator insert_or_assign(T& x) {
            size_t index = this->binary_search(x);
            if ((*this)[index] == x) {
                (*this)[index] = x;
                return Iterator(data_ + index);
            }

            if (size_ == 0) {
                (*this)[size_++] = x;
                return Iterator(data_);
            }

            if (size_ == capacity_) this->resize();

            for (size_t i = size_; i > index; i--)
                data_[i] = data_[i - 1];
            size_++;
            data_[index] = x;
            return Iterator(data_ + index);
        }
        

/**
 * @brief Оператор "квадратные скобки"
 * @param index Индекс элемента
 * @returns Элемент таблицы по индексу
*/
        T& operator [](size_t index) const { return data_[index]; }


/**
 * @brief Копирующий оператор "="
 * @param x Копируемая таблица
 * @returns Копия
*/
        Table<T>& operator =(const Table<T>& x) {
            data_ = x.data_;
            return *this;
        }


/**
 * @brief Итератор begin
 * @returns Итератор
*/
        Iterator begin() const { return Iterator(data_); }


/**
 * @brief Итератор end
 * @returns Итератор
*/
        Iterator end() const { return Iterator(data_ + size_); }


        friend std::ostream& operator <<(std::ostream& os, const Table<T>& table) {
            if (table.size_ == 0) std::cout << "Table is empty" << std::endl;
            for (size_t i = 0; i < table.size_; ++i) {
                os << table[i];
                std::cout << std::endl;
            }
            return os;
        }


        friend std::istream& operator >>(std::istream& is, Table<T> table) {
            delete [] table.data_;
            std::cout << "Input size of table:" << std::endl;
            while (!tryInput(table.size_)) std::cout << "Repeat the input" << std::endl;
            table.data_ = new T[table.size_];
            table.capacity_ = table.size_;
            for (size_t i = 0; i < table.size_; ++i) is >> table[i];
            return is;
        }
};

#endif

