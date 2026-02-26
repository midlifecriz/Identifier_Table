#include "threads.hpp"
#include "variable_descriptor.hpp"
#include "vector_descriptor.hpp"
#include "matrix_descriptor.hpp"
#include "identifier.hpp"
#include "table.hpp"
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>


size_t calculate_single_threaded(const Table<Identifier>& table) {
    if (table.size() == 0) return 0;
    size_t summary_size = 0;
    for (size_t i = 0; i < table.size(); ++i) summary_size += table[i].get_descriptor()->size_of();
    return summary_size;
}



size_t calculate_multithreading(const Table<Identifier>& table) {
    if (table.size() == 0) return 0;
    size_t summary_size = 0;

    size_t var_sum = 0;
    size_t vec_sum = 0;
    size_t matr_sum = 0;

    std::queue<Identifier> variables;
    std::queue<Identifier> vectors;
    std::queue<Identifier> matrixes;

    std::mutex mtx;
    std::condition_variable cv_var;
    std::condition_variable cv_vec;
    std::condition_variable cv_matr;

    bool var_queue_filled = false;
    bool vec_queue_filled = false;
    bool matr_queue_filled = false;


    //вычисляем суммарный размер для каждого типа
    auto calculate_sum = [&](std::queue<Identifier>& identifiers, size_t& sum, std::condition_variable& cv, bool& queue_filled) -> void {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]{ return queue_filled || !identifiers.empty(); });

            if (identifiers.empty()) {
                if (queue_filled) {
                    return; //завершаем, если очередь пустая и больше не будет заполняться
                } else {
                    continue; //ждем дальше
                }
            }

            sum += (identifiers.front()).get_descriptor()->size_of();
            identifiers.pop();
            lock.unlock(); //чтобы другие потоки могли получить доступ к своим очередям
        }
    };

    auto var_future = std::async(std::launch::async, calculate_sum, std::ref(variables), std::ref(var_sum), std::ref(cv_var), std::ref(var_queue_filled));
    auto vec_future = std::async(std::launch::async, calculate_sum, std::ref(vectors), std::ref(vec_sum), std::ref(cv_vec), std::ref(vec_queue_filled));
    auto matr_future = std::async(std::launch::async, calculate_sum, std::ref(matrixes), std::ref(matr_sum), std::ref(cv_matr), std::ref(matr_queue_filled));


    //раскидываем идентификаторы в 3 массива
    for (size_t i = 0; i < table.size(); ++i) {
        std::lock_guard<std::mutex> lock(mtx); // защита доступа к очередям
        if ((table[i].get_descriptor())->type() == "variable") {
            variables.push(table[i]);
            cv_var.notify_one(); //говорим потоку об изменении очереди
        } else if ((table[i].get_descriptor())->type() == "vector") {
            vectors.push(table[i]);
            cv_vec.notify_one();
        } else {
            matrixes.push(table[i]);
            cv_matr.notify_one();
        }
    }

    //флаги завершениz заполнения очередей
    {
        std::lock_guard<std::mutex> lock(mtx); //защита доступа к переменным queue_filled
        var_queue_filled = true;
        vec_queue_filled = true;
        matr_queue_filled = true;
    }

    cv_var.notify_all();
    cv_vec.notify_all();
    cv_matr.notify_all();

    //ждем завершения задач
    var_future.get();
    vec_future.get();
    matr_future.get();

    summary_size = var_sum + vec_sum + matr_sum;
    return summary_size;
}


/* плохая многопоточка
size_t calculate_multithreading(const Table<Identifier>& table){
    if (table.size() == 0) return 0;
    size_t summary_size = 0;

    size_t var_sum = 0;
    size_t vec_sum = 0;
    size_t matr_sum = 0;

    std::queue<Identifier> variables;
    std::queue<Identifier> vectors;
    std::queue<Identifier> matrixes;

    //вычисляем суммарный размер для каждого типа
    auto calculate_sum = [](std::queue<Identifier>& identifiers) -> size_t {
        size_t sum = 0;
        while (true) {
            if (!identifiers.empty()) {
                sum += (identifiers.front()).get_descriptor()->size_of();
                identifiers.pop();
            }
        }
        return sum;
    };

  //раскидываем идентификаторы в 3 массива
    for (size_t i = 0; i < table.size(); ++i) {
        if ((table[i].get_descriptor())->type() == "variable")
            variables.push(table[i]);
        else if ((table[i].get_descriptor())->type() == "vector")
            vectors.push(table[i]);
        else matrixes.push(table[i]);
    }

    std::thread var_thread([&]() { var_sum = calculate_sum(variables); });
    std::thread vec_thread([&]() { vec_sum = calculate_sum(vectors); });
    std::thread matr_thread([&]() { matr_sum = calculate_sum(matrixes); });

    var_thread.join();
    vec_thread.join();
    matr_thread.join();

    summary_size = var_sum + vec_sum + matr_sum;
    return summary_size;
}
*/
