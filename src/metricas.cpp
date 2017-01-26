#include "metricas.h"

int metrica1(Tablero t)
{

  if(t.quienGana())
    {
      std::cout << "Turno: " << t.GetTurno() << " gana: " << t.quienGana() << std::endl;
      std::cout << t << std::endl;
      return 1000;
    }

    return 0;
}
