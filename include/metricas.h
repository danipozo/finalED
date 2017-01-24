#ifndef METRICAS_H
#define METRICAS_H

#include "tablero.h"
#include <utility>

/*
 * FIXME: La idea no es que las propias métricas se encarguen de devolver un par (últ. movimiento,valor heurístico),
 * sino que devuelvan solo el valor heurístico y otra función se encargue de usar aplicarFuncionHojas con una función
 * que tome los nodos del árbol y devuelva (últ. movimiento, metrica(tablero)).
 *
 * FIXME: Para evitar que, al construir los pares por defecto en aplicarFuncionHojas, se pierdan los últimos
 * movimientos de los nodos no terminales, generalizarla y permitir que tome una función que inicialice los nodos
 * no terminales. Así, esta función pasaría a ser equivalente a aplicarFuncion, solo que aplicaría funciones distintas
 * a nodos terminales y no terminales. Por otro lado, esto permitiría la implementación de aplicarFuncion como el caso
 * de aplicarFuncionHojas en el que ambas funciones son iguales.
 */

/*
 * Métrica binaria. Devuelve un valor heurístico lo suficientemente grande en valor absoluto
 * como para que el tablero sea seleccionado si corresponde a una victoria de alguno de los jugadores.
 */
std::pair<int,int> metrica1(std::pair<int,Tablero> t);


#endif // METRICAS_H
