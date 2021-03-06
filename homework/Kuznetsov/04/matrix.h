#include <iostream>


class Matrix
{
public:
	struct Proxy {
		size_t len;
		int* row;
		Proxy(int row[], size_t len) : row(row), len(len) {};
		const int& operator[](size_t i) const{
			if (i >= len)
				throw std::out_of_range("index out of range");
			return row[i];
		}
		int& operator[](size_t i)  {
			if (i >= len)
				throw std::out_of_range("index out of range");
			return row[i];
		}
	};
	Matrix(size_t r, size_t c): rowCount(r), columnCount(c) {
		matrix = new int*[rowCount];
		for (size_t i = 0; i < rowCount; i++) {
			matrix[i] = new int[columnCount];
			for (size_t j = 0; j < columnCount; j++)
				matrix[i][j] = 0;
		}
	}
	~Matrix(){
		for (size_t i = 0; i < rowCount; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	size_t getRows() const{
		return columnCount;
	}
	size_t getColumns() const{
		return rowCount;
	}
	Proxy operator[](size_t i){
		if (i >= rowCount)
			throw std::out_of_range("index out of range");
		return Proxy(matrix[i], columnCount);
	}
	const Proxy operator[](size_t i) const{
		if (i >= rowCount)
			throw std::out_of_range("index out of range");
		return Proxy(matrix[i], columnCount);
	}
	
	Matrix& operator*=(int number) {
		for (size_t i = 0; i < rowCount; i++) {
			for (size_t j = 0; j < columnCount; j++) {
				matrix[i][j] = matrix[i][j] * number;
			}
		}
		return *this;
	}
	bool operator==(const Matrix& other) const{
		if (other.rowCount != rowCount || other.columnCount != columnCount)
			return false;

		for (size_t i = 0; i < rowCount; i++) {
			for (size_t j = 0; j < columnCount; j++) {
				if (matrix[i][j] != other.matrix[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& other) const{
		return !(*this == other);
	}

private:
	
	int** matrix;
	size_t rowCount;
	size_t columnCount;
};
