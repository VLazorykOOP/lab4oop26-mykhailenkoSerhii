#include "Task1.h"
#include <iostream>
#include <cmath>
using namespace std;

class VectorFloat {
public:
    enum ErrorCode {
        OK = 0,
        OUT_OF_MEMORY = 1,
        OUT_OF_BOUNDS = 2
    };

private:
    float* data;
    size_t size;
    int codeError;

    static int objectCount;

public:
    VectorFloat() : size(1), codeError(OK)
    {
        data = new(nothrow) float[size];
        if (!data) {
            codeError = OUT_OF_MEMORY;
            size = 0;
        } else {
            data[0] = 0.0f;
        }
        objectCount++;
    }

    VectorFloat(size_t n)
    {
        codeError = OK;

        if (n == 0)
            size = 1;
        else size = n;

        data = new(nothrow) float[size];
        if (!data) {
            codeError = OUT_OF_MEMORY;
            size = 0;
        } else {
            for (size_t i = 0; i < size; ++i) data[i] = 0.0f;
        }
        objectCount++;
    }

    VectorFloat(size_t n, float initValue) : size(n), codeError(OK) {
        if (n == 0) { size = 1; }
        data = new(nothrow) float[size];
        if (!data) {
            codeError = OUT_OF_MEMORY;
            size = 0;
        } else {
            for (size_t i = 0; i < size; ++i) data[i] = initValue;
        }
        objectCount++;
    }

    VectorFloat(const VectorFloat& other) : size(other.size), codeError(other.codeError) {
        data = new(nothrow) float[size];
        if (!data) {
            codeError = OUT_OF_MEMORY;
            size = 0;
        } else {
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }
        objectCount++;
    }

    ~VectorFloat() {
        delete[] data;
        objectCount--;
    }

    VectorFloat& operator++()
    {
        for (size_t i = 0; i < size; ++i) data[i] += 1.0f;
        return *this;
    }
    VectorFloat operator++(int)
    {
        VectorFloat temp(*this);
        ++(*this);
        return temp;
    }
    VectorFloat& operator--()
    {
        for (size_t i = 0; i < size; ++i) data[i] -= 1.0f;
        return *this;
    }
    VectorFloat operator--(int)
    {
        VectorFloat temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const
    {
        return size != 0;
    }

    VectorFloat operator-() const
    {
        VectorFloat result(size);
        for (size_t i = 0; i < size; ++i) result.data[i] = -this->data[i];
        return result;
    }

    VectorFloat& operator=(const VectorFloat& other)
    {
        if (this != &other) {
            delete[] data;
            size = other.size;
            codeError = other.codeError;
            data = new(nothrow) float[size];
            if (data) {
                for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
            } else {
                codeError = OUT_OF_MEMORY;
                size = 0;
            }
        }
        return *this;
    }

    VectorFloat& operator+=(const VectorFloat& other)
    {
        size_t minSize = (size < other.size) ? size : other.size;
        for (size_t i = 0; i < minSize; ++i) data[i] += other.data[i];
        return *this;
    }
    VectorFloat& operator-=(const VectorFloat& other)
    {
        size_t minSize = (size < other.size) ? size : other.size;
        for (size_t i = 0; i < minSize; ++i) data[i] -= other.data[i];
        return *this;
    }
    VectorFloat& operator*=(float val)
    {
        for (size_t i = 0; i < size; ++i) data[i] *= val;
        return *this;
    }
    VectorFloat& operator/=(float val)
    {
        if (val != 0) {
            for (size_t i = 0; i < size; ++i) data[i] /= val;
        }
        return *this;
    }
    VectorFloat& operator%=(int val) {
        if (val != 0) {
            for (size_t i = 0; i < size; ++i) data[i] = std::fmod(data[i], static_cast<float>(val));
        }
        return *this;
    }

    VectorFloat operator+(const VectorFloat& other) const {
        VectorFloat result(*this);
        result += other;
        return result;
    }

    VectorFloat operator-(const VectorFloat& other) const {
        VectorFloat result(*this);
        result -= other;
        return result;
    }

    VectorFloat operator*(float val) const
    {
        VectorFloat result(*this);
        result *= val;
        return result;
    }

    VectorFloat operator/(float val) const
    {
        VectorFloat result(*this);
        result /= val;
        return result;
    }

    VectorFloat operator%(int val) const
    {
        VectorFloat result(*this);
        result %= val;
        return result;
    }

    friend ostream& operator<<(ostream& os, const VectorFloat& vec)
    {
        os << "[ ";
        for (size_t i = 0; i < vec.size; ++i) os << vec.data[i] << " ";
        os << "] (Err: " << vec.codeError << ")";
        return os;
    }

    friend istream& operator>>(istream& is, VectorFloat& vec) {
        cout << "Input " << vec.size << " elements: ";
        for (size_t i = 0; i < vec.size; ++i) {
            is >> vec.data[i];
        }
        return is;
    }

    bool operator==(const VectorFloat& other) const
    {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const VectorFloat& other) const
    {
        return !(*this == other);
    }

    float& operator[](size_t index) {
        if (index >= size) {
            codeError = OUT_OF_BOUNDS;
            return data[size - 1];
        }
        codeError = OK;
        return data[index];
    }

    void* operator new(size_t sz)
    {
        return ::operator new(sz);
    }

    void operator delete(void* ptr)
    {
        ::operator delete(ptr);
    }

    void* operator new[](size_t sz)
    {
        return ::operator new[](sz);
    }

    void operator delete[](void* ptr)
    {
        ::operator delete[](ptr);
    }

    float operator()() const
    {
        float sum = 0.0f;
        for (size_t i = 0; i < size; ++i) sum += data[i];
        return sum;
    }

    bool operator>(const VectorFloat& other) const
    {
        return this->operator()() > other.operator()();
    }

    bool operator>=(const VectorFloat& other) const
    {
        return this->operator()() >= other.operator()();
    }

    bool operator<(const VectorFloat& other) const
    {
        return this->operator()() < other.operator()();
    }

    bool operator<=(const VectorFloat& other) const
    {
        return this->operator()() <= other.operator()();
    }

    int getError() const
    {
        return codeError;
    }
    static int getObjectCount()
    {
        return objectCount;
    }
};

int VectorFloat::objectCount = 0;

void task1() {
    cout << "CONSTRUCTORS" << endl;
    VectorFloat v1;
    VectorFloat v2(3);
    VectorFloat v3(3, 2.5f);

    cout << "PARAMETERLESS: " << v1 << endl;
    cout << "PARAMETER - SIZE 3: " << v2 << endl;
    cout << "PARAMETER - SIZE 3, INIT VALUE 2.5F: " << v3 << endl;
    cout << "AMOUNT OF OBJECTS: " << VectorFloat::getObjectCount() << "\n" << endl;

    cout << "UNARY OPERATORS" << endl;
    cout << "++ : " << v3++ << endl;
    cout << "-- : " << --v3 << endl;
    cout << "- : " << -v3 << endl;
    cout << "! : " << (!v3 ? "True" : "False") << "\n" << endl;

    cout << "INDEXATION [] AND ERROR PROCESSING" << endl;
    v3[0] = 10.0f;
    cout << "AFTER [0] = 10f: " << v3 << endl;
    cout << "OUT OF BOUNDS [10]: ";
    v3[10] = 99.9f;
    cout << "\nOBJECT : " << v3 << " ([ERROR]: " << v3.getError() << ")\n" << endl;

    cout << "BINARY AND ARITHMETIC" << endl;
    VectorFloat v4(3, 5.0f);
    cout << "BASE - SIZE 3, INIT VALUE 5: " << v4 << endl;
    cout << "CURRENT + PREVIOUS: " << (v4 + v3) << endl;
    cout << "CURRENT * 2: " << (v4 * 2.0f) << endl;
    cout << "CURRENT % 3 (remainder): " << (v4 % 3) << endl;

    v4 += v3;
    cout << "CURRENT += PREVIOUS: " << v4 << "\n" << endl;

    cout << "COMPARISONS" << endl;
    cout << "CURRENT > PREVIOUS: " << (v4 > v3 ? "True" : "False") << endl;
    cout << "CURRENT == PREVIOUS: " << (v4 == v3 ? "True" : "False") << endl;
    cout << "CURRENT != PREVIOUS: " << (v4 != v3 ? "True" : "False") << "\n" << endl;

    cout << "() CALL" << endl;
    cout << "PREVIOUS() : " << v3() << "\n" << endl;

    cout << "\nFINAL OBJECT COUNT: " << VectorFloat::getObjectCount() << endl;
}
