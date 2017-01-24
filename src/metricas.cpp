#include "metricas.h"

std::pair<int,int> metrica1(std::pair<int,Tablero> t)
{
  
    if(t.second.quienGana() == t.second.GetTurno())
      return std::make_pair(t.first,1000);

    else if(t.second.quienGana() == (t.second.GetTurno() == 1 ? 2 : 1))
      return std::make_pair(t.first, -1000);

    return std::make_pair(t.first, 0);
}
