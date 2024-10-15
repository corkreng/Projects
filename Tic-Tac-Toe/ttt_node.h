#include <vector>
using namespace std;



class Node {
    public:
        Node();
        Node(string board1, Node* parent1, char turn1);
        vector<Node*>child;
        void Print_board();
        char Peekturn();
        char PeekNextTurn();
        int size();
         string board;
         int score;
        //char board(int i);
    private:
       
        Node * parent ;
        char turn;
        
};
Node::Node(){
    board = "         ";
    parent = nullptr;
    turn ='X';
}

void Node::Print_board(){
    cout<< board[0]<<"|"<< board[1]<<"|"<< board[2]<<endl;
    cout<< "______"<<endl;
    cout<< board[3]<<"|"<< board[4]<<"|"<< board[5]<<endl;
    cout<< "______"<<endl;
    cout<< board[6]<<"|"<< board[7]<<"|"<< board[8]<<endl;
    cout<<endl;
}   





Node::Node(string board1, Node *parent1, char turn1){
    board = board1;
    parent = parent1;
    
    turn = turn1;

}
/*
string* Node::Peekboard(){
    return board;
}
*/
char Node::Peekturn(){
    return turn;
}
char Node::PeekNextTurn(){
    if(turn == 'O'){
        return 'X';
    }
    else{
        return 'O';
    }
}
int Node::size(){
    int size = child.size();

    return size;
}/*
string Node::board(int i){
    char character = board.at(i);

    return character;
}*/







class Stack{
    public:
        Stack();
        Node*pop();
        void push(Node* node);
        
        int top_pos;
    private:
        vector<Node*> stack;
        
};
Stack::Stack(){
    top_pos =0;
}



void Stack::push(Node* node){
    stack.push_back(node);
    top_pos += 1;
}

Node* Stack::pop(){
    top_pos = top_pos -1;
    return stack.at(top_pos);
}



