#include <iostream>
#include <string>
#include <limits>

bool tryInput(int& dst, int left, int right) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail() || (dst < left || dst > right)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    //if (dst < left || dst > right) return false;
    return true;
}


bool tryInput(unsigned int& dst, unsigned int left, unsigned int right) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail() || (dst < left || dst > right)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    //if (dst < left || dst > right) return false;
    return true;
}


bool tryInput(size_t& dst) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}


bool tryInput(int& dst) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}


bool tryInput(unsigned int& dst) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}


bool tryInput(std::string& dst) {
    std::cin >> dst;
    if (std::cin.eof()) throw std::runtime_error("END OF FILE");
    else if (std::cin.bad()) throw std::runtime_error("ERROR");
    return true;
}


bool tryInput(std::string& dst, std::string& parameter1, std::string& parameter2) {
    std::cin >> dst;
    if (std::cin.eof()) {
        throw std::runtime_error("END OF FILE");
    } else if (std::cin.bad()) {
        throw std::runtime_error("ERROR");
    } else if (std::cin.fail() || (dst != parameter1 && dst != parameter2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}
