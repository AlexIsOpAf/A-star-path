#include "Node.h" 
#include <iostream>
#include <utility>
#include <vector>


//Purely for design reasons to make the interface access cleaner 
// for e.g (std::get<0>(container) -> std::get<cost>(container) -- This makes more sense)

using namespace selection;


Node::Node(int startPos_X, int startPos_Y, int endPos_X, int endPos_Y): 
startPosition{startPos_X, startPos_Y}, endPosition{endPos_X, endPos_Y},
traversalInformation { std::make_tuple(0, 0, 0,0,0)} {

    assign_nodes();

}
/*
    Emulating a doubly linked list
    When Node class is created, we create 2 *temps on the heap
    Rootnode is equivalent to "HEAD"
    Targetnode is equivalent to "TAIL"
    Because it's not always certain that we can reach target, we need a Currentnode
    as an iterator
*/
void Node::assign_nodes(){
    NodeStruct *temp = new NodeStruct;
    rootNode = temp;
    rootNode->prev = nullptr;
    rootNode->coordinateValues = startPosition;
    rootNode->next = targetNode;

    currentNode = rootNode;

    NodeStruct *temp2 = new NodeStruct;
    targetNode = temp2;
    targetNode->next = nullptr;
    targetNode->prev = rootNode;
    targetNode->coordinateValues = endPosition;
}
//*******************Get methods************************
int Node::get_traversal_score() const { return (std::get<cost>(traversalInformation)); }
int Node::get_traversal_informationX_() const {return (std::get<x_val>(traversalInformation));}
int Node::get_traversal_informationY_() const {return (std::get<y_val>(traversalInformation));}
int Node::get_start_positionX_() const{return startPosition.first;}
int Node::get_start_positionY_() const{ return startPosition.second;}
int Node::get_end_positionX_() const{ return endPosition.first; }
int Node::get_end_positionY_() const{ return endPosition.second;}
std::vector<std::pair<int, int>> Node::get_path() const {return critical_path;}
//*******************Get methods************************

void Node::add_node() {

    NodeStruct *temp = new NodeStruct;
    temp->next = targetNode;
    temp->prev = currentNode;
    currentNode->next = temp;
    currentNode = temp;
    targetNode->prev = temp;

    //X coordinates
    currentNode->f = std::get<cost>(traversalInformation);
    currentNode->g = std::get<g_val>(traversalInformation);
    currentNode->h = std::get<h_val>(traversalInformation);

    currentNode->coordinateValues.first = std::get<x_val>(traversalInformation);
    //Y coordinates
    currentNode->coordinateValues.second = std::get<y_val>(traversalInformation);
    if (currentNode->coordinateValues == targetNode->coordinateValues){
        currentNode = targetNode;
    }

    std::cout << "Position Added: " << currentNode->coordinateValues.first << ' ' << 
    currentNode->coordinateValues.second << "\nNode's values(F,G,H): " << currentNode->f 
    << ' ' <<  currentNode->g << ' ' << currentNode->h << std::endl; 
}

//Because this is a doubly linked list
//the deletion becomes trivial
void Node::pop_node() {
    NodeStruct *temp = new NodeStruct;

    std::cout << "Popping off : " << currentNode->coordinateValues.first << ' ';
    std::cout << currentNode->coordinateValues.second << std::endl;

    temp = currentNode;
    currentNode = temp->prev;
    temp->prev = nullptr;
    currentNode->next = targetNode;
    targetNode->prev = currentNode;
    temp->next = nullptr;
    delete temp;

    std::cout << "Position Current is atlea: " << currentNode->coordinateValues.first << ' ' << 
    currentNode->coordinateValues.second << "\nNode's values(F,G,H): " << currentNode->f 
    << ' ' <<  currentNode->g << ' ' << currentNode->h << std::endl; 

    store_traversal_cost(currentNode->coordinateValues.first,currentNode->coordinateValues.second,
    currentNode->f, currentNode->g, currentNode->h);

}

bool Node::check_coordinates(int x, int y, int cost, int g, int h) {
    if (x == endPosition.first && y == endPosition.second){
        traversalInformation = std::make_tuple(cost,x,y, g, h);
        return true;
    }
    return false;
}
//Return true if the function has stored the traversal information
//Return false if the function has to second check due to cost's being the same
void Node::store_traversal_cost(int x, int y, int cost, int g, int h) {
    traversalInformation = std::make_tuple(cost, x, y, g, h);
}
void Node::read_in_blocked(int x, int y) {
    blocked_path.push_back(std::pair<int,int>(x,y));
}
//If the value in the traversal information is equal to a blocked area
//go to previous position and re-calibrate
bool Node::if_blocked(int x, int y) const{
    for (const auto& item : blocked_path)
        if (x == item.first && y == item.second)
            return true;
    return false;
}

void Node::store_critical_path(){
    NodeStruct *temp = new NodeStruct;
    temp = rootNode;
    while (temp != targetNode)
    {
        critical_path.push_back(temp->coordinateValues);
        temp = temp->next;
    }
    temp = nullptr;
    delete temp;
}

bool Node::check()const {
    if (currentNode != targetNode) 
        return false;
    return true;
}

Node::~Node() {  
    // NodeStruct *temp = new NodeStruct;
    NodeStruct *temp = new NodeStruct;
    while (rootNode != targetNode){
        temp = rootNode->next;
        rootNode->next = nullptr;
        temp->prev = nullptr;
        delete rootNode;
        rootNode = temp;
    }
    std::cout << currentNode->coordinateValues.first << ' ';
    std::cout << currentNode->coordinateValues.second << std::endl;
    delete targetNode; 
    rootNode = nullptr;
    currentNode = nullptr;
    targetNode = nullptr;
    temp = nullptr;
    std::cout << "Destructor called " << std::endl;
}

