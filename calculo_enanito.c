#include <stdio.h>
#include <stdbool.h>
#include "calculo_enanito.h"

const char INVIERNO = 'I';
const char VERANO = 'V';

const int PUNTAJE_LECHUGA = 0;
const int PUNTAJE_BROCOLI = 5;
const int PUNTAJE_ZANAHORIA = 10;
const int PUNTAJE_TOMATE = 15;

const int MIN_PUNTAJE_ENOJO = 0;
const int MAX_PUNTAJE_ENOJO = 5;

const int PUNTAJE_TEAM_VERANO = 10;
const int PUNTAJE_TEAM_INVIERNO = 0;

const float MIN_TIEMPO_CULTIVO = 40;
const float MAX_TIEMPO_CULTIVO = 120;

const float DIVISION_PUNTAJE_FINAL = 8.0;

const int MIN_PUNTAJE_GRUNION = 0;
const int MAX_PUNTAJE_GRUNION = 9;

const int MIN_PUNTAJE_DORMILON = 10;
const int MAX_PUNTAJE_DORMILON = 19;

const int MIN_PUNTAJE_SABIO = 20;
const int MAX_PUNTAJE_SABIO = 29;

const int PUNTAJE_FELIZ = 30;

/*
-Pre:
-Post: Verifica que la verdura elegida sea correcta.
*/
bool es_verdura_correcta(char verdura_elegida){
	return (verdura_elegida == LECHUGA || verdura_elegida == BROCOLI || verdura_elegida == ZANAHORIA || verdura_elegida == TOMATE);
}

/*
-Pre:
-Post: Verifica que la estacion elegida sea correcta.
*/
bool es_estacion_correcta(char estacion_elegida){
	return (estacion_elegida == VERANO || estacion_elegida == INVIERNO);
}

/*
-Pre:
-Post: Verifica que el nivel de enojo elegido sea correcto.
*/
bool es_nivel_enojo_correcto(int nivel){
	return (nivel >= MIN_PUNTAJE_ENOJO && nivel <= MAX_PUNTAJE_ENOJO);
}

/*
-Pre:
-Post: Verifica que el numero ingresado este dado entre los rangos establecidos y sea correcto.
*/
bool es_tiempo_cultivo_correcto(float tiempo_cosecha){
	return (tiempo_cosecha >= MIN_TIEMPO_CULTIVO && tiempo_cosecha <= MAX_TIEMPO_CULTIVO);
}

/*
-Pre:
-Post: Se selecciona la verdura favorita y verifica que sea correcta.
*/
void elegir_verdura_favorita(char *verdura_elegida){

	printf("¿Cual es tu verdura favorita entre Lechuga (%c), Brocoli (%c), Zanahoria (%c), Tomate (%c)?: ", LECHUGA, BROCOLI, ZANAHORIA, TOMATE);
	scanf(" %c", verdura_elegida);

	while(!(es_verdura_correcta(*verdura_elegida))){
		printf("NO! Ingresaste mal, volve a ingresar \n");
		printf("¿Cual es tu verdura favorita entre Lechuga (A), Brocoli (B), Zanahoria (C), Tomate (D)?: ");
		scanf(" %c", verdura_elegida);
	}
}

/*
-Pre:
-Post: Asigna un puntaje respecto a la verdura elegida
*/
void puntaje_verdura_elegida(char verdura_elegida, int *puntaje_enanito){

	if (verdura_elegida == LECHUGA){
		*puntaje_enanito = PUNTAJE_LECHUGA;
	}else if (verdura_elegida == BROCOLI){
		*puntaje_enanito = PUNTAJE_BROCOLI;
	}else if (verdura_elegida == ZANAHORIA){
		*puntaje_enanito = PUNTAJE_ZANAHORIA;
	}else{
		*puntaje_enanito = PUNTAJE_TOMATE;
	}
}

/*
-Pre:
-Post: Se selecciona la estacion favorita y se verifica que sea correcta la eleccion.
*/
void elegir_estacion_favorita(char *estacion_elegida){

	printf("¿Cual es tu estacion favorita entre Verano (%c) e Invierno (%c)?: ", VERANO, INVIERNO);
	scanf(" %c", estacion_elegida);

	while(!(es_estacion_correcta(*estacion_elegida))){
		printf("NO! Ingresaste mal, volve a ingresar \n");
		printf("¿Cual es tu estacion favorita entre Verano (%c) e Invierno (%c)?: ", VERANO, INVIERNO);
		scanf(" %c", estacion_elegida);
	}
}

/*
-Pre:
-Post: Asigna un puntaje respecto a la estacion elegida
*/
void puntaje_estacion_elegida(char estacion_elegida, int *puntaje_enanito){
	if (estacion_elegida == VERANO){
		*puntaje_enanito = *puntaje_enanito + PUNTAJE_TEAM_VERANO;
	}else{
		*puntaje_enanito = *puntaje_enanito + PUNTAJE_TEAM_INVIERNO;
	}
}

/*
-Pre:
-Post: Se selecciona el nivel de enojo segun la estacion elegida y se verifica que sea correcto.
*/
void preguntar_enojo(char estacion_elegida, int *puntaje_enanito, int *nivel_enojo){

	if (estacion_elegida == VERANO){
		printf("Cuanto te enojan los mosquitos?? (entre 0 y 5) : ");
		scanf("%i", nivel_enojo);
		while(!(es_nivel_enojo_correcto(*nivel_enojo))){
			printf("NO! Te equivocaste, ingresaste un numero erroneo.\n");
			printf("Cuanto te enojan los mosquitos?? (entre 0 y 5) : ");
			scanf("%i", nivel_enojo);
		}
	}else{
		printf("Cuanto te enoja trabajar abajo de la lluvia?? (entre 0 y 5): ");
		scanf("%i", nivel_enojo);
		while(!(es_nivel_enojo_correcto(*nivel_enojo))){
			printf("NO! Te equivocaste, ingresaste un numero erroneo.\n");
			printf("Cuanto te enoja trabajar abajo de la lluvia?? (entre 0 y 5): ");
			scanf("%i", nivel_enojo);
		}
	}
}

/*
-Pre:
-Post: Asigna un puntaje respecto al nivel de enojo elegido.
*/
void puntar_enojo(int *puntaje_enanito, int *nivel_enojo){
	*puntaje_enanito = *puntaje_enanito - *nivel_enojo;
}

/*
-Pre: El numero tiene que ser positivo y estar en un rango dado
-Post: Se determina cuanto tiempo tardas en hacer la accion
*/
void cosechar_cultivo(float *tiempo_cosecha){

	printf("Cuanto tiempo te llevaria cosechar un cultivo de 10m²? (Entre 40 y 120 minutos podes usar decimales): ");
	scanf("%f", tiempo_cosecha);

	while(!(es_tiempo_cultivo_correcto(*tiempo_cosecha))){
		printf("NO! Ingresaste un numero incorrecto, ingresa de nuevo.\n");
		printf("Cuanto tiempo te llevaria cosechar un cultivo de 10m²? (Entre 40 y 120 minutos podes usar decimales): ");
		scanf("%f", tiempo_cosecha);
	}
}

/*
-Pre: Recibe el puntaje de todas las preguntas anteriores.
-Post: Devuelve el puntaje total en base a las respuestas dadas.
*/
float calcular_puntaje(float tiempo_cosecha, int puntaje_enanito){

	float puntaje_final = 0;

	puntaje_final = ((float)tiempo_cosecha/DIVISION_PUNTAJE_FINAL)+(float)puntaje_enanito;
	printf("El puntaje es: %.2f\n", puntaje_final);

	return puntaje_final;
}

void calcular_enanito(char *inicial_enanito){

	printf("Bienvenido al test de personalidad!\n");
	printf("Aca vas a saber que enanito sos, solo tenes que responder las siguientes preguntas:\n");
	printf("\n");

	char verdura_elegida;
	char estacion_elegida;
	int puntaje_enanito = 0;
	int nivel_enojo = 0;
	float tiempo_cosecha = 0;

	elegir_verdura_favorita(&verdura_elegida);
	puntaje_verdura_elegida(verdura_elegida, &puntaje_enanito);
	elegir_estacion_favorita(&estacion_elegida);
	puntaje_estacion_elegida(estacion_elegida, &puntaje_enanito);
	preguntar_enojo(estacion_elegida, &puntaje_enanito, &nivel_enojo);
	puntar_enojo(&puntaje_enanito, &nivel_enojo);
	cosechar_cultivo(&tiempo_cosecha);
	float puntaje_total = calcular_puntaje(tiempo_cosecha, puntaje_enanito);

	if (puntaje_total >= MIN_PUNTAJE_GRUNION && puntaje_total <= MAX_PUNTAJE_GRUNION){
		printf("De acuerdo a las respuestas dadas sos el enanito -GRUÑÓN- \n");
		*inicial_enanito = GRUNION;
	}else if (puntaje_total >= MIN_PUNTAJE_DORMILON && puntaje_total <= MAX_PUNTAJE_DORMILON){
		printf("De acuerdo a las respuestas dadas sos el enanito -DORMILÓN- \n");
		*inicial_enanito = DORMILON;
	}else if (puntaje_total >= MIN_PUNTAJE_SABIO && puntaje_total <= MAX_PUNTAJE_SABIO){
		printf("De acuerdo a las respuestas dadas sos el enanito -SABIO- \n");
		*inicial_enanito = SABIO;
	}else{
		printf("De acuerdo a las respuestas dadas sos el enanito -FELIZ- \n");
		*inicial_enanito = FELIZ;
	}
}