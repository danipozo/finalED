#include <iostream>

using namespace std;

#include "conecta4.h"

int main()
{
  Tablero t(4, 2);

  Conecta4 c(t, 7);
  int m = c.calcularMejorMovimiento();

  std::cout << "Mejor movimiento: " << m << std::endl;
  //a.recorrer_por_niveles(a.raiz());

  return 0;
}
