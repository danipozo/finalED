#include "conecta4.h"

std::ostream& operator<<(std::ostream& os, std::pair<int,Tablero> p)
{
  os << p.second;

  return os;
}

std::ostream& operator<<(std::ostream& os, std::pair<int,int> p)
{
  os << p.second;

  return os;
}

void modificarTurno(int t, Tablero& tab)
{
  if(tab.cambiarTurno() != t)
    tab.cambiarTurno();
}

void Conecta4::generarArbolMovimientos(ArbolGeneral<std::pair<int,Tablero>>::Nodo n, int p)
{
  if(p == profundidad)
    return;

  Tablero copiaTablero(n->etiqueta.second.GetFilas(), n->etiqueta.second.GetColumnas());
  modificarTurno(n->etiqueta.second.GetTurno() == 1 ? 2 : 1, copiaTablero);

  for(int i=0; i<n->etiqueta.second.GetColumnas(); i++)
  {
    if(n->etiqueta.second.hayHueco(i) == -1)
        continue;

    copiaTablero = n->etiqueta.second;
    copiaTablero.colocarFicha(i);

    ArbolGeneral<std::pair<int,Tablero>> a(std::make_pair(i,copiaTablero));
    arbol.insertar_hijomasizquierda(n, a);

    generarArbolMovimientos(n->izqda, p+1);
  }
}

// FIXME: ONLY FOR TESTING PURPOSES.
#include <utility>

std::ostream& operator<<(std::ostream& os, std::pair<Tablero,int> p)
{
  os << "Número: " << p.second << std::endl;
  os << p.first << std::endl;

  return os;
}

std::pair<Tablero,int> f(Tablero t)
{
  static int i=0;
  return std::make_pair(t, i++);
}

int f2(Tablero t)
{
  return 5;
}

std::pair<int,int> fn_no_terminal(std::pair<int,Tablero> t)
{
  return std::make_pair(t.first, 0);
}

std::pair<int,int> fn_terminal(std::pair<int,Tablero> t, int(*metrica)(Tablero))
{
  return std::make_pair(t.first, metrica(t.second));
}

int Conecta4::calcularMejorMovimiento()
{
  generarArbolMovimientos(arbol.raiz());
  //auto arbolInt = aplicarFuncion(arbol, f);
  auto fn_term = std::bind(fn_terminal, std::placeholders::_1, metrica1);
  auto arbolInt2 = aplicarFuncionHojas(arbol, fn_term, fn_no_terminal);

  arbol.recorrer_por_niveles(arbol.raiz());
  //arbolInt.recorrer_por_niveles(arbolInt.raiz());
  arbolInt2.recorrer_por_niveles(arbolInt2.raiz());
}
