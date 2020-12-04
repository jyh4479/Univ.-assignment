
class Matrix //Declare Class of Matrix
{
private: //This variable is only accessible within the Class
	double matrix[3][3] = { NULL }; //Declare variables used only in Matrix Class

	int i = 0, j = 0, k=0; //Declare variables used only in Matrix Class
	double k_ = 0; //Declare variables used only in Matrix Class

public: //This variable can be accessed from outside of the Class
	Matrix();
	~Matrix();

	void set_matrix(); //Function declaration returning nothing
	void print_matrix(); //Function declaration returning nothing

	Matrix rotation_Left(); //Declare the Function That Returns the Matrix
	Matrix rotation_Right(); //Declare the Function That Returns the Matrix
	Matrix Inverse(); //Declare the Function That Returns the Matrix

	Matrix operator + (const Matrix& mat); //Function that define operator + to be used by Matrix
	Matrix operator - (const Matrix& mat); //Function that define operator - to be used by Matrix
	Matrix operator = (const Matrix& mat); //Function that define operator = to be used by Matrix
	Matrix operator * (const Matrix& mat); //Function that define operator * to be used by Matrix	 
};

