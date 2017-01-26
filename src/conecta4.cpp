#include "conecta4.h"


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

    int param;

    if(p == (profundidad-1))
      param = copiaTablero.GetTurno() == 2 ? metrica(copiaTablero) : -metrica(copiaTablero);
    else param = 0;

    ArbolGeneral<std::tuple<int,int,Tablero>> a(std::make_tuple(i,param,copiaTablero));
    arbol.insertar_hijomasizquierda(n, a);

    generarArbolMovimientos(n->izqda, p+1);
  }
}


std::pair<int,int> fn_no_terminal(std::pair<int,Tablero> t)
{
  return std::make_pair(t.first, 0);
}

int valorHeuristico(ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo n)
{
  if(!n->izqda)
    return std::get<1>(n->etiqueta);

  int ret = valorHeuristico(n->izqda);
  ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo hijo = n->izqda; 

  while(hijo = hijo->drcha)
  {
    if(valorHeuristico(hijo) > ret)
      ret = valorHeuristico(hijo);
  }

  return ret;
}

void Conecta4::propagarValoresHeuristicos(ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo n)
{
  if(!n->izqda)
    return;

  ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo hijo = n->izqda;
  std::get<1>(hijo->etiqueta) = valorHeuristico(hijo);

  while(hijo = hijo->drcha)
    std::get<1>(hijo->etiqueta) = valorHeuristico(hijo);
}

void Conecta4::actualizarTablero(const Tablero& t)
{
  arbol = ArbolGeneral<std::tuple<int,int,Tablero>>();
  arbol.AsignaRaiz(std::make_tuple(-1,0,t));
}

std::pair<int,int> fn_terminal(std::pair<int,Tablero> t, int(*metrica)(Tablero))
{
  return std::make_pair(t.first, t.second.GetTurno() == 2 ? metrica(t.second) : -metrica(t.second));
}

int Conecta4::calcularMejorMovimiento()
{
  generarArbolMovimientos(arbol.raiz());
  propagarValoresHeuristicos(arbol.raiz());

  auto n = arbol.raiz()->izqda;
  int ret = std::get<0>(n->etiqueta);
  int maxValor = std::get<1>(n->etiqueta);

  for(; n = n->drcha;)
  {
    if(maxValor < std::get<1>(n->etiqueta))
    {
      maxValor = std::get<1>(n->etiqueta);
      ret = std::get<0>(n->etiqueta);
    }
  }

  return ret;
 }
