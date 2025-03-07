#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

class matrix
{
public:
	matrix(size_t rows, size_t cols) : m_Rows(rows), m_Cols(cols)
	{
		m_Matrix = new float[rows * cols];
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
				m_Matrix[i * cols + j] = 0.0f;
		}
	}

	matrix(const matrix& other) : m_Rows(other.m_Rows), m_Cols(other.m_Cols)
	{
		m_Matrix = new float[m_Rows * m_Cols];
		for (size_t i = 0; i < m_Rows; i++)
		{
			for (size_t j = 0; j < m_Cols; j++)
				m_Matrix[i * m_Cols + j] = other.m_Matrix[i * m_Cols + j];
		}
	}

	~matrix() { delete[] m_Matrix; }

	void operator=(const matrix& other)
	{
		m_Matrix = new float[m_Rows * m_Cols];
		for (size_t i = 0; i < m_Rows; i++)
		{
			for (size_t j = 0; j < m_Cols; j++)
				m_Matrix[i * m_Cols + j] = other.m_Matrix[i * m_Cols + j];
		}
	}

	size_t rows() const { return m_Rows; }
	size_t cols() const { return m_Cols; }

	float& operator()(size_t i, size_t j) { return m_Matrix[i * m_Cols + j]; }
	float operator()(size_t i, size_t j) const { return m_Matrix[i * m_Cols + j]; }

	matrix transpose() const
	{
		matrix t(m_Cols, m_Rows);
		for (size_t i = 0; i < m_Rows; i++)
		{
			for (size_t j = 0; j < m_Cols; j++)
				t(j, i) = m_Matrix[i * m_Cols + j];
		}

		return t;
	}

private:
	size_t m_Rows, m_Cols;
	float* m_Matrix;
};

#endif