#include <iostream> //Declare iostream

using namespace std; //Declare using namespace std

void change_head(char* output, int&i, int&j); //Declare the function that contain 3 variable
void bublesort(char* output, int& i); //Declare the function that contain 2 variable
void biggerlsGreater(char* input,char* output) //Delcare the function that contatin char* variable
{
	int i = 0, j = 0, k = 0, count=0; //Declare the integer variable and Save 0
	char sub_input[100] = { NULL }; //Declare char variable and Save NULL

	for (i = 0; input[i]; i++) //Declare i = 0 ,If input[i] not end , update i + 1
		output[i] = input[i]; //Save input[i] to output[i]
	
	if (strlen(output) > 10) //IF strlen(input) > 10 , practice function
	{
		cout << "Range is over!" << endl; //Print"Range is over!"
		output[0] = NULL; //Save NULL to output[0]
		return ; //return 0 and end of main function
	}

	for (int count = 0; output[count] != NULL; count++)
	{/*Declare integer count and save 0 to count, If input[count] is not NULL repeat the function
	 and end the function once, update count + 1 */
		if (output[count] < 96 || input[count] > 122) //If input[count] < 96 or input[count] > 122 practice function
		{
			cout << "Only Alphabetic letter!!" << endl; //Print "Only Alphabetic letter!!"
			output[0] = NULL; //Save NULL to output[0]
			return ; //return 0 and end of main function
		}
	}

	for (; output[count] != NULL; count++) /*If input[count] is not NULL repeat the function
										  and end the function once , update count + 1 */
	{
		if (output[count] < output[count + 1]) //If input[count]<input[count + 1] practice the function
			break; //Declare break

		else if (output[count + 1] == NULL) //If input[count + 1] == NULL practice the function
		{
			strcpy_s(output,10,"No answer"); //Save "No answer" to output
			return ; //return  and end of main function
		}
	}

	for (i = 0; output[i] != NULL; i++); /*Save 0 to i , If output[i] is not NULL, Repeat the function
									   and the function end once, update i+1*/
	j = i - 1; //Save i-1 to j

	for (; output[j] >= output[i]; j--, i--); /*If output[j] is equal or bigger than output[i] practice the function
										 and the function end once, update j-1, i-1 */
	
	change_head(output,i,j); //practice the change_head function

}

void change_head(char* output,int& i,int&j) //Declare the function the contain 3 variable
{
	int count = 1, sub_i = 0; //Declare integer variable and Save each value to variable
	char suboutput[10] = { NULL }; //Declare char variable and Save NULL to variable

	sub_i = i; //Save i to sub_i

	for (; output[j] + count != output[sub_i];count++) /*If output[j]+count is not output[sub_i], repeat the function
												   and the function end once, update count + 1 */
	{
		for (sub_i = i; output[sub_i] != NULL; sub_i++) /*Save i to sub_i, If output[sub_i] is not NULL, repeat the function
													  and the function end once, update sub_i +1 */
		{
			if (output[j] + count == output[sub_i]) //If output[j] + count is equal output[sub_i] practice the function
				break; //Declare break
		}
		if (output[j] + count == output[sub_i]) //If output[j] + count is equal output[sub_i] practice the function
			break; //Declare break
	}

	suboutput[i] = output[j]; //Save output[j] tp suboutput[i]
	output[j] = output[sub_i]; //Save output[sub_i] to output[j]
	output[sub_i] = suboutput[i]; //Save suboutput[i] to output[sub_i]

	bublesort(output, i); //Practice the function of bublesort
}

void bublesort(char* output,int& i) //Declare the functon that contain 2 variable
{

	int j = i + 1, sub_i = i; //Declare integer variable and Save each vlaue to variable
	char suboutput[100] = { NULL }; //Declare char variable and save NULL

	for (; output[sub_i] != NULL; sub_i++) /*If output[sub_i] is not NULL repeat the function
										 and end the function once update sub_i +1 */
	{
		j = sub_i + 1; //Save sub_i + 1 to j
		for (; output[j] != NULL; j++) /*If output[j] is not NULL repeat the function
									 and end the function once update j++ */
		{
			if (output[sub_i] > output[j]) //If output[sub_i] is bigger than output[j] practice the function
			{
				suboutput[sub_i] = output[sub_i]; //Save output[sub_i] to suboutput[sub_i]
				output[sub_i] = output[j]; //Save output[j] to output[sub_i]
				output[j] = suboutput[sub_i]; //Save suboutput[sub_i] to output[j]
			}
		}
	}
}

int main() //Declare main function
{
	int i = 0; //Declare integer i save 0 to i
	int count = 0; //Declare integer variable and save 0 to variable
	char input[100] = { NULL }; //Declare char variable and sabe NULL to variable
	char output[100] = { NULL }; //Declare char variable and sabe NULL to variable

	cout << "Input your string" << endl<< ": "; //Print "Input your string" "endl" ": "
	cin >> input; //Get information of input

	biggerlsGreater(input,output); //Practice the bigger IsGreater function

	if (output[0] != NULL) //If output[0] is not NULL practice the function
	{
		cout << "Out put" << endl << ": "; //Print "Out put"
		cout << output << endl; //Print output
	}

	return 0; //return 0 and end of main function
}