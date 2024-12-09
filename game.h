/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/


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

    // Define as principais funções do jogo

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