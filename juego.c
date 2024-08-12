#include <time.h>
#include <stdlib.h>
#include "granja.h"
#include "calculo_enanito.h"

int main(){

	juego_t juego;
	char inicial_enanito = FELIZ;
	char accion = 'n';
	calcular_enanito(&inicial_enanito);
	srand ((unsigned)time(NULL));
	
	inicializar_juego(&juego, inicial_enanito);

	while(estado_juego(juego) == JUGANDO){
		imprimir_terreno(juego);
		realizar_jugada(&juego,accion);
		system("clear");
    }

	return 0; 
}