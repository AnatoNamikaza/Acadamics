#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


void largest(std::vector<std::vector<int>>& maze, int i_r, int i_c, int f_r, int f_c, int pre, int& max)
{
    if (i_r + 1 >= f_r && i_c + 1 >= f_c)
        return;
    else if (i_r + 1 < f_r && i_c + 1 < f_c)
    {
        if (pre + maze[i_r + 1][i_c] > pre + maze[i_r][i_c + 1])
        {
            if (pre + maze[i_r + 1][i_c] > max)
                max = pre + maze[i_r + 1][i_c];
        }
        else
            if (pre + maze[i_r][i_c + 1] > max)
                max = pre + maze[i_r][i_c + 1];
        largest(maze, i_r + 1, i_c, f_r, f_c, pre + maze[i_r + 1][i_c], max);
        largest(maze, i_r, i_c + 1, f_r, f_c, pre + maze[i_r][i_c + 1], max);

    }
    else if (i_r + 1 < f_r && i_c + 1 >= f_c)
    {
        if (pre + maze[i_r + 1][i_c] > max)
            max = pre + maze[i_r + 1][i_c];
        largest(maze, i_r + 1, i_c, f_r, f_c, pre + maze[i_r + 1][i_c], max);
    }
    else if (i_r + 1 >= f_r && i_c + 1 < f_c)
    {
        if (pre + maze[i_r][i_c + 1] > max)
            max = pre + maze[i_r][i_c + 1];
        largest(maze, i_r, i_c + 1, f_r, f_c, pre + maze[i_r][i_c + 1], max);
    }
}

int swampExplorer(std::vector<std::vector<int>>& swamp_maze)
{
    int rows = swamp_maze.size(), cols = swamp_maze[0].size();

    int max = swamp_maze[0][0];

    largest(swamp_maze, 0, 0, rows, cols, swamp_maze[0][0], max);

    return max;
}

int main() 
{
    vector<vector<int>> maz = { {5,3,4},{8,6,9},{1,3,2} };

    cout << swampExplorer(maz) << endl;

    return 0;
}
