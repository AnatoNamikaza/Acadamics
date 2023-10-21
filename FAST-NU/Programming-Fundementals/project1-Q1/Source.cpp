#include <iostream>

using namespace std;

int farmhouse_fields[4][6] = 
{   {   5,  1,  21, -1, -1, -1},
    {   -1, -1, -1, -1, -1, -1},
    {   23, 5,  20, 5,  30, -1},
    {   1,  9,  5,  0,  -1, -1} 
};

void all_empty()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 6; j++)
            farmhouse_fields[i][j] = -1;
}

void display_field()
{
    for (int i = 0; i < 4; i++)
    {
        cout << "Field" << i + 1 << ':';
        for (int j = 0; j < 6; j++)
        {
            cout << '\t' << farmhouse_fields[i][j];
        }
        cout << endl;
    }
}

void display_filled_field()
{
    int n = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 6; j++)
            if (farmhouse_fields[i][j] != -1) n++;
    cout << "There are " << n << " test score values entered in table.\n";
}

void display_avg_field()
{
    for (int i = 0; i < 4; i++)
    {
        double sum = 0, n = 0, em = 1;
        cout << "Field" << i + 1 << ':';
        for (int j = 0; j < 6; j++)
            if (farmhouse_fields[i][j] != -1)
                sum += farmhouse_fields[i][j], n++, em = 0;
        if (em == 0)
            cout << (sum / n) << endl;
        else
            cout << "Empty Field" << endl;
    }
}

void delete_value()
{
    int x = 0, y = 0;
    cout << "Enter the field no: ";
    cin >> x;
    if (x > 4 || x < 1)
    {
        cout << "invalid field no.\n";
        return;
    }
    cout << "Enter the test no: ";
    cin >> y;
    if (y > 6 || y < 1)
    {
        cout << "invalid test no.\n";
        return;
    }
    farmhouse_fields[x - 1][y - 1] = -1;
}

void insert_value()
{
    int x = 0, y = 0;
    cout << "Enter the field in which you want to enter a value: ";
    cin >> x;
    if (x > 4 || x < 1)
    {
        cout << "invalid field no.\n";
        return;
    }

    for (int j = 0; j < 6; j++)
    {
        if (farmhouse_fields[x-1][j] == -1)
        {
            cout << "Enter the value you want to enter: ";
            cin >> farmhouse_fields[x-1][j];
            return;
        }
    }
 
    cout << "Field is full.\n";
}

int menu()
{
    int c = 0;
    cout << "Press 1 to insert new test result.\n";
    cout << "Press 2 to display total number of results in table.\n";
    cout << "Press 3 to delete any test value from table.\n";
    cout << "Press 4 to display the 2 most frequent values in table.\n";
    cout << "Press 5 to display average scores of each field.\n";
    cout << "Press 6 to display field having maximum success score.\n";
    cout << "Press 7 to EXIT.\n";
    cout << "Enter: ";
    cin >> c;
    return c;
}

void display_2_most_values()
{
    int arr1[24]{ 0 }, arr2[24]{ 0 };

    int k = 0, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 6; j++)
            arr1[k] = farmhouse_fields[i][j], k++;

    for (k = 0; k < 24; k++)
    {
        if (arr1[k] != -1)
            for (int v = k + 1; v < 24; v++)
            {
                if (arr1[v] == arr1[k] && arr1[k] != -1)
                {
                    arr2[k]++, arr1[v] = -1;
                }
                if (v - 1 == k)
                {
                    arr2[k]++;
                }
            }
    }

    int temp1 = 0, temp2 = 0;
    for (i = 0; i < 24; i++)
    {
        for (j = i + 1; j < 24; j++)
        {
            if (arr2[i] < arr2[j])
            {
                temp1 = arr1[i];
                temp2 = arr2[i];
                arr1[i] = arr1[j];
                arr2[i] = arr2[j];
                arr1[j] = temp1;
                arr2[j] = temp2;
            }
        }
    }

    if (arr1[0] != -1)
    {
        cout << "1st most occurrence value is " << arr1[0] << " with total " << arr2[0] << " occurrence.\n";
        if (arr1[1] != -1)
        {
            cout << "2st most occurrence value is " << arr1[1] << " with total " << arr2[1] << " occurrence.\n";
        }
        else
        {
            cout << "2st most occurrence value is not present.\n";
        }
    }
    else
    {
        cout << "All fields are empty.\n";
    }
}

void display_max_success_fields()
{
    int max = -1, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 6; j++)
            if (max < farmhouse_fields[i][j]) max = farmhouse_fields[i][j];

    if (max != -1)
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 6; j++)
                if (farmhouse_fields[i][j] == max)
                    cout << "Field " << i + 1 << " has the maximum success score.\n";
        }
    else
        cout << "All fields are empty.\n";
}

int main()
{
    //all_empty();

    while (1) {
        display_field();
        cout << "---------------------------------------------------\n";
        int ch = menu();
        cout << "---------------------------------------------------\n";

        if (ch == 1)
        {
            insert_value();
        }
        else if (ch == 2)
        {
            display_filled_field();
        }
        else if (ch == 3)
        {
            delete_value();
        }
        else if (ch == 4)
        {
            display_2_most_values();
        }
        else if (ch == 5)
        {
            display_avg_field();
        }
        else if (ch == 6)
        {
            display_max_success_fields();
        }
        else if (ch == 7) { break; }
        else
        {
            cout << "Incorrect choice.\n";
        }
        cout << "---------------------------------------------------\n";
        system("pause");
        system("cls");
    }
}