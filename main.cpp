#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

// --- CONFIGURATION ---
const int ROWS = 10;
const int COLS = 10;
const int CELL_SIZE = 50;
const int OFFSET_X = 150;
const int OFFSET_Y = 50;

float colors[][3] = {
    {0.9, 0.2, 0.2}, {0.2, 0.9, 0.2}, {0.2, 0.2, 0.9}, 
    {0.9, 0.9, 0.2}, {0.9, 0.2, 0.9}, {0.1, 0.1, 0.1} // 5 is 'Empty'
};

// --- GAME DATA ---
int grid[ROWS][COLS];
int score = 0;
float gameTimer = 60.0f; // 60 seconds game
bool gameOver = false;
int selR = -1, selC = -1; 

// --- BACKEND LOGIC ---
void InitGrid() {
    srand(time(0));
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = rand() % 5;
}

void ApplyGravity() {
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            if (grid[i][j] == 5) { // If empty
                for (int k = i; k < ROWS - 1; k++)
                    grid[k][j] = grid[k + 1][j];
                grid[ROWS - 1][j] = rand() % 5; // Fill top with new
            }
        }
    }
}

void CheckMatches() {
    vector<pair<int, int>> toClear;
    // Horizontal scan
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 2; j++) {
            if (grid[i][j] != 5 && grid[i][j] == grid[i][j+1] && grid[i][j] == grid[i][j+2]) {
                toClear.push_back({i, j}); toClear.push_back({i, j+1}); toClear.push_back({i, j+2});
            }
        }
    }
    // Vertical scan
    for (int i = 0; i < ROWS - 2; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] != 5 && grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j]) {
                toClear.push_back({i, j}); toClear.push_back({i+1, j}); toClear.push_back({i+2, j});
            }
        }
    }
    
    if (!toClear.empty()) {
        for (auto p : toClear) grid[p.first][p.second] = 5;
        score += toClear.size() * 10;
        ApplyGravity();
    }
}

// --- FRONTEND ---
void DrawCircle(float x, float y, float r, float* c) {
    glColor3fv(c);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i += 10)
        glVertex2f(x + r * cos(i * M_PI / 180), y + r * sin(i * M_PI / 180));
    glEnd();
}

void Display() {
    glClearColor(0.05, 0.05, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver) {
        string msg = "GAME OVER! FINAL SCORE: " + to_string(score);
        glColor3f(1, 0, 0);
        glRasterPos2f(250, 300);
        for (char c : msg) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    } else {
        // UI
        glColor3f(1, 1, 1);
        string ui = "Score: " + to_string(score) + " | Time: " + to_string((int)gameTimer) + "s";
        glRasterPos2f(OFFSET_X, 570);
        for (char c : ui) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        

        // Grid
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                int x = OFFSET_X + j * CELL_SIZE;
                int y = OFFSET_Y + i * CELL_SIZE;
                
                // Draw Cell
                if (i == selR && j == selC) glColor3f(0.3, 0.3, 0.3);
                else glColor3f(0.15, 0.15, 0.15);
                glBegin(GL_LINE_LOOP);
                glVertex2i(x, y); glVertex2i(x+50, y); glVertex2i(x+50, y+50); glVertex2i(x, y+50);
                glEnd();

                if (grid[i][j] != 5)
                    DrawCircle(x + 25, y + 25, 18, colors[grid[i][j]]);
            }
        }
    }
    glutSwapBuffers();
}

// --- CONTROLS ---
void Mouse(int button, int state, int x, int y) {
    if (gameOver) return;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int r = (600 - y - OFFSET_Y) / CELL_SIZE;
        int c = (x - OFFSET_X) / CELL_SIZE;

        if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
            if (selR == -1) { selR = r; selC = c; }
            else {
                if (abs(selR - r) + abs(selC - c) == 1) {
                    swap(grid[selR][selC], grid[r][c]);
                    CheckMatches();
                }
                selR = -1; selC = -1;
            }
        }
    }
}

void Timer(int v) {
    if (!gameOver) {
        gameTimer -= 0.016f; // Decrease based on ~60fps
        if (gameTimer <= 0) gameOver = true;
        CheckMatches(); // Constant check for falling matches
    }
    glutPostRedisplay();
    glutTimerFunc(16, Timer, 0);
}

int main(int argc, char** argv) {
    InitGrid();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cookie Crash: Gravity Edition");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}
