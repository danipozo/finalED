#ifndef CONECTA4_H
#define CONECTA4_H

#include "ArbolGeneral.h"
#include "tablero.h"


class Conecta4
{
  ArbolGeneral<Tablero> arbol;
  int profundidad;

  void generarArbolMovimientos(ArbolGeneral<Tablero>::Nodo n, int p);
public:
  Conecta4() { }
  Conecta4(const Tablero& t, int profundidad) : arbol(t), profundidad(profundidad) { }

  int calcularMejorMovimiento();

  ArbolGeneral<Tablero>& obtenerArbol() { return arbol; }
};


#endif // CONECTA4_H
