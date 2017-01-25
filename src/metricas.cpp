#include "metricas.h"

int metrica1(Tablero t)
{

    if(t.quienGana() == t.GetTurno())
      return 1000;

    else if(t.quienGana() == (t.GetTurno() == 1 ? 2 : 1))
      return -1000;

    return 0;
}
