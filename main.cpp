/*
Name: Omar Yossuf
SID: 900212166
Instructor: Nada GabAllah
Course: CSCE 2203
Section #03
Date: Oct 25th, 2022
*/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > matr;

matr MatrixMult(matr, matr);

matr MatrixAdd(matr, matr);

matr MatrixSub(matr, matr);

void printMatrix(const matr);

int main()
{
    matr 
    M1 = 
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }, 

    M2 = 
    {
        {-1, -2, -3, -4},
        {-5, -6, -7, -8},
        {-9, -10, -11, -12},
        {-13, -14, -15, -16}
    };

    matr res = MatrixMult(M1, M2);

    printMatrix(res);

    return 0;
}

matr MatrixMult(matr M1, matr M2)
{
    int size = M1.size();

    matr res((size), vector<int> (size));

    if(size == 1)
    {
        res[0][0] = M1[0][0] * M2[0][0];
        return res;
    }

    matr A((size / 2), vector<int> (size / 2)), P1((size / 2), vector<int> (size / 2));
    matr B((size / 2), vector<int> (size / 2)), P2((size / 2), vector<int> (size / 2));
    matr C((size / 2), vector<int> (size / 2)), P3((size / 2), vector<int> (size / 2));
    matr D((size / 2), vector<int> (size / 2)), P4((size / 2), vector<int> (size / 2));
    matr E((size / 2), vector<int> (size / 2)), P5((size / 2), vector<int> (size / 2));
    matr F((size / 2), vector<int> (size / 2)), P6((size / 2), vector<int> (size / 2));
    matr G((size / 2), vector<int> (size / 2)), P7((size / 2), vector<int> (size / 2));
    matr H((size / 2), vector<int> (size / 2));

    for(int i = 0; i < size / 2; i++)
    {
        for(int j = 0; j < size / 2; j++)
        {
            A[i][j] = M1[i][j];
            B[i][j] = M1[i][j + size / 2];
            C[i][j] = M1[i + size / 2][j];
            D[i][j] = M1[i + size / 2][j + size / 2];

            E[i][j] = M2[i][j];
            F[i][j] = M2[i][j + size / 2];
            G[i][j] = M2[i + size / 2][j];
            H[i][j] = M2[i + size / 2][j + size / 2];
        }
    }
    

    P1 = MatrixMult(A, MatrixSub(F, H)),
    P2 = MatrixMult(MatrixAdd(A, B), H),
    P3 = MatrixMult(MatrixAdd(C, D), E),
    P4 = MatrixMult(D, MatrixSub(G, E)),
    P5 = MatrixMult(MatrixAdd(A, D), MatrixAdd(E, H)),
    P6 = MatrixMult(MatrixSub(B, D), MatrixAdd(G, H)),
    P7 = MatrixMult(MatrixSub(A, C), MatrixAdd(E, F));

    matr
    z11((size / 2), vector<int> (size / 2)),
    z12((size / 2), vector<int> (size / 2)),
    z21((size / 2), vector<int> (size / 2)),
    z22((size / 2), vector<int> (size / 2));

    z11 = MatrixAdd(MatrixSub(MatrixAdd(P5, P4), P2), P6),
    z12 = MatrixAdd(P1, P2),
    z21 = MatrixAdd(P3, P4),
    z22 = MatrixSub(MatrixSub(MatrixAdd(P1, P5), P3),P7);

    for(int i = 0; i < size / 2; i++)
    {
        for(int j = 0; j < size / 2; j++)
        {
            res[i][j] = z11[i][j];
            res[i][j + size / 2] = z12[i][j];
            res[i + size / 2][j] = z21[i][j];
            res[i + size / 2][j + size / 2] = z22[i][j];
        }
    }

    return res;

}

matr MatrixSub(matr M1, matr M2)
{
    int size = M1.size();

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M1[i][j] -= M2[i][j];
    return M1;
}

matr MatrixAdd(matr M1, matr M2)
{
    int size = M1.size();

     for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M1[i][j] += M2[i][j];
    return M1;
}

void printMatrix(const matr m)
{

    int size = m.size();

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            cout << m[i][j] << "\t";
        cout << endl;
    }
}