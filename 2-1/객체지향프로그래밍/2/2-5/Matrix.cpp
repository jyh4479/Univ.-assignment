#include<iostream> //Declare iostream
#include "Matrix.h" //Declare Matrix.h

using namespace std; //Declare using nmaespace std;

Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::set_matrix() //Declare set_matrix() function of Matrix
{
	cout << "Input 3x3 matrix" << endl << ": "; //Print "Input 3x3 matrix"

	i = 0, j = 0; //Declare integer and save 0 to i and j
	 
	while (i != 3) //If i is not 3, repeat the function
	{
		for (i = 0; i < 3; i++) /*Save 0 to i, If i is smaller than 3 repeat the function
								and the function end once, update i + 1 */
			for (j = 0; j < 3; j++) /*Savj e 0 to j, If j is smaller than 3 repeat the function
									and the function end once, update j + 1 */
			{
				cin >> k_; //Get information from keyboard and save to k_
				matrix[i][j] = k_; //Save k_ to matrix[i][j]
			}
	}
}

Matrix Matrix::operator = (const Matrix& mat) //Declare operator =, that is used in matrix class operation
{
	i = 0, j = 0; //Declare integer i, j and save 0 to each integer

	for (i = 0; i < 3; i++) /*Save 0 to i, If i is smaller than 3 repeat the function
							and end function once, update i + 1 */
	{
		for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaller than 3 repeat the function
								and end function once, update j + 1 */
		{
			matrix[i][j] = mat.matrix[i][j]; //Save mat.marix[i][j] to matrix[i][j]
		}
	}
	return *this; //return matrix that is pointed now
}

Matrix Matrix::operator + (const Matrix& mat) //Declare operator +, that is used each matrix class operation
{
	Matrix sum; //Declare Matrix sum

	i = 0, j = 0; //Save 0 to i, j

	for (i = 0; i < 3; i++) /*Save 0 to i, If i is smaller than 3, repeat the function
							and end the function once, update i + 1 */
		for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaler than 3, repeat the function
								and end the function once, update j + 1 */
		{
			sum.matrix[i][j] = matrix[i][j]; + mat.matrix[i][j]; //Save (matrix[i][j] + mat.matrix[i][j]) to sum.matrix[i][j]
		}
	return sum; //return matrix of sum
}

Matrix Matrix::operator - (const Matrix& mat) //Declare operator -, that is used each matrix class operation
{
	Matrix sub; //Delcare Matrix sub

	i = 0, j = 0; //Save 0 to i, j
	
	for(i=0;i<3;i++) /*Save 0 to i, If i is smaller than 3, repeat the function
					 and end of function once, update i + 1 */
		for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaller than 3, repeat the function
								and end of function once, update j + 1 */
		{
			sub.matrix[i][j] = matrix[i][j] - mat.matrix[i][j]; //Save (matrix[i][j] - mat.matrix[i][j]) to sub.matrix[i][j]
		}
	return sub; //return matrix of sub
}

Matrix Matrix::operator * (const Matrix& mat) //Declare operator *, that is used each matrix class operation
{
	Matrix Multi; //Declare Matrix Multi

	i = 0, j = 0; //Save0 to i, j

	for (i = 0; i < 3; i++) /*Save 0 to i, If i is smaller than 3, repeat the function
							and end of function once, update i + 1 */
		for (j = 0; j < 3; j++)/*Save 0 to j, If j is smaller than 3, repeat the function
							   and end of function once, update j + 1 */
			for (k = 0; k < 3; k++) /*Save 0 to k, If k is smaller than 3, repeat the function
									and end of function once, update k + 1 */
			{
				Multi.matrix[i][j] += matrix[i][k] * mat.matrix[k][j]; /*Save Multi.matrix[i][j]+(matrix[i][k]*mat.matrix[k][j])
																	   to Multi.matrix[i][j] */
			}
	return Multi; //return matrix of Multi
}

void Matrix::print_matrix() //Declare void function of Matirx Print_matrix()
{
	i = 0, j = 0; //Save 0 to i, j

	while (i != 3) //If i is not 3, repeat the function
	{
		for (i = 0; i < 3; i++) /*Save 0 to i, If i is smaller than 3, repeat the function
								and end function once update i + 1 */
		{
			for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaller than 3, repeat the function
									and end function once update j + 1 */
			{
				cout << matrix[i][j] << " "; //Print matrix[i][j] " "
			}
			cout << endl; //Print "endl"
		}
	}
}

Matrix Matrix::rotation_Left() //Declare Matrix rotation_Left() that return Matrix
{

	Matrix Leftarr; //Declare Matrix Leftarr variable

	i = 0, j = 0; //Save 0 to i, j

	for (i = 0; i<3; i++) /*Save 0 to i, If i is smaller than 3, repeat the function
						  and end function once, update i + 1 */
		for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaller than 3, repeat the function
								and end function once, update j + 1 */
		{
			Leftarr.matrix[2 - j][i] = matrix[i][j]; //Save matrix[i][j] to Leftarr.matrix[2-j][i]
		}
	return Leftarr; //return matrix of Leftarr
}

Matrix Matrix::rotation_Right() //Declare Matrix rotation_Right() that return Matrix
{

	Matrix Rightarr; //Declare Matrix Rightarr

	i = 0, j = 0; //Save 0 to i, j

	for (i = 0; i<3; i++) /*Save 0 to i, If i is smaller than 3, repeat the function
						  and end function once, update i + 1 */
		for (j = 0; j < 3; j++) /*Save 0 to j, If j is smaller than 3, repeat the function
								and end function once, update j + 1 */
		{
			Rightarr.matrix[j][2 - i] = matrix[i][j]; //Save matrix[i][j] to Right.matrix[j][2-i]
		}
	return Rightarr; //return matrix of Rightarr
}

Matrix Matrix::Inverse() //Declare Matrix Inverse() that return Matrix
{
	Matrix Inversearr; //Declare Matrix Inversearr

	double a1, a2, a3, b1, b2, b3, c1, c2, c3; //Declare doubel variable

	a1 = matrix[0][0]; //Save matrix[0][0] to a1
	a2 = matrix[0][1]; //Save matrix[0][1] to a1
	a3 = matrix[0][2]; //Save matrix[0][2] to a1
	b1 = matrix[1][0]; //Save matrix[1][0] to a1
	b2 = matrix[1][1]; //Save matrix[1][1] to a1
	b3 = matrix[1][2]; //Save matrix[1][2] to a1
	c1 = matrix[2][0]; //Save matrix[2][0] to a1
	c2 = matrix[2][1]; //Save matrix[2][1] to a1
	c3 = matrix[2][2]; //Save matrix[2][2] to a1

	if ((a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2) == 0)
	{ //If (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2) is 0 practice the function
		for (i = 0; i < 3; i++)/*Save 0 to i, If i is smaller than 3, repeat the function
							   and end function once update i + 1 */
		{
			for (j = 0; j < 3; j++)/*Save 0 to j, If j is smaller than 3, repeat the function
							   and end function once update j + 1 */
			{
				Inversearr.matrix[i][j] = 0; //Save 0 to Inversearr.matrix[i][j]
			}
		}
		return Inversearr; //return matrix of Inversearr
	}

	Inversearr.matrix[0][0] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(b2*c3 - b3*c2);
	Inversearr.matrix[0][1] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(-a2*c3 + a3*c2);
	Inversearr.matrix[0][2] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(a2*b3 - a3*b2);
	Inversearr.matrix[1][0] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(-b1*c3 + b3*c1);
	Inversearr.matrix[1][1] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(a1*c3 - a3*c1);
	Inversearr.matrix[1][2] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(-a1*b3 + a3*b1);
	Inversearr.matrix[2][0] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(b1*c2 - b2*c1);
	Inversearr.matrix[2][1] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(-a1*c2 + a2*c1);
	Inversearr.matrix[2][2] = 1 / (a1*b2*c3 - a1*b3*c2 - b1*a2*c3 + b1*a3*c2 + c1*a2*b3 - c1*a3*b2)*(a1*b2 - a2*b1);
	//Save each Inverse value to martrix of Inversearr
	return Inversearr; //return matrix of Inversearr
}