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
void iterate(double grid[ROW][COLUMN],double* error_prcent);

int main(int argc, char* argv[]) // Main Function
{
    double grids[ROW][COLUMN] = {0}; // Creating grids 12 gaps x 12 gaps  = 13 grids x 13 grids
    double error_percent = 1000; // Error in percentage
    // print_grids(grids);
    set_initial_conditions(grids); // Creating the shape on grids
    print_grids(grids); // Printing the shape 
    while(error_percent>1) // While the maximum error is bigger than 1%, make iteration.
    {
        iterate(grids,&error_percent);
        // print_grids(grids);
    }
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
   for(u_int8_t i = 0; i < ROW; i++)
   {
       for(u_int8_t j = 0; j < COLUMN; j++)
       {
           if(j == 0 && i != ROW-1) // setting the "a" line 
           {
               grid[i][j] = 20;
           }
           else if(i == j) // setting the "c" line
           {
               grid[i][j] = 10;
           }
        // "b" line is 0. Do not need to set it.
       }
   }
}

void print_grids(double grid[ROW][COLUMN])
{
    for(u_int8_t i = 0; i < ROW; i++)
    {
        for(u_int8_t j = 0; j < COLUMN; j++)
        {
            printf("%.3lf\t",grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void iterate(double grid[ROW][COLUMN],double* error_prcent)
{
    double grid_prev[ROW][COLUMN];
    for(u_int8_t i = 0; i < ROW; i++)
    {
        for(u_int8_t j = 0; j < COLUMN; j++)
        {
            grid_prev[i][j] = grid[i][j];
        }
    }
    for(u_int8_t i = 0; i < ROW; i++)
    {
        for(u_int8_t j = 0; j < COLUMN; j++)
        {
            if(i==j || i == ROW - 1 || j == 0) // If the grid is on the line
            {
                continue; // Do not change anything and continue
            }
            if(i > 0 && i < ROW - 1 && j > 0 && j < COLUMN -1) 
            {
                /*
                If grid is not on the line and the grid is not in the first row or the last row or the first row or the last column
                Then sum four of the grid around the current grid and divide them by 4
                */
                grid[i][j] = (grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1])/4;
            }
            else if(i == 0) // if grid is in the first row
            {
                if(j!=0 && j!=COLUMN-1) // If grid is not on the last column or first column in the first row
                {
                    grid[i][j] = (grid[i+1][j] + grid[i][j+1]+ grid[i][j-1])/3;
                }
                else if(j==COLUMN - 1) // if it is in the last column in the first row
                {
                    grid[i][j] = (grid[i+1][j] + grid[i][j-1])/2;
                }
                else if(j == 0) // It will never enter here since there is a line in j = 0
                {
                    grid[i][j] = (grid[i+1][j] + grid[i][j+1])/2;
                }
            }
            else if(i == ROW - 1) // If grid is in the last row
            {
                if(j!=0 && j!=COLUMN-1) // If grid is not on the last column or first column in the last row
                {
                    grid[i][j] = (grid[i-1][j] + grid[i][j+1]+ grid[i][j-1])/3;
                }
                else if(j==COLUMN - 1) // if it is in the last column in the last row
                {
                    grid[i][j] = (grid[i-1][j] + grid[i][j-1])/2;
                }
                else if(j == 0) // It will never enter here since there is a line in j = 0
                {
                    grid[i][j] = (grid[i-1][j] + grid[i][j+1])/2;
                }
            }
            else if(j == COLUMN - 1) // If grid is neither on the first row nor on the last row but on the last column.
            {
                grid[i][j] = (grid[i+1][j] + grid[i-1][j] + grid[i][j-1])/3;
            }
        }
    }
    double temp; // temporary double variable for holding the errors
    double temp_max_error = 0; // The max error between iterations
    for(u_int8_t i = 0; i < ROW; i++)
    {
        for(u_int8_t j = 0; j < COLUMN; j++)
        {
            temp = (grid[i][j] - grid_prev[i][j])*100/grid[i][j];
            if(temp<0) // If it is negative, make it positive
            {
                temp = -1*temp;
            }
            if(temp_max_error < temp)
            {
                temp_max_error = temp;
            }
        }
        *error_prcent = temp_max_error;
    }
}