#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

using namespace std;

template <typename T>
class DynamicArray{
    private:
        T* data;
        size_t size;
        size_t capacity;

    public:
        DynamicArray(){
            capacity = 2;
            data = new T[capacity];
            size = 0;
        }
        ~DynamicArray(){
            delete[] data;
        }
        /* Copy constructor */
        DynamicArray(const DynamicArray& other){
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            std::copy(other.data, other.data + size, data);
        }
        /* Move constructor */
        DynamicArray(DynamicArray&& other) noexcept{
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            // set null pointers to avoid double free
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        /*Copy assignment operator*/
        DynamicArray& operator=(const DynamicArray& other){
            if (this != &other){
                delete[] data;
                capacity = other.capacity;
                size = other.size;
                data = new T[capacity];
                std::copy(other.data, other.data + size, data);
            }
            return *this;
        }
        /* Move assignment operator */
        DynamicArray& operator = (DynamicArray&& other) noexcept{
            if (this != &other){
                delete[] data;
                data = other.data;
                size = other.size;
                capacity = other.capacity;
                // set null pointers to avoid double free
                other.data = nullptr;
                other.size = 0;
                other.capacity = 0;
            }
            return *this;
        }
        /* O(1) constant time */
        inline size_t size() const{
            return this->size;
        }
        inline void resize(size_t newSize){
            if (newSize > capacity)
                reserve(newSize);
            if (newSize > size){
                for (size_t i = size; i < newSize; i++)
                    data[i] = T();
            }
            size = newSize;
        }
        inline void shrinkToFit(){
            if (size > capacity) throw std::logic_error("Size is greater than capacity");
            if (size == capacity || size == 0) return;
            capacity = size;
            T* newData = new T[capacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
        }
        /* O(1) constant time */
        inline void clear() {
            size = 0;
            capacity = 2;
            delete[] data;
            data = new T[capacity];
        }
        
        inline bool empty() const{ return size == 0; }
        /*O(1) constant time*/
        inline T& operator[](size_t index) const {
            if (index >= size) throw std::out_of_range("Index out of range");
            return data[index];
        };
        /* O(1) */
        inline const T& operator[](size_t index) const {
            if (index >= size)
                throw std::out_of_range("Index out of range");
            return data[index];
        };
        /* Resize the capacity of the array to the newCapacity
        * Takes O(n) time in the worst case
        */
        void reserve(size_t newCapacity){
            if (newCapacity > capacity){
                capacity = newCapacity;
                T* newData = new T[capacity];
                std::copy(data, data + size, newData);
                delete[] data;
                data = newData;
            }
        }

        /* O(1) amortized */
        void append(const T& value) {
            if (size >= capacity)
                reserve(capacity * 2);
            data[size++] = value;
        }
        /* O(n) worst case */
        void insert(size_t index, T value){
            if (index > size) 
                throw std::out_of_range("Index out of range");
            else if (size >= capacity){
                capacity *= 2;
                T* newData = new T[capacity];
                std::copy(data, data + index, newData);
                std::copy(data + index, data + size, newData + index + 1);
                delete[] data;
                data = newData;
                data[index] = value;
                size++;
            }
            else {
                std::move_backward(data + index, data + size, data + size + 1);
                data[index] = value;
                size++;
            }
        }
        /* O(n) worst case */
        void remove(size_t index){
            if (index >= size) 
                throw std::out_of_range("Index out of range");
            std::move(data + index + 1, data + size, data + index);
            size--;
        }
        //iterator begin and end
        const T* begin() const{ return data; }
        const T* end() const{ return data + size; }

};
#endif