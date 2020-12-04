#include<iostream> //Declare iostream
#include"Matrix.h" //Declare "Matrix.h"
using namespace std; //Declare using namespace std;

int main() //Declare main function
{
	Matrix mat1, mat2, mat3, mat4, mat5; //Declare Matrix 5 variable

	mat1.set_matrix(); //practice set_matrix() function of mat1
	mat2.set_matrix(); //practice set_matrix() function of mat2

	cout << "+ operation" << endl; //Print "+ operation"
	mat3 = mat1 + mat2; //Save mat1 + mat2 to mat3
	mat3.print_matrix(); //practice print_matrix() function of mat3
	cout << "- operation" << endl; //Print "- operation"
	mat3 = mat1 - mat2; //Save mat1 - mat2 to mat3
	mat3.print_matrix(); //practice print_matrix() function of mat3
	cout << "* operation" << endl; //Print "* operation"
	mat3 = mat1 * mat2; //Save mat1 * mat2 to mat3
	mat3.print_matrix(); //practice print_matrix() function of mat3

	cout << "L rotation" << endl; //Print "L rotation"
	mat4 = mat1.rotation_Left(); //Save mat1.rotation_Left() to mat4
	mat4.print_matrix(); //practice print_matrix() function of mat4
	cout << "R rotation" << endl; //Print "R rotation"
	mat4 = mat4.rotation_Right(); //Save mat4.rotation_Reft() to mat4
	mat4.print_matrix(); //practice print_matrix() function of mat4
	cout << "inverse" << endl; //Print "inverse"
	mat5 = mat4.Inverse(); //Save mat4.Inverse() to mat5
	mat5.print_matrix(); //practice print_matrix() function of mat5

	return 0; //return 0 and end of main function
}