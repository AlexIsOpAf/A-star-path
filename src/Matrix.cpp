#include "includes/Matrix.h"
#include <iostream>

//Default
Matrix::Matrix() : Matrix{3,3} {
}

//  Don't want to create an empty vector, THEN, re-size it. Not an efficient approach
//  We can create it with a fixed size using an init list. 
Matrix::Matrix(int row, int col)
    : _X{row}, _Y{col}, sourceMatrix {std::vector<std::vector<int>>(_X, std::vector<int>(_Y,0))}{
    std::cout << "\nOverloaded Created" << std::endl;
    
}

void Matrix::read_in_path(const std::vector<std::pair<int,int>> &path ) {
    criticalPath = path;

    std::cout << "In Matrix!!" << std::endl;
    for (const auto &item : criticalPath){
        std::cout << "Coordinates: " << item.first << ' ' << item.second << std::endl;
    }
}

int Matrix::get_col() const {return _Y;}
int Matrix::get_row() const { return _X;}

void Matrix::color_in_path() {
    
    //We can use this function later to feed the information of the path to be coloured
    //Into an SDL2 container
    for (auto &item : criticalPath)
        sourceMatrix.at(item.first).at(item.second) = 1;

}

void Matrix::create_blocked_cells(int x, int y) {
    sourceMatrix.at(x).at(y) = 00;
}

Matrix::~Matrix() {
    std::cout << "\nDestructor called" << std::endl;
}

void Matrix::display_matrix() const {

    for (size_t j = 0; j < _X; j++)
    {
        std::cout << '\n';
        for (size_t i = 0; i < _Y; i++)
        {
            std::cout << "|   " << sourceMatrix.at(i).at(j) << "   |";
        }
    }
}