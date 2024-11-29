#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

#define windowWidth 600
#define windowHeight 600

typedef struct _inimigo{
  float radius;
  float x;
  float y;
  float hp;
}INIMIGO;

typedef struct _torre{
  float radius;
  float tamanho;
  float x;
  float y;
}TORRE;

INIMIGO inimigo1;

INIMIGO inimigo2;

TORRE torre1;
TORRE torre2;
TORRE torre3;




//---------- Protótipos de função ----------//
void draw();// Função para desenhar
void timer(int);// Função de loop
void desenha_circulo(float x, float y, float raio);

//------------------ Main -----------------//
int main(int argc, char** argv){

    inimigo1.hp = 1000;
    inimigo1.radius = 0.05;
    inimigo1.x = -1;
    inimigo1.y = 0.5;

    inimigo2.hp = 1000;
    inimigo2.radius = 0.05;
    inimigo2.x = -1;
    inimigo2.y = -0.5;

    torre1.tamanho = 0.12;
    torre1.radius = 0.5;
    torre1.x = -0.2;
    torre1.y = 0.75;

    torre2.tamanho = 0.12;
    torre2.radius = 0.5;
    torre2.x = 0.2;
    torre2.y = 0.75;


    torre3.tamanho = 0.12;
    torre3.radius = 0.5;
    torre3.x = 0;
    torre3.y = -0.75;

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

void move_inimigo(INIMIGO * ini){
    if(ini->x > 1){
        ini->x = -1;
    }
    ini->x += 0.005f;
}

//------------------ Draw -----------------//
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);

    desenha_circunferencia(torre1.x, torre1.y, torre1.radius);
    desenha_circunferencia(torre2.x, torre2.y, torre2.radius);
    desenha_circunferencia(torre3.x, torre3.y, torre3.radius);

    desenha_linha(-1.0, 0.5, 1.0, 0.5);
    desenha_linha(-1.0, -0.5, 1.0, -0.5);

    desenha_circulo(inimigo1.x, inimigo1.y, inimigo1.radius);
    desenha_circulo(inimigo2.x, inimigo2.y, inimigo2.radius);

    desenha_triangulo(torre1.x, torre1.y, torre1.tamanho);
    desenha_triangulo(torre2.x, torre2.y, torre2.tamanho);
    desenha_triangulo(torre3.x, torre3.y, torre3.tamanho);


    glLineWidth(20.0f);  // Define a espessura da linha
    glColor3f(1.0, 0.6, 0.0);
    if((inimigo1.x - torre1.x)*(inimigo1.x - torre1.x) + (inimigo1.y - torre1.y)*(inimigo1.y - torre1.y) <= 0.25){
        glBegin(GL_LINE_STRIP);
            glVertex2d( torre1.x, torre1.y);
            glVertex2d(inimigo1.x, inimigo1.y);
        glEnd();
    }

    if((inimigo1.x - torre2.x)*(inimigo1.x - torre2.x) + (inimigo1.y - torre2.y)*(inimigo1.y - torre2.y) <= 0.25){
        glBegin(GL_LINE_STRIP);
            glVertex2d( torre2.x, torre2.y);
            glVertex2d(inimigo1.x, inimigo1.y);
        glEnd();
    }
    glLineWidth(0.01f);  // Define a espessura da linha


  glutSwapBuffers();
}

//------------------ Timer -----------------//
void timer(int){
  // Essa função é chamada em loop, é aqui que realizaremos as animações

  // Tenta ficar mudando os parâmetros para ver o que muda! :)
  move_inimigo(&inimigo1);
  move_inimigo(&inimigo2);


  // Executa a função draw para desenhar novamente
  glutPostRedisplay();

  // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
  // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
  glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}
