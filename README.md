# TP Poker 
## Algoritmo y Estrutura de Datos - Curso de verano 2020

Realizar un programa que permita jugar al poker. Al iniciar el juego se deberá determinar la cantidad de rondas y la cantidad de jugadores. Gana la ronda el jugador que tiene la combinación de mayor valor, y se suman los resultados parciales de cada ronda para determinar el ganador del torneo.

En caso de empate, gana la jugada con las cartas más altas (siendo el As la carta de mayor valor). En caso de tener exactamente las mismas cartas, gana el más próximo al jugador mano (el que ha empezado la ronda).

Valor de las jugadas
Escalera Real: 5 cartas seguidas del mismo palo desde el 10 al As.
Probabilidad: 1 entre 649.739

Escalera: idem pero de cualquier palo

Full: 3 cartas iguales más otras dos iguales. Es decir, un trio y una pareja. En caso de empate, gana el que tiene el trio más alto.
Probabilidad: 1 entre 693.

Color: Las 5 cartas del mismo palo.
Probabilidad: 1 entre 507.

Trío - 3 cartas iguales.
Probabilidad: 1 entre 46.

Doble Pareja - Dos parejas de cartas iguales.
Probabilidad: 1 entre 20.

Pareja - Una pareja de cartas iguales.
Probabilidad: 1 entre aproximadamente 2

Poker: 4 cartas iguales.
Probabilidad: 1 entre 4.164.

Carta más alta - El As es la carta más alta.

Deberan asignarle valor a cada posible juego para poder contabilizar cada ronda. Puede utilzar cualquier estructura que le resulte conveniente.
Para repartir las cartas deben utilizar números aleatorios e ir sacando del mazo. Dicho mazo puede tener 3 posibilidades: archivo, vector o lista.
Como jugar:
1) ingresar cantidad de manos
2) Ingresar cantidad de jugadores
3) repartir 5 cartas a cada jugador
4) mostrar las cartas del jugador 1 , preguntar cuales desea cambiar, sacar del mazo las n nuevas cartas.
5) repetir paso 4 hasta completar los n jugadores.
6) calcular y guardar el resultado parcial
7) completar las m rondas e informar ganador

Entregas
1° Entrega: 14/2 juego utilizando vectores para almacenar cartas.
2° Entrega: 4/3 completar con los metodos con archivo y listas y entregar un ranking de jugadores con el nombre y el resultado final
