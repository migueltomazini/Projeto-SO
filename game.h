#ifndef GAME_H
    #define GAME_H

    #include <iostream>
    #include <vector>
    #include <thread>
    #include <atomic>
    #include <unistd.h> // Para usleep
    #include <semaphore> // Para std::binary_semaphore
    #include "torre.h"
    #include "inimigo.h"
    #include "graphics.h"

    // Estado do jogo
    enum EstadoJogo {
        MENU,
        JOGANDO,
        GAME_OVER
    };

    void torre_func(Torre* torre, Inimigo* inimigo);
    void desenha_texto(void);
    void draw();
    void timer(int);
    void inicializar_threads();
    void executar_loop();
    void mouseFunc(int button, int state, int x, int y);
    void teclado(unsigned char key, int x, int y);

#endif