# Poker en C++
## (1er parte)


### El programa fue realizado con Dev-C++


Lo primero que hicimos fue crear un struct el cual será la estructura del mazo de cartas, lo que contiene el número, el palo (diamante, trébol, pica o corazón) y un booleano que nos indicará “true” si la carta salió, o “false” si la carta aún está en el mazo.

Comenzamos el programa preguntando al usuario la cantidad de rondas que desea jugar y la cantidad de jugadores; luego se creará una matriz que almacenará en las 8 filas los puntajes de las 8 jugadas (Escalera real, escalera, full, color, trío, doble pareja, pareja y poker), y como columnas la cantidad de jugadores identificándolos como jugador 1 en la posición 0, jugador 2 en la posición 1, y así sucesivamente. Después creamos dos vectores, uno tendrá el mazo completo de cartas y el otro, las cartas que tienen los jugadores en mano que serán “Jugadores x 5”.

La primera función que invocamos es la de crearVectorDeMazo(mazo); la cuál de manera automática nos creará un vector con todas las cartas, 53 en total.

Luego invocamos a repartirCartas(mazo, cart, M); que funciona de la siguiente manera: Dentro de un for() que tiene como condición iterar mientras que la variable inicializada en cero no llegue al tamaño del vector de las cartas en mano (Jugadores x 5), se genera un número random que lo utilizaremos para posicionarnos en algún lugar del vector del mazo de cartas completo, de esta forma iremos sacando cartas (cambiando el bool de un false a un true) hasta que se complete el vector de cartas en mano, es decir, copiando las cartas de un vector a otro.

Y por último, la función imprimirCartasDeJugadores(cart, M); que nos imprimirá las 5 cartas de cada jugador y se podrá evidenciar que las cartas se repartieron de forma aleatoria a cada jugador y sin repetir.
 
 
## (2da parte)

A continuación, luego de repartir las cartas a los 5 jugadores, creamos la función void muestraCartas() en la cual se invoca a la función void mostrarYCambiarCartas(), y lo que hace es mostrar las cartas del primer jugador, preguntar si quiere cambiarlas, y luego de cambiar todas las cartas que quiera cambiar, se muestra la nueva mano. En este proceso también invocamos a la función void meterCartaEnMazo() y esta nos permite cambiar la carta que el jugador desea, metiéndola en el mazo y aleatoriamente sacando una carta nueva y ponerla en el mismo lugar de donde la carta anterior fue sacada, y las cartas nuevas de la mano del jugador son mostradas luego de cambiar todas para que el jugador no especule sobre su nueva mano. Este proceso se repite con los N jugadores.

Antes de calcular los resultados, también agregamos la función void reiniciarPuntaje() que lo único que hace es inicializar todo el puntaje en 0, para no acumular “basura”.

Después de mostrar todas las manos de los jugadores, invocamos a void calcularResultados() y esta invoca a todas las funciones de las jugadas, es decir, invoca a  int escaleraReal() y suma 100 puntos en caso de que la mano sea escalera real, o suma 0, en caso de que no. De esta forma hacemos lo mismo con las otras funciones, cada una tiene un proceso distinto para comparar las cartas,  y solo suma UNA jugada por ronda: si un jugador tiene “doble pareja” solo se le suma su respectivo puntaje, y hasta la otra ronda, ese puntaje es el que acumula. La posición 8 en el vector de jugadores (jugadores[x][8]), guarda el puntaje total acumulado.

Luego mostramos los resultados de los jugadores, y por último reiniciamos los booleanos de las cartas poniéndolos en false y de esta forma, se simula que los jugadores ponen las cartas de sus manos en el mazo y así, continuar con la siguiente ronda. Todo este proceso de repartir, mostrar, calcular y reiniciar lo realizamos hasta completar las M rondas.

Por último hacemos el ranking, y lo hacemos con una lista; gracias a lo práctica que es la función insertarOrdenado, vamos acomodando ordenadamente a los jugadores en una lista según sus resultados, y luego mostramos, en primer lugar al jugador ganador con más puntaje, y después a los demás ordenados desde el que tiene más puntaje hasta el último.


