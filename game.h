#ifndef GAME_H
    #define GAME_H

    #include <iostream>
    #include <vector>
    #include <thread>
    #include <atomic>
    #include <unistd.h> // Para usleep
    #include "torre.h"
    #include "inimigo.h"
    #include "graphics.h"

    typedef int semaphore; // Semáforos são representados como inteiros

    void down(semaphore *s);
    void up(semaphore *s);
    void torre_func(Torre* torre, Inimigo* inimigo, semaphore* mutex);
    void desenha_texto(void);
    void draw();
    void timer(int);
    void inicializar_threads();
    void executar_loop();

#endif