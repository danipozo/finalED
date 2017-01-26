#include "metricas.h"

int metrica1(Tablero t)
{

  if(t.quienGana())
    return 1000;

    return 0;
}

int DatoEn(int fila, int columna, std::vector<std::vector<int>> t)
{
  int filas = t.size();
  int columnas = t[0].size();

  if(fila == -1 || fila == filas || columna == -1 || columna == columnas)
    return 0;

  return t[fila][columna];
}

int signo(int i)
{
    if(i < 0) return -1;

    return i ? 1 : 0;
}


void AvanzarEnDireccion(int f, int c, int& i, int& j, std::vector<std::vector<int>> matriz)
{
  while(DatoEn(f,c,matriz) == DatoEn(f+i,c+j,matriz)) { i += signo(i); j += signo(j); }
}

bool ComprobarNEnRaya(int f, int c, std::vector<std::vector<int>> matriz, int numeroAlinear)
{

    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
          if(DatoEn(f,c,matriz) == DatoEn(f+i,c+j,matriz) && (j != 0 || i != 0))
            {
                int i_temp = i, j_temp = j, f_temp = f, c_temp = c;
                AvanzarEnDireccion(f, c, i_temp, j_temp, matriz);

                f_temp += i_temp;
                c_temp += j_temp;

                if(i_temp) i_temp /= -std::abs(i_temp);
                if(j_temp) j_temp /= -std::abs(j_temp);

                AvanzarEnDireccion(f_temp+i_temp, c_temp+j_temp, i_temp, j_temp, matriz);

                if(std::abs(i_temp) == numeroAlinear || std::abs(j_temp) == numeroAlinear)
                    return true;

            }
        }
    }

    return false;
}


int metrica2(Tablero t)
{
  Tablero copia(t.GetFilas(), t.GetColumnas());
  int ret = 0;

  copia = t;
  copia.cambiarTurno();

  for(int i=0; i<t.GetColumnas(); i++)
  {
    int fila = t.hayHueco(i);
    if(fila == -1)
      continue;

    copia.colocarFicha(i);

    if(ComprobarNEnRaya(fila, i, copia.GetTablero(), 2))
      ret += 300;

    if(ComprobarNEnRaya(fila, i, copia.GetTablero(), 3))
      ret += 800;
    if(ComprobarNEnRaya(fila, i, copia.GetTablero(), 4))
      ret += 1000;

    copia = t;
  }

  return ret;
}
