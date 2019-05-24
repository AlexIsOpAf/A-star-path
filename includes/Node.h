#pragma once
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
// **************************************************************
// *************************************************************
/*
    Create a Node class -- 

    f = TOTAL Cost of the node
    g = the distance between the current node and the start node
    h = the estimated distance from the current node to the end node -- Heuristic (A^2 + B^2 = C^2) = 
    
    A = Horizontal Distance
    B = Vertical Distance\
*/
// **************************************************************
// **************************************************************


//We should create a node pre-struct to implement in our class
//We can implement a nodestruct as a pseudo doubly linked list

struct NodeStruct {
    NodeStruct *prev;
    // f = TOTAL Cost of the node
    double f{0};
    // g = the distance between the current node and the start node
    double g{0}; 
    //h = the estimated distance from the current node to the end node
    double h{0}; 
    // We need a value to every node coordinate
    std::pair<int,int> coordinateValues;
    //
    NodeStruct *next;
};
//Purely for design reasons to make the interface access cleaner
// for e.g (std::get<0>(container) -> std::get<cost>(container) -- This makes more sense)
namespace selection
{
    enum traversal_iterator
    {
        cost = 0,
        x_val = 1,
        y_val = 2,
        g_val = 3,
        h_val = 4,
    };
}

class Node{
private:
    
    std::pair<int,int> startPosition, endPosition;
    //We could use unique pointers here, that way we can shallow copy and still have each variable
    //represent it's own area individual memory, than being associated from the class it's 
    //been copied from
    NodeStruct *rootNode, *currentNode,  *targetNode;
    std::vector<std::pair<int, int>> critical_path, blocked_path;
    //(0) = Most optimal traversal cost from current node to next
    //(1) = Next node's X_ value
    //(2) = Next node's Y_ value
    //(3) = Node's G value
    //(4) = Node's H value

    std::tuple<int,int,int,int,int> traversalInformation; 
    void assign_nodes();
    //We will never need to copy the contents. We can simply instantiate another instance of the class
    Node(const Node &rhs) = delete;
public:

    Node(int startPos_X, int startPos_Y, int endPos_X, int endPos_Y);
    //
    void add_node();
    void store_critical_path();
    void read_in_blocked(int x, int y) ;
    void store_traversal_cost(int x, int y, int cost, int g, int h);
    void pop_node();

    //
    bool check_coordinates(int x, int y, int cost, int g, int h);
    bool check() const;
    bool if_blocked(int,int) const;
    //
    int get_start_positionX_() const ;
    int get_start_positionY_() const ;
    int get_end_positionX_() const;
    int get_end_positionY_() const;
    int get_traversal_informationX_() const;
    int get_traversal_informationY_() const;
    int get_traversal_score() const;
    //
    std::vector<std::pair<int, int>> get_path() const;
    //
    ~Node();
};

