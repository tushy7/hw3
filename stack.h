#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack: private std::vector<T>
{
public:
    Stack(){}
    ~Stack(){}

    bool empty() const {
        if (this -> size() == 0) {
            return true;
        }
        return false;
    }

    size_t size() const {
        return std::vector<T> ::size();
    }

    void push(const T& item) {
        std::vector<T>:: push_back(item);
    }
    
    void pop(){  // throws std::underflow_error if empty
        if (this -> empty()) {
            throw std::underflow_error("empty");
        }
        std::vector<T>:: pop_back();
    }
    const T& top() const{ // throws std::underflow_error if empty
        if (this -> empty()) {
            throw std::underflow_error("empty");
        }
        return std::vector<T>:: back();
    }

    // Add other members only if necessary
};


#endif