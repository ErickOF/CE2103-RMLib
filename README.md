# RMLib

#### Curso CE2103

#### Algoritmos y Estructuras de Datos II

#### Grupo 1

#### Elaborado por:
* Erick Obregón Fonseca 2016123157

#### Profesor del curso:
* Jose Isaac Ramirez Herrera

#### Semestre II 
#### 2017


## Introducción

El presente proyecto se lleva a cabo con el fin de desarrollar una biblioteca, en el lenguaje C/C++, que sea capaz de encapsular las funcionalidades necesarias para el manejo de memoria de manera remota. La memoria disponible, tanto en el nodo primario como el secundario, es gestionada por un servidor, que escucha por sockets.

El interés de este proyecto se desarrolló en torno a la idea de implementar una biblioteca genérica empaquetada como una biblioteca de C/C++ que permita que otros programas, creados en este lenguaje, puedan ser enlazados con ella y utilizar sus funcionalidades. La biblioteca se llamará simplemente rmlib y funciona como una interfaz a la memoria, la cual se ejecuta como un servidor por sockets.

Como sistema operativo se utilizó la distribución de Linux, Ubuntu 14.06 LTS. Para la codificación de la biblioteca “rmlib” se utilizó el lenguaje C/C++ y, como editor de código, Qt Creator para facilitar la creación de la interfaz gráfica, tanto del usuario cuando esté manejando la memoria, como del servidor para mostrar los elementos que han sido guardados en la memoria que posee. En la documentación del código fuente se utilizó Doxygen para generar la documentación de manera automática.

El proyecto contiene la librería que le permite enlazar una aplicación con ella y dotarla de funcionalidades que permiten la conexión del servidor por medio de un ip y un puerto tanto del servidor activo como del pasivo. La biblioteca permite integrar las funcionalidades de agregar un elemento a la memoria, eliminarlo y poder ver que hay dentro de ella por medio de una llave.

## Descripción del problema

El proyecto consiste en un programa cliente-servidor. El cliente es una biblioteca que encapsula funciones de manejo de memoria. El servidor es un programa que gestiona la memoria disponible en el nodo principal y el nodo secundario.

La biblioteca cliente, llamada “rmlib”, es una biblioteca genérica que podrá ser empleada en el lenguaje C++. Debe permitir a otros programas ser enlazados y poder utilizar sus funcionalidades para conectarse a una memoria remota. La memoria remota se ejecuta como un servidor por sockets, el cual cuenta con failover automático. Antes de enviar una petición, la biblioteca verifica que el servidor esté disponible, de lo contrario, la remitirá al servidor HA (High Availability).

El servidor es un programa que escucha por sockets y que conoce de la existencia de un servidor pasivo de alta disponibilidad y se encarga de sincronizarlo. Cuando se inicia el programa servidor, se indica si será pasivo o activo. Cuando se especifica que el servidor será pasivo, se debe indicar el IP y puerto del activo. El cual se reporta con el activo y empieza a recibir los datos de sincronización.

El servidor activo y el pasivo constantemente verifican que el otro esté funcionando. En caso de que el activo no esté disponible, el pasivo asume el rol del activo. Cuando el activo original regresa, el pasivo lo sincroniza y entrega el rol de activo.

La memoria se comporta en esencia como un mapa llave-valor, por así decirlo, es una lista enlazada en la que hay una llave que permite buscar el valor guardado. A parte del valor, se guarda un conteo de referencias que permite, posteriormente, hacer recolección de basura. La memoria remota tiene un proceso que corre cada cierto tiempo, buscando la memoria que no tenga referencias activas, y la elimina automáticamente.

Para mejorar el tiempo de respuesta, la memoria debe tener un caché pequeño de no más de 5 entradas. Se debe implementar un algoritmo para controlar este caché. También se le solicita que implemente un mecanismo de control de concurrencia, puesto que la memoria puede ser accedida por varios programas a la vez. Además, se debe implementar un mecanismo de encripción/desencripción entre “rmlib” y el servidor, de tal forma que el envío de datos sea seguro.

Para finalizar, se debe implementar un monitor con interfaz gráfica que permita ver el estado de la memoria y del caché, donde se muestren todos los datos necesarios para demostrar la funcionalidad.
