#ifndef MATRIX_H
#define MATRIX_H


#include <array>
#include <stdexcept>


template<size_t row_num, size_t col_num>
class Matrix{
	
	public:
		
		std::array<std::array<double, col_num>, row_num> mat_ent;

		
		explicit Matrix(std::array<std::array<double, col_num>, row_num> arr){
			mat_ent = arr;
		}


		void print(){

			// Add documentation

			for(int i = 0; i < row_num; i++){

				for(int j = 0; j < col_num; j++){
			
					std::cout << this -> mat_ent[i][j] << "\t";
				}

			std::cout << "\n";

			}
		}


		/*
		Operators to overload:
		- Addition +, done
		- Multiplication *, done
		- Subtraction -, done
		- Element access [], done
		*/


		template<size_t T1, size_t T2, size_t T3>
		friend Matrix<T1, T3> operator * (Matrix<T1, T2> const &mat1, Matrix<T2, T3> const &mat2);


		Matrix<row_num, col_num> operator + (Matrix<row_num, col_num> &mat){

			std::array<std::array<double, col_num>, row_num> arr;

			arr.fill({});

			Matrix<row_num, col_num> result_mat(arr);

			for(int i = 0; i < row_num; i++){

				for(int j = 0; j < col_num; j++){
			
					// I have doing the declaration wrong. It may be working if I rewrite it using arrays.
					result_mat.mat_ent[i][j] = mat.mat_ent[i][j] + this -> mat_ent[i][j];

				}

			}

			return result_mat;

		}


		Matrix<row_num, col_num> operator - (Matrix<row_num, col_num> const &mat){

			std::array<std::array<double, col_num>, row_num> arr;

			arr.fill({});

			Matrix<row_num, col_num> result_mat(arr);

			for(int i = 0; i < row_num; i++){

				for(int j = 0; j < col_num; j++){
			
					// I have doing the declaration wrong. It may be working if I rewrite it using arrays.
					result_mat.mat_ent[i][j] = mat.mat_ent[i][j] - this -> mat_ent[i][j];

				}

			}

			return result_mat;

		}


		std::array<double, col_num> operator [] (int index){
			if(0 <= index && index < row_num){
				return mat_ent[index];
			}
			else{
				throw std::out_of_range("index is out of range");
			}
		}

};


template<size_t T1, size_t T2, size_t T3>
Matrix<T1, T3> operator * (Matrix<T1, T2> const &mat1, Matrix<T2, T3> const &mat2){
	
	std::array<std::array<double, T3>, T1> arr;

	arr.fill({});

	Matrix<T1, T3> result_mat(arr);

	for(int i = 0; i < T1; i++){

		for(int j = 0; j < T3; j++){

			for(int k = 0; k < T2; k++){

				result_mat.mat_ent[i][j] = result_mat.mat_ent[i][j] + mat1.mat_ent[i][k] * mat2.mat_ent[k][j];

			}
		}
	}

	return result_mat;
}

#endif