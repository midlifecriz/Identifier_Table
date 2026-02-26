#ifndef THREADS_HPP
#define THREADS_HPP

#include <iostream>
#include <thread>
#include <vector>
#include "table.hpp"
#include "identifier.hpp"

size_t calculate_single_threaded(const Table<Identifier>& table);
size_t calculate_multithreading(const Table<Identifier>& table);

#endif

