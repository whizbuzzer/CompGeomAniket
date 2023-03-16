/* "#pragma once" is a preprocessor directive which ensures that this file would
 * be included only once in a single compilation. This avoids multiple
 * inclusions/datatype definitions and thus avoids compilation error(s):
 */
#pragma once

#include <array>
#include <cfloat>  // For FLT_MIN
#include <iostream>
#include <type_traits>

#include "Core.h"

namespace cga {

    /* Using templates instead of inheritance for compile-time polymorphism
     * IT'S FASTER!
     */
    template<typename coordinate_type, size_t dimensions> class Vector;

    /* Forward declarations so that friend declarations could be used: */
    // Cross product:
    template<typename coordinate_type, size_t dimensions>
    Vector<coordinate_type, dimensions> crossProduct(const Vector<coordinate_type, dimensions>& v1, const Vector<coordinate_type, dimensions>& v2);

    // Dot product:
    template<typename coordinate_type, size_t dimensions>
    float dotProduct(const Vector<coordinate_type, dimensions>& v1, const Vector<coordinate_type, dimensions>& v2);


    template<typename coordinate_type, size_t dimensions>
    class Vector {
        // To ensure that only arithmetic values are stored in the vector
        static_assert(std::is_arithmetic<coordinate_type>::value == true, "Vector can store only arithmetic values");
        // To ensure that the vector is at least 2D
        static_assert(dimensions >= DIM2, "Vector should at least be 2-dimensional");

        // For storing the components:
        std::array<coordinate_type, dimensions> coords = {};

    public:
        Vector() {}  // Default constructor

        // Parametrized constructor. : means that it initializes 
        // member variable (coords array in this case)
        // before constructor body is executed
        Vector(std::array<coordinate_type, dimensions> _coords):coords(_coords) {}

        // For 2D case
        Vector(coordinate_type _x, coordinate_type _y):coords({_x, _y}) {}

        // For 3D case
        Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z):coords({_x, _y, _z}) {}

        /* Operators. Would be defined outside the class so that they can be modified as needed */
        // Indexing operator
        coordinate_type operator [] (const unsigned int) const;

        // Equality check
        bool operator == (const Vector<coordinate_type, dimensions>&) const;

        // Non-Equality check
        bool operator != (const Vector<coordinate_type, dimensions>&) const;

        // Greater than check
        bool operator > (const Vector<coordinate_type, dimensions>&) const;

        // Less than check
        bool operator < (const Vector<coordinate_type, dimensions>&) const;

        // Addition
        Vector<coordinate_type, dimensions> operator + (const Vector<coordinate_type, dimensions>&) const;

        // Subtraction
        Vector<coordinate_type, dimensions> operator - (const Vector<coordinate_type, dimensions>&) const;

        // Multiplication with scalar
        Vector<coordinate_type, dimensions> operator * (coordinate_type) const;

        // Multiplication with another vector element-wise
        Vector<coordinate_type, dimensions> operator * (const Vector<coordinate_type, dimensions>&) const;

        // Division with scalar
        Vector<coordinate_type, dimensions> operator / (coordinate_type) const;

        // Division with another vector element-wise
        Vector<coordinate_type, dimensions> operator / (const Vector<coordinate_type, dimensions>&) const;

        /* Functions. Would be defined outside the class so that they can be modified as needed */
        // Gives the size of the vector
        // size_t size();

        // Assign method for modifying an already defined vector
        void assign(unsigned int dimension, coordinate_type value);

        // Cross product:
        friend Vector crossProduct<coordinate_type, dimensions>(const Vector<coordinate_type, dimensions>&, const Vector<coordinate_type, dimensions>&);

        // Dot product:
        friend float dotProduct<coordinate_type, dimensions>(const Vector<coordinate_type, dimensions>&, const Vector<coordinate_type, dimensions>&);

        // Magnitude of a vector
        float magnitude() const;

        // Normalize a vector
        void normalize();
    };

    // Fetches value from a certain index
    template<typename coordinate_type, size_t dimensions>
    inline coordinate_type Vector<coordinate_type, dimensions>::operator [] (const unsigned int _index) const {
        if (_index >= coords.size()) {
            std::cout << "Index out of bound\n" << std::endl;
            return coordinate_type();
        }

        return coords[_index];
    }

    // Checks whether two vectors are equal
    template<typename coordinate_type, size_t dimensions>
    inline bool Vector<coordinate_type, dimensions>::operator == (const Vector<coordinate_type, dimensions>& _other) const {
        for (size_t i = 0; i < dimensions; i++) {
            if (isEqualD(coords[i], _other.coords[i]))
            return false;
        }
        return true;
    }

    // Checks whether two vectors are unequal
    template<typename coordinate_type, size_t dimensions>
    inline bool Vector<coordinate_type, dimensions>::operator != (const Vector<coordinate_type, dimensions>& _other) const {
        return !(*this == _other);  // Can implement this way because operator == has already been overloaded
    }

    // Checks whether one vector is greater than the other
    template<typename coordinate_type, size_t dimensions>
    inline bool Vector<coordinate_type, dimensions>::operator > (const Vector<coordinate_type, dimensions>& _other) const {
        for (int i = 0; i < dimensions; i++) {
            if (this->coords[i] > _other.coords[i])
                return true;
            else if (this->coords[i] < _other.coords[i])
                return false;
        }

        return false; // When all coordinates are equal
    }

    // Checks whether one vector is less than the other
    template<typename coordinate_type, size_t dimensions>
    inline bool Vector<coordinate_type, dimensions>::operator < (const Vector<coordinate_type, dimensions>& _other) const {
        // Can implement this way because operators == and > have already been overloaded
        if (*this == _other)
            return false;

        return !(*this > _other);
    }

    // Adds one vector with another
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator + (const Vector<coordinate_type, dimensions>& _other) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] + _other.coords[i];
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // Subtracts one vector from another
    template<typename coordinate_type, size_t dimensions>
    Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator - (const Vector<coordinate_type, dimensions>& _other) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] - _other.coords[i];
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // Multiplies vector with scalar
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator * (coordinate_type scale) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] * scale;
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // Multiplies one vector with another element-wise
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator * (const Vector<coordinate_type, dimensions>& _other) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] * _other.coords[i];
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // Divides vector with scalar
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator / (coordinate_type scale) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] / scale;
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // Divides one vector with another element-wise
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> Vector<coordinate_type, dimensions>::operator / (const Vector<coordinate_type, dimensions>& _other) const {
        std::array<coordinate_type, dimensions> result;

        for (size_t i = 0; i < dimensions; i++) {
            result[i] = coords[i] / _other.coords[i];
        }

        return Vector<coordinate_type, dimensions>(result);
    }

    // // Gives the size of the vector
    // template<typename coordinate_type, size_t dimensions>
    // inline size_t Vector<coordinate_type, dimensions>::size() {
    //     return coords.size();
    // }

    // Assigns given value at a given index in the vector
    template<typename coordinate_type, size_t dimensions>
    inline void Vector<coordinate_type, dimensions>::assign(unsigned int dimension, coordinate_type value) {
        if (dimension >= coords.size()) {
            std::cout << "Dimension is out of bound" << std::endl;
        }

        else if (dimension < 0) {
            dimension = coords.size() + dimension;
        }

        coords[dimension] = value;
    }

    // Cross product of two vectors
    template<typename coordinate_type, size_t dimensions>
    inline Vector<coordinate_type, dimensions> crossProduct(const Vector<coordinate_type, dimensions>& v1, const Vector<coordinate_type, dimensions>& v2) {
        if (v1.size() != v2.size()) {
            std::cout << "Vectors are not of the same size/dimension. Vectors must be of same size for dot product" << std::endl;
            return FLT_MIN;  // from <cfloat>
        }

        if (v1.size() == DIM2) {
            return (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
        }
        
        else if (v1.size() == DIM3) {
            float _x = 0, _y = 0, _z = 0;
            _x = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
            _y = -((v1[X] * v2[Z]) - (v1[Z] * v2[X]));
            _z = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);

            return Vector<coordinate_type, dimensions>(_x, _y, _z);
        }
    }

    // Dot product of two vectors
    template<typename coordinate_type, size_t dimensions>
    inline float dotProduct(const Vector<coordinate_type, dimensions>& v1, const Vector<coordinate_type, dimensions>& v2) {
        if (v1.coords.size() != v2.coords.size()) {
            std::cout << "Vectors are not of the same size/dimension. Vectors must be of same size for dot product" << std::endl;
            return FLT_MIN;  // from <cfloat>
        } else {
            // Vector<coordinate_type, dimensions> resultVector = v1 * v2;
            float result = 0;
            for (size_t i = 0; i < v1.coords.size(); i++) {
                // std::cout << "result: " << result << std::endl;
                // std::cout << "v1[i]: " << v1[i] << std::endl;
                // std::cout << "v2[i]: " << v2[i] << std::endl;
                result += v1[i] * v2[i];  // No need to use .coords since assignment operator has already been defined.
            }
            // std::cout << "result: " << result << std::endl;
            return result;
        }
    }

    // Magnitude of a vector
    template<typename coordinate_type, size_t dimensions>
    inline float Vector<coordinate_type, dimensions>::magnitude() const {
        float result_square = 0.0f;
        for (size_t i = 0; i < dimensions; i++) {
            // std::cout << "result_square: " << result_square << std::endl;
            // std::cout << "coords[i]: " << coords[i] << std::endl;
            result_square += pow(coords[i], 2.0);
        }

        return sqrt(result_square);
        // Square root is a costly operation. So it isn't uncommon for people to skip taking square root.
    }

    // Normalize a vector
    template<typename coordinate_type, size_t dimensions>
    inline void Vector<coordinate_type, dimensions>::normalize() {
        float _magnitude = magnitude();
        for (size_t i = 0; i < dimensions; i++) {
            assign(i, coords[i] / _magnitude);
        }
    }

    // Aliases for certain specialised functions
    typedef Vector<float, DIM2>     Vector2D;
    typedef Vector<float, DIM3>     Vector3D;
    
    // Defined in Vector.cpp:
    float crossProduct2D(Vector2D v1, Vector2D v2);

    Vector3D crossProduct3D(Vector3D v1, Vector3D v2);

    float scalarTripleProduct(Vector3D v1, Vector3D v2, Vector3D v3);
}

