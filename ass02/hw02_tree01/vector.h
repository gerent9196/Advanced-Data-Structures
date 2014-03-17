#pragma once

template <typename T>
class vector {
public:
  vector();
  ~vector();
  void push_back(T value);
  void pop_back();
  size_t size();
  T get(int index);
  void set(int index, T value);
  void clear();
private:
  size_t m_size;
  size_t m_cap;
  T * m_data;
};

template <typename T>
vector<T>::vector(){
  m_size = 0;
  m_cap = 8;
  m_data = new T[m_cap];
}
 
template <typename T>
vector<T>::~vector(){
  delete [] m_data;
}

template <typename T>
void vector<T>::clear(){
  delete [] m_data;
  m_size = 0;
  m_cap = 8;
  m_data = new T[m_cap];
}


template <typename T>
void vector<T>::push_back(T value){
  if(m_size == m_cap){
    int cap_new = 2 * m_cap;
    T * new_data = new T[cap_new];
    for(int i = 0; i < m_size; ++i){
      new_data[i] = m_data[i];
    }
    delete [] m_data;
    m_data = new_data;
    m_cap = cap_new;
  }
  m_data[m_size] = value;
  ++m_size;
}

template <typename T>
void vector<T>::set(int index, T value){
  m_data[index] = value;
}

template <typename T>
void vector<T>::pop_back(){
  --m_size;
  if(m_size == m_cap / 2 && m_cap > 8){
    int cap_new = m_cap / 2;
    T * new_data = new T[cap_new];
    for(int i = 0; i < m_size; ++i){
      new_data[i] = m_data[i];
    }
    delete [] m_data;
    m_data = new_data;
    m_cap = cap_new;
  }
}
 
template <typename T>
size_t vector<T>::size(){
  return m_size;
}
 
template <typename T>
T vector<T>::get(int index){
  return m_data[index];
}
