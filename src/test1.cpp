#include <iostream>

using namespace std;

#include "conecta4.h"

int main()
{
  Tablero t(4, 2);

  Conecta4 c(t, 8);
  c.calcularMejorMovimiento();

  auto a = c.obtenerArbol();

  std::cout << "Altura del primer nivel: " << a.altura(a.raiz()) << std::endl;
  std::cout << "Altura del segundo nivel: " << a.altura(a.raiz()->izqda->drcha) << std::endl;
  std::cout << "Altura del tercer nivel: " << a.altura(a.raiz()->izqda->izqda->drcha) << std::endl;
  std::cout << "Altura del cuarto nivel: " << a.altura(a.raiz()->izqda->izqda->izqda->drcha) << std::endl;

  //a.recorrer_por_niveles(a.raiz());

  return 0;
}
