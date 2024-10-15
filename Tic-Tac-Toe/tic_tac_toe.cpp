
#include <iostream>
#include <stack>
#include "ttt_node.h"
using namespace std;

/*
void Printtree(Node *root){
    //level order 
    root->Print_board();
    cout<< "^^^ 1st layer"<<endl;

    vector<Node*> queue;
    for(int i =0; i < root->child.size(); ++i){
        Node * currNode = root->child.at(i);
        currNode->Print_board();
        queue.push_back(currNode);
        
    }
    
    cout<< "^^ second layer"<<endl;
    for(int j=0; j< queue.size();++j){
        Node* currNode = queue.at(j);
        for(int i =0; i < currNode->child.size(); ++i){
            Node * childNode = currNode->child.at(i);
            currNode->Print_board();
           
        }
        
    }

    
    
    
    cout<< "3rd layer "<<endl;

}
*/


int endGame(string board ){
    //const string board2 = board;
    //check row wise
    for(int i=0; i<9;i=i+3){
        if(board[i]==board[i+1]&&board[i]==board[i+2] && board[i]!=' '){
            if(board[i]=='O'){
                return 1;
            }
            else{
                return -2;
            }
        }
    }
        //check col-wise
    for(int i=0; i<3;++i){
        if(board[i]==board[i+3]&&board[i]==board[i+6] && board[i]!=' '){
            if(board[i]=='O'){
                return 1;
            }
            else{
                return -2;
            }
        }
    }
    //check adj
    if(board[0]==board[4] && board[0]==board[8] && board[0]!=' '){
         if(board[0]=='O'){
            return 1;
        }
        else{
            return -2;
        }
    }
    if(board[2]==board[4] && board[2]==board[6] && board[2]!= ' '){
         if(board[2]=='O'){
            return 1;
        }
        else{
            return -2;
        }
    }
    //check not tie
    for(int i =0; i<9; ++i){
        if(board[i]==' '){
            return 0;
        }
    }
    
    return -1; 
    //is tie^^
}

bool InVisitedStack(Node* node, vector<Node*> visited){
    for(int i=0; i <visited.size(); ++i ){
        if(node->board == visited[i]->board){
            return true;
        }
        
    }
    return false;
}

void print_board(string list){
    cout<< list[0]<<"|"<< list[1]<<"|"<< list[2]<<endl;
    cout<< "______"<<endl;
    cout<< list[3]<<"|"<< list[4]<<"|"<< list[5]<<endl;
    cout<< "______"<<endl;
    cout<< list[6]<<"|"<< list[7]<<"|"<< list[8]<<endl;

}

Node * MakeTree( string board){
    /* makes 3 layers of trees 
        must determine turn 


    */
   int nodecount =0;
   //cout<<"tree print start "<<endl;
    
    Node *root = new Node(board, nullptr, 'X');
    //root->Print_board();
    //cout<<"^^ first layer"<<endl;
    nodecount +=1;

    vector<Node*> queue;
    for(int i =0; i < 9; ++i){
        if (board[i]== ' '){
            string tempboard = board;
        
            tempboard[i] = 'O';
            Node * currNode = new Node(tempboard, root, root->PeekNextTurn());
            nodecount +=1;
            //currNode->Print_board();
             root->child.push_back(currNode);
            if (endGame(tempboard)==0){
               
                queue.push_back(currNode);
            }
            
        }
    }
    //cout<< "^^ second layer"<<endl;

    vector< Node*> queue2;
    for(int j=0; j< queue.size();++j){
        Node* rootchildNode = queue.at(j);
        for(int i =0; i < 9; ++i){
            if( rootchildNode->board[i]==' '){
                string tempboard = rootchildNode->board;
                

                tempboard[i] = rootchildNode->PeekNextTurn();
                Node * childNode = new Node(tempboard, rootchildNode, rootchildNode->PeekNextTurn());
                nodecount +=1;
                //childNode->Print_board();
                rootchildNode->child.push_back(childNode);
                if(endGame(tempboard)==0){
                    queue2.push_back(childNode);
                }
                
                
            } 
        }
        
    }
    //cout<< "third layer ^^"<<endl;
    for(int i=0; i < queue2.size(); ++i){
        Node* fourthlayerNode = queue2.at(i);
        for(int h=0; h < 9; ++h){
            if (fourthlayerNode->board[h]==' '){
                string tempboard2 = fourthlayerNode->board;
            
                tempboard2[h]= fourthlayerNode->PeekNextTurn();
                Node *grandchild = new Node(tempboard2, fourthlayerNode, fourthlayerNode->PeekNextTurn());
                grandchild->score = endGame(tempboard2);
                nodecount +=1;
                //grandchild->Print_board();
                fourthlayerNode->child.push_back(grandchild);
            
                /// ??? fix me how print 
            }
        }
    }

    cout<< "fourth layer^^ >> nodecount:"<< nodecount<<endl;
    
    return root;
}




int minimax( Node* root){
    int spot; 
    //Node *currNode= root; 
    
    
    
    for(int i =0; i < root->child.size(); ++i){
        
        Node * rootchild = root->child.at(i);

    
        int min= 1;
        for(int j =0; j < rootchild->child.size(); ++j){
            
            Node * grandchild = rootchild->child.at(j);
            
            int max = -2;
            for(int h=0; h< grandchild->child.size();++h){
                
                Node * greatgrandchild = grandchild->child.at(h);
                
                if ( max < greatgrandchild->score){
                    max = greatgrandchild->score;
                }
                
            }

            
            grandchild->score = max;
            

            if ( min > grandchild->score){
                min = grandchild->score;
            }

            

        }
       

        rootchild->score = min;
    }
    

    //find first layer maxer 
    int max = -2; 
    for(int i = 0; i <root->child.size(); ++i){
        Node * maxer = root->child.at(i);
        if (maxer->score > max){
            max = maxer->score;
        }
    }
    for(int i = 0; i <root->child.size(); ++i){
        Node * maxer = root->child.at(i);
        if (maxer->score == max){
            //find diff from root node 
            for(int j=0; j < 9; ++j){
                if (root->board[j] != maxer->board[j]){
                    spot = j;
                    break;
                }
            }

        }
    }

   
    return spot;



    
}


int main(){
    int endgame = 0;
    bool correctHoz=false;
    bool correctVer=false;
    bool validPos=false;
    bool you_sure;
    int who_wins=0; 
    string yousurestring;
    int posNum;
    int turn=0;
    char x_or_o;
    string endGameInput;
    string userHozpos;
    string userVertpos;
    string board = "         " ;

    //Node root = Node();
    print_board(board);
    //Node* root = MakeTree(board);
    //Printtree(root);







    while(endgame==0){
        turn +=1;
        you_sure = false;

        

        if ((turn % 2) ==0){
            
            Node* root = MakeTree(board);
            int minispot = minimax(root);
            cout<< minispot<<endl;
            
            cout<<endl;
            board[minispot] = 'O';
            print_board(board);
             
        }
        else{

            


            while(!you_sure){
                validPos=false;
                while(!validPos){
                    correctVer= false;
                    correctHoz = false;
                    while(!correctHoz){
                        cout<< "left, right or center: "<<endl;
                        cin>> userHozpos;
                        if ( userHozpos =="right"|| userHozpos=="left"|| userHozpos=="center"){
                            correctHoz = true;
                        }
                        if(userHozpos == "q"){
                            return 0;
                        }
                    }   
                    while(!correctVer){
                        cout<<"top, bottom. or center:"<<endl;
                        cin>> userVertpos;
                        if ( userVertpos =="top"|| userVertpos=="bottom"|| userVertpos=="center"){
                            correctVer = true;
                        }
                        
                    }
                    if(userVertpos=="bottom"){
                        posNum=6;
                    }
                    else if(userVertpos=="center"){
                        posNum=3;
                    }
                    else{
                        posNum=0;
                    }
                    if(userHozpos=="right"){
                        posNum=posNum+2;
                    }
                    else if(userHozpos=="center"){
                        posNum= posNum+1;
                    }
                    else{
                    }

                    if(board[posNum] == ' '){
                        validPos=true;
                    }
                    else{
                        cout<<"Position already taken"<<endl;
                    }
                }
                /*
                if(turn% 2){
                    x_or_o ='X';
                }
                else{
                    x_or_o='O';
                } */
                board[posNum]= 'X';
                print_board(board);

                validPos=false;
                while(!validPos){
                    cout<<"You Sure? (y or n)"<<endl;
                    cin>> yousurestring;
                    if(yousurestring =="y"){
                        you_sure=true;
                        validPos=true;
                    }
                    else if(yousurestring=="n"){
                        you_sure=false;
                        validPos=true;
                    }

                }
            }
            
        }

        

        endgame = endGame(board);
        cout<< "???endgame="<<endgame<<endl;
        if(endgame ==1){
            cout<< "O's Won!!!"<<endl;
        }
        else if (endgame==-2){
            cout<< "X's Won!!!"<< endl;
        }
        else if (endgame ==-1){
            cout<< "It's a tie!!!"<<endl;
        }
        



        


    }




    return 0;
}






