#ifndef CONECTA4_H
#define CONECTA4_H

#include "ArbolGeneral.h"
#include "tablero.h"
#include "metricas.h"
#include <utility>
#include <functional>

std::ostream& operator<<(std::ostream& os, std::pair<int,Tablero> p);

std::ostream& operator<<(std::ostream& os, std::pair<int,int> p);

template <class A, class B, class FnTerm>
void aplicarFuncionHojas(typename ArbolGeneral<A>::Nodo n, FnTerm fn_terminal,
                         B(*fn_no_terminal)(A), ArbolGeneral<B>& arbolB,
                         typename ArbolGeneral<B>::Nodo n2);

/*
 * Esta función creará un árbol con elementos de tipo B, con la misma estructura que el
 * primer árbol, cuyas hojas serán el resultado de aplicar *fn_terminal* a las hojas
 * del primer árbol, y *fn_no_terminal* al resto de nodos.
 *
 * El objetivo de esta función es poder usarla para evaluar las métricas solo en los tableros
 * finales. Esto nos servirá posteriormente para aplicar las métricas sobre los árboles de
 * forma cómoda, pudiendo aplicarla a todos los tableros del árbol de una vez, y después propagar
 * hacia arriba los valores heurísticos de los tableros (como en el algoritmo negamax) de una
 * forma genérica, sin necesidad de que lo haga cada métrica.
 */
template <class A, class B, class FnTerm>
ArbolGeneral<B> aplicarFuncionHojas(const ArbolGeneral<A>& arbol, FnTerm fn_terminal,
                                    B(*fn_no_terminal)(A));

class Conecta4
{
  ArbolGeneral<std::pair<int,Tablero>> arbol;
  ArbolGeneral<std::pair<int,int>> arbolHeuristico; // Pares jugada/valor heurístico.
  int profundidad;
  int (*metrica)(Tablero);

  void generarArbolMovimientos(ArbolGeneral<std::pair<int,Tablero>>::Nodo n, int p = 0);
  void propagarValoresHeuristicos(ArbolGeneral<std::pair<int,int>>::Nodo n);
public:
  Conecta4() { }
  //FIXME: Eliminar parámetro por defecto.
  Conecta4(const Tablero& t, int profundidad, int(*metrica)(Tablero) = metrica1) : arbol(std::make_pair(-1, t)), profundidad(profundidad), metrica(metrica) { }

  int calcularMejorMovimiento();
  void modificarMetrica(int(*m)(Tablero));

  ArbolGeneral<std::pair<int,Tablero>>& obtenerArbol() { return arbol; }
};


#endif // CONECTA4_H
