#ifndef _CALCULO_ENANITO_H_
#define _CALCULO_ENANITO_H_

#define GRUNION 'G'
#define DORMILON 'D'
#define SABIO 'S'
#define FELIZ 'F'

#define LECHUGA 'A'
#define BROCOLI 'B'
#define ZANAHORIA 'C'
#define TOMATE 'D'

#define JUGANDO 0
#define GANADO 1
#define PERDIDO -1


/*
Pre: -
Post: Se le harán preguntas al usuario y en base a sus respuestas se le asignará un enanito. El enanito asignado será devuelto por referencia en el parámetro inicial_enanito que va a contener su inicial.
G: Gruñón
D: Dormilón
S: Sabio
F: Feliz
*/
void calcular_enanito(char* inicial_enanito);


#endif /*_CALCULO_ENANITO_H_*/