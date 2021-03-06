// ConsoleApplication3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<math.h>
#include<stdio.h>
#define matrix_size_type 3
using namespace std;


class Matrix
	/*
	This Matrix calculation programming was developed by Keigo Takamura
	It is a program created based on a static matrix size
	*/
{	//C言語的な可読性を高める為にArrayクラスは不使用

	static const int Original_matrix_size = matrix_size_type;//行列の初期サイズ (基本使わない)
public:
	double matrix_over_type[matrix_size_type][matrix_size_type + 1];//拡大係数行列
	double matrix_default_type[matrix_size_type][matrix_size_type];//正方行列
	int over_frag = 0;//正方行列かどうか判断する

	Matrix();
	double matrix_default_copy(double mat[matrix_size_type][matrix_size_type] ) {//正方行列のコピー
		
		for (int i = 0; i < matrix_size_type; i++) {
			for (size_t t = 0; t < matrix_size_type; t++){
				matrix_default_type[i][t] = mat[i][t];
			}
		}
	}

	double matrix_over_copy(double mat[matrix_size_type][matrix_size_type + 1]) {//拡大係数行列のコピー
		over_frag = 1;
		for (size_t i = 0; i < matrix_size_type; i++){
			for (size_t t = 0; t < matrix_size_type + 1; t++) {
				matrix_over_type[i][t] = mat[i][t];
			}
		}
	}
	int matrix_size_view() {
		if (over_frag == 0) {
			return sizeof(matrix_default_type);
		}
		else {
			return sizeof(matrix_over_type);
		}
	}
	
	double matrix_Determinant(Matrix a) {//行列式
		double Determinant = 1.0;
		double pivot = 0.0;
		if (over_frag == 1) {
			cout << "エラー！正方行列ではありません！" << endl;
			return NULL;
		}
		if (Original_matrix_size == 2) {//二次行列の場合はたすき掛けで解法を求める
			Determinant = a.matrix_default_type[0][0] * a.matrix_default_type[0][1];
			Determinant -= a.matrix_default_type[0][1] * a.matrix_default_type[1][0];
		}
		else {//行列サイズが3以上の場合は三角行列を生成するアルゴリズムでやる
			for (int i = 0; i < Original_matrix_size; i++)
			{
				for (int t = 0; t < Original_matrix_size; t++)
				{
					if (i < t) {
						pivot = a.matrix_default_type[t][i] / a.matrix_default_type[i][i];// i <  tの時
					}
					for (int k = 0; k < Original_matrix_size; k++)
					{
						a.matrix_default_type[t][k] -= a.matrix_default_type[t][k] * pivot; //三角行列を作る
					}
				}

				for (int i = 0; i < Original_matrix_size; i++) {
					Determinant *= a.matrix_default_type[i][i]; //対角成分との積
				}
			}


		}
		return Determinant;
	}

	Matrix inv_matrix(Matrix a) {
		double Identity_matrix[Original_matrix_size][Original_matrix_size];

		for (int i = 0; i < Original_matrix_size; i++) {
			for (int t = 0; t < Original_matrix_size; t++)//単位行列を作成する
			{
				if (i == t) {
					Identity_matrix[i][t] = 1;
				}
				else {
					Identity_matrix[i][t] = 0;
				}
			}
		}
	}

	};



Matrix operator +(Matrix a, Matrix b) {
	if (a.matrix_size_view() != b.matrix_size_view() ) {//行列サイズがそれぞれ異なっているときの処理
		cout << "Some error!! Matrix sizes are different and matrix sum can not be summed" << endl;
		exit(1);
	}
	if (a.over_frag == 0 && b.over_frag) {
		for (int i=0; i < matrix_size_type; i++) {
			for (int t = 0; t < matrix_size_type; t++) {
				b.matrix_default_type[i][t]=a.matrix_default_type[i][t]+b.matrix_default_type[i][t];
			}
		}
	}
	else
	{
		for (int i = 0; i < matrix_size_type+1; i++) {
			for (int t = 0; t < matrix_size_type+1; t++) {
				b.matrix_over_type[i][t] = a.matrix_over_type[i][t] + b.matrix_over_type[i][t];
			}
		}
	}

	return b;
}

int main(){
	int matrix_size=matrix_size_type;//
	Matrix a,b;

	double mat1[matrix_size_type][matrix_size_type + 1] = { {2,5,7,4},{4,13,20,11},{8,29,50,29} };//テスト用拡大係数行列
	




}
