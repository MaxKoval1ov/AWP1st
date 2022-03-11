
#include <iostream>
#include<ctime>
#include <stdlib.h>

using namespace std;
double generateRandomDouble(double min,double max)
{
    return (double)rand() / (double)RAND_MAX * (max - min) + min;
}

double ****generate4Darr(double ****initArr,int row1,int col1, int row3, int col3)
{
    srand(time(0));

    for (int i = 0; i < row1; i++)
    {
        initArr[i] = new double** [col1];
        for (int j = 0; j < col1; j++)
        {
            initArr[i][j] = new double* [row3];
            for (int l = 0; l < row3; l++)
            {
                initArr[i][j][l] = new double[col3];
                for (int m = 0; m < col3; m++)
                {
                    initArr[i][j][l][m] = generateRandomDouble(0, 100);
                }
            }
        }
    }
    return initArr;
}

void print4Darr(double**** initArr, int row1, int col1, int row3, int col3)
{
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            for (int l = 0; l < row3; l++)
            {
                for (int m = 0; m < col3; m++)
                {
                    cout << initArr[i][j][l][m] << "||";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
}

void multiply2DArr(double** arr1, double** arr2, double** res,int row1,int col1, int col2)
{
    for (int i = 0; i < row1; i++)
    {
       
        for (int j = 0; j < col2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < col1; k++)
                res[i][j] += arr1[i][k] * arr2[k][j];
        }
    }
}

void multiply4DArr(double**** arr1, double**** arr2, double**** res, int row1, int col1, int col2, int row3, int col3 , int col4)
{
    for (int i = 0; i < row3; i++)
    {

        for (int j = 0; j < col4; j++)
        {
            for (int k = 0; k < col3; k++)
                multiply2DArr(arr1[i][k], arr2[k][j], res[i][j], row1, col1, col2);
        }
    }
}



int main()
{
	srand(time(0));
    int row1, row2, col1, col2, row3, col3, row4, col4;
    double ****outer1;
    double ****outer2;
    double ****result;
	system("chcp 1251");
    system("cls");
    cout << "1st row: ";
    cin >> row1;
    cout << "1st col: ";
    cin >> col1;
    cout << "2nd row: ";
    cin >> row2;
    cout << "2nd col: ";
    cin >> col2;

    cout << "3d row: ";
    cin >> row3;
    cout << "3d col: ";
    cin >> col3;
    cout << "4th row: ";
    cin >> row4;
    cout << "4th col: ";
    cin >> col4;

    if (col1 != row2 || col3!= row4)
    {
        cout << "Умножение невозможно!";
        cin.get(); cin.get();
        return 0;
    }

    outer1 = new double*** [row1];
    outer2 = new double*** [row2];
    result = new double*** [row2];

    generate4Darr(outer1, row1, col1, row3, col3);
	generate4Darr(outer2, row2, col2, row4, col4);
    generate4Darr(result, row2, col1, row4, col3);


    multiply4DArr(outer1, outer2, result, row1, col1, col2, row3, col3, col4);
   /* for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            for (int l = 0; l < row3; l++)
            {
                for (int m = 0; m < col3; m++)
                {

                }
            }
        }
    }*/

    print4Darr(result, row2, col1, row4, col3);
    cin.get(); cin.get();
    return 0;
}

