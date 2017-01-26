#ifndef METRICAS_H
#define METRICAS_H

#include "tablero.h"
#include <utility>

/*
 * Métrica binaria. Devuelve un valor heurístico lo suficientemente grande en valor absoluto
 * como para que el tablero sea seleccionado si corresponde a una victoria de alguno de los jugadores.
 */
int metrica1(Tablero t);

int metrica2(Tablero t);


#endif // METRICAS_H
