#pragma once
#include <iostream>


template <class T>
class DynamicArray{
private:
    //поля
    T* m_data;
    int m_size;//количество элементов
    int m_capacity;//количество свободных ячеек
public:
    ~DynamicArray(){
        delete[] m_data;
    }
    //создание
    DynamicArray(){//конструктор по умолчанию
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }


    DynamicArray(int size){//конструктор с числом элементов
        m_size = size;
        m_capacity = size;
        m_data = new T[size];
        for (int i = 0; i < size; ++i) {
            m_data[i] = T();
        }
    }

    DynamicArray(T* items,int count){//копировать элементы
        if(items == nullptr){
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        else{
            m_size = count;			//из переданного массива
            m_capacity = count;
            m_data = new T[count];
            for (int i = 0; i < count; ++i)
            {
                m_data[i] = items[i];
            }
        }
    }

    //операции
    void Resize(int newSize){//перераспределение памяти
        if(newSize > m_capacity){
            int new_capacity = std::max(2 * m_size, newSize);
            T* new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = newSize;
    }

    T& Get(int index) const{
        return m_data[index];
    }

    void Set(int index,T value){//задать элемент по индексу
        m_data[index] = value;
    }

    int GetSize() const{//получить размер массива
        return m_size;
    }

    void Append(T val){//добавление элемента в конец массива
        Resize(m_size + 1);//выделение доп памяти при необходимости
        m_data[m_size - 1] = val;
    }

    void Prepend(T val){//добавление элемента в начало массива
        Resize(m_size + 1);//выделение доп памяти при необходимости
        for (int i = m_size - 2; i >= 0; --i)
        {
            m_data[i + 1] = m_data[i];
        }
        m_data[0] = val;
    }
    void Print(){
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_data[i] << ' ';
        }
        std::cout << std::endl;
    }
    T & operator [] (int i){//перегрузка оператора "[]" для удобства вывода
        return m_data[i];
    }

};

template <typename T>
std::ostream & operator << (std::ostream & out, DynamicArray<T> a){//перегрузка оператора << для вывода
    for(int i = 0; i < a.GetSize();++i){
        out << a[i] << " ";
    }
    return out;
}
