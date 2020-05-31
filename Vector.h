#include "Matrix.h"

template<typename T>
class TVector : public Matrix<T>
{
	using Matrix<T>::elements;
	using Matrix<T>::row;
	using Matrix<T>::col;

	void swap(int index1, int index2);
	void quick(int begin, int end);

public:
	TVector();
	TVector(const TVector& other);
	TVector(int row_, T* elements_);
	TVector(int row_);
	~TVector();

	int getSize();

	T& operator[] (int index);
	const T& operator[] (int index) const;

	TVector<T>& operator=(const TVector& other);
	TVector<T> operator+(const TVector& other);
	TVector<T> operator-(const TVector& other);
	T operator*(const TVector& other);

	bool operator==(const TVector& other);
	bool operator!=(const TVector& other);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const TVector<T>& vector);
	template<typename T>
	friend std::istream& operator>>(std::istream& in, TVector<T>& vector);

	void bubbleSort();
	void insertSort();
	void quickSort();

	int count(T value);
	TVector<int> getPos(T value);
};

template<typename T>
void TVector<T>::swap(int index1, int index2)
{
	T temp = elements[index1][0];
	elements[index1][0] = elements[index2][0];
	elements[index2][0] = temp;
}

template<typename T>
void TVector<T>::quick(int begin, int end)
{
	T comp = elements[(begin + end) / 2][0];
	int i = begin, j = end;
	do
	{
		while (elements[i][0] < comp)
			i++;
		while (elements[j][0] > comp)
			j--;
		if (i <= j)
		{
			if (elements[i][0] > elements[j][0])
				swap(i, j);
			i++;
			j--;
		}
	} while (i <= j);
	if (i < end)
		quick(i, end);
	if (j > begin)
		quick(begin, j);
}

template<typename T>
TVector<T>::TVector()
	: Matrix<T>()
{
	col = 1;
}

template<typename T>
TVector<T>::TVector(const TVector& other)
	: Matrix<T>(other.row, 1, other.elements)
{
}

template<typename T>
TVector<T>::TVector(int row_, T* elements_)
	: Matrix<T>(row_, 1)
{
	for (int i = 0; i < row; i++)
		elements[i][0] = elements_[i];
}

template<typename T>
TVector<T>::TVector(int row_)
	: Matrix<T>(row_, 1)
{
}

template<typename T>
TVector<T>::~TVector()
{
}

template<typename T>
int TVector<T>::getSize()
{
	return row;
}

template<typename T>
T& TVector<T>::operator[](int index)
{
	return elements[index][0];
}

template<typename T>
const T& TVector<T>::operator[](int index) const
{
	return elements[index][0];
}

template<typename T>
inline TVector<T>& TVector<T>::operator=(const TVector& other)
{
	if (&other == this)
		return *this;
	if (elements != nullptr)
	{
		for (int i = 0; i < row; i++)
			delete elements[i];
		delete[] elements;
	}
	row = other.row;
	if (row == 0)
	{
		elements = nullptr;
		return *this;
	}
	elements = new T * [row];
	for (int i = 0; i < row; i++)
		elements[i] = new T(other.elements[i][0]);
	return *this;
}

template<typename T>
TVector<T> TVector<T>::operator+(const TVector& other)
{
	if (row != other.row)
		throw "different vector sizes";
	TVector<T> result(*this);
	for (int i = 0; i < result.row; i++)
		result.elements[i][0] += other.elements[i][0];
	return result;
}

template<typename T>
TVector<T> TVector<T>::operator-(const TVector& other)
{
	if (row != other.row)
		throw "different vector sizes";
	TVector<T> result(*this);
	for (int i = 0; i < result.row; i++)
		result.elements[i][0] -= other.elements[i][0];
	return result;
}

template<typename T>
T TVector<T>::operator*(const TVector& other)
{
	if (row != other.row)
		throw "different vector sizes";
	T result = 0;
	for (int i = 0; i < row; i++)
		result += elements[i][0] * other.elements[i][0];
	return result;
}

template<typename T>
bool TVector<T>::operator==(const TVector& other)
{
	if (row != other.row)
		return false;
	for (int i = 0; i < row; i++)
		if (elements[i][0] != other.elements[i][0])
			return false;
	return true;
}

template<typename T>
bool TVector<T>::operator!=(const TVector& other)
{
	if (row != other.row)
		return true;
	for (int i = 0; i < row; i++)
		if (elements[i][0] != other.elements[i][0])
			return true;
	return false;
}

template<typename T>
void TVector<T>::bubbleSort()
{
	for (int i = 0; i < row; i++)
		for (int j = 1; j < row - i; j++)
			if (elements[j - 1][0] > elements[j][0])
				swap(j, j - 1);
}

template<typename T>
void TVector<T>::insertSort()
{
	for (int i = 1; i < row; i++)
	{
		T temp = elements[i][0];
		int j = i - 1;
		while ((j >= 0) && (elements[j][0] > temp))
		{
			swap(j, j + 1);
			j--;
		}
	}
}

template<typename T>
void TVector<T>::quickSort()
{
	if (row > 1)
		quick(0, row - 1);
}

template<typename T>
int TVector<T>::count(T value)
{
	int k = 0;
	for (int i = 0; i < row; i++)
		if (elements[i][0] == value)
			k++;
	return k;
}

template<typename T>
TVector<int> TVector<T>::getPos(T value)
{
	int k = 0;
	int n = count(value);
	TVector<int> result(n);
	if (n == 0)
		for (int i = 0; i < row; i++)
			if (elements[i][0] == value)
			{
				result[k] = i;
				k++;
			}
	return result;
}

/*template<typename T>
TVector<T> operator*(const Matrix<T>& left, const TVector<T>& right)
{
	if (left.col != right.row)
		throw "inappropriate vector or matrix sizes";
	TVector<T> result(left.row);
	for (int i = 0; i < left.row; i++)
		for (int j = 0; j < right.row; j++)
			result.elements[i][0] += left.elements[i][j] * right.elements[i][0];
	return result;
}*/

template<typename T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& vector)
{
	out << "[ ";
	for (int i = 0; i < vector.row; i++)
		out << vector.elements[i][0] << ' ';
	out << ']' << std::endl;
	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, TVector<T>& vector)
{
	int row;
	in >> row;
	vector = TVector<T>(row);
	for (int i = 0; i < vector.row; i++)
		in >> vector.elements[i][0];
	return in;
}
