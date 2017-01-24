#include <iostream>

using namespace std;

#include "conecta4.h"

int main()
{
  Tablero t(3, 3);

  Conecta4 c(t, 2);
  c.calcularMejorMovimiento();

  ArbolGeneral<Tablero> a = c.obtenerArbol();

  //a.recorrer_por_niveles(a.raiz());

  return 0;
}
