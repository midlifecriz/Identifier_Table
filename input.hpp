#include <iostream>
#include <string>

#ifndef INPUT_H
#define INPUT_H

bool tryInput(size_t&);
bool tryInput(int&, int, int);
bool tryInput(unsigned int&, unsigned int, unsigned int);
bool tryInput(std::string&);
bool tryInput(std::string&, std::string&, std::string&);
bool tryInput(int&);
bool tryInput(unsigned int&);

#endif

