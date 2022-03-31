#pragma once
#include "QuadMatrix.h"

template<typename T>
class AVXVectorizedQuadMatrixService
{
private:
	void sumSubmatrices(T** firstMatrix, T** secondMatrix, int lines, int columns, T** resultMatrix) {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j += 8) {
				_mm256_storeu_pd((double*)resultMatrix[i] + j, _mm256_add_pd(_mm_loadu_pd((double*)firstMatrix[i] + j), _mm256_loadu_pd((double*)secondMatrix[i] + j)));
			}
		}
	};
	void multiplySubmatrices(T** firstMatrix, int firstMatrixLines, int firstMatrixColumns, T** secondMatrix, int secondMatrixColumns, T** resultMatrix) {
		/*for (auto i = 0; i < firstMatrixLines; i++) {
			for (auto k = 0; k < firstMatrixColumns; k++) {
				for (auto j = 0; j < secondMatrixColumns; j += 8 ) {
					_mm256_storeu_pd((double*)resultMatrix[i] + j, _mm256_add_pd(_mm256_loadu_pd((const double*)resultMatrix[i] + j),
						_mm256_mul_pd(_mm256_set1_pd((const double)firstMatrix[i][k]), _mm256_loadu_pd((const double*)secondMatrix[k] + j))));
				}
			}
		}*/
		//for (int row_first_matrix = 0; row_first_matrix < firstMatrixLines; row_first_matrix++)
		//{
		//	T* result_temp_row = resultMatrix[row_first_matrix];

		//	for (int common_dimension_index = 0; common_dimension_index < firstMatrixColumns; common_dimension_index++)
		//	{
		//		T first_matrix_temp = firstMatrix[row_first_matrix][common_dimension_index];
		//		T* second_matrix_temp_row = secondMatrix[common_dimension_index];

		//		for (int column_second_matrix = 0; column_second_matrix < secondMatrixColumns; column_second_matrix += 4)
		//		{
		//			// _mm256_set1_pd : Broadcast single-precision (32-bit) floating-point value a to all elements of dst.
		//			const __m256d first_matrix_multiplier = _mm256_set1_pd(first_matrix_temp);
		//			// load the result row to accumulate the multiplication result
		//			__m256d prev_result = _mm256_load_pd(result_temp_row + column_second_matrix);

		//			// load the row from the second matrix
		//			__m256d second_matrix_row = _mm256_load_pd(second_matrix_temp_row + column_second_matrix);

		//			// multiply vectors
		//			__m256d mult_result = _mm256_mul_pd(first_matrix_multiplier, second_matrix_row);

		//			// accumulate the result
		//			__m256d sum_result = _mm256_add_pd(prev_result, mult_result);

		//			// store the result
		//			_mm256_store_pd(result_temp_row + column_second_matrix, sum_result);
		//		}
		//	}
		//}

		//_mm256_storeu_pd(resultMatrix[0], _mm256_add_pd(_mm256_loadu_pd(resultMatrix[0]), _mm256_mul_pd(_mm256_set1_pd(firstMatrix[0][0]), _mm256_loadu_pd(secondMatrix[0]))));
			for (auto i = 0; i < firstMatrixLines; i++)
			{
				for (auto k = 0; k < firstMatrixColumns; k++)
				{
					for (auto j = 0; j < secondMatrixColumns; j += 8)
					{
						_mm256_storeu_pd(resultMatrix[i] + j, _mm256_add_pd(_mm256_loadu_pd(resultMatrix[i] + j), _mm256_mul_pd(_mm256_set1_pd(firstMatrix[i][k]), _mm256_loadu_pd(secondMatrix[k] + j))));
					}
				}
			}

	};

public:
	QuadMatrix<T>* multiplyMatrices(QuadMatrix<T>& firstMatrix, QuadMatrix<T>& secondMatrix) {
		QuadMatrix<T>* resultMatrix = new QuadMatrix<T>(firstMatrix.lines, secondMatrix.columns, firstMatrix.includedLines, secondMatrix.includedColumns);
		T** __restrict temp = new T * [firstMatrix.includedLines];

		for (auto m = 0; m < firstMatrix.lines; m++) {
			for (auto n = 0; n < secondMatrix.columns; n++) {
				for (auto l = 0; l < firstMatrix.columns; l++) {
					multiplySubmatrices(firstMatrix.matrix[m][l], firstMatrix.includedLines, firstMatrix.includedColumns,
						secondMatrix.matrix[l][n], secondMatrix.includedColumns, resultMatrix->matrix[m][n]);
				}
			}
		}

		return resultMatrix;
	};
};