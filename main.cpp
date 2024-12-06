#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    configurar_interface(argc, argv); // Configura janela e gráficos

    executar_loop(); // Executa o loop principal do GLUT

    return 0;
}
