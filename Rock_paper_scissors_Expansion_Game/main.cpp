//
//  main.cpp
//  Rock_paper_scissors_Expansion_Game
//
//  Created by 세광 on 2021/08/06.
//

#include <iostream>
#include <fstream>
#include <random>
#include <string>

#define win 1
#define draw 0
#define lose -1
#define array_size 1024

using namespace std;

class Game {
public:
    Game();
    ~Game();
    
    void Input();
    void Output();
    void SetNumber();
    void DecideWinner();

    string Strategy(int);
    int Random(int, int);
    int Judgement(string, string);
    
private:
    int index, count;
    int **arr;
    int *temp, *n;
    string a[array_size][array_size];
};

int main() {
    Game *game = new Game;
    game->Input();
    game->SetNumber();
    game->DecideWinner();
    game->Output();
    delete game;
}

Game::Game() : index(0), count(0) {}

Game::~Game() {
    for (size_t i = 0; i < index; i++) delete arr[i];
    delete [] n;
    delete [] temp;
    delete [] arr;
    n = NULL;
    temp = NULL;
    arr = NULL;
}

void Game::Input() {
    ifstream fin("input2.txt");
    if (fin.fail()) {
        cout << "Could not open input2.txt file" << endl;
        exit(1);
    }
    if (fin.is_open()) {
        n = new int[array_size];
        temp = new int[array_size];
        arr = new int*[array_size];
        while (!fin.eof()) {
            fin >> n[index];
            arr[index] = new int[n[index]];
            for (size_t i = 0; i < n[index]; i++) {
                fin >> arr[index][i];
            }
            index++;
        }
    }
    fin.close();
}

void Game::Output() {
    ofstream fout("output.txt");
    for (size_t i = 0; i < index; i++) fout << '\n' << temp[i] << '\n';
    fout.close();
}

void Game::SetNumber() {
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < n[i]; j++) {
            a[i][j] = Strategy(arr[i][j]);
        }
    }
}

void Game::DecideWinner() {
    for (size_t i = 0; i < index; i++) {
        for (size_t j = 0; j < n[i]; j++) {
            for (size_t k = 0; k < n[i]; k++) {
                count += Judgement(a[i][j], a[i][k]);
            }
            if (count == n[i] - 1) {
                temp[i] = arr[i][j];
                count = 0;
                break;
            } else temp[i] = 0;
            count = 0;
        }
    }
}

string Game::Strategy(int number) {
    if (number == 1) return "scissor";
    else if (number == 2) return "rock";
    else if (number == 3) return "paper";
    else if (number == 4) return "lizard";
    else if (number == 5) return "spock";
    else if (number == 6) return Strategy(Random(1, 2));
    else if (number == 7) return Strategy(Random(3, 5));
    else if (number == 8) return Strategy(Random(1, 3));
    else return Strategy(Random(1, 5));
}

int Game::Random(int x, int y) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(x, y);
    return dis(gen);
}

int Game::Judgement(string x, string y) {
    if (x == "rock") {
        if (y == "scissor" || y == "lizard") return win;
        else if (y == "spock" || y == "paper") return lose;
        else return draw;
    }
    if (x == "scissor") {
        if (y == "paper" || y == "lizard") return win;
        else if (y == "rock" || y == "spock") return lose;
        else return draw;
    }
    if (x == "paper") {
        if (y == "rock" || y == "spock") return win;
        else if (y == "scissor" || y == "lizard") return lose;
        else return draw;
    }
    if (x == "lizard") {
        if (y == "spock" || y == "paper") return win;
        else if (y == "scissor" || y == "rock") return lose;
        else return draw;
    }
    if (x == "spock") {
        if (y == "scissor" || y == "rock") return win;
        else if (y == "paper" || y == "lizard") return lose;
        else return draw;
    }
    else return -2;
}
