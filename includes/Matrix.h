#pragma once
#include <iostream>
#include <vector>
#include <utility>

class Matrix {

private:
    
    //Use these variables to interract with matrix indicies
    //
    int _X, _Y; 
    std::vector<std::vector<int >> sourceMatrix;
    std::vector<std::pair<int,int>> criticalPath;
public:
    Matrix();
    Matrix(int row, int col);
    ~Matrix();
    void display_matrix() const;
    void read_in_path(const std::vector<std::pair<int, int>> &);
    void color_in_path();
    void create_blocked_cells(int x, int y);
    int get_row() const;
    int get_col() const;
};