#include "table.hpp"
#include "threads.hpp"
#include "identifier.hpp"
#include "variable_descriptor.hpp"
#include "vector_descriptor.hpp"
#include "matrix_descriptor.hpp"
#include "input.hpp"


#define MENU "1) insert\n2) set value\n3) delete\n4) print\n5) calculate sum\n6) end"
#define MSG "Repeat the input"
#define THREADS 3


typedef enum Options {
    INSERT = 1,
    INSERT_OR_ASSIGN,
    DELETE,
    PRINT,
    CALCULATE_SUM,
    END
} Options;


typedef enum DescriptorTypes {
    VARIABLE = 1,
    VECTOR,
    MATRIX
} DescriptorTypes; 


void menu();


int main() {
    try {
        menu();
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}


void menu() {
    Table<Identifier> table;
    VariableDescriptor<int> var;
    VectorDescriptor<VariableDescriptor<int>> vector;
    MatrixDescriptor<VariableDescriptor<int>> matrix;
    Identifier id;
    Table<Identifier>::Iterator it;
    Descriptor *ptr;

    std::string name;
    unsigned int option = 0;
    unsigned int el = 0;
    unsigned int action = 0;

    while (option != END) {
        std::cout << MENU << std::endl;
        while (!tryInput(option, INSERT, END)) std::cout << MSG << std::endl;
        switch (option) {
            case INSERT:
                std::cout << "Input name of the identifier:" << std::endl;
                while (!tryInput(name)) std::cout << MSG << std::endl;

                std::cout << "Choose: (1) variable (2) vector (3) matrix\n" << std::endl;
                while (!tryInput(el, VARIABLE, MATRIX)) std::cout << MSG << std::endl;

                if (el == VARIABLE) ptr = static_cast<Descriptor*>(&var);                
                else if (el == VECTOR) ptr = static_cast<Descriptor*>(&vector);
                else ptr = static_cast<Descriptor*>(&matrix);
                id.set_parameters(name, ptr);
                table.insert(id);
                break;

            case INSERT_OR_ASSIGN:
                std::cout << "Input name of the identifier:" << std::endl;
                while (!tryInput(name)) std::cout << MSG << std::endl;

                std::cout << "Choose: (1) variable (2) vector (3) matrix" << std::endl;
                while (!tryInput(el, VARIABLE, MATRIX)) std::cout << MSG << std::endl;
                
                if (el == VARIABLE) {
                    std::cin >> var;
                    ptr = static_cast<Descriptor*>(&var);
                } else if (el == VECTOR) {
                    std::cin >> vector;
                    ptr = static_cast<Descriptor*>(&vector);
                } else {
                    std::cin >> matrix;
                    ptr = static_cast<Descriptor*>(&matrix);
                }

                id.set_parameters(name, ptr);
                table.insert_or_assign(id);
                break;

            case DELETE: 
                std::cout << "Input name:" << std::endl;
                while (!tryInput(name)) std::cout << MSG << std::endl;
                id.set_parameters(name, nullptr); 
                it = table.find(id);
                table.erase(it);
                break;

            case PRINT:
                std::cout << table;
                break;

            case CALCULATE_SUM:
                std::cout << "Choose (1) single-threaded (2) multithreading" << std::endl;
                while (!tryInput(action, 1, 2)) std::cout << MSG << std::endl;
                std::cout << "Result: ";
                if (action == 1) std::cout << calculate_single_threaded(table) << std::endl;
                else std::cout << calculate_multithreading(table) << std::endl;
                break;
        }
    }
}

