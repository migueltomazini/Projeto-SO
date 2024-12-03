#include "game.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600

// Semáforos
semaphore mutexInimigo1HP = 1;
semaphore mutexInimigo2HP = 1;

// Criação dos inimigos
Inimigo inimigo1(-1.0f, 0.5f, 1000, 0.05f, 0.05f);
Inimigo inimigo2(-1.0f, -0.5f, 1000, 0.05f, 0.05f);

// Criando torres
Torre torre1(-0.2, 0.75, 0.5, 0.12);
Torre torre2(0.2, 0.75, 0.5, 0.12);
Torre torre3(0, -0.75, 0.5, 0.12);

// Função para decrementar o semáforo
void down(semaphore *s) {
    while (*s <= 0) {
        usleep(100); // Evita consumir 100% da CPU
    }
    __sync_fetch_and_sub(s, 1); // Decrementa o semáforo de forma atômica
}

// Função para incrementar o semáforo
void up(semaphore *s) {
    __sync_fetch_and_add(s, 1); // Incrementa o semáforo de forma atômica
}


// Função da torre executada pelas threads
void torre_func(Torre* torre, Inimigo* inimigo, semaphore* mutex) {
    while (true) {
        // Calcula distância entre a torre e o inimigo
        float dx = inimigo->getX() - torre->getX();
        float dy = inimigo->getY() - torre->getY();
        float distancia = dx * dx + dy * dy;

        // Verifica se o inimigo está no raio de ataque e está vivo
        if (distancia <= torre->getRadius() * torre->getRadius() && inimigo->isAlive()) {
            down(mutex); // Bloqueia acesso à vida do inimigo
            inimigo->aplicaDano(DANO); // Aplica o dano
            cout << "Torre em (" << torre->getX() << ", " << torre->getY() 
                 << ") atacou o inimigo. Vida restante: " << inimigo->getHealth() << endl;
            up(mutex); // Libera acesso
            usleep(100000); // Espera antes de atacar novamente
        }
    }
}

void desenha_texto(void) {
    for (int i = 1; i <= NUM_INIMIGOS; i++) {
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

void inicializar_threads(){
    // Criação de threads para cada torre
    thread torre1Thread(torre_func, &torre1, &inimigo1, &mutexInimigo1HP);
    thread torre2Thread(torre_func, &torre2, &inimigo1, &mutexInimigo1HP);
    thread torre3Thread(torre_func, &torre3, &inimigo2, &mutexInimigo2HP);

    // Separa as threads de cada torre da thread principal para execução concorrente
    torre1Thread.detach();
    torre2Thread.detach();
    torre3Thread.detach();
}

void executar_loop(){
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0); // Define função de loop
    glutMainLoop();
}