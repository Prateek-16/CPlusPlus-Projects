#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

class Game {
private:
    map<int, int> snakes;               // Maps snake head to tail
    map<int, int> ladders;              // Maps ladder start to end
    vector<string> players;             // List of player names
    map<string, int> playerPositions;  // Maps player name to position
    queue<string> turnQueue;           // Queue for player turns

    int rollDice() {
        return (rand() % 6) + 1; // Roll a dice and get a number between 1 and 6
    }

public:
    // Constructor to initialize game state
    Game(const map<int, int>& sn, const map<int, int>& lad, const vector<string>& play)
        : snakes(sn), ladders(lad), players(play) {
        // Initialize player positions and turn queue
        for (const auto& player : players) {
            playerPositions[player] = 0;  // Set initial position to 0
            turnQueue.push(player);  // Add player to the turn queue
        }
        srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    }

    void play() {
        while (true) {
            string currentPlayer = turnQueue.front();
            turnQueue.pop();

            int diceRoll = rollDice();

            int currentPosition = playerPositions[currentPlayer];
            int newPosition = currentPosition + diceRoll;

            // If the move exceeds the board, the player stays in the same position
            if (newPosition > 100) {
                cout << currentPlayer << " cannot move beyond 100." << endl;
                turnQueue.push(currentPlayer);  // Re-add player to the queue
                continue;
            }

            // Check for snakes and ladders
            if (snakes.find(newPosition) != snakes.end()) {
                newPosition = snakes[newPosition];
            } else if (ladders.find(newPosition) != ladders.end()) {
                newPosition = ladders[newPosition];
            }

            playerPositions[currentPlayer] = newPosition;
            cout << currentPlayer << " Rolled a " << diceRoll << " and moved from " << currentPosition << " to " << newPosition << endl;

            // Check for win condition
            if (newPosition == 100) {
                cout << currentPlayer << " wins the game" << endl;
                break;
            }

            turnQueue.push(currentPlayer);  // Re-add player to the queue
        }
    }
};

int main() {
    int s, l, p;

    cout << "Enter the number of snakes: ";
    cin >> s;

    map<int, int> snakes;
    cout << "Enter the head and tail positions of each snake:" << endl;
    for (int i = 0; i < s; i++) {
        int head, tail;
        cin >> head >> tail;
        snakes[head] = tail;
    }

    cout << "Enter the number of ladders: ";
    cin >> l;

    map<int, int> ladders;
    cout << "Enter the start and end positions of each ladder:" << endl;
    for (int i = 0; i < l; i++) {
        int start, end;
        cin >> start >> end;
        ladders[start] = end;
    }

    cout << "Enter the number of players: ";
    cin >> p;

    vector<string> players;
    cout << "Enter the names of the players:" << endl;
    for (int i = 0; i < p; i++) {
        string name;
        cin >> name;
        players.push_back(name);
    }

    // Create and start the game
    Game game(snakes, ladders, players);
    game.play();

    return 0;
}
