/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#include "graphics.h"
#include  "game.h"

void desenha_circulo(float x, float y, float raio){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i+=5) {
        glVertex2d( raio*cos(i/180.0*M_PI) + x, raio*sin(i/180.0*M_PI) + y);
    }
    glEnd();
}

void desenha_circunferencia(float x, float y, float raio){
    glColor3f(0.0, 0.0, 0.5);
    for (int i = 0; i <= 360; i+=10) {
        glBegin(GL_LINE_STRIP);
            glVertex2d( raio*cos(i/180.0*M_PI) + x, raio*sin(i/180.0*M_PI) + y);
            glVertex2d( raio*cos((i+7)/180.0*M_PI) + x, raio*sin((i+7)/180.0*M_PI) + y);
        glEnd();
    }
}

void desenha_triangulo(float x, float y, float raio){
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = -30; i < 360; i+=120) {
        glVertex2d( raio*cos(i/180.0*M_PI) + x, raio*sin(i/180.0*M_PI) + y);
    }
    glEnd();
}

void desenha_linha(float x1, float y1, float x2, float y2){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);  // Ponto inicial (canto superior esquerdo)
    glVertex2f(x2, y2);  // Ponto inicial (canto superior esquerdo)
    glEnd();
}

// Desenha texto na tela
void desenha_texto_na_tela(const char* texto, float x, float y) {
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void configurar_interface(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tower Defense com Threads e Semaforos");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(draw);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, timer, 0);
}

void desenha_retangulo(float x, float y, float largura, float altura, float r, float g, float b) {
    glColor3f(r, g, b); // Define a cor
    glBegin(GL_QUADS); // Começa o desenho de um quadrilátero
    glVertex2f(x, y);               // Vértice inferior esquerdo
    glVertex2f(x + largura, y);     // Vértice inferior direito
    glVertex2f(x + largura, y + altura); // Vértice superior direito
    glVertex2f(x, y + altura);      // Vértice superior esquerdo
    glEnd(); // Termina o desenho
}

void desenha_barra_de_vida(const string& texto, float xTexto, float yTexto, int vidaAtual, int vidaMaxima) {
    // Desenha o texto
    desenha_texto_na_tela(texto.c_str(), xTexto, yTexto);

    // Calcula as dimensões da barra
    float larguraTotalBarra = 0.2f; // Largura total da barra
    float alturaBarra = 0.05f;      // Altura da barra
    float espacoTextoBarra = 0.1f;  // Espaço entre o texto e a barra
    float xBarra = xTexto + espacoTextoBarra + 0.53f; // Posição da barra ao lado do texto
    float yBarra = yTexto - 0.01f;  // Posição da barra alinhada na linha do texto

    // Calcula a largura proporcional à vida atual
    float larguraAtualBarra = larguraTotalBarra * ((float)vidaAtual / vidaMaxima);

    // Define a cor com base no percentual de vida (verde → amarelo → vermelho)
    float r = 1.0f - ((float)vidaAtual / vidaMaxima); // Mais vermelho conforme perde vida
    float g = (float)vidaAtual / vidaMaxima;         // Mais verde conforme tem vida

    // Desenha a barra de fundo (cor cinza escuro)
    desenha_retangulo(xBarra, yBarra, larguraTotalBarra, alturaBarra, 0.2f, 0.2f, 0.2f);

    // Desenha a barra de vida
    desenha_retangulo(xBarra, yBarra, larguraAtualBarra, alturaBarra, r, g, 0.0f);
}