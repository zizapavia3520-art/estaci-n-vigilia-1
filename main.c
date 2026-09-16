#include<stdio.h>
int main(){
  int opcion;
do{
printf("ESTACION VIRGIA\n");
printf("1.gestionar usuarios\n");
printf("2.registrar datos\n");
printf("3.gestionar reportes\n");
printf("4.salir\n");

printf("elegir una opcion: ");
scanf("%d", &opcion);

if(opcion != 4){
printf("opcion%d -En desarrollo  \n\n", opcion);
}
} while(opcion != 4);
printf("saliendo del programa \n");
return 0;
}
