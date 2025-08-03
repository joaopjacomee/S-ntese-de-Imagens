// Define a biblioteca principal do OpenGL e demais bibliotecas necessárias
#include "freeglut-3.4.0/include/GL/glut.h"
#include "glu-903/include/GL/glu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define constantes para tamanho do mapa, dos tiles, número de inimigos e total de fases
#define MAP_SIZE 20
#define TILE_SIZE 30
#define NUM_INIMIGOS 3
#define TOTAL_ROUNDS 3

// Matriz tridimensional que armazena os mapas de cada fase
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

// Variáveis para controlar o estado atual do jogo
int faseAtual = 0;             // Índice da fase atual
int playerX = 1, playerY = 1;  // Posição do jogador no mapa
int gameOver = 0;              // Flag de fim de jogo por derrota
int gameWon = 0;               // Flag de fim de jogo por vitória
int modoDesenvolvedor = 0;     // Modo desenvolvedor (atravessa paredes)

// Estrutura para representar inimigos
typedef struct { int x, y; } Inimigo;

// Array com os inimigos
Inimigo inimigos[NUM_INIMIGOS];

// Função para posicionar o jogador no início da fase
void inicializarPosicoes() {
    playerX = 1;
    playerY = 1;
}

// Função que reinicializa a posição dos inimigos aleatoriamente
void reiniciarInimigos() {
    for (int i = 0; i < NUM_INIMIGOS; i++) {
        do {
            inimigos[i].x = rand() % MAP_SIZE;
            inimigos[i].y = rand() % MAP_SIZE;
        } while (mapas[faseAtual][inimigos[i].y][inimigos[i].x] != 0 || (inimigos[i].x == playerX && inimigos[i].y == playerY));
    }
}

// Função que verifica se uma posição no mapa é válida para mover
int podeMover(int x, int y) {
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
        return 0;
    if (modoDesenvolvedor)
        return 1;
    int tile = mapas[faseAtual][y][x];
    return tile == 0 || tile == 5;
}

// Função para desenhar um quadrado colorido em uma posição específica
void desenharQuadrado(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2i(x * TILE_SIZE, y * TILE_SIZE);
        glVertex2i((x + 1) * TILE_SIZE, y * TILE_SIZE);
        glVertex2i((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
        glVertex2i(x * TILE_SIZE, (y + 1) * TILE_SIZE);
    glEnd();
}


// Função chamada quando o jogador vence todas as fases
void vencerJogo() {
    gameWon = 1;
    glutPostRedisplay();
}

// Função chamada quando o jogador perde
void perderJogo() {
    gameOver = 1;
    glutPostRedisplay(); // Força redesenho da tela
}

// Verifica se algum inimigo colidiu com o jogador
int verificarColisao() {
    if (modoDesenvolvedor) return 0;
    for (int i = 0; i < NUM_INIMIGOS; i++)
        if (playerX == inimigos[i].x && playerY == inimigos[i].y)
            return 1;
    return 0;
}

// Move o jogador se possível, verifica fim de fase ou colisões
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

// Calcula a distância Euclidiana entre duas posições
double distancia(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

// Move os inimigos em direção ao jogador, se possível
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

// Função de temporização para mover os inimigos em intervalos
void timer(int v) {
    moverInimigos();
    glutTimerFunc(500, timer, 0); // Chama a si mesma novamente após 500ms
}

// Escreve texto na tela
void desenharTexto(float x, float y, const char *texto) {
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    while (*texto)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto++);
}

// Função principal de desenho da tela
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
                if (tile == 1) desenharQuadrado(x, y, 0.2f, 0.2f, 0.2f); // parede
                else if (tile == 5) desenharQuadrado(x, y, 0, 1, 0);    // saída
            }

        desenharQuadrado(playerX, playerY, modoDesenvolvedor ? 0.6f : 0, 0, modoDesenvolvedor ? 0.6f : 1); // jogador

        for (int i = 0; i < NUM_INIMIGOS; i++)
            desenharQuadrado(inimigos[i].x, inimigos[i].y, 1, 0, 0); // inimigos
    }

    glutSwapBuffers(); // Troca o buffer para atualizar a tela
}

// Teclas direcionais (setas) para mover o jogador
void tecladoEspecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: moverJogador(0, -1); break;
        case GLUT_KEY_DOWN: moverJogador(0, 1); break;
        case GLUT_KEY_LEFT: moverJogador(-1, 0); break;
        case GLUT_KEY_RIGHT: moverJogador(1, 0); break;
    }
}

// Teclado normal: R para reiniciar, D para modo dev, ESC para sair
void tecladoNormal(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Tecla ESC sai do programa
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

// Função principal: inicializa o jogo e configura o GLUT
int main(int argc, char **argv) {
    srand(time(NULL)); // Inicializa semente aleatória
    inicializarPosicoes(); // Posição inicial do jogador
    reiniciarInimigos();   // Inimigos em posições válidas

    glutInit(&argc, argv); // Inicializa GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Duplo buffer + RGB
    glutInitWindowSize(MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE); // Tamanho da janela
    glutCreateWindow("Labirinto Inteligente"); // Cria janela com título
    gluOrtho2D(0, MAP_SIZE * TILE_SIZE, MAP_SIZE * TILE_SIZE, 0); // Projeção 2D

    glutDisplayFunc(display); // Define função de desenho
    glutSpecialFunc(tecladoEspecial); // Define entrada de teclas especiais
    glutKeyboardFunc(tecladoNormal);  // Define entrada de teclas normais
    glutTimerFunc(500, timer, 0);     // Inicia temporizador para inimigos

    glutMainLoop(); // Inicia o loop principal do GLUT
    return 0;
}