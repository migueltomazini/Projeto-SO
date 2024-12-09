/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#include "game.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600

// Semáforo binário
binary_semaphore mutexInimigoHP(1); // Inicializado com 1

// Criação do inimigo
Inimigo inimigo(-1.0f, 0.0f, 1050, 0.01f, 0.05f); // Movimento apenas horizontal

// Vetor de torres
vector<Torre> torres; 
const int maxTorres = 3;    // número máximo de torres

// Distância mínima entre a torre e a linha do inimigo
const float distanciaMinima = 0.2f;

// Variável que controla o estado atual do jogo
EstadoJogo estadoAtual = MENU;

// Funcao para capturar clique do mouse
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

// Funcao que captura tecla apertada do teclado
void teclado(unsigned char key, int x, int y) {
    if (estadoAtual == MENU && key == 's') {    // inicia o jogo
        estadoAtual = JOGANDO;
        inicializar_threads();
    } else if (estadoAtual == GAME_OVER && key == 'r') {
        estadoAtual = MENU;
        torres.clear();
        inimigo.resetar(); // Reinicia o inimigo
    }
}

// Função da torre executada pelas threads
void torre_func(Torre* torre, Inimigo* inimigo) {
    while (estadoAtual == JOGANDO) {
        // Calcula distância entre a torre e o inimigo
        float dx = inimigo->getX() - torre->getX();
        float dy = inimigo->getY() - torre->getY();
        float distancia = dx * dx + dy * dy;

        // Verifica se o inimigo está no raio de ataque e está vivo
        if (distancia <= torre->getRadius() * torre->getRadius() && inimigo->isAlive()) {
            mutexInimigoHP.acquire(); // Bloqueia acesso à vida do inimigo
            inimigo->aplicaDano(DANO); // Região Crítica
            mutexInimigoHP.release(); // Libera acesso
            usleep(100000);
        }
    }
}

// Função de renderização
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estadoAtual == MENU) {  // Jogo no menu inicial
        // Desenha a linha horizontal do caminho do inimigo
        desenha_linha(-1.0f, 0.0f, 1.0f, 0.0f);

        // Desenha linhas que demarcam área onde pode ser colocada uma torre
        glColor3f(1.0, 1.0, 0.0);
        glLineWidth(10.0f);  // Define a espessura da linha
        desenha_linha(-1.0f, 0.2f, 1.0f, 0.2f);
        desenha_linha(-1.0f, -0.2f, 1.0f, -0.2f);
        glLineWidth(1.0f);  // Define a espessura da linha

        // Desenha torres
        for (auto& torre : torres) {
            desenha_circunferencia(torre.getX(), torre.getY(), torre.getRadius());
            desenha_triangulo(torre.getX(), torre.getY(), torre.getTamanho());
        }

        // Desenha mensagens na tela
        desenha_texto_na_tela("Clique para posicionar as torres (no maximo 3).", -0.9f, 0.9f);
        desenha_texto_na_tela("As torres nao podem estar entre as linhas.", -0.9f, 0.8f);
        desenha_texto_na_tela("Pressione 'S' para comecar.", -0.9f, 0.7f);

    } else if (estadoAtual == JOGANDO) {    // Jogo rodando
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

            for(auto& torre : torres){  // Desenha linha que indica ataque da torre ao inimigo
                if((inimigo.getX() - torre.getX())*(inimigo.getX() - torre.getX()) + (inimigo.getY() - torre.getY())*(inimigo.getY() - torre.getY()) <= (torre.getRadius() * torre.getRadius())){  
                    // Se iniigo está no range de ataque, desenha linha
                    glLineWidth(20.0f);  // Define a espessura da linha
                    glColor3f(1.0, 0.6, 0.0);

                    glBegin(GL_LINE_STRIP);
                        glVertex2d(torre.getX(), torre.getY());
                        glVertex2d(inimigo.getX(), inimigo.getY());
                    glEnd();

                    glLineWidth(1.0f); 
                }
            }
        }

        // Escreve na tela vida do inimigo
        string vidaInimigoTexto = "Vida do inimigo: " + to_string(inimigo.getHealth());
        desenha_texto_na_tela(vidaInimigoTexto.c_str(), -0.9f, -0.9f);

    } else if (estadoAtual == GAME_OVER) {  // Se o jogo terminou (jogador ganhou ou perdeu)

        if (!inimigo.isAlive()) {   // Inimigo vivo, jogador perdeu
            desenha_texto_na_tela("Voce venceu! Pressione R para reiniciar.", -0.5f, 0.0f);
        } else {    // Inimigo morto, jogador venceu
            desenha_texto_na_tela("GAME OVER! Pressione R para reiniciar.", -0.5f, 0.0f);
        }
    }

    glutSwapBuffers();
}

void timer(int) {
    if (estadoAtual == JOGANDO) {
        inimigo.mover();    // move inimigo

        if (inimigo.getX() > 1.0f || !inimigo.isAlive()) {  // se inimigo chegou ao fim da tela ou se morreu
            estadoAtual = GAME_OVER;    // jogo terminou
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0); // jogo rodando a 60 fps
}

// Função que inicializa threads
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

// Loop do jogo
void executar_loop() {
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(teclado);
    glutMainLoop();
}
