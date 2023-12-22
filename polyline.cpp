#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>
#include <stdlib.h>
#include <conio.h>
#include <complex>

const double PI = 3.141592653589793238463;

using namespace std;

namespace polyline {

	template <typename T>
	struct Point {
		T _x;
		T _y;

		Point() : _x(0), _y(0) {}
		Point(T x, T y) : _x(x), _y(y) {}
		Point(const Point<T>& a) : _x(a._x), _y(a._y) {}

		T get_x() const { return _x; }
		T get_y() const { return _y; }

		void operator=(const Point<T>& a) {
			_x = a._x;
			_y = a._y;
		}

		bool operator==(const Point<T> a) {
			if ((_x == a._x) && (_y == a._y))
				return true;
			else
				return false;
		}

		void print(const Point<T>& a) {
			cout << "(" << _x << "; " << _y << ")" << endl;
		}
	};

	template<typename U>
	double len(Point<complex<U>>& a, Point<complex<U>>& b) {
		return fabs(sqrt(pow(a.get_x().real() - b.get_x().real(), 2) + pow(a.get_y().real() - b.get_y().real(), 2)));
	}
	template<typename T>
	double len(Point<T>& a, Point<T>& b) {
		return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
	}

	template <typename T>
	ostream& operator<<(ostream& os, const Point<T>& a) {
		os << a._x << " " << a._y << endl;
		return os;
	}

	template <typename T>
	class Polyline {
	private:
		Point<T>* _data;
		size_t _size;
		const double epsilon = 0.0001;
	public:
		Polyline() {
			_data = nullptr;
			_size = 0;
		}

		Polyline(const Point<T>& a) {
			_data = new Point<T>;
			_data[0] = Point<T>(a._x, a._y);
			_size = 1;
		}

		Polyline(size_t size) {
			_data = new Point<T>[size];
			for (int i = 0; i < size; ++i)
				_data[i] = Point<T>(_data[i]);
			_size = size;
		}

		Polyline(int count, T x1, T y1, T x2, T y2) {
			_data = new Point<T>[count];
			for (int i = 0; i < count; ++i)
				_data[i] = new Point<T>(random(x1, x2), random(y1, y2));
			_size = count;
		}

		void swap(Polyline<T>& a) noexcept {
			std::swap(_data, a._data);
			std::swap(_size, a._size);
		}

		Polyline operator=(Polyline<T>& a) {
			swap(a);
			return *this;
		}

		bool operator==(Polyline<T>& a) const {
			if (_size != a._size)
				return false;
			for (int i = 0; i < _size; ++i) {
				if (fabs(_data[i] - a[i]) > epsilon)
					return false;
			}
			return true;
		}

		bool operator!=(Polyline<T>& a) const {
			return !(_data == a);
		}

		Point<T>& operator[](size_t index) const {
			if (index >= _size)
				throw("Index is out of range");
			return _data[index];
		}

		Polyline<T> operator+(Polyline<T>& a) {
			Polyline<T> new_line(_data[0]);
			for (int i = 1; i < _size; ++i)
				new_line.push_back(_data[i]);
			for (int i = 0; i < _size; ++i)
				new_line.push_back(a._data[i]);
			return new_line;
		}

		void push_back(Point<T>& point) {
			auto temp = new Point<T>[_size + 1];
			for (int i = 0; i < _size; ++i)
				temp[i] = _data[i];
			temp[_size] = point;
				delete[] _data;
			_data = temp;
			_size++;
		}

		void push_front(Point<T>& point) {
			auto temp = new Point<T>[_size + 1];
			for (int i = 1; i < _size + 1; ++i)
				temp[i] = _data[i - 1];
			temp[0] = point;
				delete[] _data;
			_data = temp;
			_size++;
		}

		Polyline(Polyline<T>& other) {
			_data = new Point<T>[other._size];
			for (int i = 0; i < other._size; ++i)
				_data[i] = other._data[i];
			_size = other._size;
		}

		float len() {
			float length = 0;
			for (int i = 1; i<_size; ++i)
				length += (_data[i]).len(_data[i - 1]);
			return length;
		}

		size_t get_size() {
			return _size;
		}

		~Polyline() {
			delete[] _data;
			_data = nullptr;
			_size = 0;
		}
	};


	template<typename T>
	ostream& operator<<(ostream& os, Polyline<T>& line)
	{
		for (int i = 0; i < line.get_size(); ++i)
		{
			os << line[i] << endl;
		}
		return os;
	}

	template<typename T>
	Polyline<T>& operator+(Point<T>& point, Polyline<T>& line) {
		line.push_front(point);
		return line;
	}

	template<typename T>
	Polyline<T>& operator+(Polyline<T>& line, Point<T>& point) {
		line.push_back(point);
		return line;
	}

	template<typename T>
	bool operator==(Polyline<complex<T>>& line1, Polyline<complex<T>>& line2) {
		if (line1.get_size() != line2.get_size())
			return false;
		for (int i = 0; i < line1.get_size(); ++i) {
			if (line1[i].real() != line2[i].real() || line1[i].imag() != line2[i].imag())
				return false;
		}
		return true;
	}

	template<typename T>
	bool operator!=(Polyline<complex<T>>& line1, Polyline<complex<T>>& line2) {
		return !(line1 == line2);
	}

	template <typename T>
	T random(T a, T b)
	{
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(a, b);
		T x = distribution(generator);
		return x;
	}

	template<typename T>
	Polyline<T> trapezoid(T a, T b, T h)
	{
		if (a < 0 or b < 0 or h < 0)
		{
			throw std::invalid_argument("Dimensions cannot be negative");
		}
		else
		{
			Point<T> f(0, 0);
			Point<T> s(a, 0);
			Point<T> t(b, h);
			Point<T> fo(0, h);
			Polyline<T> trapezoid;
			trapezoid.push_back(f);
			trapezoid.push_back(s);
			trapezoid.push_back(t);
			trapezoid.push_back(fo);
			return trapezoid;
		}
	}

}