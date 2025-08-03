// Includes principais
#include "freeglut-3.4.0/include/GL/glut.h"
#include "glu-903/include/GL/glu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Constantes
#define MAP_SIZE 20
#define TILE_SIZE 30
#define NUM_INIMIGOS 3
#define TOTAL_ROUNDS 3

// Tipos e variáveis globais
typedef struct { int x, y; } Inimigo;

// Mapa
int mapas[TOTAL_ROUNDS][MAP_SIZE][MAP_SIZE] = {
    {
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,2,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,5,1},
     {1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1},
     {1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1},
     {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
     {1,0,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
     {1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1},
     {1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
     {1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
     {1,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
     {1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
     {1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    },
    {
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,2,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,5,1},
     {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
     {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
     {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1},
     {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1},
     {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1},
     {1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0,1},
     {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1},
     {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1},
     {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1},
     {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1},
     {1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
     {1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
     {1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    },
    {
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,2,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,5,1},
     {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
     {1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
     {1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
     {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
     {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
     {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
     {1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1},
     {1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1},
     {1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    }
};

int faseAtual = 0;
int playerX = 1, playerY = 1;
int gameOver = 0;
int gameWon = 0;
int modoDesenvolvedor = 0;
Inimigo inimigos[NUM_INIMIGOS];

// Funções utilitárias
double distancia(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int podeMover(int x, int y) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
        return 0;
    if (modoDesenvolvedor)
        return 1;
    int tile = mapas[faseAtual][y][x];
    return tile == 0 || tile == 5;
}

int verificarColisao() {
    if (modoDesenvolvedor) return 0;
    for (int i = 0; i < NUM_INIMIGOS; i++)
        if (playerX == inimigos[i].x && playerY == inimigos[i].y)
            return 1;
    return 0;
}

// Inicializações
void inicializarPosicoes() {
    playerX = 1;
    playerY = 1;
}

void reiniciarInimigos() {
    for (int i = 0; i < NUM_INIMIGOS; i++) {
        do {
            inimigos[i].x = rand() % MAP_SIZE;
            inimigos[i].y = rand() % MAP_SIZE;
        } while (mapas[faseAtual][inimigos[i].y][inimigos[i].x] != 0 || (inimigos[i].x == playerX && inimigos[i].y == playerY));
    }
}

// Eventos de jogo
void vencerJogo() {
    gameWon = 1;
    glutPostRedisplay();
}

void perderJogo() {
    gameOver = 1;
    glutPostRedisplay();
}

void moverJogador(int dx, int dy) {
    if (gameOver || gameWon) return;

    int nx = playerX + dx, ny = playerY + dy;

    if (podeMover(nx, ny)) {
        playerX = nx;
        playerY = ny;

        if (verificarColisao()) {
            perderJogo();
            return;
        }

        if (mapas[faseAtual][playerY][playerX] == 5) {
            if (++faseAtual >= TOTAL_ROUNDS) {
                vencerJogo();
                return;
            }
            inicializarPosicoes();
            reiniciarInimigos();
        }
    }
    glutPostRedisplay();
}

void moverInimigos() {
    if (gameOver || gameWon) return;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < NUM_INIMIGOS; i++) {
        int bestX = inimigos[i].x, bestY = inimigos[i].y;
        double bestDist = distancia(bestX, bestY, playerX, playerY);

        for (int d = 0; d < 4; d++) {
            int nx = inimigos[i].x + dx[d], ny = inimigos[i].y + dy[d];
            if (podeMover(nx, ny)) {
                double dist = distancia(nx, ny, playerX, playerY);
                if (dist < bestDist) {
                    bestX = nx;
                    bestY = ny;
                    bestDist = dist;
                }
            }
        }
        inimigos[i].x = bestX;
        inimigos[i].y = bestY;
    }

    if (verificarColisao()) perderJogo();

    glutPostRedisplay();
}

// Timer
void timer(int v) {
    moverInimigos();
    glutTimerFunc(500, timer, 0);
}

// Rendering
void desenharQuadrado(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2i(x * TILE_SIZE, y * TILE_SIZE);
        glVertex2i((x + 1) * TILE_SIZE, y * TILE_SIZE);
        glVertex2i((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
        glVertex2i(x * TILE_SIZE, (y + 1) * TILE_SIZE);
    glEnd();
}

void desenharTexto(float x, float y, const char *texto) {
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    while (*texto)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto++);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver) {
        desenharTexto(180, 250, "Voce perdeu o jogo!");
    } else if (gameWon) {
        desenharTexto(180, 250, "Voce venceu todas as fases!");
    } else {
        for (int y = 0; y < MAP_SIZE; y++)
            for (int x = 0; x < MAP_SIZE; x++) {
                int tile = mapas[faseAtual][y][x];
                if (tile == 1) desenharQuadrado(x, y, 0.2f, 0.2f, 0.2f);
                else if (tile == 5) desenharQuadrado(x, y, 0, 1, 0);
            }

        desenharQuadrado(playerX, playerY, modoDesenvolvedor ? 0.6f : 0, 0, modoDesenvolvedor ? 0.6f : 1);

        for (int i = 0; i < NUM_INIMIGOS; i++)
            desenharQuadrado(inimigos[i].x, inimigos[i].y, 1, 0, 0);
    }

    glutSwapBuffers();
}

// Input
void tecladoEspecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: moverJogador(0, -1); break;
        case GLUT_KEY_DOWN: moverJogador(0, 1); break;
        case GLUT_KEY_LEFT: moverJogador(-1, 0); break;
        case GLUT_KEY_RIGHT: moverJogador(1, 0); break;
    }
}

void tecladoNormal(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    else if (key == 'r' || key == 'R') {
        faseAtual = gameOver = gameWon = modoDesenvolvedor = 0;
        inicializarPosicoes();
        reiniciarInimigos();
        glutPostRedisplay();
    }
    else if (key == 'd' || key == 'D') {
        modoDesenvolvedor = !modoDesenvolvedor;
        glutPostRedisplay();
    }
}
// Função principal
int main(int argc, char **argv) {
    srand(time(NULL));
    inicializarPosicoes();
    reiniciarInimigos();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE);
    glutCreateWindow("Labirinto Inteligente");
    gluOrtho2D(0, MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE, 0);

    glutDisplayFunc(display);
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(tecladoNormal);
    glutTimerFunc(500, timer, 0);

    glutMainLoop();
    return 0;
}
