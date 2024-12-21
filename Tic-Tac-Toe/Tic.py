import copy

def print_board(board):
    print(board[0] + ' | ' + board[1] + ' | ' + board[2])
    print("-" * 9)
    print(board[3] + ' | ' + board[4] + ' | ' + board[5])
    print("-" * 9)
    print(board[6] + ' | ' + board[7] + ' | ' + board[8])

def endgame(board):
    #checking horizontally
    for i in range(3):
        if board[0 + i*3] == board[1+ i*3 ] == board[2+ i*3] and board[0+ i*3] != ' ':
            return 1 if board[0 + i * 3] == 'X' else -1


    #checking vertically
    for i in range(3):
        if board[i] == board[i +3] == board[i+6] and board[i] != ' ':
            return 1 if board[i] == 'X' else -1
        
    #checking diagonaling
    if board[0] == board[4] == board[8] and board[0] != ' ':
        return 1 if board[0] == 'X' else -1
    if board[2] == board[4] == board[6] and board[2] != ' ':
        return 1 if board[2] == 'X' else -1
    return 0

class TreeNode:
    def __init__(self, board, spot):
        self.score = 0
        self.spot = spot
        self.board = board
        self.children = []

    def add_child(self, child_node):
        self.children.append(child_node)
    
    def update_score(self, new_score):
        self.score = new_score

    def to_dict(self):
        """
        Convert the tree node and its children to a dictionary format.
        """
        return {
            "score": self.score,
            "board": self.board,
            "children": [child.to_dict() for child in self.children]
        }

# Create the tree
def build_tree_recursive(board, depth, turn, spot):
    # Create the current node
    node = TreeNode(board,spot)

    # Check if this is an endgame state or we've reached maximum depth
    node_score = endgame(node.board)
    if node_score != 0 :
        node.score = node_score
        return node
    if ' ' not in board or depth == 0 :  # No more moves (draw)
        node.score = 0
        return node
    # Generate child nodes (customize child generation logic)
    for i in range(9):  # Example: Add scores of +1, +2, +3
        #check avialable spots
        if board[i]==' ':
            temp_board = copy.deepcopy(board)
            if turn % 2 == 0:
                temp_board[i] ='X'
                child_node = build_tree_recursive(temp_board, depth - 1,turn +1, i)
                node.add_child(child_node)
            else:
                temp_board[i] ='O'
                child_node = build_tree_recursive(temp_board, depth - 1, turn +1, i)
                node.add_child(child_node)
        

    return node

def MiniMax( root, turn):
    max_score = -10
    min_score = 10
    if len(root.children)==0:
        return None 
    else:
        for i in range(len(root.children)):
            child = root.children[i]
            if turn %2 == 0:
                #find max
                if child.score > max_score:
                    max_score = child.score
            else:
                #find min score 
                if child.score < min_score:
                    min_score = child.score
            MiniMax(child, turn +1)
    #find max or min of parent
    if turn % 2 ==0:
        root.score = max_score
    else:
        root.score = min_score
        
#MiniMax(root, 0)
def Get_best_Move(root,turn):
    min_score = 10
    max_score = -10
    if turn ==0:
        return 4
    if turn%2 == 0:
        for i in range(len(root.children)):
            if root.children[i].score > max_score:
                max_score = root.children[i].score
        for j in range(len(root.children)):
            if root.children[j].score == max_score:
                return root.children[j].spot

    else:
        for i in range(len(root.children)):
            if root.children[i].score < min_score:
                min_score = root.children[i].score
        for j in range(len(root.children)):
            if root.children[j].score == min_score:
                return root.children[j].spot
    print("best move error")
    return None
    
#we need recursion to go to tranverse through tree and update scores based on
# leaves score 

def X_OR_O():
    while True:
        user_input = input("Would you like to be X's (Y/N)").strip().upper()
        if user_input in ['Y', 'N']:
            return user_input
        else:
            print("Invalid input. Please enter 'Y' or 'N'.")

def user_spot(board):
    while True:
        spot = int(input("Enter number(0-8): "))
        if board[spot] == ' ':
            return spot
        else:
            print("Spot already taken, try again.")



def main():
    board = [' ',' ',' ',' ',' ',' ',' ',' ',' ']
    print("Welcome to Tic Tac Toe!")
    x_or_o = X_OR_O()
    print_board(board)
    for turn in range(9):
        
        player = "X" if turn % 2 == 0 else "O"
        print(f"Player {player}'s turn:")
        if player == "X" and x_or_o == 'Y':
            spot = user_spot(board)
            board[int(spot)] = 'X'
        elif player == "X" and x_or_o == 'N':     
            root =build_tree_recursive(board,5,turn, 0)
            MiniMax(root,turn)
            spot = Get_best_Move(root,turn)
            board[spot] = 'X'
        elif player == "O" and x_or_o == 'Y':
            root =build_tree_recursive(board,5,turn,0)
            MiniMax(root,turn)
            spot = Get_best_Move(root,turn)
            board[spot] = 'O'
        else:
            spot = user_spot(board)
            board[int(spot)] = 'O'
        
        print_board(board)
        winner = endgame(board)

        if winner==1:
            print("Player X wins!")
            return
        if winner == -1:
            print("Player O wins!")
            return
    print("It's a tie!")

main()