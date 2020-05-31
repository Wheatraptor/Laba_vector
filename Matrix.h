#include <iostream>

template<typename T>
class Matrix
{
protected:
	T** elements;
	int row;
	int col;
public:
	Matrix();
	Matrix(const Matrix& other);
	Matrix(int row_, int col_, T** elements_);
	Matrix(int row_, int col_);
	~Matrix();

	int getrow();
	int getcol();
	T* operator[] (int index);
	const T* operator[] (int index) const;

	Matrix<T> operator+(const Matrix& other);
	Matrix<T> operator-(const Matrix& other);
	Matrix<T> operator*(const Matrix& other);

	Matrix<T>& operator=(const Matrix& other);

	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);
	template<typename T>
	friend std::istream& operator>>(std::istream& in, Matrix<T>& matrix);
};


template<typename T>
Matrix<T>::Matrix()
{
	elements = nullptr;
	col = 0;
	row = 0;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other)
{
	row = other.row;
	col = other.col;
	if (row * col == 0)
	{
		elements = nullptr;
		return;
	}
	elements = new T * [row];
	for (int i = 0; i < row; i++)
		elements[i] = new T[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			elements[i][j] = other.elements[i][j];
}

template<typename T>
Matrix<T>::Matrix(int row_, int col_, T** elements_)
{
	if ((row_ < 0) || (col_ < 0))
		throw "invalid parameters";
	row = row_;
	col = col_;
	if (row * col == 0)
	{
		elements = nullptr;
		return;
	}
	elements = new T * [row];
	for (int i = 0; i < row; i++)
		elements[i] = new T[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			elements[i][j] = elements_[i][j];
}

template<typename T>
Matrix<T>::Matrix(int row_, int col_)
{
	if ((row_ < 0) || (col_ < 0))
		throw "invalid parameters";
	row = row_;
	col = col_;
	if (row * col == 0)
	{
		elements = nullptr;
		return;
	}
	elements = new T * [row];
	for (int i = 0; i < row; i++)
		elements[i] = new T[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			elements[i][j] = 0;
}

template<typename T>
Matrix<T>::~Matrix()
{
	if (elements == nullptr)
		return;
	for (int i = 0; i < row; i++)
		delete[] elements[i];
	delete[] elements;
}

template<typename T>
int Matrix<T>::getrow()
{
	return row;
}

template<typename T>
int Matrix<T>::getcol()
{
	return col;
}

template<typename T>
T* Matrix<T>::operator[](int index)
{
	return elements[index];
}

template<typename T>
const T* Matrix<T>::operator[](int index) const
{
	return elements[index];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other)
{
	if ((col != other.col) || (row != other.row))
		throw "different matrix sizes";
	Matrix<T> result(*this);
	for (int i = 0; i < result.row; i++)
		for (int j = 0; j < result.col; j++)
			result.elements[i][j] += other.elements[i][j];
	return result;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other)
{
	if ((col != other.col) || (row != other.row))
		throw "different matrix sizes";
	Matrix<T> result(*this);
	for (int i = 0; i < result.row; i++)
		for (int j = 0; j < result.col; j++)
			result.elements[i][j] -= -other.elements[i][j];
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other)
{
	if (col != other.row)
		throw "inappropriate matrix sizes";
	Matrix<T> result(row, other.col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			for (int k = 0; k < other.col; k++)
				result.elements[i][j] += elements[i][k] * other.elements[k][j];
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
	if (&other == this)
		return *this;
	if (elements != nullptr)
	{
		for (int i = 0; i < row; i++)
			delete[] elements[i];
		delete[] elements;
	}
	row = other.row;
	col = other.col;
	if (row * col == 0)
	{
		elements = nullptr;
		return *this;
	}
	elements = new T * [row];
	for (int i = 0; i < row; i++)
		elements[i] = new T[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			elements[i][j] = other.elements[i][j];
	return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& other)
{
	if ((col != other.col) || (row != other.row))
		return false;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (elements[i][j] != other.elements[i][j])
				return false;
	return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& other)
{
	if ((col != other.col) || (row != other.row))
		return true;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (elements[i][j] != other.elements[i][j])
				return true;
	return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
{
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.col; j++)
			out << matrix.elements[i][j] << ' ';
		out << std::endl;
	}
	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix)
{
	int row, col;
	in >> row >> col;
	matrix = Matrix<T>(row, col);
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			in >> matrix.elements[i][j];
	return in;
}