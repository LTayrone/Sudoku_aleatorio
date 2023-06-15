#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Tamanho do tabuleiro de Sudoku
#define BOARD_SIZE 9

// Fun��o para imprimir o tabuleiro
void printBoard(vector<vector<int>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                cout << "_ ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Fun��o para verificar se um n�mero pode ser colocado em uma determinada posi��o do tabuleiro
bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
    // Verificar a linha
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Verificar a coluna
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Verificar o quadrante 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Fun��o para resolver o Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    bool isEmpty = false;

    // Verificar se o tabuleiro est� completo
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // Se o tabuleiro est� completo, retorna verdadeiro
    if (!isEmpty) {
        return true;
    }

    // Tentar colocar n�meros de 1 a 9 na posi��o vazia
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0; // Se a atribui��o atual n�o leva a uma solu��o, redefinir para 0
        }
    }

    return false;
}

// Fun��o para gerar um tabuleiro de Sudoku aleatoriamente
void generateBoard(vector<vector<int>>& board) {
    // Limpar o tabuleiro
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.push_back(vector<int>(BOARD_SIZE, 0));
    }

    // Preencher valores iniciais aleat�rios
    srand(time(0));

    // Preencher c�lulas aleat�rias com n�meros v�lidos
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (rand() % 4 == 0) {
                int num = rand() % 9 + 1;
                if (isSafe(board, i, j, num)) {
                    board[i][j] = num;
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> board;
    generateBoard(board);

    cout << "Bem-vindo ao jogo de Sudoku!" << endl;
    cout << "Digite as coordenadas (linha e coluna) e o valor para preencher uma c�lula." << endl;
    cout << "Use valores de linha e coluna entre 1 e 9." << endl;
    cout << "Digite 0 (zero) para sair do jogo." << endl;
    cout << endl;

    while (true) {
        cout << "Tabuleiro atual:" << endl;
        printBoard(board);

        int row, col, num;
        cout << "Digite a linha (0 para sair): ";
        cin >> row;

        if (row == 0) {
            break;
        }

        cout << "Digite a coluna (0 para sair): ";
        cin >> col;

        if (col == 0) {
            break;
        }

        cout << "Digite o n�mero (0 para apagar): ";
        cin >> num;

        if (num == 0) {
            board[row - 1][col - 1] = 0;
        }
        else {
            if (isSafe(board, row - 1, col - 1, num)) {
                board[row - 1][col - 1] = num;
            }
            else {
                cout << "N�mero inv�lido!" << endl;
            }
        }

        cout << endl;
    }

    return 0;
}
