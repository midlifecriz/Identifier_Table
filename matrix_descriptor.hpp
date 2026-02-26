#ifndef MATRIX_DESCRIPTOR_HPP
#define MATRIX_DESCRIPTOR_HPP


#include "vector.hpp"
#include "descriptor.hpp"


/**
 * @brief Шаблонный класс - непрямоугольная матрица, содержит в себе вектор векторов data, количетсво строк height и максимальное количество столбцов width
*/
template <typename T>
class MatrixDescriptor : public Descriptor {
    private:
        size_t height_;
        size_t width_;
        Vector<Vector<T>> data_;

    public:
/**
 * @brief Пустой конструктор
*/
        MatrixDescriptor() : height_(1), width_(1) {;}

/**
 * @brief Деструктор
*/
        ~MatrixDescriptor() override {;}


/**
 * @brief Геттер
 * @returns Количество строк
*/
        size_t height() const { return height_; }


/**
 * @brief Геттер
 * @returns Количество столбцов
*/
        size_t width() const { return width_; }


/**
 * @brief Копирующий оператор "="
 * @param src Копируемая матрица
 * @returns Копия
*/
        MatrixDescriptor& operator =(const MatrixDescriptor& src) {
            height_ = src.height_;
            width_ = src.width_;
            data_ = src.data_;
            return *this;
        }


/**
 * @brief Оператор "квадратный скобки"
 * @param index Индекс
 * @returns Строка матрицы
*/
        Vector<T>& operator [](size_t index) { return data_[index]; }


/**
 * @brief Вывод матрицы в консоль
*/
        void print() const override {
            std::cout << "height: " << height_ << "; width: " << width_ << "; data: ";
            std::cout << data_;
        }


/**
 * @brief Ввод матрицы с клавиатуры
*/
        void input() override {
            std::cin >> data_;
            height_ = data_.size();
            size_t max = 0;
            for (size_t i = 0; i < height_; ++i) max = max < data_[i].size() ? data_[i].size() : max;
            width_ = max;
        }


/**
 * @brief Геттер
 * @returns Тип дескриптора
*/
        std::string type() const override { return "matrix"; }


/**
 * @brief Геттер
 * @returns Флаг заполненности массива строк
*/
        bool init() const override { return data_.full(); }


        size_t size_of() const override { return sizeof(*this); }

/**
 * @brief Оператор вывода
 * @param os Поток вывода
 * @param x Матрица
 * @returns Поток вывода
*/
        friend std::ostream& operator <<(std::ostream& os, const MatrixDescriptor& x) {
            for (size_t i = 0; i < x.height_; ++i) { os << x.data_[i]; std::cout << std::endl; }
            return os;
        }


/**
 * @brief Оператор ввода
 * @param is Поток ввода
 * @param x Матрица
 * @returns Поток ввода
*/
        friend std::istream& operator >>(std::istream& is, MatrixDescriptor& x) {
            is >> x.data_;
            return is;
        }
};


#endif

