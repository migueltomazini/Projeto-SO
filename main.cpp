#include "game.h"

using namespace std;

int main(int argc, char** argv) {

    configurar_interface(argc, argv);

    inicializar_threads();

    executar_loop();

    return 0;
}