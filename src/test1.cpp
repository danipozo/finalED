#include <iostream>

using namespace std;

#include "conecta4.h"

int main()
{
  Tablero t(4, 2);

  Conecta4 c(t, 8);
  c.calcularMejorMovimiento();

  auto a = c.obtenerArbol();

  //a.recorrer_por_niveles(a.raiz());

  return 0;
}
