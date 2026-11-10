// proyecto: Estacion de tren - Indios Verdes
// Corte de proyecto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50 // tamaño maximo para arreglos

// Fase 1: Estructura Usuario
typedef struct {
char nombre[50];    // nombre del usuario
char correo[50];    // correo del usuario
int num_tarjeta;    // numero de tarjeta
int dias_pasados;   // dias que ha pasado en la estacion
} Usuario;

Usuario *lista_usuarios = NULL; // arreglo dinamico para guardar usuarios
int cantidad_usuarios = 0;      // contador de usuarios registrados

// Fase 2: Lista enlazada de Historial
typedef struct NodoHistorial {
    int tarjeta;                  // numero de tarjeta que se registra
    char fecha[20];              // fecha en que paso la tarjeta
    struct NodoHistorial *siguiente; // puntero al siguiente nodo
} NodoHistorial;

NodoHistorial *inicio = NULL; // puntero al inicio de la lista, empieza vacio

// Fase 3: Pila (deshacer registro)
Usuario pila[MAX]; // arreglo que funciona como pila para guardar usuarios
int cima = -1;     // indica que la pila esta vacia

//  para verificar si la pila esta llena
int pila_llena() {
return cima >= MAX - 1; // si cima llega al ultimo indice esta llena
}

//  para verificar si la pila esta vacia
int pila_vacia() {
return cima < 0; // si cima es menor que 0 no hay elementos
}

// FASE 1: PASAR TARJETA 
void pasar_tarjeta() {
    int tarjeta; // variable para guardar el numero de tarjeta

printf("PASAR TARJETA\n");
printf("numero de tarjeta: ");
scanf("%d", &tarjeta); // lee el numero de tarjeta
printf("tarjeta leida.\n"); // mensaje de confirmacion
}

//FASE 1: REGISTRAR USUARIO 
void registrar_usuario() {
// realloc: aumenta el tamaño del arreglo dinamico para un usuario mas
lista_usuarios = (Usuario*)realloc(lista_usuarios, (cantidad_usuarios + 1) * sizeof(Usuario));
Usuario *u = &lista_usuarios[cantidad_usuarios];

printf("REGISTRAR DATOS \n");

printf("NOMBRE: ");
getchar(); // limpia el salto de linea que dejo el scanf
fgets(u->nombre, 50, stdin); // lee el nombre completo
u->nombre[strcspn(u->nombre, "\n")] = 0; // quita el salto de linea

printf("CORREO: ");
fgets(u->correo, 50, stdin);
u->correo[strcspn(u->correo, "\n")] = 0;

printf("NUMERO DE TARJETA: ");
scanf("%d", &u->num_tarjeta);

printf("DIAS QUE HAS PASADO: ");
scanf("%d", &u->dias_pasados);

// guarda el nuevo usuario en la pila para poder deshacerlo
if (!pila_llena()) {
pila[cima + 1] = *u;
cima++;
}

cantidad_usuarios++; // aumenta el contador de usuarios
printf("Usuario registrado correctamente.\n");
}

//  FASE 1: VER USUARIOS / GESTIONAR REPORTES 
void ver_usuarios() {
printf(" GESTION REPORTES ===\n");

// revisa si no hay usuarios registrados
if (cantidad_usuarios == 0) {
printf("Sin registros.\n");
return;
}

// ciclo for: recorre todo el arreglo dinamico
for (int i = 0; i < cantidad_usuarios; i++) {
printf("usuario %d:\n", i + 1);
printf("nombre: %s\n", lista_usuarios[i].nombre);
printf("correo: %s\n", lista_usuarios[i].correo);
printf("tarjeta: %d\n", lista_usuarios[i].num_tarjeta);
printf("dias: %d\n\n", lista_usuarios[i].dias_pasados);
    }
}

//FASE 2: AGREGAR AL HISTORIAL 
void agregar_historial(int tarjeta) {
// malloc: reserva memoria para un nuevo nodo
NodoHistorial *nuevo = (NodoHistorial*)malloc(sizeof(NodoHistorial));

nuevo->tarjeta = tarjeta;
strcpy(nuevo->fecha, "08/11/2026"); // copia la fecha fija
nuevo->siguiente = NULL; // el nuevo nodo no apunta a nada

// si la lista esta vacia el nuevo nodo pasa a ser el primero
if (inicio == NULL) {
inicio = nuevo;
} else {
NodoHistorial *temp = inicio;
// recorre hasta llegar al ultimo nodo
while (temp->siguiente != NULL) {
temp = temp->siguiente;
}
temp->siguiente = nuevo; // agrega el nodo al final
}
}

// FASE 2: MOSTRAR HISTORIAL 
void mostrar_historial() {
printf("VER HISTORIAL \n");

// si la lista esta vacia muestra mensaje y sale
if (inicio == NULL) {
printf("Sin registros en el historial.\n");
return;
}

NodoHistorial *temp = inicio; // empieza desde el primer nodo
int i = 1; // contador para numerar registros

// recorre toda la lista hasta llegar al final (NULL)
while (temp != NULL) {
printf("%d. tarjeta: %d | fecha: %s\n", i, temp->tarjeta, temp->fecha);
temp = temp->siguiente; // avanza al siguiente nodo
i++; // aumenta el contador
}
}

// FASE 3: DESHACER ULTIMO REGISTRO (PILA) 
void deshacer_registro() {
// primero verifica si hay algo que deshacer
if (pila_vacia()) {
printf("nada que deshacer.\n");
    return;
}

// muestra el usuario que se va a eliminar
printf("deshacer: %s\n", pila[cima].nombre);
cima--; // bajamos la cima, el ultimo elemento ya no esta en la pila
cantidad_usuarios--; // reduce el contador de usuarios
}

//  MENU PRINCIPAL 
int main() {
int opcion; // variable para guardar la opcion que elija el usuario

printf("\n");
printf("     ESTACION DE TREN\n");
printf("     INDIOS VERDES\n");
printf("\n");

// ciclo principal del menu, se repite hasta que el usuario elija salir
do {
printf("\n===== MENU =====\n");
printf("1. ¿tienes tarjeta?        <- Fase 1\n");
printf("2. pasar numero de tarjeta <- Fase 1\n");
printf("3. registrarse             <- Fase 1\n");
printf("4. gestionar reportes     <- Fase 1\n");
printf("5. ver historial           <- Fase 2\n");
printf("6. deshacer ultimo registro<- Fase 3\n");
printf("0. salir\n");

printf("ELIGE UNA OPCION: "); //pedi al usuario que elija una opcion
scanf("%d", &opcion);

//  OPCION 1: ¿TIENES TARJETA? 
if (opcion == 1) {
int r; //variable para guardar la respuesta ,1=si ,0=no
printf("\n¿tienes tarjeta?\n1. Si\n0. No\nElige: ");
scanf("%d", &r);

// si dice si, llama a la funcion para pasar su tarjeta
if (r == 1) {
pasar_tarjeta();
}
// si dice no, pregunta si quiere registrarse
else {
int reg;
printf("¿quieres registrarte? 1.SI  0.NO: ");
scanf("%d", &reg);

// si dice que si llama a registrar_usuario
if (reg == 1) {
registrar_usuario();
}
// si dice que no muestra mensaje y sale de esta opcion
else {
printf("saliendo.\n");
 }
}
}

// OPCION 2: PASAR TARJETA 
else if (opcion == 2) {
// llama a la funcion pasar_tarjeta directamente desde el menu
pasar_tarjeta();
}
//  OPCION 3: REGISTRARSE (FASE 1) 
else if (opcion == 3) {
    
// opcion 3, registra un nuevo usuario
registrar_usuario();
}
//OPCION 4: GESTIONAR REPORTES 
else if (opcion == 4) {
// opcion 4, ver todos los usuarios registrados
ver_usuarios();
}

// OPCION 5: VER HISTORIAL 
else if (opcion == 5) {
// opcion 5, muestra el historial de tarjetas
mostrar_historial();
}

//  OPCION 6: DESHACER REGISTRO 
else if (opcion == 6) {
// opcion 6, elimina el ultimo registro
 deshacer_registro();
}

//  OPCION 0: SALIR + LIBERAR MEMORIA 
else if (opcion == 0) {
// libera la memoria dinamica del arreglo de usuarios
free(lista_usuarios);

// recorre y liberamos cada nodo del historial
while (inicio != NULL) {
NodoHistorial *temp = inicio;
inicio = inicio->siguiente;
free(temp); // libera el nodo guardado
}
printf("memoria liberada. adios.\n");
}

//  OPCION INVALIDA 
else {
// muestra mensaje si el usuario escribe algo que no es una opcion del menu
printf("opcion no valida.\n");
}
// el menu se repite mientras no elija la opcion 0 salir
} while (opcion != 0);

    return 0; // programa termina correctamente
}

