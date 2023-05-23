/**
 * @brief This is an implementation of a std::vector like class. Indeed, Arduino doesn't care of STL...
 */

#ifndef ARDUINO_STD_VECTOR_HPP
#define ARDUINO_STD_VECTOR_HPP

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

#endif  // ARDUINO_STD_VECTOR_HPP
