#include <stdio.h>
#include <stdlib.h>
#include "granja.h"
#include "calculo_enanito.h"

#define FILAS_HUERTA 3
#define COLUMNAS_HUERTA 3
#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 20

const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';

const char BLANCANIEVES = 'S';
const char CULTIVO_VACIO = 'C';
const char DEPOSITO = 'D';
const char VACIO = '.';

const char ESPINAS = 'E';
const char PLAGAS = 'P';
const char FERTILIZANTE = 'F';

const char TIPO_ZANAHORIA = 'Z';
const char TIPO_TOMATE = 'T';
const char TIPO_LECHUGA = 'L';
const char TIPO_BROCOLI = 'B';

const char SEMBRAR_ZANAHORIA = 'Z';
const char SEMBRAR_TOMATE = 'T';
const char SEMBRAR_LECHUGA = 'L';
const char SEMBRAR_BROCOLI = 'B';

const char USAR_INSECTICIDA = 'I';
const char USAR_FERTILIZANTE = 'F';

const int PRIMER_HUERTA = 0;
const int SEGUNDA_HUERTA = 1;
const int TERCER_HUERTA = 2;

const int MONEDAS_PARA_PERDER = 0;
const int DISTANCIA_INTERCAMBIAR = 2;
const int CANTIDAD_MONEDAS_GRUNION = 150;
const int CANTIDAD_MONEDAS_DORMILON = 200;
const int CANTIDAD_MONEDAS_SABIO = 250;
const int CANTIDAD_MONEDAS_FELIZ = 300;
const int MONEDAS_PARA_GANAR = 1000;

const int DIMENSION = 20;
const int CANTIDAD_INSECTICIDAS = 3;
const int POSEE_FERTILIZANTE = 1;
const int CANTIDAD_ESPINAS = 5;
const int MAX_CULTIVOS_CANASTA = 6;
const int MOVIMIENTOS_APARECER_PLAGAS = 10;
const int MOVIMIENTOS_APARECER_FERTILIZANTES = 15;
const int CANTIDAD_MINIMA_FERTILIZANTES = 1;
const int CANTIDAD_MONEDAS_PERDIDAS_ESPINA = 5;
const int MOVIMIENTOS_LIQUIDAR_HUERTA = 10;

const int PRECIO_SEMBRAR_TOMATE = 5;
const int PRECIO_SEMBRAR_ZANAHORIA = 10;
const int PRECIO_SEMBRAR_BROCOLI = 15;
const int PRECIO_SEMBRAR_LECHUGA = 20;

const int CRECIMIENTO_LECHUGA = 10;
const int CRECIMIENTO_BROCOLI = 10;
const int CRECIMIENTO_ZANAHORIA = 15;
const int CRECIMIENTO_TOMATE = 20;

const int VIDA_LECHUGA = 15;
const int VIDA_BROCOLI = 20;
const int VIDA_ZANAHORIA = 25;
const int VIDA_TOMATE = 30;

const int VENTA_TOMATE = 30;
const int VENTA_ZANAHORIA = 50;
const int VENTA_BROCOLI = 70;
const int VENTA_LECHUGA = 80;


/*
Pre:
Post: Devuelvo una coordenada aleatoria
*/
coordenada_t coordenada_aleatoria(int dimension){

	coordenada_t coordenada;
	
	coordenada.fila = rand() % dimension;
	coordenada.columna = rand() % dimension;

	return coordenada;

}

/*
Pre: 
Post: Devuelve el valor absoluto de dos posiciones
*/
int distancia_manhattan(coordenada_t posicion_1, coordenada_t posicion_2){
	return (abs(posicion_1.fila - posicion_2.fila) + abs(posicion_1.columna - posicion_2.columna));
}

/*
Pre:
Post: verifica si dos coordenadas son iguales
*/
bool coordenadas_iguales(coordenada_t a, coordenada_t b){
	return (a.fila == b.fila && a.columna == b.columna);
}

/*
Pre: 
Post: verifica si dos elementos estan en la misma posicion, si lo estan, cambia la posicion del primero
*/
coordenada_t choque_elementos(coordenada_t elemento_1, coordenada_t elemento_2){

	while(coordenadas_iguales(elemento_1, elemento_2)){
		elemento_1 = coordenada_aleatoria(DIMENSION);
	}
	return elemento_1;

}

/*
Pre:
Post: Devuelve true si la jugada es valida, si no lo es devuelve false.
*/
bool jugada_valida(char movimiento){

	if(movimiento == ARRIBA|| movimiento == ABAJO || movimiento == IZQUIERDA ||  movimiento == DERECHA || movimiento == SEMBRAR_TOMATE || movimiento == SEMBRAR_BROCOLI || movimiento == SEMBRAR_LECHUGA || movimiento == SEMBRAR_ZANAHORIA || movimiento == USAR_INSECTICIDA || movimiento == USAR_FERTILIZANTE){
		return true;
	}
	return false;

}

/*
Pre:
Post: Devuelve true si algun objeto al inicializarse en el mapa choca sobre una huerta
*/
bool choque_con_huertas(juego_t* juego, coordenada_t posicion) {

	bool pisa_huerta = false;

	for (int i = 0; i < MAX_HUERTA; i++) {
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++) {
			if (coordenadas_iguales(posicion, juego->huertas[i].cultivos[j].posicion)) {
				pisa_huerta = true;
			}
		}
	}
	return pisa_huerta;

}

/*
Pre:
Post: Devuelve true si el jugador esta parado sobre un cultivo de una huerta.
*/
bool choque_jugador_huerta(juego_t juego, coordenada_t pos_jugador, coordenada_t pos_huerta){

	bool choque = false;

	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego.huertas[i].tope_cultivos; j++){
			if(coordenadas_iguales(juego.huertas[i].cultivos[j].posicion,juego.jugador.posicion)){
				choque = true;
			}
		}
	}
	return choque;

}

/*
Pre: 
Post: Devuelve el precio de cada tipo de cultivo
*/
int precio_vender_verduras(char cultivo){
	int precio_verdura = 0;

	if (cultivo == TIPO_TOMATE){
		precio_verdura = VENTA_TOMATE;
	}else if (cultivo == TIPO_ZANAHORIA){
		precio_verdura = VENTA_ZANAHORIA;
	}else if (cultivo == TIPO_BROCOLI){
		precio_verdura = VENTA_BROCOLI;
	}else if (cultivo == TIPO_LECHUGA){
		precio_verdura = VENTA_LECHUGA;
	}
	return precio_verdura;

}

/*
Pre: NEcesito responder las preguntas del TP1.
Post: Segun el enanito obtenido en el test de personalidad (el TP1), se asigna una cantidad de monedas para comenzar.
*/
int cantidad_monedas_segun_enanito(juego_t* juego, char enanito){
	
	int cantidad_monedas_inicial = 0;
	juego->jugador.cant_monedas = 0;

	if(enanito == GRUNION){
		juego->jugador.cant_monedas = CANTIDAD_MONEDAS_GRUNION;
	}else if(enanito == DORMILON){
		juego->jugador.cant_monedas = CANTIDAD_MONEDAS_DORMILON;
	}else if(enanito == SABIO){
		juego->jugador.cant_monedas = CANTIDAD_MONEDAS_SABIO;
	}else{
		juego->jugador.cant_monedas = CANTIDAD_MONEDAS_FELIZ;
	}

	cantidad_monedas_inicial = juego->jugador.cant_monedas;

	return cantidad_monedas_inicial;

}

/*
Pre:
Post: Inicializo los structs relacionados a objetos.
*/
void inicializar_objetos(juego_t* juego){

	juego->tope_objetos = 0;
	
	juego->objetos[juego->tope_objetos].tipo = 0;
	juego->objetos[juego->tope_objetos].posicion = coordenada_aleatoria(DIMENSION);
	
}

/*
Pre:
Post: Inicializo los structs relacionados al personaje.
*/
void inicializar_personaje(juego_t* juego){

	juego->jugador.posicion = coordenada_aleatoria(DIMENSION);
	juego->jugador.tiene_fertilizante = false;
	juego->jugador.cant_insecticidas = 0;
	juego->jugador.cant_monedas = 0;
	for (int i = 0; i < MAX_CULTIVOS_CANASTA; i++){
		juego->jugador.canasta[0] = 0;
	}
	juego->jugador.tope_canasta = 0;

}

/*
Pre: Un obstaculo tiene que inicializarse sobre una herramienta
Post: Cambia la posicion del objeto si en su posicion hay algun objeto/herramienta/huerta o si esta sobre el deposito/jugador
*/
void choque_obstaculos_herramientas(juego_t* juego){

	for (int i = 0; i < juego->tope_objetos; i++){
		if (!(juego->objetos[i].tipo == PLAGAS)){
			while(choque_con_huertas(juego, juego->objetos[i].posicion)){
				juego->objetos[i].posicion = coordenada_aleatoria(DIMENSION);
			}
		}
		choque_elementos(juego->objetos[i].posicion,juego->objetos[i].posicion);
		choque_elementos(juego->objetos[i].posicion,juego->jugador.posicion);
		choque_elementos(juego->objetos[i].posicion,juego->deposito);
	}

}

/*
Pre:
Post: Segun una cantidad de movimientos, aparece una herramienta en la matriz
*/
void aparecer_herramienta(juego_t* juego, char herramienta, int cantidad_movimientos){

	if (juego->movimientos % cantidad_movimientos == 0 && juego->tope_objetos < MAX_OBJETOS){
		juego->objetos[juego->tope_objetos].posicion = coordenada_aleatoria(DIMENSION);
		juego->objetos[juego->tope_objetos].tipo = herramienta;
		juego->tope_objetos++;
	}
	choque_obstaculos_herramientas(juego);

}

/*
Pre:
Post: Inicializo los structs relacionados a los cultivos y las huertas
*/
void inicializar_cultivos(juego_t* juego, int numero_huerta){

		juego->huertas[numero_huerta].movimientos_plagado = 0;
		juego->huertas[numero_huerta].plagado = false;
		juego->huertas[numero_huerta].tope_cultivos = 0;
		juego->huertas[numero_huerta].cultivos[0].posicion = coordenada_aleatoria(DIMENSION);
		juego->huertas[numero_huerta].cultivos[0].tipo = CULTIVO_VACIO;
		juego->huertas[numero_huerta].cultivos[0].ocupado = false;
		juego->huertas[numero_huerta].tope_cultivos++;

}

/*
Pre:
Post: Genero 1 huerta para el juego
*/
void generar_huertas(juego_t* juego, int numero_huerta){

	juego->huertas[numero_huerta].tope_cultivos = 1;
	juego->huertas[numero_huerta].plagado = false;
	juego->huertas[numero_huerta].movimientos_plagado = 0;


	int fil_cultivo_medio = juego->huertas[numero_huerta].cultivos[0].posicion.fila;
	int col_cultivo_medio = juego->huertas[numero_huerta].cultivos[0].posicion.columna;
		
	for (int j = - 1; j <= 1; j++){
		for (int k = - 1; k <=  1; k++){
			if (j != 0 || k != 0){
				int posicion_fil = fil_cultivo_medio + j;
				int posicion_col = col_cultivo_medio + k;

				if (posicion_fil >= 0 && posicion_fil < DIMENSION && posicion_col >= 0 && posicion_col < DIMENSION){
					int tope_cultivos = juego->huertas[numero_huerta].tope_cultivos;
					juego->huertas[numero_huerta].cultivos[tope_cultivos].posicion.fila = posicion_fil;
					juego->huertas[numero_huerta].cultivos[tope_cultivos].posicion.columna = posicion_col;
					juego->huertas[numero_huerta].cultivos[tope_cultivos].tipo = CULTIVO_VACIO;
					juego->huertas[numero_huerta].cultivos[tope_cultivos].ocupado = false;
					juego->huertas[numero_huerta].tope_cultivos++;
				}
			}
		}
	}

}

/*
Pre: Necesito tener las 3 huertas inicializadas
Post: Verifica que no choque una huerta con otra, si lo hace se cambia la posicion de la segunda creada
*/
void choque_entre_huertas(juego_t* juego, int huerta_uno, int huerta_dos){

	for (int i = 0; i < juego->huertas[huerta_uno].tope_cultivos; i++){
		for (int j = 0; j < juego->huertas[huerta_dos].tope_cultivos; j++){
			while(coordenadas_iguales(juego->huertas[huerta_uno].cultivos[i].posicion,juego->huertas[huerta_dos].cultivos[j].posicion)){
				inicializar_cultivos(juego,huerta_dos);
				generar_huertas(juego, huerta_dos);
			}
		}
	}

}

/*
Pre:
Post: Genero las huertas del juego y verifico que ni haya choques
*/
void terreno_huertas(juego_t* juego){

	inicializar_cultivos(juego,PRIMER_HUERTA);
	generar_huertas(juego, PRIMER_HUERTA);

	inicializar_cultivos(juego,SEGUNDA_HUERTA);
	generar_huertas(juego, SEGUNDA_HUERTA);

	inicializar_cultivos(juego,TERCER_HUERTA);
	generar_huertas(juego, TERCER_HUERTA);
	
	choque_entre_huertas(juego, PRIMER_HUERTA,SEGUNDA_HUERTA);
	choque_entre_huertas(juego, SEGUNDA_HUERTA,TERCER_HUERTA);
	choque_entre_huertas(juego, PRIMER_HUERTA,TERCER_HUERTA);
	choque_entre_huertas(juego, SEGUNDA_HUERTA,TERCER_HUERTA);
	
}

/*
Pre:
Post: Genero las plagas del juego, despues de determinada cant de movimientos, esta desaparece y se inicializa de nuevo
*/
void generar_plagas(juego_t* juego){

	if(juego->movimientos % MOVIMIENTOS_APARECER_PLAGAS == 0 && juego->tope_objetos < MAX_OBJETOS){
		for (int i = 0; i < juego->tope_objetos; i++){
			if (juego->objetos[i].tipo == PLAGAS){
				juego->objetos[i].tipo = VACIO;
			}
		}
	}

	aparecer_herramienta(juego, PLAGAS, MOVIMIENTOS_APARECER_PLAGAS);

}

/*
Pre:
Post: Genera las espinas en el terreno
*/
void generar_espinas(juego_t* juego){

	for (int i = 0; i < CANTIDAD_ESPINAS; i++){
		juego->objetos[juego->tope_objetos].posicion = coordenada_aleatoria(DIMENSION);
		juego->objetos[juego->tope_objetos].tipo = ESPINAS;
		juego->tope_objetos++;
	}

}

/*
Pre: Recibe todas las funciones/procedimientos referentes a los obstaculos
Post: Crea los obstaculos segun lo pedido
*/
void generar_obstaculos(juego_t* juego){
	
	generar_espinas(juego);
	choque_obstaculos_herramientas(juego);

}

/*
Pre:
Post: Verifica si el jugador tiene fertilizantes, si los tiene devuelve true
*/
bool tiene_fertilizantes(juego_t* juego){
	return (juego->jugador.tiene_fertilizante == CANTIDAD_MINIMA_FERTILIZANTES);
}

/*
Pre:
Post: Verifica si el jugador tiene fertilizantes, si los tiene devuelve true, al agarrarlo deja un espacio vacio
*/
void agarrar_fertilizantes(juego_t* juego){

	if (!juego->jugador.tiene_fertilizante){
		for (int i = 0; i < juego->tope_objetos; i++){
			if (coordenadas_iguales(juego->jugador.posicion,juego->objetos[i].posicion) && juego->objetos[i].tipo == FERTILIZANTE){
				juego->jugador.tiene_fertilizante = true;
				juego->objetos[i].tipo = VACIO;
			}
		}
	}

}

/*
Pre:
Post: asigna una cantidad de insecticidas para usar en el juego
*/
void cantidad_inicial_insecticidas(juego_t* juego){
	juego->jugador.cant_insecticidas = CANTIDAD_INSECTICIDAS;
}

/*
Pre: Llama a todas las funciones/procedimientos relacionadas a herramientas
Post: Genera las herramientas para el juego
*/
void generar_herramientas(juego_t* juego){
	cantidad_inicial_insecticidas(juego);
}

/*
Pre:
Post: Inicializa el deposito del juego.
*/
void inicializar_deposito(juego_t* juego){
	juego->deposito = coordenada_aleatoria(DIMENSION);
}

/*
Pre:
Post: Se fija que el deposito no se inicialice sobre un obstaculo/herramienta
*/
void choques_deposito(juego_t* juego){

	for (int i = 0; i < juego->tope_objetos; i++){
		while(choque_con_huertas(juego, juego->deposito)){
			inicializar_deposito(juego);
		}
		choque_elementos(juego->deposito,juego->objetos[i].posicion);
		choque_elementos(juego->deposito,juego->jugador.posicion);
	}

}

/*
Pre: Usa las funciones referentes para usar el deposito
Post: Genera el deposito en el juego
*/
void generar_deposito(juego_t* juego){
	
	inicializar_deposito(juego);
	choques_deposito(juego);

}

/*
Pre: 
Post: Doy una posicion aleatoria al personaje
*/
void generar_posicion_personaje(juego_t* juego){
	juego->jugador.posicion = coordenada_aleatoria(DIMENSION);
}

/*
Pre:
Post: Verifica que blancanieves no se inicialice en el mapa sobre una huerta/obstaculo/herramienta o el deposito.
*/
void choques_blancanieves(juego_t* juego){

	for (int i = 0; i < juego->tope_objetos; i++){
		while(choque_con_huertas(juego, juego->jugador.posicion)){
			generar_posicion_personaje(juego);
		}
		choque_elementos(juego->jugador.posicion,juego->objetos[i].posicion);
	}

}

/*
Pre: Recibe todas las funciones/procedimientos para inicializar a blancanieves
Post: Genera el personaje con todos sus atributos
*/
void generar_blancanieves(juego_t* juego, char inicial_enanito){

	generar_posicion_personaje(juego);
	juego->jugador.tiene_fertilizante = tiene_fertilizantes(juego);
	cantidad_inicial_insecticidas(juego);
	juego->jugador.tope_canasta = 0;
	juego->jugador.cant_monedas = cantidad_monedas_segun_enanito(juego, inicial_enanito);
	choques_blancanieves(juego);

}

void inicializar_juego(juego_t* juego, char enanito){

	juego->movimientos = 0;
	juego->jugador.cant_monedas = 0;
	terreno_huertas(juego);
	generar_obstaculos(juego);
	generar_herramientas(juego);
	generar_blancanieves(juego, enanito);
	generar_deposito(juego);

}

/*
Pre: El movimiento tiene que ser valido.
Post: El personaje se mueve y aumenta sus movimientos.
*/
void realizar_movimiento(juego_t* juego, char accion){

	coordenada_t nueva_posicion;
	nueva_posicion.fila = juego->jugador.posicion.fila;
	nueva_posicion.columna = juego->jugador.posicion.columna;
	bool aumenta_movimiento = false;

	if(accion == ARRIBA){
		nueva_posicion.fila = juego->jugador.posicion.fila-1;
		aumenta_movimiento = true;
	}else if(accion == ABAJO){
		nueva_posicion.fila = juego->jugador.posicion.fila+1;
		aumenta_movimiento = true;
	}else if(accion == IZQUIERDA){
		nueva_posicion.columna = juego->jugador.posicion.columna-1;
		aumenta_movimiento = true;
	}else if(accion == DERECHA){
		nueva_posicion.columna = juego->jugador.posicion.columna+1;
		aumenta_movimiento = true;
	}

	if (aumenta_movimiento && nueva_posicion.fila >= 0 && nueva_posicion.fila < DIMENSION && nueva_posicion.columna >= 0 && nueva_posicion.columna < DIMENSION){
		juego->jugador.posicion.fila = nueva_posicion.fila;
		juego->jugador.posicion.columna = nueva_posicion.columna;
		juego->movimientos++;
	}

}

/*
Pre: El juego tiene que tener espinas sobre su matriz
Post: Si el personaje choca con una espina, se descuentan monedas
*/
void choque_espina(juego_t* juego){

	for (int i = 0; i < CANTIDAD_ESPINAS; i++){
		if(juego->objetos[i].tipo == ESPINAS){
			if(coordenadas_iguales(juego->jugador.posicion,juego->objetos[i].posicion)){
				juego->jugador.cant_monedas = juego->jugador.cant_monedas - CANTIDAD_MONEDAS_PERDIDAS_ESPINA;
			}
		}
	}

}

/*
Pre: 
Post: Si la huerta esta plagada devuelve true
*/
bool huerta_plagada(juego_t* juego, int numero_huerta) {

	bool plagado = false;
	juego->huertas[numero_huerta].plagado = false;

	for (int i = 0; i < juego->huertas[numero_huerta].tope_cultivos; i++) {
		for (int j = 0; j < juego->tope_objetos; j++) {
			if (coordenadas_iguales(juego->huertas[numero_huerta].cultivos[i].posicion, juego->objetos[j].posicion) && (juego->objetos[j].tipo == PLAGAS)) {
				juego->huertas[numero_huerta].plagado = true;
				juego->huertas[numero_huerta].movimientos_plagado = juego->movimientos+1;
				plagado = true;
			}
		}
	}
	return plagado;

}

/*
Pre: Tiene que haber verduras plantadas en la huerta.
Post: Pasada una cantidad de movimientos, se pudren los cultivos de la huerta.
*/
void matar_huerta(juego_t* juego, int numero_huerta){

	if(huerta_plagada(juego, numero_huerta) && juego->huertas[numero_huerta].movimientos_plagado % MOVIMIENTOS_LIQUIDAR_HUERTA == 0){
		for(int j = 0; j < juego->huertas[numero_huerta].tope_cultivos; j++){
			juego->huertas[numero_huerta].cultivos[j].tipo = CULTIVO_VACIO;
			juego->huertas[numero_huerta].cultivos[j].ocupado = false;
		}
	juego->huertas[numero_huerta].plagado = false;
	juego->huertas[numero_huerta].movimientos_plagado = 0;
	}

}

/*
Pre: 
Post: Paso los parametros para cada huerta
*/
void huertas_muertas(juego_t* juego){

	matar_huerta(juego,PRIMER_HUERTA);
	matar_huerta(juego,SEGUNDA_HUERTA);
	matar_huerta(juego,TERCER_HUERTA);

}

/*
Pre: Tengo que tener insecticidas y la huerta tiene que estar plagada
Post: 
*/
void matar_plaga(juego_t* juego, int numero_huerta){

	for (int i = 0; i < juego->tope_objetos; i++){
		if (juego->objetos[i].tipo == PLAGAS){
			juego->huertas[numero_huerta].movimientos_plagado = 0;
			juego->huertas[numero_huerta].plagado = false;
			juego->objetos[i].tipo = VACIO;
		}
	}

}

/*
Pre: Tengo que tener insecticidas
Post: Si el insecticida se acciona sobre una huerta plagada, se cura la misma
*/
void accionar_insecticida(juego_t* juego, int numero_huerta){

	if (juego->jugador.cant_insecticidas > 0){
		for (int j = 0; j < juego->huertas[numero_huerta].tope_cultivos; j++){
			if(huerta_plagada(juego, numero_huerta)){
				if (coordenadas_iguales(juego->jugador.posicion,juego->huertas[numero_huerta].cultivos[j].posicion)){
					juego->huertas[numero_huerta].plagado = false;
					juego->huertas[numero_huerta].movimientos_plagado = 0;
					matar_plaga(juego,numero_huerta);
				}
			}	
		}
	}

}

/*
Pre: 
Post: Paso los parametros para cada huerta
*/
void insecticidas_parametros(juego_t* juego){

	accionar_insecticida(juego,PRIMER_HUERTA);
	accionar_insecticida(juego,SEGUNDA_HUERTA);
	accionar_insecticida(juego,TERCER_HUERTA);

}

/*
Pre: El tope de la canasta tiene que ser menor a 6 y ubicarme sobre un cultivo maduro
Post: Aumenta el tope y devuelve la posicion de la huerta a su estado original
*/
void cargar_canasta(juego_t* juego){

	coordenada_t pos_jugador;
	coordenada_t pos_cultivo;

	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++){
			pos_jugador = juego->jugador.posicion;
			pos_cultivo = juego->huertas[i].cultivos[j].posicion;
			if (coordenadas_iguales(pos_jugador,pos_cultivo) && juego->huertas[i].cultivos[j].ocupado){
				if (juego->jugador.tope_canasta < MAX_CULTIVOS_CANASTA){
					juego->jugador.canasta[juego->jugador.tope_canasta] = juego->huertas[i].cultivos[j].tipo;
					juego->huertas[i].cultivos[j].ocupado = false;
					juego->huertas[i].cultivos[j].tipo = CULTIVO_VACIO;
					juego->huertas[i].cultivos[j].movimiento_plantado = 0;
					juego->jugador.tope_canasta++;
				}
			}
		}
	}

}

/*
Pre: Necesita una cantidad suficiente de monedas
Post: Al sembrar una planta sobre una huerta, pierdo una cantidad de monedas
*/
void sembrar_planta(juego_t* juego, int precio_siembra, char verdura){

	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++){
			if ((coordenadas_iguales(juego->huertas[i].cultivos[j].posicion, juego->jugador.posicion)) && !(juego->huertas[i].cultivos[j].ocupado)){
				if (juego->jugador.cant_monedas >= precio_siembra){
					juego->huertas[i].cultivos[j].tipo = verdura;
					juego->huertas[i].cultivos[j].ocupado = true;
					juego->jugador.cant_monedas -= precio_siembra;
					juego->huertas[i].cultivos[j].movimiento_plantado = juego->movimientos;
				}
			}
		}
	}

}

/*
Pre: 
Post: LA verdura al estar entre un rango especifico de movimientos (estar madura), puede guardarse en la canasta
*/
void cosechar_verdura(juego_t* juego, int verdura_madura, int muerte_verdura, char verdura){

	int movimientos = 0;
	int mov_plantado = 0;

	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++){
			if (juego->huertas[i].cultivos[j].tipo == verdura){
				movimientos = juego->movimientos;
				mov_plantado = juego->huertas[i].cultivos[j].movimiento_plantado;
				if ((movimientos - mov_plantado > verdura_madura && movimientos - mov_plantado <= muerte_verdura)){
					cargar_canasta(juego);
				}
			}
		}
	}

}

/*
Pre: 
Post: Se pasa la funcion cosechar_verdura con sus distintos parametros.
*/
void cultivar(juego_t* juego){

	cosechar_verdura(juego, CRECIMIENTO_TOMATE, VIDA_TOMATE, TIPO_TOMATE);
	cosechar_verdura(juego, CRECIMIENTO_ZANAHORIA, VIDA_ZANAHORIA, TIPO_ZANAHORIA);
	cosechar_verdura(juego, CRECIMIENTO_BROCOLI, VIDA_BROCOLI, TIPO_BROCOLI);
	cosechar_verdura(juego, CRECIMIENTO_LECHUGA, VIDA_LECHUGA, TIPO_LECHUGA);

}

/*
Pre: Tener fertilizantes y verduras en la huerta
Post: Despues de usar el fertilizante puedo directamente cargar la canasta
*/
void crecer_verduras(juego_t* juego, char verdura, int verdura_madura){
	
	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++){
			if (juego->huertas[i].cultivos[j].tipo == verdura){
				if (choque_jugador_huerta(*juego,juego->jugador.posicion,juego->huertas[i].cultivos[j].posicion)){
					juego->huertas[i].cultivos[j].movimiento_plantado = juego->movimientos - verdura_madura;
					cargar_canasta(juego);
				}
			}
		}
	}

}

/*
Pre: 
Post: Se pasa la funcion crecer_verdura con sus distintos parametros.
*/
void madurar_verduras(juego_t* juego){

	crecer_verduras(juego,TIPO_TOMATE, CRECIMIENTO_TOMATE);
	crecer_verduras(juego,TIPO_BROCOLI, CRECIMIENTO_BROCOLI);
	crecer_verduras(juego,TIPO_ZANAHORIA, CRECIMIENTO_ZANAHORIA);
	crecer_verduras(juego,TIPO_LECHUGA, CRECIMIENTO_LECHUGA);

}

/*
Pre: Tiene que haber un cultivo sobre la huerta
Post: Despues de determinada cantidad de movimientos, la verdura se pudre y desaparece
*/
void verdura_pudrida(juego_t* juego, int muerte_verdura, char verdura){

	for (int i = 0; i < MAX_HUERTA; i++){
		for (int j = 0; j < juego->huertas[i].tope_cultivos; j++){
			if (juego->huertas[i].cultivos[j].tipo == verdura && juego->movimientos - juego->huertas[i].cultivos[j].movimiento_plantado >= muerte_verdura){
				juego->huertas[i].cultivos[j].ocupado = false;
				if (coordenadas_iguales(juego->jugador.posicion, juego->huertas[i].cultivos[j].posicion)){
					juego->huertas[i].cultivos[j].tipo = CULTIVO_VACIO;
				}
			}
		}
	}

}

/*
Pre: 
Post: Se pasa la funcion verdura_pudrida con sus distintos parametros.
*/
void matar_verdura(juego_t* juego){

	verdura_pudrida(juego, VIDA_TOMATE, TIPO_TOMATE);
	verdura_pudrida(juego, VIDA_BROCOLI, TIPO_BROCOLI);
	verdura_pudrida(juego, VIDA_LECHUGA, TIPO_LECHUGA);
	verdura_pudrida(juego, VIDA_ZANAHORIA, TIPO_ZANAHORIA);

}

/*
Pre: 
Post: Al usar una jugada, se siembra la planta
*/
void accion_sembrar(juego_t* juego, char accion){

	if (accion == SEMBRAR_TOMATE){
		sembrar_planta(juego, PRECIO_SEMBRAR_TOMATE, TIPO_TOMATE);
	}else if (accion == SEMBRAR_LECHUGA){
		sembrar_planta(juego, PRECIO_SEMBRAR_LECHUGA, TIPO_LECHUGA);
	}else if (accion == SEMBRAR_ZANAHORIA){
		sembrar_planta(juego, PRECIO_SEMBRAR_ZANAHORIA, TIPO_ZANAHORIA);
	}else if (accion == SEMBRAR_BROCOLI){
		sembrar_planta(juego, PRECIO_SEMBRAR_BROCOLI, TIPO_BROCOLI);
	}

}

/*
Pre: Tengo que tener la canasta con verduras
Post: Si me encuentro a distancia manhattan 2 o menos del deposito, se vacia la canasta y gano monedas
*/
void vaciar_canasta(juego_t* juego){

	if (distancia_manhattan(juego->jugador.posicion,juego->deposito) <= DISTANCIA_INTERCAMBIAR){
		for (int i = 0; i < juego->jugador.tope_canasta; i++){
			juego->jugador.cant_monedas += precio_vender_verduras(juego->jugador.canasta[i]);
		}
		juego->jugador.tope_canasta = 0;
	}

}

void realizar_jugada(juego_t* juego, char accion){
	
	while(!(jugada_valida(accion))){
		scanf(" %c", &accion);
	}
	realizar_movimiento(juego, accion);
	
	if (accion == USAR_FERTILIZANTE && juego->jugador.tiene_fertilizante){
		madurar_verduras(juego);
		juego->jugador.tiene_fertilizante = false;
	}

	if (accion == USAR_INSECTICIDA && juego->jugador.cant_insecticidas > 0){
		insecticidas_parametros(juego);
		juego->jugador.cant_insecticidas--;
	}

	aparecer_herramienta(juego, FERTILIZANTE, MOVIMIENTOS_APARECER_FERTILIZANTES);
	choque_espina(juego);
	cultivar(juego);
	matar_verdura(juego);
	agarrar_fertilizantes(juego);
	accion_sembrar(juego, accion);
	generar_plagas(juego);
	huertas_muertas(juego);
	vaciar_canasta(juego);
	
}

/*
Pre: 
Post: Imprime los atributos del jugador, monedas, movimientos, si una huerta esta plagada, etc.
*/
void estado_jugador(juego_t juego){

	printf("ESTADO ACTUAL: \n\n");

	printf("Movimientos realizados: %i\n", juego.movimientos);
	printf("Cantidad monedas: %i\n", juego.jugador.cant_monedas);
	printf("Cantidad insecticidas: %i\n", juego.jugador.cant_insecticidas);

	if (juego.jugador.tiene_fertilizante){
		printf("Tiene fertilizante\n");
	}else{
		printf("No tiene fertilizante\n");
	}

	if (huerta_plagada(&juego,PRIMER_HUERTA) || huerta_plagada(&juego,SEGUNDA_HUERTA) || huerta_plagada(&juego,TERCER_HUERTA)){
		printf("Hay una huerta plagada\n");
	}else{
		printf("No hay una huerta plagada\n");
	}
	printf("Tope de objetos: %i\n", juego.tope_objetos);
	printf("Cantidad de verduras en la canasta: %i\n", juego.jugador.tope_canasta);

	printf("\n\n\n");

}

void imprimir_terreno(juego_t juego){

	char terreno[DIMENSION][DIMENSION];

	estado_jugador(juego);

	for (int i = 0; i < DIMENSION; i++){
		for (int j = 0; j < DIMENSION; j++){
			terreno[i][j] = VACIO;
		}
	}

	for (int i = 0; i < MAX_HUERTA; i++) {
		for (int j = 0; j < juego.huertas[i].tope_cultivos; j++) {
			terreno[juego.huertas[i].cultivos[j].posicion.fila][juego.huertas[i].cultivos[j].posicion.columna] = juego.huertas[i].cultivos[j].tipo;
		}
	}


	for (int i = 0; i < juego.tope_objetos; i++){
		terreno[juego.objetos[i].posicion.fila][juego.objetos[i].posicion.columna] = juego.objetos[i].tipo;
	}

	terreno[juego.jugador.posicion.fila][juego.jugador.posicion.columna] = BLANCANIEVES;

	terreno[juego.deposito.fila][juego.deposito.columna] = DEPOSITO;

	for (int i = 0; i < DIMENSION; i++){
		for (int j = 0; j < DIMENSION; j++){
			printf(" %c",terreno[i][j]);
		} 
		printf("\n");
  	}

}

int estado_juego(juego_t juego){

	if (juego.jugador.cant_monedas <= MONEDAS_PARA_PERDER){
		printf("PERDISTE\n");
		return PERDIDO;
	}else if (juego.jugador.cant_monedas >= MONEDAS_PARA_GANAR){
		printf("GANASTE!\n");
		return GANADO;
	}else{
		return JUGANDO;
	}

}