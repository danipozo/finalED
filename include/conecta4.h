/**
 * @file   conecta4.h
 * @author Daniel Pozo Escalona
 * 
 * @brief  Fichero de cabecera del TDA Conecta4.
 */

#ifndef CONECTA4_H
#define CONECTA4_H

#include "ArbolGeneral.h"
#include "tablero.h"
#include "metricas.h"
#include <utility>
#include <tuple>
#include <functional>


/**
 * @brief TDA Conecta4.
 *
 *
 * Se encarga de explorar el árbol de posibilidades de una partida a partir de un tablero dado. Usa
 * una implementación del algoritmo negamax para hallar el movimiento óptimo a partir de una métrica.
 * 
 */

class Conecta4
{
  /**
   * @brief Árbol de posibilidades. Cada nodo contiene una tupla
   * (últ. mov., valor heurístico, tablero).
   * 
   */

  ArbolGeneral<std::tuple<int,int,Tablero>> arbol;
  int profundidad;		/**< Profundidad a la que se quiere explorar. */
  int (*metrica)(Tablero);	/**< Métrica con la que se evalúan los tableros. */

  /** 
   * Se encarga de generar el árbol de posibilidades y evaluar las hojas con la
   * métrica seleccionada.
   * 
   * @param n Nodo raíz del árbol.
   * @param p Profundidad inicial (cero).
   */
  void generarArbolMovimientos(ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo n, int p = 0);

  /** 
   * Se encarga de propagar hacia los hijos directos de la raíz los valores heurísticos
   * de las hojas.
   * 
   * @param n Nodo a partir del cual se quiere explorar el árbol y propagar los valores.
   */
  void propagarValoresHeuristicos(ArbolGeneral<std::tuple<int,int,Tablero>>::Nodo n);
public:
  /**
   * Constructor por defecto.
   */

  Conecta4() { }
  /** 
   * Constructor con los datos relevantes para la partida.
   * 
   * @param t Tablero inicial.
   * @param profundidad
   * @param metrica Métrica que se quiere emplear.
   */
  Conecta4(const Tablero& t, int profundidad, int(*metrica)(Tablero)) : arbol(std::make_tuple(-1, 0, t)), profundidad(profundidad), metrica(metrica) { }

  /** 
   * @return Columna que indica el mejor movimiento.
   */
  int calcularMejorMovimiento();
  /** 
   * El objeto pasa a emplear la métrica @e m.
   * @param m 
   */
  void modificarMetrica(int(*m)(Tablero));
  /** 
   * Destruye el árbol y lo inicializa como uno con un solo nodo, que contiene
   * el tablero @e t.
   * 
   * @param t 
   */
  void actualizarTablero(const Tablero& t);

  /** 
   * @return El árbol contenido en el objeto.
   */
  ArbolGeneral<std::tuple<int,int,Tablero>>& obtenerArbol() { return arbol; }
};


#endif // CONECTA4_H
