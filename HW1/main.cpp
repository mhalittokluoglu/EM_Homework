/*
        EEE456
ELECTROMAGNETIC MODELLING HOMEWORK - 1
GROUP #1

Lecturer: Prof. Dr. Erkan AFACAN

Students:
Onur AKSOY 161110004
Mine Nur ÖZER 161110057
Muhammed Halit TOKLUOĞLU 161110070
*/

#include <iostream>

#define ROW 13
#define COLUMN 13

/* FUNCTION DEFINITIONS */
void set_initial_conditions(double grid[ROW][COLUMN]);
void print_grids(double grid[ROW][COLUMN]);
void iterate(double grid[ROW][COLUMN], bool* is_satisfied, double* error_percent);

int main(int argc, char* argv[]) // Main Function
{
    int iterate_number = 0;
    double grids[ROW][COLUMN] = { 0 }; // Creating grids 12 gaps x 12 gaps  = 13 grids x 13 grids
    double error_percent = 1000; // Error in percentage
    bool is_satisfied = false; // Two digit after decimal point shall not change
    // print_grids(grids);
    set_initial_conditions(grids); // Creating the shape on grids
    print_grids(grids); // Printing the shape
    while (!is_satisfied) // While condition is not satisfied.
    {
        iterate_number++;
        iterate(grids, &is_satisfied, &error_percent);
        /*
        std::cout << "Error: " << error_percent << std::endl;
        std::cout << "Iteration: " << iterate_number << std::endl;
        print_grids(grids);
        */
    }
    std::cout << "_____-----_____-----_____-----_____" << std::endl;
    std::cout << "Error: " << error_percent << std::endl;
    std::cout << "Iteration: " << iterate_number << std::endl;
    print_grids(grids); // After iteration finishes print out the grids
    return 0;
}


void set_initial_conditions(double grid[ROW][COLUMN])
{
    /*
    |\
    | \
    |  \
    |   \
    |    \
    |     \10V
    |      \C
    |a      \
    |12cm    \
    |20V      \
    |          \
    |           \
    |____________\
     b 12cm 0V

    The top corner belongs to "a"
    The left down corner belongs to "b"
    The right down corner belongs to "c"
    */
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (j == 0 && i != ROW - 1) // setting the "a" line 
            {
                grid[i][j] = 20;
            }
            else if (i == j) // setting the "c" line
            {
                grid[i][j] = 10;
            }
            // "b" line is 0. Do not need to set it.
        }
    }
}

void print_grids(double grid[ROW][COLUMN])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (i < j) // Print needed elements
            {
                continue;
            }
            printf("%.3lf\t", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void iterate(double grid[ROW][COLUMN], bool* is_satisfied, double* error_percent)
{
    double grid_prev[ROW][COLUMN];
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            grid_prev[i][j] = grid[i][j];
        }
    }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (i <= j || i == ROW - 1 || j == 0) // If the grid is on the line and out of the boundaries
            {
                continue; // Do not change anything and continue
            }
            if (i > 0 && i < ROW - 1 && j > 0 && j < COLUMN - 1)
            {
                /*
                If grid is not on the line and the grid is not out of shape boundaries
                Then sum four of the grid around the current grid and divide them by 4
                */
                grid[i][j] = (grid[i - 1][j] + grid[i + 1][j] + grid[i][j - 1] + grid[i][j + 1]) / 4;
            }
        }
    }
    double temp; // temporary double variable for holding the errors
    double temp_percent;
    double temp_max_percent = 0;
    double temp_max_error = 0; // The max error between iterations
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            temp = (grid[i][j] - grid_prev[i][j]);
            temp_percent = 100*(grid[i][j] - grid_prev[i][j])/grid[i][j];
            if (temp < 0) // If it is negative, make it positive
            {
                temp = -1 * temp;
                temp_percent = -1 * temp_percent;
            }
            if (temp_max_error < temp)
            {
                temp_max_error = temp;
                temp_max_percent = temp_percent;

            }
        }
    }
    *error_percent = temp_max_percent;
        if(temp_max_error<0.01)
        {
            *is_satisfied = true;
        }
}
