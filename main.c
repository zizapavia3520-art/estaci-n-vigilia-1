// proyecto: Estacion de tren - Indios Verdes
// Corte de proyecto


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50


// fase 1: memoria dinamica
typedef struct {
    char nombre[50]; //para el nombre completo del usuario
    char correo[50];//para el correo electronico
    int num_tarjeta;//para el numero de la tarjeta 
    int dias_pasados;//para los dias que a pasado por la estacion
} Usuario;
//puntero al bufer dinamico que guardara a todos los usuarios
Usuario *lista_usuarios = NULL;//contador para saber cuantos usuarios tenemos registrados
int cantidad_usuarios = 0;//esta funcion es para registrar a nuevos usuarios y agregar al bufer dinamico

void registrar_usuario() {//amplia la memoria para poder guardar un usuario mas
lista_usuarios = (Usuario*)realloc(lista_usuarios, (cantidad_usuarios + 1) * sizeof(Usuario));
//apunta a la memoria para doder guardar un usuario mas
Usuario *u = &lista_usuarios[cantidad_usuarios];
//aqui en esta parte se pide y se guardan los datos del usuario
printf(" REGISTRAR DATOS \n");
printf("NOMBRE: ");//pedimos y guardamos el nombre del usuario
getchar();
fgets(u->nombre, 50, stdin);//leemos el nombre con espacios
u->nombre[strcspn(u->nombre, "\n")] = 0;
    //quitamos el asalto de linea 
printf("CORREO: ");//pedimos y guardamos el correo electronico
fgets(u->correo, 50, stdin);//lee el correo
u->correo[strcspn(u->correo, "\n")] = 0;//quitamos el salto de linea
    
printf("NUMERO DE TARGETA: ");//pide y guarda el numero de targeta
scanf("%d", &u->num_tarjeta);
    
printf("DIAS QUE HAS PASADO: ");//pedimos y guardamos cuantos dias ha pasado por la estacion
scanf("%d", &u->dias_pasados);
    //aumenta el contador,para cuanda ya tendriamos mas usuarios registrados
cantidad_usuarios++;
printf("usuario registrado.\n");
}

void ver_usuarios() {//muestra todos los usuarios que han sido registrados
printf("GESTIONAR REPORTES \n");
if (cantidad_usuarios == 0) {//si no hay ningun usuario registrado,muestra un mensaje y sale
printf("sin registros.\n");
 return;
}
for (int i = 0; i < cantidad_usuarios; i++) {//recorre el arreglo dinamico y mustra los datos de cada usuario
printf("\nusuario %d:\n", i + 1);//se mustra el numero del usuario
printf("nombre: %s\n", lista_usuarios[i].nombre);//muestra el nombre
printf("correo: %s\n", lista_usuarios[i].correo);//muestra el correo
printf("tarjeta: %d\n", lista_usuarios[i].num_tarjeta);//muestra el numero de tarjeta
printf("dias: %d\n", lista_usuarios[i].dias_pasados);//muestra los dias registrados
    }
}
//solicita el numero de tarjeta y confirma que fue leido
void pasar_tarjeta() {
int tarjeta;
printf("PASAR TARJETA \n");
printf("numero de tarjeta: ");//pedimos el numero de tarjeta
scanf("%d", &tarjeta);//lee el numero ingresado
printf("tarjeta leida.\n");//confirma que se leyo correctamente
}


// fase 2: lista enlazada â€” historial

typedef struct NodoHistorial {//definimos la estructura paa cada nodo de la lista
    int tarjeta;// numero de tarjeta que se registro
    char fecha[20];//fecha en que se paso o registro la tarjeta
    struct NodoHistorial *siguiente;//puntero al siguiente nodo de la lista
} NodoHistorial;
//puntero al inicio de la lista enlazada,empeza vacio

NodoHistorial *inicio = NULL;
//creo un nuevo nodo y lo agrega al final de la lista
void agregar_historial(int tarjeta) {//resarva memoria para el nuevo nodo
    NodoHistorial *nuevo = (NodoHistorial*)malloc(sizeof(NodoHistorial));
    //guarda el numero de tarjeta y fecha en el nuevo nodo
    nuevo->tarjeta = tarjeta;
    strcpy(nuevo->fecha, "08/11/2026");
    nuevo->siguiente = NULL;//el nuevo nodo al final no apunta a nada todavia
 //si la lista esta vacia, el nuevo nodo pasa a ser el primero   
if (inicio == NULL) {
inicio = nuevo;
} else {//si no esta vacia,recorre hasta llegar al ultimo nodo
NodoHistorial *temp = inicio;
while (temp->siguiente != NULL) {
temp = temp->siguiente;
}//agrega el nuevo nodo al final de la lista
temp->siguiente = nuevo;
}
}
///recorre toda la lista enlazada y muestra cada registro
void mostrar_historial() {
printf("\n VER HISTORIAL\n");
if (inicio == NULL) {//si la lista esta vacia,muestra mensaje y sale
printf("sin registros.\n");
    return;
}
NodoHistorial *temp = inicio;//empieza desde el primer nodo de la lista
int i = 1;///contador para numerar los registros
//recorre la lista hasta llegar al final
while (temp != NULL) {//mostrar el numero ,la tarjeta y la fecha de cada redistros
printf("%d. tarjeta: %d â€” %s\n", i, temp->tarjeta, temp->fecha);
temp = temp->siguiente;//pasamos al siguiente nodo
  i++;//aumentamos el contador
}
}


// fase 3: cola

typedef struct {//estructura para guardar los datos de cada persona en la cola
    char nombre[50];//nombre de la persona
    int turno;//numero de turnos que le corresponde
} Persona;//arreglo que funciona como cola y variables para controlarla

Persona cola[MAX];//espacio donde se guardan las personas
int frente = 0, final = 0;//frente=primer espacio/final=siguiente espacio libre

int cola_llena() {//verifica si la cola ya esta llena
    return (final - frente) == MAX;//si la diferencia es igual al tamaÃ±o maximo ,esta llena
}

int cola_vacia() {//verifica si no hay nadie en la cola
    return frente == final;//si ambos son iguales,no hay elemetos
}
//agreda una nueva persona al final de la cola
void hacer_fila() {//aqui va el resto de la funsion
if (cola_llena()) {
printf("Cola llena.\n");
    return;//salimos por que ya no cabe nadie mas
}
printf("tu nombre: ");//pedi el nombre de las personas
getchar();//limpia el buffer del teclado
fgets(cola[final % MAX].nombre, 50, stdin);//lee el nombre
//quita el salto de linea que lee fgets
cola[final % MAX].nombre[strcspn(cola[final % MAX].nombre, "\n")] = 0;
cola[final % MAX].turno = final + 1;//asignamos su turno y lo mostramos
printf("turno #%d\n", cola[final % MAX].turno);
final++;//avanza al siguiente espacio disponible 
}
//saca a la persona que esta al frente de la cola
void llamar_siguiente() {
    //verificamos si no hay nadie esperando
if (cola_vacia()) {
printf("no hay personas esperando.\n");
   return;//salimos porque la cola esta vacia
}//mostramos a la persona que pasa y avanza al siguiente
printf("Siguiente: %s â€” Turno #%d\n", cola[frente % MAX].nombre, cola[frente % MAX].turno);
frente++;//la siguiente persona pasa al frente
}


// fase 3: PILA

Usuario pila[MAX];//arreglo que funciona como pila para guardar usuarios
int cima = -1;//indica la posicion del ultimo elemento
//verifica si la pila ya no puede guardar mas elementos
int pila_llena() {
    return cima >= MAX - 1;//si la cima llega al ultimo indice,esta llena
}
//verifica si no hay elementos guardados en la pila
int pila_vacia() {
    return cima < 0;//si la cima es menor que 0,la pila esta vacia
}
//elimina el ultimo usuario que fue registrado
void deshacer_registro() {//primero verifica si hay algo que deshacer
    if (pila_vacia()) {
        printf("Nada que deshacer.\n");
        return;//sale por que la pila esta vacia
    }//muestra el usuario que se va a eliminar
    printf("Deshacer: %s\n", pila[cima].nombre);
    cima--;//bajamos la cima,el ultimo elemento ya no esta en la pila
    cantidad_usuarios--;//reduce el contador de usuarios al deshacer un registro
}


// MENU PRINCIPAL

int main() {
    int opcion;//variable para guardar la opcion que elija el usuario
  //muestra el titulo del programa   
printf("\n");
printf("       ESTACION DE TREN\n");
printf("        INDIOS VERDES\n");
printf("\n");
    //ciclo principal del menu,se repite hasta que el usuario elija salir
do {//muestra todas las opciones del menu
printf("\n===== MENU =====\n");
printf("1. Â¿tienes tarjeta?\n");
printf("2. pasar numero de tarjeta          <- Fase 1\n");
printf("3. registrarse                        <- Fase 1\n");
printf("4. gestionar reportes                 <- Fase 1\n");
printf("5. ver historial                      <- Fase 2\n");
printf("6. hacer fila                         <- Fase 3\n");
printf("7. llamar siguiente persona           <- Fase 3\n");
printf("8. deshacer ultimo registro          <- Fase 3\n");
printf("0. salir\n");
printf("ELIGE UNA OPCION: ");//pedi al usuario que elija una opcion
scanf("%d", &opcion);
   
if (opcion == 1) {
int r;//variable para guardar la respuesta ,1=si ,0=no
printf("\n¿tienes tarjeta?\n1. Si­\no. No\nelige: ");
scanf("%d", &r);
if (r == 1) {//si dece si,llama a la funcion para pasar su tarjeta
pasar_tarjeta();
} else {//si dice que no,pregunta si quiere registrarse
int reg;
printf("¿quieres registrarte? 1.SI  0.NO: ");
scanf("%d", &reg);
if (reg == 1) {//si dice que si.llama a la funcion para registrar sus datos
registrar_usuario();
} else {//si dece que no,muestra mensaje y salimos de esta opcion
printf("saliendo.\n");
}
}
}//opcion 2,pasar tarjeta directamente desde el menu
else if (opcion == 2) {
pasar_tarjeta();
}
else if (opcion == 3) {//opcion 3,registra un nuevo usuario
registrar_usuario();
}
else if (opcion == 4) {//opcion 4,ver todos los usuarios registrados
ver_usuarios();
}
else if (opcion == 5) {//opcion 5,muestra el historial de tarjetas
mostrar_historial();
}
else if (opcion == 6) {//opcion 6,agrega una persona al final de la cola
hacer_fila();
}
else if (opcion == 7) {//opcion 7,llama y atiende a la persona que esta al frente de la cola
llamar_siguiente();
}
else if (opcion == 8) {//opcion 8,elimina el ultimo registro de usuario
deshacer_registro();
}
else if (opcion == 0) {//opcion 0,salir del programa y libera toda la memoria
free(lista_usuarios);//libera la memoria del bufer dinamico de usuario
while (inicio != NULL) {//recore y liberamos cada nodo de la lista del historial
NodoHistorial *temp = inicio;//guarda el nodo actual
inicio = inicio->siguiente;//avanzamos al siguiente nodo
free(temp);//libera el nodo guardado
}
printf("memoria liberada. adios.\n");//confirmamos que todo se libero correctamente
}//si el usuario escribe algo que no es una opcion del menu
else {
printf("opcion no valida.\n");//mostramos mensaje de error
}
   //el menu se repite mientras no elija la opcion o salir
} while (opcion != 0);
    
    return 0;//el programa termina correctamente
}
