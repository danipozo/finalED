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

    //copiaTablero.cambiarTurno();
    copiaTablero.colocarFicha(i);

    ArbolGeneral<Tablero> a(copiaTablero); // WARNING: might explode.
    arbol.insertar_hijomasizquierda(n, a);

    generarArbolMovimientos(n->izqda, p+1);
  }
}

int Conecta4::calcularMejorMovimiento()
{
  generarArbolMovimientos(arbol.raiz(), 0); // FIXME: Hardcoded value.
}
