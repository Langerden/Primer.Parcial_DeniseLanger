
#include <stdio.h>
#include <stdlib.h>
#include "utn_getDato.h"
#include "dataWarehouse.h"
#include "Electro.h"
#include "Reparacion.h"

#define LARGO_MARCA 5
#define LARGO_SERVICIO 4
#define HARCOARRAY 10

int main(void)
{
	setbuf(stdout, NULL);
	int IDElectro;
	int IDReparacion;
	int orden;
	int datoUser;
	int flagMenu = 0;
	char salir = 'N';

	/*//NO HARDCODEO
	IDElectro = 1;
	IDReparacion = 1;
	*/

	//SI HARDCODEO
	IDElectro = 11;
	IDReparacion = 11;


	Marca arrayMarca [LARGO_MARCA] = {{1000,"Gafa"},{1001,"Liliana"},{1002,"Philips"},{1003,"Sony"},{1004,"Whirpool"}};
	Servicio arrayServicio [LARGO_SERVICIO] = {{20000,"Garantia",250},{20001,"Mantenimiento",500},{20002,"Repuestos",400},{20003,"Refaccion",600}};
	Electro arrayElectro [HARCOARRAY];
	Reparacion arrayReparacion [HARCOARRAY];


	// inicializar las listas
	initElectro(arrayElectro, HARCOARRAY);
	initReparacion(arrayReparacion, HARCOARRAY);

	// SI HARD
	hardcodearDatos(arrayElectro, HARCOARRAY, arrayReparacion, HARCOARRAY, &flagMenu);

	do{
		switch(menu())
		{
			case 'A': 	//Alta Electro
				if(cargarElectro(arrayElectro, HARCOARRAY, &IDElectro, arrayMarca, LARGO_MARCA))
				{
					flagMenu++;
				}
				break;
			case 'B': //Modificar Electro - Ingresar ID y modificar Serie y Modelo
				if(flagMenu)
				{
					modificarElectro(arrayElectro, HARCOARRAY, arrayMarca, LARGO_MARCA);
				} else {
					printf("Se debe dar de alta una Electro primero\n");
				}
				break;
			case 'C': //Bajar Electro - Ingresar ID y se hace una baja logica
				if(flagMenu)
				{
					listarElectros(arrayElectro, HARCOARRAY, arrayMarca, LARGO_MARCA);
					utn_getInt(&datoUser, "Ingrese el ID a eliminar: \n", "ERROR. ID INVALIDO\n", 1, 10, 7);
					if(eliminarIDElectro(arrayElectro, HARCOARRAY, datoUser, arrayMarca, LARGO_MARCA) != -1)
					{
						flagMenu--;
					}
				} else {
					printf("Se debe dar de alta una Electro primero\n");
				}
				break;
			case 'D': //Listar Electros - Mostrar ordenando por Modelo y Serie
				if(flagMenu)
				{
					utn_getInt(&orden, "Ingrese el orden de Modelo y Serie (1 = DESC / 0 = ASC): \n", "ERROR. OPCION INVALIDA\n", 0, 1, 7);
					ordenarElectro(arrayElectro, HARCOARRAY, orden, arrayMarca, LARGO_MARCA);
				} else {
					printf("Se debe dar de alta una Electro primero\n");
				}
				break;
			case 'E': //Listar Marcas
				listarMarcas(arrayMarca, LARGO_MARCA);
				break;
			case 'F': //Listar Servicios
				listarServicios(arrayServicio, LARGO_SERVICIO);
				break;
			case 'G': //Alta Reparacion - se da de alta cada Reparacion pidiendo elegir una Electro y un servicio
				if(flagMenu)
				{
				altaReparacion(arrayReparacion, HARCOARRAY, &IDReparacion, arrayElectro, HARCOARRAY, arrayServicio, LARGO_SERVICIO, arrayMarca, LARGO_MARCA);
				} else {
					printf("Se debe dar de alta una Electro primero\n");
				}
				break;
			case 'H': //Listar Reparaciones
				if(IDReparacion == 1)
				{
					printf("Se debe registrar una reparacion primero\n");
				} else {
					listarReparaciones(arrayReparacion, HARCOARRAY, arrayServicio, LARGO_SERVICIO);
				}
				break;
			case 'I': //Exit
				utn_getChar(&salir, "¿Desea salir? (Y / N): \n", "ERROR. Opcion invalida\n", 'N', 'Y', 7);
				if(salir == 'Y')
				{
					return EXIT_SUCCESS;
				}
		}
		system("pause");
		system("cls");
	}while (salir == 'N');
	return EXIT_SUCCESS;
}
