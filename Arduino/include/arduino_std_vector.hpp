/**
 * @brief This is an implementation of a std::vector like class. Indeed, Arduino doesn't care of STL...
 */

#ifndef ARDUINO_STD_VECTOR_HPP
#define ARDUINO_STD_VECTOR_HPP


/* IMPLEMENTATION */

namespace std {

template <typename T>
class vector {
    public:
        vector ();
        ~vector ();

        void push_back(const T& element);

        void pop_back ();

        T& operator[](int index);

        const T& operator[](int index) const;

        int size() const;

        void clear();

    private:
        T* data;
        int N_max;
        int N;
};

}


/* SPECIFICATION */

using namespace std;

template <typename T>
vector<T>::vector () {
    N_max = 0;
    N = 0;
    data = nullptr;
}

template <typename T>
vector<T>::~vector () {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

template <typename T>
void vector<T>::push_back (const T& element) {
    if (N == N_max) {
        // reserve more space
        int newN_max = N_max == 0 ? 1 : N_max * 2;

        T* newData = new T[newN_max];
        for (int i = 0; i < N; ++i) {
            newData[i] = data[i];
        }

        if (data != nullptr) {
            delete[] data;
        }
        data = newData;
        N_max = newN_max;
    }
    data [N] = element;
    N++;
}

template <typename T>
void vector<T>::pop_back () {
    if (N > 0) {
        N--;
    }
}

template <typename T>
T& vector<T>::operator[](int index) {
    return data[index];
}

template <typename T>
const T& vector<T>::operator[](int index) const {
    return data[index];
}

template <typename T>
int vector<T>::size () const {
    return N;
}

template <typename T>
void vector<T>::clear() {
    N = 0;
}

#endif  // ARDUINO_STD_VECTOR_HPP
