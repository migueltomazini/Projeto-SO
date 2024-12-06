#include "game.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600

bool jogo_rodando;

// Semáforo binário
binary_semaphore mutexInimigoHP(1); // Inicializado com 1

// Criação do inimigo
Inimigo inimigo(-1.0f, 0.0f, 1000, 0.01f, 0.05f); // Movimento apenas horizontal

// Vetor de torres
vector<Torre> torres; 
const int maxTorres = 3;

// Distância mínima entre a torre e a linha do inimigo
const float distanciaMinima = 0.2f;

EstadoJogo estadoAtual = MENU;

void mouseFunc(int button, int state, int x, int y) {
    if (estadoAtual == MENU && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && torres.size() < maxTorres) {
        float posX = (float)x / windowWidth * 2.0f - 1.0f;
        float posY = 1.0f - (float)y / windowHeight * 2.0f;

        // Verifica se a torre está longe o suficiente da linha do inimigo
        if (abs(posY - 0.0f) >= distanciaMinima) {
            torres.push_back(Torre(posX, posY, 0.5, 0.12));
        } else {
            cout << "Torre muito próxima da linha do inimigo! Escolha outro local.\n";
        }
    }
}

void teclado(unsigned char key, int x, int y) {
    if (estadoAtual == MENU && key == 's') {
        estadoAtual = JOGANDO;
        jogo_rodando = true;
        inicializar_threads();
    } else if (estadoAtual == GAME_OVER && key == 'r') {
        jogo_rodando = true;
        estadoAtual = MENU;
        torres.clear();
        inimigo.resetar(); // Reinicia o inimigo
    }
}

// Função da torre executada pelas threads
void torre_func(Torre* torre, Inimigo* inimigo) {
    while (jogo_rodando) {
        // Calcula distância entre a torre e o inimigo
        float dx = inimigo->getX() - torre->getX();
        float dy = inimigo->getY() - torre->getY();
        float distancia = dx * dx + dy * dy;

        // Verifica se o inimigo está no raio de ataque e está vivo
        if (distancia <= torre->getRadius() * torre->getRadius() && inimigo->isAlive()) {
            mutexInimigoHP.acquire(); // Bloqueia acesso à vida do inimigo
            inimigo->aplicaDano(DANO); 
            cout << "Torre em (" << torre->getX() << ", " << torre->getY() 
                 << ") atacou o inimigo. Vida restante: " << inimigo->getHealth() << endl;
            mutexInimigoHP.release(); // Libera acesso
            usleep(100000);
        }
    }
}

// Função de renderização
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estadoAtual == MENU) {
        // Desenha a linha horizontal do caminho do inimigo
        desenha_linha(-1.0f, 0.0f, 1.0f, 0.0f);

        // Desenha linhas que demarcam área onde pode ser colocada uma torre
        desenha_linha(-1.0f, 0.2f, 1.0f, 0.2f);
        desenha_linha(-1.0f, -0.2f, 1.0f, -0.2f);

        for (auto& torre : torres) {
            desenha_circunferencia(torre.getX(), torre.getY(), torre.getRadius());
            desenha_triangulo(torre.getX(), torre.getY(), torre.getTamanho());
        }
        desenha_texto_na_tela("Clique para posicionar as torres (no maximo 3).", -0.9f, 0.9f);
        desenha_texto_na_tela("As torres nao podem estar entre as linhas.", -0.9f, 0.8f);
        desenha_texto_na_tela("Pressione 'S' para comecar.", -0.9f, 0.7f);
    } else if (estadoAtual == JOGANDO) {
        // Desenha a linha horizontal
        desenha_linha(-1.0f, 0.0f, 1.0f, 0.0f);

        // Desenha torres
        for (auto& torre : torres) {
            desenha_circunferencia(torre.getX(), torre.getY(), torre.getRadius());
            desenha_triangulo(torre.getX(), torre.getY(), torre.getTamanho());
        }

        // Desenha o inimigo
        if (inimigo.isAlive()) {
            desenha_circulo(inimigo.getX(), inimigo.getY(), inimigo.getRadius());
        }

        string vidaInimigoTexto = "Vida do inimigo: " + to_string(inimigo.getHealth());
        desenha_texto_na_tela(vidaInimigoTexto.c_str(), -0.9f, -0.9f);

    } else if (estadoAtual == GAME_OVER) {
        jogo_rodando = false;

        if (!inimigo.isAlive()) {
            desenha_texto_na_tela("Voce venceu! Pressione R para reiniciar.", -0.5f, 0.0f);
        } else {
            desenha_texto_na_tela("GAME OVER! Pressione R para reiniciar.", -0.5f, 0.0f);
        }
    }

    glutSwapBuffers();
}

void timer(int) {
    if (estadoAtual == JOGANDO) {
        inimigo.mover();

        if (inimigo.getX() > 1.0f || !inimigo.isAlive()) {
            estadoAtual = GAME_OVER;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void inicializar_threads(){
    // Criação de threads para cada torre
    thread torre1Thread(torre_func, &torres[0], &inimigo);
    thread torre2Thread(torre_func, &torres[1], &inimigo);
    thread torre3Thread(torre_func, &torres[2], &inimigo);

    // Separa as threads de cada torre da thread principal para execução concorrente
    torre1Thread.detach();
    torre2Thread.detach();
    torre3Thread.detach();
}

void executar_loop() {
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(teclado);
    glutMainLoop();
}
