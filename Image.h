#pragma once
#pragma once
#include <iostream>
#include <algorithm>
#include <limits>
#include <random>
#include<typeinfo>
using namespace std;
template <typename T>

class Image
{
private:
    size_t _width;    // ������ �����������
    size_t _height;   // ������ �����������
    T** data;

   
public:

    Image(size_t width, size_t height, bool random_fill) : _width(width), _height(height)
    {

        if (random_fill)
        {

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, 50);

            data = new T * [_height];
            for (size_t i = 0; i < _height; ++i)
            {
                data[i] = new T[_width];
                for (size_t j = 0; j < _width; j++)
                {
                    data[i][j] = static_cast<T>(dis(gen));
                }
            }
        }
        else
        {
            data = new T * [_height];
            for (size_t i = 0; i < _height; ++i)
            {
                data[i] = new T[_width];
                for (size_t j = 0; j < _width; j++)
                {
                    data[i][j] = 0;
                }
            }
        }
    }

    Image(size_t width, size_t height) : _width(width), _height(height)
    {
        data = new T * [_height];
        for (size_t i = 0; i < _height; ++i) {
            data[i] = new T[_width];
        }
    }

    Image& operator=(const Image& other)
    {
        if (this == &other)
        {
            return *this;
        }

        for (size_t i = 0; i < _height; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;

        _width = other._width;
        _height = other._height;

        data = new T * [_height];
        for (size_t i = 0; i < _height; ++i) 
        {
            data[i] = new T[_width];
        }

        for (size_t i = 0; i < _height; ++i)
        {
            std::copy(other.data[i], other.data[i] + _width, data[i]);
        }

        return *this;
    }

    /// ����������� �����������
    Image(const Image& other) : _width(other._width), _height(other._height)
    {
        data = new T * [_width];
        for (size_t i = 0; i < _width; i++) {
            data[i] = new T[_height];
            for (size_t j = 0; j < _height; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // ����������
    ~Image() {
        for (size_t i = 0; i < _height; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    size_t Get_width() const
    {
        return _width;
    }

    size_t  Get_height() const
    {
        return _height;
    }

    // �������� () ��� ������� � ���������
    T& operator()(size_t row, size_t col)
    {
        if ((row >= _width || col >= _height) && (row < 0 || col < 0))
        {
            throw std::out_of_range("������ ��� ���������");
        }
        return data[row][col];
    }

    const T operator()(size_t row, size_t col) const
    {
        if ((row >= _width || col >= _height) && (row < 0 || col < 0))
        {
            throw std::out_of_range("������ ��� ���������");
        }
        return data[row][col];
    }

    // ��������� ��������� � �������� ��� ������ �����
    template <typename T>
    Image<T>& operator*(const Image<T>& other) {
        if (_width != other._width || _height != other._height)
        {
            Image<T>* result = new Image<T>(other._width, other._height);

            for (size_t i = 0; i < other._height; ++i)
            {
                for (size_t j = 0; j < other._width; ++j)
                {
                    if (i >= this->_height || j >= this->_width)
                    {
                        (*result)(i, j) = other(i, j);
                    }
                    else
                    {
                        (*result)(i, j) = (*this)(i, j) + other(i, j);
                    }
                }
            }

            return *result;
        }

        Image<T>* result = new Image<T>(_width, _height);
        for (size_t i = 0; i < _height; ++i)
        {
            for (size_t j = 0; j < _width; ++j)
            {
                (*result)(i, j) = (*this)(i, j) * other(i, j);  // ������������ ���������
            }
        }
        return *result;
    }

  const  Image<T>& operator!()
    {
        Image<T>* result = new Image<T>(_width, _height);
        for (size_t i = 0; i < _height; ++i)
        {
            for (size_t j = 0; j < _width; ++j)
            {
                (*result)(i, j) = -((*this)(i, j));
            }
        }
        return *result;
    }

    template <typename T>
    Image<T>& operator+(const Image<T>& other) const
    {
        if (_width != other._width || _height != other._height)
        {
            Image<T>* result = new Image<T>(other._width, other._height);

            for (size_t i=0 ; i < other._height; ++i)
            {
                for (size_t j=0 ; j < other._width; ++j)
                {
                    if (i >= this->_height || j >= this->_width)
                    {
                        (*result)(i, j) = other(i, j);
                    }
                    else
                    {
                        (*result)(i, j) = (*this)(i, j) + other(i, j);
                    }
                }
            }

            return *result;
        }

        Image<T>* result = new Image<T>(_width, _height);
        for (size_t i = 0; i < _height; ++i) {
            for (size_t j = 0; j < _width; ++j) {
                (*result)(i, j) = (*this)(i, j) + other(i, j);  // ������������ ��������
            }
        }
        return *result;
    }

  Image<bool>& operator*(const Image<bool>& other)  const {
        if (_width != other._width || _height != other._height)
        {
            throw runtime_error("Dimensions do not match");
        }

        Image<bool>* result = new Image<bool>(_width, _height);
        for (size_t i = 0; i < _height; ++i)
        {
            for (size_t j = 0; j < _width; ++j)
            {
                (*result)(i, j) = (*this)(i, j) && other(i, j);  // ������������ �
            }
        }
        return *result;
    }

   Image<bool>& operator+(const Image<bool>& other)  const
    {
        if (_width != other._width || _height != other._height)
        {
            throw runtime_error("Dimensions do not match");
        }

        Image<bool>* result = new Image<bool>(_width, _height);
        for (size_t i = 0; i < _height; ++i)
        {
            for (size_t j = 0; j < _width; ++j)
            {
                (*result)(i, j) = (*this)(i, j) || other(i, j);  // ������������ ���
            }
        }
        return *result;
    }

    // ��������� ��������� � �������� ����������� �� ���������
   Image<T>& operator*(T value) const {
        Image<T>* result = new Image<T>(_width, _height);
        for (size_t i = 0; i < _height; ++i) {
            for (size_t j = 0; j < _width; ++j)
            {
                auto tmp = data[i][j] * value;
                if (tmp > std::numeric_limits<T>::max())
                {
                    (*result)(i, j) = std::numeric_limits<T>::max();
                }
                if (tmp < std::numeric_limits<T>::min())
                {
                    (*result)(i, j) = std::numeric_limits<T>::min();
                }
                else
                (*result)(i, j) = data[i][j] * value;  // ��������� �� ���������
            }
        }
        return *result;
    }

   Image<T>& operator+(T value) const {
        Image<T>* result = new Image<T>(_width, _height);
        for (size_t i = 0; i < _height; ++i)
        {
            for (size_t j = 0; j < _width; ++j)
            {
                auto tmp = data[i][j] + value;
                if (tmp > std::numeric_limits<T>::max())
                {
                    (*result)(i, j) = std::numeric_limits<T>::max();
                }
                if (tmp < std::numeric_limits<T>::min())
                {
                    (*result)(i, j) = std::numeric_limits<T>::min();
                }
                else
                (*result)(i, j) = data[i][j] + value;

               
            }
        }
        return *result;
    }

   // ���������� ������������ ���������� �����������
   double getFillRatio() const 
   {
       double sum = 0;
       for (size_t i = 0; i < _height; ++i)
       {
           for (size_t j = 0; j < _width; ++j)
           {
               sum += (*this)(i,j);
           }
       }

       double totalPixels = _width * _height;

       double sizepix = (totalPixels * std::numeric_limits<T>::max());

       double fillRatio = sum / (totalPixels * std::numeric_limits<T>::max());

       return fillRatio;
   }


    //�����
    T PixelImage(const Image img)
    {
        for (size_t i = 0; i < img.Get_height(); ++i) {
            for (size_t j = 0; j < img.Get_width(); ++j)
            {
                if (img(i, j) != 5)
                {
                    cout << ' ';
                }
                else
                {
                    cout << '7';
                }
            }
            cout << endl;
        }
        return 1;
    }
};


template <typename T>
ostream& operator<<(ostream& stream, const Image<T> img)
{
    for (size_t i = 0; i < img.Get_height(); ++i)
    {
        for (size_t j = 0; j < img.Get_width(); ++j)
        {
            stream << img(i, j) << ' ';
        }
        stream << '\n';
    }
    return stream;
};
