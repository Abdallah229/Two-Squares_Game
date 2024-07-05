#include <iostream>
#include <vector>
#include <iomanip>

// This game is played on a 4x4 board. Two players take turns placing rectangles
// (covering two squares) on the board. Only one rectangle can be on a square,
// and a square cannot be covered twice. The last player who can place a rectangle wins.
void Print_Status(const std::vector<std::vector<int>>& board);
bool Valid(std::vector<std::vector<int>>& board, int first_num, int second_num);
bool IsGameOver(const std::vector<std::vector<int>>& board);

int main() {
    // Initialize the game board with numbers representing positions
    std::vector<std::vector<int>> board = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
    int turn = 1; // Keep track of the current player's turn
    bool winning = false;
    while (true) {
        // Print the current board status
        Print_Status(board);
        int first_pos, second_pos;
        // Prompt the current player to enter their move
        std::cout << "Player " << turn << " Please enter Your Square :  " << std::endl;
        std::cout << "The First Position: ";
        std::cin >> first_pos;
        std::cout << "The Second Position: ";
        std::cin >> second_pos;

        // Validate the move entered by the player
        if (!Valid(board, first_pos, second_pos)) {
            continue;
        }

        // Switch turns to the other player
        turn = (turn == 1) ? 2 : 1;

        // Check if the game is over after the current player's move
        winning = IsGameOver(board);
        if (winning) {
            std::cout << "Game over! Player " << ((turn == 1) ? 2 : 1) << " wins!" << std::endl;
            break;
        }
    }

    return 0;
}

// Prints the current state of the game board in a formatted way
void Print_Status(const std::vector<std::vector<int>>& board) {
    // Determine the width needed for each cell on the board
    int cell_width = 3; // Assuming numbers are small enough; adjust if needed

    // Print the top border
    std::cout << std::string(25, '-') << std::endl;

    for (const auto& row : board) {
        // Print the left border for each row
        std::cout << "|";

        for (int num : row) {
            if (num == 'X') {
                // Print 'X' for covered positions
                std::cout << std::setw(cell_width) << "X" << std::setw(cell_width) << "|";
            } else {
                // Print the number for empty positions
                std::cout << std::setw(cell_width) << num << std::setw(cell_width) << "|";
            }
        }
        std::cout << std::endl;

        // Print the separator line after each row
        std::cout << std::string(25, '-') << std::endl;
    }
}

// Checks if the positions entered by the player are valid for placing a rectangle
bool Valid (std :: vector <std :: vector<int>> &  board ,int First_Num ,int Second_Num)
{   int First_Num_Vector = -1 , Second_Num_Vector = -1 ,Num_1_Pos = -1 ,Num_2_Pos = -1 ;
    // Find the positions of the first and second numbers on the board
    for (int i = 0; i < board.size() ; ++i) {
        for (int j = 0; j < board[i].size() ; ++j) {
            if (board[i][j] == First_Num) {
                First_Num_Vector = i ;
                Num_1_Pos =  j ;
            }
            if (board[i][j] == Second_Num) {
                Second_Num_Vector = i ;
                Num_2_Pos =  j ;
            }
        }
    }
    // Check if both positions are found
    if (First_Num_Vector == -1 || Second_Num_Vector == -1) {
        std::cout << "One or both of the positions are not found on the board." << std::endl;
        return false;
    }
        //Check if both positions are already covered
    else if ( board[First_Num_Vector] [Num_1_Pos] == 'X' ||  board[Second_Num_Vector][Num_2_Pos] == 'X' ) {
        std::cout << "One or both of the positions are already covered." << std::endl;
        return false ;
    }
    // Check if the positions are adjacent (either horizontally or vertically)
    bool adjacent = ((Num_1_Pos == Num_2_Pos - 1 || Num_1_Pos == Num_2_Pos +1 ) && First_Num_Vector == Second_Num_Vector )||
                    ((Num_1_Pos == Num_2_Pos ) && (First_Num_Vector == Second_Num_Vector -1 || First_Num_Vector == Second_Num_Vector +1)) ;
    if (adjacent){
        board[First_Num_Vector] [Num_1_Pos] = 'X' ;
        board[Second_Num_Vector][Num_2_Pos] = 'X' ;
        return true ;
    }
    else {
        std::cout << "The positions are not adjacent." << std::endl;
        return false;
    }
}
bool IsGameOver(const std::vector<std::vector<int>>& board) {
    // Check for any possible valid moves remaining only on empty spaces
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 'X') {
                continue; // Skip already filled positions
            }

            // Check right and down neighbors
            if (j + 1 < board[i].size() && board[i][j + 1] != 'X')
                return false;
            if (i + 1 < board.size() && board[i + 1][j] != 'X')
                return false;
        }
    }
    return true;
}