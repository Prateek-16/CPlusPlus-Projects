#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player{
    public :
        string name;
        char symbol;
        Player(string name, char symbol) : name(name), symbol(symbol) {}
};

class Board{
    private:
        vector<vector<char>> grid;
        // vector<vector<char>> board(3, vector<char>(3, '-')); I cant do this directly , i have to initalize using constructor 
    public :
        Board() {
        this->grid = vector<vector<char>>(3, vector<char>(3, ' '));
        }

        void display() {
            for(int i = 0; i < 3;i++){
                for(int j = 0; j < 3;j++){
                    cout<<grid[i][j];
                    if (j < 2) cout << " | ";
                }
                cout<<endl;
                if (i < 2) cout << "--|---|--" << endl;
            }
        }
        
        bool makeMove(int row , int col , char symbol){
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' '){
                return false;
            }
            grid[row][col] = symbol;
            return true;
        }

        bool isDraw() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[i][j] == ' ')
                        return false;
                }
            }
            return true;
        }

        bool isWin(char symbol){
            //Check Horizontal and vertical
            for(int i = 0 ; i < 3 ; i++){
                //Horizontal
                if(grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol){
                    return true;
                }
                //Vertical
                if(grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol){
                    return true;
                }
            }
            //Check Diagonals
            if(grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol){
                return true;
            }
            if(grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol){
                return true;
            }
            return false;   //No condition is satisfied
        }

        bool isEmpty(int row, int col){
            return grid[row][col] == ' ';

        }
};

class Game{
    private:
        Board board;
        Player player1;
        Player player2;
        Player* currentPlayer;
    
    public:
        Game(Player player1,Player player2) : player1(player1), player2(player2) {}

        void play(){
            int row, col;
            bool gameOver = false;

            board.display();
            while(!gameOver){
                currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
                cout << currentPlayer->name << " (" << currentPlayer->symbol << "), enter your move (row and column): ";
                cin >> row >> col;
                char symbol = currentPlayer->symbol;
                if(!board.makeMove(row - 1,col - 1,symbol)){
                    cout << "Invalid Move" << endl;
                    continue;
                }
                board.display();

                if(board.isWin(symbol)){
                    cout << "Game Over" << endl;
                    gameOver = true;
                }
                else if(board.isDraw()){
                    cout << "Game Draw" << endl;
                    gameOver = true;
                } 
            }
        }
};

int main(){
    string p1, p2;
    cout<<"Enter the name of Player 1 : ";
    cin>>p1;

    cout<<"Enter the name of Player 2 : ";
    cin>>p2;

    Player player1(p1, 'X');
    Player player2(p2, 'O');

    Game game(player1, player2);
    game.play();
    return 0;
}