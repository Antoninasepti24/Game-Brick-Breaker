#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

// Base class
class BrickBreaker {
protected:
    int width, height;
    int paddleX;
    int ballX, ballY;
    int ballDirX, ballDirY;
    vector<vector<bool>> bricks;
    bool gameOver;
    int score;
    HANDLE hConsole;
    const char BALL_SYMBOL = '@'; // 🔧 Simbol bola bisa diganti sesuai selera

public:
    // Constructor
    BrickBreaker(int w = 30, int h = 15) : width(w), height(h) {
        paddleX = width / 2 - 3;
        ballX = width / 2;
        ballY = height - 3;
        ballDirX = 1;
        ballDirY = -1;
        gameOver = false;
        score = 0;

        bricks = vector<vector<bool>>(5, vector<bool>(width, true));
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    // Destructor
    virtual ~BrickBreaker() {
        cout << "coding by Antonina S\n";
    }

    void Draw() {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(hConsole, coord);

        cout << string(width + 2, '#') << "\n";
        for (int i = 0; i < height; i++) {
            cout << "#";
            for (int j = 0; j < width; j++) {
                if (i < 5 && bricks[i][j]) cout << "=";
                else if (i == ballY && j == ballX) cout << BALL_SYMBOL;
                else if (i == height - 1 && j >= paddleX && j < paddleX + 6) cout << "-";
                else cout << " ";
            }
            cout << "#\n";
        }
        cout << string(width + 2, '#') << "\n";
        cout << "Score: " << score << "\n";
    }

    void Input() {
        if (GetAsyncKeyState('A') & 0x8000) { 
            if (paddleX > 0) paddleX -= 4;
        }
        if (GetAsyncKeyState('D') & 0x8000) { 
            if (paddleX < width - 6) paddleX += 4;
        }
    }

    void Logic() {
        ballX += ballDirX;
        ballY += ballDirY;

        if (ballX <= 0 || ballX >= width - 1) ballDirX *= -1;
        if (ballY <= 0) ballDirY *= -1;

        if (ballY == height - 1 && ballX >= paddleX && ballX < paddleX + 6)
            ballDirY *= -1;

        if (ballY >= height) gameOver = true;

        if (ballY < 5 && bricks[ballY][ballX]) {
            bricks[ballY][ballX] = false;
            ballDirY *= -1;
            score++;
        }
    }

    virtual void Run() {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(10); // Bisa disesuaikan
        }
        cout << "Game Over! Final Score: " << score << endl;
    }
};

// Derived class
class AdvancedBrickBreaker : public BrickBreaker {
private:
    bool powerUpActive;

public:
    AdvancedBrickBreaker(int w = 30, int h = 15) : BrickBreaker(w, h) {
        powerUpActive = false;
    }

    ~AdvancedBrickBreaker() {
        cout << "Game selesai. Objek, Nina hilangkan.\n";
    }

    void ActivatePowerUp() {
        powerUpActive = true;
        cout << "Power-up Aktif!\n";
    }

    void Run() override {
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            if (score >= 5 && !powerUpActive) {
                ActivatePowerUp();
            }
            Sleep(50);
        }
        cout << "Game Over! Final Score: " << score << endl;
    }
};

int main() {
    AdvancedBrickBreaker game(30, 15);
    game.Run();
    return 0;
}
