/*
Autores:
Bruno Basckeira Chinaglia - 14562233
Giordano Santorum Lorenzetto - 14574017
Miguel Tomazini Rodrigues - 14599300
Victor Moreli dos Santos - 14610514
*/

#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    configurar_interface(argc, argv); // Configura janela e gráficos

    executar_loop(); // Executa o loop principal do GLUT

    return 0;
}
