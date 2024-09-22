#ifndef LAB_1_STACK_H
#define LAB_1_STACK_H

#include <iostream>
#include <initializer_list>

template <typename T>
class Stack{
private:
    T *elements;
    int stack_size, stack_capacity;

    void resize_up(){
        T* new_elements = new T[this->stack_capacity * 2];
        for (int i = 0; i < this->stack_size; ++i)
            new_elements[i] = this->elements[i];
        this->stack_capacity *= 2;
        delete[] this->elements;
        this->elements = new_elements;
    }

    void resize_down(){
        T* new_elements = new T[this->stack_capacity / 2];
        for (int i = 0; i < this->stack_size; ++i)
            new_elements[i] = this->elements[i];
        this->stack_capacity /= 2;
        delete[] this->elements;
        this->elements = new_elements;
    }

public:
    Stack(){
        this->elements = new T[10];
        this->stack_size = 0;
        this->stack_capacity = 10;
    }

    Stack(const Stack& other){
        this->elements = new T[other.stack_capacity];
        this->stack_size = other.stack_size;
        this->stack_capacity = other.stack_capacity;
        for (int i = 0; i < this->stack_size; ++i)
            this->elements[i] = other.elements[i];
    }

    Stack(Stack&& other) noexcept {
        this->elements = new T[other.stack_capacity];
        this->stack_size = other.stack_size;
        this->stack_capacity = other.stack_capacity;
        for (int i = 0; i < this->stack_size; ++i)
            this->elements[i] = other.elements[i];
    }

    Stack(std::initializer_list<T>&& input){
        this->stack_size = input.size();
        this->stack_capacity = this->stack_size + (10 - this->stack_size % 10);
        this->elements = new T[this->stack_capacity];
        const T current = input.begin();
        for (int i = 0; i < this->stack_size; ++i)
            this->elements[i] = *current++;
    }

    Stack& operator=(const Stack& other){
        this->elements = new T[other.stack_capacity];
        this->stack_size = other.stack_size;
        this->stack_capacity = other.stack_capacity;
        for (int i = 0; i < this->stack_size; ++i)
            this->elements[i] = other.elements[i];
        return *this;
    }

    Stack& operator=(Stack&& other) noexcept {
        this->elements = new T[other.stack_capacity];
        this->stack_size = other.stack_size;
        this->stack_capacity = other.stack_capacity;
        for (int i = 0; i < this->stack_size; ++i)
            this->elements[i] = other.elements[i];
        return *this;
    }

    void push(T data){
        if (this->stack_capacity - this->stack_size <= 1)
            this->resize_up();
        this->elements[this->stack_size++] = data;
    }

    T pop(){
        if (this->stack_size == 0)
            return nullptr;
        if (this->stack_size < this->stack_capacity / 2)
            this->resize_down();
        this->stack_size--;
        return this->elements[this->stack_size];
    }

    T check_pop() const{
        if (this->stack_size == 0)
            return nullptr;
        return this->elements[this->stack_size - 1];
    }

    Stack& operator << (T data){
        this->push(data);
        return *this;
    }

    Stack& operator >> (T& data){
        data = this->pop();
        return *this;
    }

    friend std::ostream& operator << (std::ostream& out, Stack<T>& stack);

    bool empty() const{
        return this->stack_size == 0;
    }

    int size() const{
        return this->stack_size;
    }

    int capacity() const{
        return this->stack_capacity;
    }

    void clear(){
        while (!this->empty())
            this->pop();
    }

    bool operator==(Stack& other) const{
        if (this->size() != other.size())
            return false;
        for (int i = 0; i < this->size(); ++i)
            if (this->elements[i] != other.elements[i])
                return false;
        return true;
    }

    bool operator!=(Stack& other) const{
        return (*this == other) == false;
    }

    void top(T data){
        this->elements[this->size() - 1] = data;
    }

    void swap(T& data){
        T t = data;
        data = this->elements[this->size() - 1];
        this->elements[this->size() - 1] = t;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, Stack<T> &stack){
    for (int i = stack.size() - 1; i >= 0; --i)
        out << stack.elements[i] << std::endl;
    return out;
}

#endif //LAB_1_STACK_H
