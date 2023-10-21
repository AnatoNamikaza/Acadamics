#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/sysinfo.h>

using namespace std;

const auto processor_count = get_nprocs();

struct free_matrix
{
    int** Matrix;
    int r;
};

class Myresult
{
public:
    int** Matrix_1, ** Matrix_2, i, j, c1, val;
    void set_values(int** Matr_1, int** Matr_2, int i, int j, int c1, int val)
    {
        this->Matrix_1 = Matr_1, this->Matrix_2 = Matr_2,
            this->i = i, this->j = j, this->c1 = c1, this->val = val;
    }
};

int** Matrix_File_Order(string* filenames, int& n)
{
    int** Matrix_Orders = new int* [n];

    for (int i = 0; i < n; i++)
        Matrix_Orders[i] = new int[2]{ 0 };

    for (int i = 0; i < n; i++)
    {
        ifstream fin(filenames[i]);

        if (!fin.is_open())
        {
            cout << "File " << filenames[i] << " is not accessable or doesnot exist." << '\n';
            continue;
        }

        int row = 0, col = 0, prevCol = 0, skip = 0;
        string line;

        while (getline(fin, line))
        {
            stringstream m_E;
            m_E << line;
            string val;
            col = 0;
            while (m_E >> val)
                col++;
            if (prevCol == 0)
                prevCol = col;
            else if (prevCol != col)
            {
                cout << "Matrix Order irregularity detected in File " << filenames[i] << ".\n";
                skip++; break;
            }
            row++;
        }

        if (skip == 1)  continue;

        Matrix_Orders[i][0] = row, Matrix_Orders[i][1] = prevCol;

        fin.close();
    }
    return Matrix_Orders;
};

void Matrix_File_Filler(string& filename, int** Matrix)
{
    ifstream fin(filename);

    if (!fin.is_open())
        cout << "File " << filename << " is not accessable or doesnot exist." << '\n';

    int row = 0, col;
    string line, val;

    while (getline(fin, line))
    {
        stringstream m_E;
        m_E << line;
        val = "";
        col = 0;
        while (m_E >> val)
            Matrix[row][col] = stoi(val),
            col++;
        row++;
    }

    fin.close();
}

void Matrix_Print(int** Matrix, int& rows, int& cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << Matrix[i][j] << '\t';
        cout << '\n';
    }
}

void* Matrix_Free_Memory(void* free_matrix)
{
    struct free_matrix* sem = (struct free_matrix*)free_matrix;

    for (int i = 0; i < sem->r; i++)
        delete[] sem->Matrix[i], sem->Matrix[i] = nullptr;
    delete[] sem->Matrix, sem->Matrix = nullptr;
    return 0;
}

int** Matrix_Initializer(int& r, int& c)
{
    int** Matrix = new int* [r];
    for (int i = 0; i < r; i++)
        Matrix[i] = new int[c] { 0 };

    return Matrix;
}

int** Matrix_Initializer_Data(string& filename, int& r, int& c)
{
    int** Matrix = new int* [r];
    for (int i = 0; i < r; i++)
        Matrix[i] = new int[c] { 0 };

    // storing data from file to matrix.
    Matrix_File_Filler(filename, Matrix);

    return Matrix;
}

void* R_entry(void* Myresult)
{
    struct Myresult* sem = (struct Myresult*)Myresult;
    int val = 0;
    for (int k = 0; k < sem->c1; ++k)
        sem->val += sem->Matrix_1[sem->i][k] * sem->Matrix_2[k][sem->j];
    return 0;
}

int** Matrix_Resultant_Generator(int** Matrix_1, int** Matrix_2, int& r1, int& c1, int& r2, int& c2)
{
    int** result_Matrix = Matrix_Initializer(r1, c2);

    pthread_t* p_th = new pthread_t[processor_count];
    Myresult* temp = new Myresult[c2];

    int i = 0, j, j1, k, x;
    while (i < r1)
    {
        j = 0, j1 = 0, k = 0;
        while (j < c2)
        {
            temp[j].set_values(Matrix_1, Matrix_2, i, j, c1, result_Matrix[i][j]);

            pthread_create(&p_th[k], NULL, R_entry, (void*)&temp[j]);

            if (k == processor_count - 1)
            {
                k = 0;
                for (x = 0; x < processor_count; x++)
                {
                    pthread_join(p_th[x], NULL);
                    result_Matrix[i][j1] = temp[j1].val;
                    //cout << i << '\t' << j << '\t' << j1 << '\t' << x << '\t' << result_Matrix[i][j1] << '\n';
                    j1++;
                }
            }
            else if (j == c2 - 1 && processor_count >= c2)
            {
                for (x = 0; x < c2; x++)
                {
                    pthread_join(p_th[x], NULL);
                    result_Matrix[i][j1] = temp[j1].val;
                    //cout << i << '\t' << j << '\t' << j1 << '\t' << x << '\t' << result_Matrix[i][j1] << '\n';
                    j1++;
                }
            }
            else if (j == c2 - 1 && processor_count < c2)
            {
                for (x = 0; x <= k; x++)
                {
                    pthread_join(p_th[x], NULL);
                    result_Matrix[i][j1] = temp[j1].val;
                    //cout << i << '\t' << j << '\t' << j1 << '\t' << x << '\t' << result_Matrix[i][j1] << '\n';
                    j1++;
                }
            }
            else { ++k; }
            ++j;
        }
        ++i;
    }
    delete[] temp;
    delete[] p_th;

    return result_Matrix;
}

int main(int arg, char* argv[])
{
    if (arg != 3)
    {
        cout << "Incorrect Arguments (-_-) \n";
        return 0;
    }

    struct timeval st, et;
    gettimeofday(&st, NULL);

    string* filename = new string[2];
    filename[0] = argv[1],
        filename[1] = argv[2];

    int n = 2,
        ** order = Matrix_File_Order(filename, n);

    cout << "Order of Matrix#1: \t rows= " << order[0][0] << "\tcols= " << order[0][1] << '\n'
        << "Order of Matrix#2: \t rows= " << order[1][0] << "\tcols= " << order[1][1] << '\n';

    if (order[0][1] != order[1][0])
    {
        cout << "\nMatrices incompatible for result_Matrixiplication.\n";
        return 0;
    }

    std::cout << "Available Processes: " << processor_count << std::endl;

    pthread_t* p_th = new pthread_t[processor_count];

    int
        //Matrix_1
        //----------------------------------------------
        ** Matrix_1 = Matrix_Initializer_Data(filename[0], order[0][0], order[0][1]),
        //Matrix_2
        //----------------------------------------------
        ** Matrix_2 = Matrix_Initializer_Data(filename[1], order[1][0], order[1][1]),
        //Resutlant_Matrix
        //----------------------------------------------
        ** result_Matrix = Matrix_Resultant_Generator(Matrix_1, Matrix_2, order[0][0], order[0][1], order[1][0], order[1][1]);

    //-----------------------------------------------------------------------------------------

    // Displaying Matrix_1.
    cout << endl << "Matrix_1: " << endl;
    Matrix_Print(Matrix_1, order[0][0], order[0][1]);

    // Displaying Matrix_2.
    cout << endl << "Matrix_2: " << endl;
    Matrix_Print(Matrix_2, order[1][0], order[1][1]);

    // Displaying the result_Matrix of two matrix.
    cout << endl << "result_Matrix: " << endl;
    Matrix_Print(result_Matrix, order[0][0], order[1][1]);

    //freeing the matrix memory

    free_matrix* m1 = new free_matrix[3];
    m1[0].Matrix = Matrix_1, m1[0].r = order[0][0],
        m1[1].Matrix = Matrix_2, m1[1].r = order[1][0],
        m1[2].Matrix = result_Matrix, m1[2].r = order[0][0];

    pthread_create(&p_th[0], NULL, &Matrix_Free_Memory, &m1[0]);
    pthread_create(&p_th[1], NULL, &Matrix_Free_Memory, &m1[1]);
    pthread_create(&p_th[2], NULL, &Matrix_Free_Memory, &m1[2]);

    pthread_join(p_th[0], NULL), pthread_join(p_th[1], NULL), pthread_join(p_th[2], NULL);
    cout << endl << "---------------------------------" << endl;

    for (int i = 0; i < 2; i++)
        delete[] order[i];
    delete[] order;
    delete[] m1;
    delete[] filename, filename = nullptr;
    delete[] p_th;

    gettimeofday(&et, NULL);

    int elapsed = (((et.tv_sec - st.tv_sec) * 1000000)
        + (et.tv_usec - st.tv_usec));
    printf("\nExecution time: %d micro seconds\n", elapsed);

    return 0;
}