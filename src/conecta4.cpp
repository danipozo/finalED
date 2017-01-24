#include "conecta4.h"

void modificarTurno(int t, Tablero& tab)
{
  if(tab.cambiarTurno() != t)
    tab.cambiarTurno();
}

void Conecta4::generarArbolMovimientos(ArbolGeneral<Tablero>::Nodo n, int p)
{
  if(p == profundidad)
    return;

  Tablero copiaTablero(n->etiqueta.GetFilas(), n->etiqueta.GetColumnas());
  modificarTurno(n->etiqueta.GetTurno() == 1 ? 2 : 1, copiaTablero);

  for(int i=0; i<n->etiqueta.GetColumnas(); i++)
  {
    if(n->etiqueta.hayHueco(i) == -1)
        continue;

    copiaTablero = n->etiqueta;
    copiaTablero.colocarFicha(i);

    ArbolGeneral<Tablero> a(copiaTablero);
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

int Conecta4::calcularMejorMovimiento()
{
  generarArbolMovimientos(arbol.raiz());
  auto arbolInt = aplicarFuncion(arbol, f);

  arbol.recorrer_por_niveles(arbol.raiz());
  arbolInt.recorrer_por_niveles(arbolInt.raiz());
}
