#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "torre.h"
#include "inimigo.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600

int dano = 10;           // Dano por aplicação
int intervalo = 1000;    // Intervalo de 1 segundo (em milissegundos)

// Criação dos inimigos
Inimigo inimigo1(-1.0f, 0.5f, 10000, 0.05f, 0.05f);
Inimigo inimigo2(-1.0f, -0.5f, 10000, 0.05f, 0.05f);

// Criando torres
Torre torre1(-0.2, 0.75, 0.5, 0.12);
Torre torre2(0.2, 0.75, 0.5, 0.12);
Torre torre3(0, -0.75, 0.5, 0.12);

//---------- Protótipos de função ----------//
void draw();// Função para desenhar
void timer(int);// Função de loop
void desenha_circulo(float x, float y, float raio);


//------------------ Main -----------------//
int main(int argc, char** argv){

    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tutorial 2 - Animation");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0);// Define qual será a função de loop
    glutMainLoop();

    return 0;
}

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

void desenha_texto(void) {
    for (int i = 1; i < NUM_INIMIGOS; i++) {
        char vidaTexto[50];
        if (i == 1) sprintf(vidaTexto, "Inimigo %d: %d", i, inimigo1.getHealth());  // gambs para corrigir depois
        else sprintf(vidaTexto, "Inimigo %d: %d", i, inimigo2.getHealth());
        glRasterPos2f(-0.9f, 0.3f - 0.2f * i); // Posiciona os textos na tela
        for (char *c = vidaTexto; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }
}

//------------------ Draw -----------------//
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    desenha_circunferencia(torre1.getX(), torre1.getY(), torre1.getRadius());
    desenha_circunferencia(torre2.getX(), torre2.getY(), torre2.getRadius());
    desenha_circunferencia(torre3.getX(), torre3.getY(), torre3.getRadius());

    desenha_linha(-1.0, 0.5, 1.0, 0.5);
    desenha_linha(-1.0, -0.5, 1.0, -0.5);

    if (inimigo1.isAlive()) // Usando método isAlive(), se existir.
        desenha_circulo(inimigo1.getX(), inimigo1.getY(), inimigo1.getRadius());
    if (inimigo2.isAlive()) // Usando método isAlive(), se existir.
        desenha_circulo(inimigo2.getX(), inimigo2.getY(), inimigo2.getRadius());

    desenha_texto();

    desenha_triangulo(torre1.getX(), torre1.getY(), torre1.getTamanho());
    desenha_triangulo(torre2.getX(), torre2.getY(), torre2.getTamanho());
    desenha_triangulo(torre3.getX(), torre3.getY(), torre3.getTamanho());

    glLineWidth(20.0f);  // Define a espessura da linha
    glColor3f(1.0, 0.6, 0.0);
    if (inimigo1.isAlive() && (inimigo1.getX() - torre1.getX())*(inimigo1.getX() - torre1.getX()) + (inimigo1.getY() - torre1.getY())*(inimigo1.getY() - torre1.getY()) <= 0.25) {
        // glutTimerFunc(intervalo, inimigo1.aplicaDano(dano), 1);

        glBegin(GL_LINE_STRIP);
            glVertex2d(torre1.getX(), torre1.getY());
            glVertex2d(inimigo1.getX(), inimigo1.getY());
        glEnd();
    }


    if (inimigo1.isAlive() && (inimigo1.getX() - torre2.getX())*(inimigo1.getX() - torre2.getX()) + (inimigo1.getY() - torre2.getY())*(inimigo1.getY() - torre2.getY()) <= 0.25) {
        // glutTimerFunc(intervalo, inimigo1.aplicaDano(dano), 1);

        glBegin(GL_LINE_STRIP);
            glVertex2d(torre2.getX(), torre2.getY());
            glVertex2d(inimigo1.getX(), inimigo1.getY());
        glEnd();
    }

    if (inimigo2.isAlive() && (inimigo2.getX() - torre3.getX())*(inimigo2.getX() - torre3.getX()) + (inimigo2.getY() - torre3.getY())*(inimigo2.getY() - torre3.getY()) <= 0.25) {
        // glutTimerFunc(intervalo, inimigo2.aplicaDano(dano), 2);

        glBegin(GL_LINE_STRIP);
            glVertex2d(torre3.getX(), torre3.getY());
            glVertex2d(inimigo2.getX(), inimigo2.getY());
        glEnd();
    }

    glLineWidth(0.01f);  // Define a espessura da linha

    glutSwapBuffers();
}


//------------------ Timer -----------------//
void timer(int){
  // Essa função é chamada em loop, é aqui que realizaremos as animações

  inimigo1.mover();
  inimigo2.mover();


  // Executa a função draw para desenhar novamente
  glutPostRedisplay();

  // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
  // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
  glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}

// void aplicarDano(int inimigoIndex) {
//     if (!inimigo[inimigoIndex].live || inimigoIndex < 0 || inimigoIndex >= NUM_INIMIGOS) return;

//     // Aplica o dano ao inimigo específico
//     inimigo[inimigoIndex].hp -= dano;
//     if (inimigo[inimigoIndex].hp < 0) {
//         inimigo[inimigoIndex].hp = 0;
//         inimigo[inimigoIndex].live = 0;
//     } 

//     printf("hp do inimigo %d: %.0lf\n", inimigoIndex, inimigo[inimigoIndex].hp);

//     // Verifica se o inimigo está vivo
//     if (inimigo[inimigoIndex].hp > 0) {
//         // Agenda o próximo dano para este inimigo
//         glutTimerFunc(intervalo, aplicarDano, inimigoIndex);
//     } else {
//         printf("O inimigo %d morreu!\n", inimigoIndex);
//     }

//     // Re-renderiza a tela, se necessário
//     glutPostRedisplay();
// }
