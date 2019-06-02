#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "Matrix.h"
#include "Node.h"
#include "OpenGLScreenMain.h"

struct Point
{
    int x;
    int y;
};

static bool path_is_unreachable = false;

enum check_status
{
    OUT_OF_BOUNDS = -1,
    STORED = true,
};
using namespace selection;
/*  
    f = TOTAL Cost of the node
    g = the movement cost to move from the starting point to a given square on the grid, 
    following the path generated to get there.
    h = the estimated movement cost to move from that given square on the 
    grid to the final destination.
    Each step. it picks the node according to a value-‘f’which is a 
    parameter equal to the sum of two other parameters – ‘g’ and ‘h’.
*/

void create_blocked_areas(Matrix &m, Node &node, int x, int y) {
    m.create_blocked_cells(x,y);
    node.read_in_blocked(x, y);
}
/*
All we are doing here is passing the node linked list structure information
// Into the matrix so we can highlight the area we've assumed is the best
// path for efficiency

Because we don't want spaghetti code where the matrix class can interract with the node class
I want to create a vector of pairs and have each coordinate read in. This will keep the code
very simple and readable, but will sacrifice some space complexity for that simplicity
*/
void link_node_and_matrix(Matrix &m, Node &node){
    node.store_critical_path();
    m.read_in_path(node.get_path());
    m.color_in_path();
    m.display_matrix();
}

inline bool check_bounds(int x, int y, const Matrix &m) {
    return ((x < 0 || y < 0) || x > m.get_row() -1   || y > m.get_col() -1  );
}

inline bool check_if_first_traversal(Node &node){
    return (node.get_traversal_score() == 0);
}
inline bool check_if_optimal(int cost, Node &node){
    return(node.get_traversal_score() >= cost); 
}

int get_g(int x, int y, const Node &node){
    int differenceOfX_ = std::abs(x - node.get_start_positionX_());
    int differenceOfY_ = std::abs(y - node.get_start_positionY_());
    
    int result = differenceOfX_ + differenceOfY_;

    return result;
}

int get_h(int x, int y, const Node &node) {
    int differenceOfX_ = std::abs(x - node.get_end_positionX_());
    int differenceOfY_ = std::abs(y - node.get_end_positionY_());
    
    int result = (differenceOfX_ * differenceOfX_) + (differenceOfY_ * differenceOfY_);
    
    return result;
}

bool store_traversal(int f, int x, int y,int g, int h , Node &node) {
    if (node.check_coordinates(x, y,f,g,h) == true){
        return true;
    }
    if (node.if_blocked(x, y) == false){
        (node.store_traversal_cost(x, y,f,g,h));
        return true;
    }
    return false;
}

std::tuple<int,int,int,int,int>calculate_cost_of_traversal(int x, int y, const Node &node, const Matrix &m){
    if (check_bounds(x,y,m)){
        return std::make_tuple(-1,0,0,0,0); 
    }
    int g_holder = get_g(x,y,node);
    int h_holder = get_h(x,y,node);
    int f_holder = g_holder + h_holder;

    return std::make_tuple(f_holder,x,y,g_holder,h_holder);
}

void update_point(Point &p, Node& node){
    if (p.x == node.get_traversal_informationX_() && p.y == node.get_traversal_informationY_()){
        path_is_unreachable = true;
        return;
    }
    p.x = node.get_traversal_informationX_();
    p.y = node.get_traversal_informationY_();
}

void erase_out_of_bound_values(std::vector<std::tuple<int,int,int,int,int>> &node_info){
    for (auto it =node_info.begin(); it != node_info.end();){
        if (std::get<cost>(*it) == OUT_OF_BOUNDS){
            node_info.erase(it);
        }else{
            ++it;
        }
    }
}

void sort_to_optimal_first(std::vector<std::tuple<int, int, int, int, int>> &node_info, Node& node){
    std::sort(std::begin(node_info), std::end(node_info),
        [&](auto &t1, auto &t2) {
            if (std::get<cost>(t1) == std::get<cost>(t2))
                return (get_h(std::get<x_val>(t1), std::get<y_val>(t1), node) < get_h(std::get<x_val>(t2), std::get<y_val>(t2), node));
            return std::get<cost>(t1) < std::get<cost>(t2);
        }
    );
}

void store_first_traversal(const std::vector<std::tuple<int, int, int, int, int>> &node_info, Node &node){
    for (auto &item : node_info){
        store_traversal(std::get<cost>(item), std::get<x_val>(item), std::get<y_val>(item), std::get<g_val>(item), std::get<h_val>(item), node);
    }
}

bool traverse_to_optimal(std::vector<std::tuple<int, int, int, int, int>> &node_info, Node &node, Matrix &m){
    for (auto &item : node_info){
        // If the most optimal calculated is optimal
        if (check_if_optimal(std::get<cost>(item), node) == true){
            //Check if it's in the blocked list
            if (store_traversal(std::get<cost>(item), std::get<x_val>(item), std::get<y_val>(item),
                std::get<g_val>(item), std::get<h_val>(item), node) == STORED){
                return true;
            }
        }
        //The most optimal path is greater than the current cost of our node
        // I.E == We're traversing back which means -- We're blocked
        // We have to keep traversing around the block
        else if (check_if_optimal(std::get<cost>(item), node) != true)
        {
            create_blocked_areas(m, node, node.get_traversal_informationX_(), node.get_traversal_informationY_());
            node.pop_node();
            return false;
        }
    }
    return false;
}

bool run_on_adjacent_positions(Point &p, Node &node, Matrix &m){
    //(0) = Most optimal traversal cost from current node to next
    //(1) = Next node's X_ value
    //(2) = Next node's Y_ value
    //(3) = Node's G value
    //(4) = Node's H value
    std::vector<std::tuple<int, int, int, int, int>> f_cost;
    f_cost.reserve(8);
    //We need to find a better way to represent the traversals in an algorithm
    f_cost.push_back(calculate_cost_of_traversal(p.x + 1, p.y + 1, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x - 1, p.y - 1, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x + 1, p.y - 1, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x - 1, p.y + 1, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x + 1, p.y, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x - 1, p.y, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x, p.y + 1, node, m));
    f_cost.push_back(calculate_cost_of_traversal(p.x, p.y - 1, node, m));

    //Removing Out of bound values and sorting to most optimal to least optimal
    erase_out_of_bound_values(f_cost);
    sort_to_optimal_first(f_cost, node);


    if (check_if_first_traversal(node) == true){
        if (path_is_unreachable != true){
            store_first_traversal(f_cost, node);
            return true;
        }
        return false;
    }

    if (traverse_to_optimal(f_cost, node,m) == true){
        return true;
    }
    return false;
}

int main (){

    Point matrix,start,end;
    //Size of board
    matrix.x = 15;
    matrix.y = 15;
    //Start coordinates
    start.x = 0;
    start.y = 0;
    //End Coordinates specified by the user
    end.x = 14;
    end.y = 14;

    Matrix m {(unsigned int)matrix.x, (unsigned int)matrix.y};
    Node node {start.x, start.y, end.x, end.y};
    
    bool check = false;

    while (node.check() != true && path_is_unreachable != true){
        check = run_on_adjacent_positions(start, node,m);
        update_point(start, node);
        if (check == true)
            node.add_node();   
    }
    link_node_and_matrix(m,node);
    
    // Right now we are just instructing OpenGL to display an abritrary board
    //In the future we can process the information the user has entered and pass it into 
    //gl::main to process the representation

    // if (mygl::mygl_main() == 0){
    //     std::cout << "OpenGL has recieved the information" << std::endl;
    // }
    

        

    return 0;
}