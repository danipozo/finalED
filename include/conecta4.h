#ifndef CONECTA4_H
#define CONECTA4_H

#include "ArbolGeneral.h"
#include "tablero.h"
#include "metricas.h"
#include <utility>
#include <functional>

std::ostream& operator<<(std::ostream& os, std::pair<int,Tablero> p);

std::ostream& operator<<(std::ostream& os, std::pair<int,int> p);

template <class A, class B>
void aplicarFuncion(typename ArbolGeneral<A>::Nodo n, B(*fn)(A), ArbolGeneral<B>& arbolB, typename ArbolGeneral<B>::Nodo n2)
{
  typename ArbolGeneral<A>::Nodo hijoA = n->izqda;

  if(!hijoA) // WARNING: Not sure of condition.
    return;

  // Nota: la exposición de los detalles de implementación de la clase
  // ArbolGeneral, concretamente la forma en que se implementa el número
  // variable de hijos de un nodo, con un hijo a la izquierda y los demás a su derecha,
  // fuerzan a duplicar una parte del código en esta función, teniendo que tratar estos
  // dos casos por separado.
  ArbolGeneral<B> aux(fn(hijoA->etiqueta));
  arbolB.insertar_hijomasizquierda(n2, aux);

  aplicarFuncion(hijoA, fn, arbolB, n2->izqda);

  // Este nodo es necesario por la forma en que se insertan los nodos en un árbol
  // (no es consistente con la forma en que se recorren).
  typename ArbolGeneral<B>::Nodo nodoAux = n2->izqda;
  while(hijoA = hijoA->drcha) // WARNING: Not sure of condition.
  {
    aux.AsignaRaiz(fn(hijoA->etiqueta));
    arbolB.insertar_hermanoderecha(nodoAux, aux);

    aplicarFuncion(hijoA, fn, arbolB, nodoAux);

    nodoAux = nodoAux->drcha;
  }
}

template <class A, class B, class FnTerm>
void aplicarFuncionHojas(typename ArbolGeneral<A>::Nodo n, FnTerm fn_terminal, B(*fn_no_terminal)(A), ArbolGeneral<B>& arbolB, typename ArbolGeneral<B>::Nodo n2)
{
  typename ArbolGeneral<A>::Nodo hijoA = n->izqda;

  if(!hijoA)
    return;

  ArbolGeneral<B> aux;

  if(hijoA->izqda == 0) // hijoA es una hoja.
    aux.AsignaRaiz(fn_terminal(hijoA->etiqueta));
  else aux.AsignaRaiz(fn_no_terminal(hijoA->etiqueta));

  arbolB.insertar_hijomasizquierda(n2, aux);

  aplicarFuncionHojas(hijoA, fn_terminal, fn_no_terminal, arbolB, n2->izqda);

  // Este nodo es necesario por la forma en que se insertan los nodos en un aŕbol
  // (no es consistente con la forma en que se recorren).
  typename ArbolGeneral<B>::Nodo nodoAux = n2->izqda;
  while(hijoA = hijoA->drcha) // WARNING: Not sure of condition.
  {
      aux = ArbolGeneral<B>();
      if(hijoA->izqda == 0) // hijoA es una hoja.
        aux.AsignaRaiz(fn_terminal(hijoA->etiqueta));
      else aux.AsignaRaiz(fn_no_terminal(hijoA->etiqueta));

      arbolB.insertar_hermanoderecha(nodoAux, aux);

      aplicarFuncionHojas(hijoA, fn_terminal, fn_no_terminal, arbolB, nodoAux);

      nodoAux = nodoAux->drcha;
  }
}

/*
 * Esta función creará un árbol con elementos de tipo B, con la misma estructura que el
 * primer árbol, cuyas hojas serán el resultado de aplicar *fn* a las hojas del primer árbol,
 * y el resto de nodos serán inicializados por defecto.
 *
 * El objetivo de esta función es poder usarla para evaluar las métricas solo en los tableros
 * finales.
 */
template <class A, class B, class FnTerm>
ArbolGeneral<B> aplicarFuncionHojas(const ArbolGeneral<A>& arbol, FnTerm fn_terminal, B(*fn_no_terminal)(A))
{
  ArbolGeneral<B> ret;
  if(arbol.empty())
    return ret;

  typename ArbolGeneral<A>::Nodo n = arbol.raiz();
  ret.AsignaRaiz(fn_no_terminal(n->etiqueta));

  aplicarFuncionHojas(n, fn_terminal, fn_no_terminal, ret, ret.raiz());

  return ret;
}

/*
  El objetivo es que ArbolGeneral con esta función sea un funtor (en el sentido en
  en que se suele usar en el contexto de la programación funcional).
  Esto nos servirá posteriormente para aplicar las métricas sobre los árboles de forma cómoda,
  pudiendo aplicarla a todos los tableros del árbol de una vez, y después propagar hacia arriba
  los valores heurísticos de los tableros (como en el algoritmo negamax) de una forma genérica,
  sin necesidad de que lo haga cada métrica.

  Nota: implementar, de forma genérica, el cambio de signo de la heurística según el turno.
  Posible implementación: versión de aplicarFuncion sin copia (solo válida para el caso A=B).
 */
template <class A, class B>
ArbolGeneral<B> aplicarFuncion(const ArbolGeneral<A>& arbol, B(*fn)(A))
{
  ArbolGeneral<B> ret;
  if(arbol.empty())
    return ret;

  typename ArbolGeneral<A>::Nodo n = arbol.raiz();
  ret.AsignaRaiz(fn(n->etiqueta));

  aplicarFuncion(n, fn, ret, ret.raiz());

  return ret;
}


class Conecta4
{
  ArbolGeneral<std::pair<int,Tablero>> arbol;
  ArbolGeneral<std::pair<int,int>> arbolHeuristico; // Pares jugada/valor heurístico.
  int profundidad;

  void generarArbolMovimientos(ArbolGeneral<std::pair<int,Tablero>>::Nodo n, int p = 0);
  //void aplicarMetrica();
public:
  Conecta4() { }
  Conecta4(const Tablero& t, int profundidad) : arbol(std::make_pair(-1, t)), profundidad(profundidad) { }

  int calcularMejorMovimiento();

  ArbolGeneral<std::pair<int,Tablero>>& obtenerArbol() { return arbol; }
};


#endif // CONECTA4_H
