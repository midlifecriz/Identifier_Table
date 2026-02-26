#include "identifier.hpp"


#define MAX_LENGTH 8


Identifier::Identifier() : name("noname"), descriptor(nullptr) {;}


Identifier::Identifier(std::string& x) {
    if (x.size() > MAX_LENGTH) throw std::invalid_argument("NAME IS TOO LONG");
    name = x;
    descriptor = nullptr;
}


Identifier::Identifier(std::string& x, Descriptor* ptr) {
    if (x.size() > MAX_LENGTH) throw std::invalid_argument("NAME IS TOO LONG");
    name = x;
    descriptor = ptr;
}


void Identifier::set_parameters(std::string& x, Descriptor* desc) {
    if (x.size() > MAX_LENGTH) throw std::invalid_argument("NAME IS TOO LONG"); 
    name = x; 
    descriptor = desc;
}


size_t Identifier::size_of() const { return descriptor->size_of(); }


std::string Identifier::get_name() const { return name; }


Descriptor* Identifier::get_descriptor() const { return descriptor; }


void Identifier::set_name(std::string& x) { 
    if (x.size() > MAX_LENGTH) throw std::invalid_argument("NAME IS TOO LONG");
    name = x;
}


void Identifier::set_descriptor(Descriptor* x) { descriptor = x; }


Identifier& Identifier::operator =(Identifier& src) {
    name = src.name;
    descriptor = src.descriptor;
    return *this;
}


bool Identifier::operator >(Identifier& x) const { return name > x.name; }


bool Identifier::operator ==(const Identifier& x) const { return (name == x.name && typeid(descriptor) == typeid(x.descriptor));}


std::ostream& operator <<(std::ostream& os, const Identifier& x) {
    os << x.name << ": ";
    if (x.descriptor) (x.descriptor)->print();
    return os;    
}


std::istream& operator >>(std::istream& is, Identifier& x) {
    (x.descriptor)->input();
    return is;
}

