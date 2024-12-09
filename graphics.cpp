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
    glutCreateWindow("Tower Defense com Threads e Semáforos");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(draw);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, timer, 0);
}

