# Proyecto: Primera Entrega

## Introducción

La gran cantidad de información virtual generada a diario ha hecho que sea indispensable la creación de nuevas formas de
almacenamiento que sean lo suficientemente seguras como para ser confiadas de datos sumamente delicados.

## Blockchain

La cadena de bloques, también conocida como blockchain, es una estructura de datos en la que se puede acoplar nueva
información agrupada en bloques.

Cada uno de estos bloques tiene un hash creado a partir de su contenido y de metainformación del bloque previo, de modo
que si se intenta cambiar la información de cualquier bloque, los siguientes mostrarán la existencia de una
discrepancia.

## Importancia

Una estructura como la cadena de bloques es importante porque, en caso sea implementada de manera correcta, supondría
una forma de almacenar información de manera inmutable, pues cualquier intento de modificarla se vería reflejado en
toda la estructura.

De este modo, serviría para guardar información valiosa, como pueden llegar a ser transacciones bancarias o los datos de
cada persona que posee un gobierno.

## Proof of work

Si alguien desea cambiar la información de un bloque que ya ha sido validado y tiene la suficiente capacidad
computacional, podría modificar completamente la estructura lo suficientemente rápido para eliminar cualquier tipo de
discrepancia generada antes que nadie se dé cuenta.

Para evitar esto en nuestra implementación, cada vez que se genera un bloque se elige al azar un número entre un rango
secreto que será llamado proof of work.

El propósito de este número es que un bloque solo podrá ser considerado válido si los n primeros dígitos de su hash
coinciden con el proof of work.

Sin embargo, es bastante improbable que un bloque sea válido la primera vez que se calcula su hash, por lo que se
tendrá que adicionar información de uso único adicional, también conocida como nonce, y recalcular el hash hasta que
cumpla con la validez.

Este proceso tardará proporcionalmente a la cantidad de dígitos de nuestro proof of work, pues más intentos serán
necesarios hasta que se logre "adivinarlo".

## Implementación

Para mayor comprensión, el código se encuentra comentado.

### Clase Record

- Clase abstracta que permite guardar datos según la implementación de sus clases hijas.


- Puede ser serializada, es decir, su información se puede representar como un texto.

### Clase Block

- Permite guardar como máximo tantos Records como desee el usuario de nuestra estructura.


- Estos registros son guardados en un array de punteros a Records.


- Cada vez que se agregue un nuevo Record cambiará el hash del bloque, pues su información ha sido modificada.

### Clase Blockchain

- Guarda cada uno de los Blocks agregados dentro de un Circular Array de punteros a bloques.


- Si se desea agregar un bloque, primero lo mina, es decir, realizará el proceso para hallar el proof of work, y luego
  lo agrega.


- Tiene métodos con propósito educativo que permiten realizar exploits sobre la propia estructura para demostrar cómo se
  verían las discrepancias en caso alguien intente vulnerarla.

## Análisis de complejidad

- Insertar bloque: Al estar usando un array circular, el push_back de un nuevo bloque se realiza en O(1). Sin
  embargo, en caso el array circular se quede sin espacio se tendrá que hacer un resize, lo que tiene una complejidad
  de O(n).


- Acceder bloque: Siempre es O(1), pues cuenta con random access al tratarse por debajo como un array.


- Exploit Modificar o Eliminar bloque: Acceder a un registro de un bloque en específico tiene una complejidad de O(1). A
  pesar de esto, todos los registros hijos tendrán que recalcular su hash, pues ha cambiado el del padre, por lo que
  tendrá complejidad de O(n).


- Exploit Minar toda la Blockchain: En el peor de los casos cuando se ha modificado el bloque génesis, se tendrá que
  minar toda la blockchain, por lo que tendrá una complejidad de O(n).

## Uso de estructuras propias

- Circular Array: La principal funcionalidad de una blockchain será el almacenar información para que posteriormente
  pueda ser revisada. Es por esto que se eligió un array circular como el contenedor de los bloques, pues permitirá el
  acceso en tiempo constante a cualquier registro y la agregación de nuevos bloques de manera constante amortizada.

  También se pudo haber usado una lista para agregar nuevos bloques de manera constante sin tener que hacer un resize
  a toda la estructura, pero se tomó como mayor prioridad el poder recuperar los datos de manera rápida, lo que en una
  lista supondría tener que iterar todos los bloques en el peor de los casos.

## Modo de uso

1. Creas un objeto Blockchain.
2. Creas un objeto Block alojado en el heap.
3. Añades registros alojados en el heap al Block recién creado.
4. Agregas el Block al Blockchain.
5. Repites los pasos 2 a 4 cuantas veces desees para llenar tu blockchain.
6. Tu Blockchain estará listo y puedes usar las funciones que esta contiene.

## Consideraciones (IMPORTANTE LEER)

- Se está usando C++ 17.

- Los métodos de la clase Blockchain que empiezan con EXPLOIT sirven para mostrar cómo se vería afectada la estructura
  si un agente malicioso tratase de dañarla, mas no pertenecen intrínsecamente a la estructura.


- Las funciones del archivo pseudoapp.h tratan de presentar una demo de cómo sería el funcionamiento de una blockchain
  que guarda registros bancarios. Sin embargo, son de uso experimental y su principal propósito es otorgar un manejo
  visual provisional de la blockchain a quien revise esta entrega.


- La clase Block cuenta con la variable global llamada MAX_BLOCK_SIZE, la cual puede ser modificada como se desee. Por
  defecto señaliza que cada bloque puede guardar 5 registros como máximo. Se eligió el uso de una variable global porque
  dejar que el usuario elija el tamaño de cada bloque quitaría su estandarización.


- La clase Block cuenta con las variables globales llamadas MIN_POW y MAX_POW, las que representan el rango en el que se
  encontrará el Proof of Work. Actualmente, ambas son iguales a 11, por lo que este número será el único que podrán
  generar. Esta decisión es para que quien revise la entrega pueda revisar el funcionamiento de la estructura sin que
  cambien los datos con cada ejecución, pero es libre de cambiarlo cuando desee.

## Bibliografía

- Narayanan, Arvind; Bonneau, Joseph; Felten, Edward; Miller, Andrew; Goldfeder, Steven (2016). Bitcoin and
  cryptocurrency technologies: a comprehensive introduction. Princeton: Princeton University Press. ISBN
  978-0-691-17169-2.