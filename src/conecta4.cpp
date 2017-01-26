#include "conecta4.h"

std::ostream& operator<<(std::ostream& os, std::pair<int,Tablero> p)
{
  os <<  p.second;

  return os;
}

std::ostream& operator<<(std::ostream& os, std::tuple<int,int,Tablero> t)
{
  os << "Jugada: " << std::get<0>(t) << std::endl;
  os << "Valor: " << std::get<1>(t) << std::endl;
  os << std::get<2>(t) << std::endl;
}

std::ostream& operator<<(std::ostream& os, std::pair<int,int> p)
{
  os << p.second;

  return os;
}

//FIXME: Obsoleta. Limpiar.
//FIXME: altera la estructura del árbol.
// template <class A, class B, class FnTerm>
// void aplicarFuncionHojas(typename ArbolGeneral<A>::Nodo n, FnTerm fn_terminal, B(*fn_no_terminal)(A), ArbolGeneral<B>& arbolB, typename ArbolGeneral<B>::Nodo n2)
// {
//   typename ArbolGeneral<A>::Nodo hijoA = n->izqda;

//   if(!hijoA)
//     return;

//   ArbolGeneral<B> aux;

//   if(hijoA->izqda == 0) // hijoA es una hoja.
//     aux.AsignaRaiz(fn_terminal(hijoA->etiqueta));
//   else
//     aux.AsignaRaiz(fn_no_terminal(hijoA->etiqueta));

//   arbolB.insertar_hijomasizquierda(n2, aux);

//   aplicarFuncionHojas(hijoA, fn_terminal, fn_no_terminal, arbolB, n2->izqda);

//   // Este nodo es necesario por la forma en que se insertan los nodos en un aŕbol
//   // (no es consistente con la forma en que se recorren).
//   typename ArbolGeneral<B>::Nodo nodoAux = n2->izqda;
//   while(hijoA = hijoA->drcha) // WARNING: Not sure of condition.
//   {
//       aux = ArbolGeneral<B>();
//       if(hijoA->izqda == 0) // hijoA es una hoja.
//         aux.AsignaRaiz(fn_terminal(hijoA->etiqueta));
//       else
//         aux.AsignaRaiz(fn_no_terminal(hijoA->etiqueta));

//       arbolB.insertar_hermanoderecha(nodoAux, aux);

//       nodoAux = nodoAux->drcha;
//       aplicarFuncionHojas(hijoA, fn_terminal, fn_no_terminal, arbolB, nodoAux);
//   }
// }

//FIXME: TEST
template<class A>
void recorrerImprimir(typename ArbolGeneral<A>::Nodo n, int p)
{
  if(!n->izqda)
    return;

  std::cout << "Profundidad: " << p << " hijo izquierda: " << n->izqda->etiqueta << std::endl;
  recorrerImprimir<A>(n->izqda, p+1);

  typename ArbolGeneral<A>::Nodo aux = n->izqda;

  while(aux = aux->drcha)
  {
    std::cout << "Profundidad: " << p << " hijo derecha: " << aux->etiqueta << std::endl;
    recorrerImprimir<A>(aux, p+1);
  }
}

//FIXME: Obsoleta. Limpiar.
// template <class A, class B, class FnTerm>
// ArbolGeneral<B> aplicarFuncionHojas(const ArbolGeneral<A>& arbol, FnTerm fn_terminal, B(*fn_no_terminal)(A))
// {
//   ArbolGeneral<B> ret;
//   if(arbol.empty())
//     return ret;

//   typename ArbolGeneral<A>::Nodo n = arbol.raiz();
//   ret.AsignaRaiz(fn_no_terminal(n->etiqueta));

//   aplicarFuncionHojas(n, fn_terminal, fn_no_terminal, ret, ret.raiz());

//   return ret;
// }


void Conecta4::modificarMetrica(int (*m)(Tablero))
{
  metrica = m;
}

void modificarTurno(int t, Tablero& tab)
{
  if(tab.cambiarTurno() != t)
    tab.cambiarTurno();
}


void Conecta4::generarArbolMovimientos(ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo n, int p)
{
  if(p == profundidad)
    return;

  if(std::get<2>(n->etiqueta).quienGana())
    return;

  Tablero copiaTablero(std::get<2>(n->etiqueta).GetFilas(), std::get<2>(n->etiqueta).GetColumnas());
  modificarTurno(std::get<2>(n->etiqueta).GetTurno() == 1 ? 2 : 1, copiaTablero);

  for(int i=0; i<std::get<2>(n->etiqueta).GetColumnas(); i++)
  {
    if(std::get<2>(n->etiqueta).hayHueco(i) == -1)
        continue;

    copiaTablero = std::get<2>(n->etiqueta);
    copiaTablero.colocarFicha(i);

    ArbolGeneral<std::tuple<int,int,Tablero>> a(std::make_tuple(i,metrica(copiaTablero),copiaTablero));
    arbol.insertar_hijomasizquierda(n, a);

    generarArbolMovimientos(n->izqda, p+1);
  }
}


std::pair<int,int> fn_no_terminal(std::pair<int,Tablero> t)
{
  return std::make_pair(t.first, 0);
}

int valorHeuristico(ArbolGeneral<std::pair<int,int>>::Nodo n)
{
  if(!n->izqda)
    return n->etiqueta.second;

  int ret = valorHeuristico(n->izqda);
  ArbolGeneral<std::pair<int,int>>::Nodo hijo = n->izqda; 

  while(hijo = hijo->drcha)
  {
    if(valorHeuristico(hijo) > ret)
      ret = valorHeuristico(hijo);
  }

  return ret;
}

//FIXME: Propagar valores correctamente.
void Conecta4::propagarValoresHeuristicos(ArbolGeneral<std::pair<int,int>>::Nodo n)
{
  if(!n->izqda)
    return;

  ArbolGeneral<std::pair<int,int>>::Nodo hijo = n->izqda;
  hijo->etiqueta.second = valorHeuristico(hijo);

  while(hijo = hijo->drcha)
    hijo->etiqueta.second = valorHeuristico(hijo);
}

std::pair<int,int> fn_terminal(std::pair<int,Tablero> t, int(*metrica)(Tablero))
{
  return std::make_pair(t.first, t.second.GetTurno() == 2 ? metrica(t.second) : -metrica(t.second));
}

//FIXME: Implementar.
int Conecta4::calcularMejorMovimiento()
{
  //WARNING: puede fallar después de la primera llamada.
  generarArbolMovimientos(arbol.raiz());
  arbol.recorrer_por_niveles(arbol.raiz());

  auto fn_term = std::bind(fn_terminal, std::placeholders::_1, metrica);
  //arbolHeuristico = aplicarFuncionHojas(arbol, fn_term, fn_no_terminal);

  //arbolHeuristico = ArbolGeneral<std::pair<int,int>>();
  //arbolHeuristico.AsignaRaiz(fn_no_terminal(arbol.raiz()->etiqueta));
  //aplicarFuncionHojas(arbol.raiz(), fn_term, fn_no_terminal, arbolHeuristico, arbolHeuristico.raiz());

  //FIXME: implementar función que propague hacia arriba los valores heurísticos máximos.
  //propagarValoresHeuristicos(arbolHeuristico.raiz()->izqda->drcha);

  //FIXME: queda todo el árbol heurístico colgando del nodo izquierdo.
  //arbol.recorrer_por_niveles(arbol.raiz());
  //recorrerImprimir<std::pair<int,int>>(arbolHeuristico.raiz()->drcha, 1);
}
