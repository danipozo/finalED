#ifndef CONECTA4_H
#define CONECTA4_H

#include "ArbolGeneral.h"
#include "tablero.h"


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

  // Este nodo es necesario por la forma en que se insertan los nodos en un aŕbol
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


/*
  El objetivo es que ArbolGeneral con esta funcion sea un funtor (en el sentido en
  en que se suele usar en el contexto de la programación funcional).
  Esto nos servirá posteriormente para aplicar las métricas sobre los árboles de forma cómoda,
  pudiendo aplicarla a todos los tableros del árbol de una vez, y después propagar hacia arriba
  los valores heurísticos de los tableros (como en el algoritmo negamax) de una forma genérica,
  sin necesidad de que lo haga cada métrica.
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
}


class Conecta4
{
  ArbolGeneral<Tablero> arbol;
  int profundidad;

  void generarArbolMovimientos(ArbolGeneral<Tablero>::Nodo n, int p = 0);
  void aplicarMetrica();
public:
  Conecta4() { }
  Conecta4(const Tablero& t, int profundidad) : arbol(t), profundidad(profundidad) { }

  int calcularMejorMovimiento();

  ArbolGeneral<Tablero>& obtenerArbol() { return arbol; }
};


#endif // CONECTA4_H
