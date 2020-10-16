#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Electro.h"
#include "utn_getDato.h"
#include "Marca.h"
//#include "Tipo.h"

void listarElectro (Electro list, Marca *listaMarca, int largoMarca) //Imprimir un solo campo
{
	char aMarcas[20];

	cargarDescripcionMarca(listaMarca, largoMarca, list.idMarca, aMarcas);
	printf("ID:%d  Serie:%s Marca:%s Modelo:%d \n",list.id,list.serie,aMarcas,list.idModelo);
}

int listarElectros (Electro *list, int largoArray, Marca *listaMarca, int largoMarca) //Imprimir el array completo
{
	int retorno = -1;

	if(list != NULL && largoArray > 0)
	{
		for (int i = 0; i < largoArray; i++)
		{
			if(list[i].id>0)
			{
				listarElectro(list[i], listaMarca, largoMarca);
				retorno = 0;
			}
		}
	}
	return retorno;
}

int initElectro(Electro *list, int largoArray) //Inicializar array (id o isEmpty)
{
	int retorno = -1;

	for (int i = 0; i < largoArray; i++)
	{
		list[i].id = 0;
		retorno = 0;
	}
	return retorno;
}

int buscarIndiceLibre(Electro *list, int largoArray) //Buscar isEmpty o espacio vacio
{
	int retorno = -1;

	for(int i = 0; i < largoArray; i++)
	{
		if(list[i].id == 0)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

int buscarIDElectro(Electro *list, int largoArray, int ID) //Buscar un ID en especifico y retornar posicion
{
	int retorno = -1;

	for(int i = 0; i < largoArray; i++)
	{
		if(list[i].id == ID && list[i].id > 0)
		{
			retorno = i;
			break;
		}
	}
	return retorno;
}

int cargarElectro (Electro *list,int largoArray, int *nextID, Marca *listaMarca,int largoMarca)
{
	int retorno = 0;
	int indice;
	int auxOpcion;
	if (list != NULL && largoArray > 0 && nextID != NULL)
		{
			indice = buscarIndiceLibre(list, largoArray);
			if(indice != -1)
			{
				list[indice].id= *nextID;
				(*nextID)++;
				utn_getInt(&auxOpcion,"Seleccione el Numero de Serie: \n 1-Rojo\n 2-Violeta\n 3-Azul\n 4-Negro\n","ERROR.OPCION INVALIDA\n",1,4,7);
				switch(auxOpcion)
				{
				case 1:
					strcpy(list[indice].serie,"Rojo");
					break;
				case 2:
					strcpy(list[indice].serie,"Violeta");
					break;
				case 3:
					strcpy(list[indice].serie,"Azul");
					break;
				case 4:
					strcpy(list[indice].serie,"Negro");
					break;
				}
				listarMarcas(listaMarca, largoMarca);
				utn_getInt(&list[indice].idMarca, "Ingrese el ID de la Marca\n", "ERROR. NO EXISTE ESE ID.\n", 1000, 1004, 7);
				utn_getInt(&list[indice].idModelo,"Ingrese el ID del Modelo (A�o de Fabricacion 2000 a 2020): \n","ERROR. NO EXISTE ESE ID\n",2000,2020,7);
				retorno = 1;
			} else {
				printf("No hay mas lugar para cargar\n");
			}
		}
	return retorno;
}

int modificarElectro(Electro *list, int largoArray, Marca *listaMarcas, int largoMarca)
{
	int retorno = -1;
	int index;
	int id;
	int auxSerie;
	char opcionMenu;
	char seguir = 's';

	listarElectros(list, largoArray, listaMarcas, largoMarca);
	utn_getInt(&id, "Ingrese el numero de ID: \n",	"ERROR. ID INVALIDO\n", 1, 100, 7);
	index = buscarIDElectro(list, largoArray, id);
	if(index != -1){
		do {
			listarElectro(list[index], listaMarcas, largoMarca);
			utn_getChar(&opcionMenu,"Ingrese que opcion desea modificar\n A)Serie\n B)Marca\n C)Modelo\n D)Salir\n","ERROR. OPCION INVALIDA\n", 'A', 'D', 7);
			switch(opcionMenu)
			{
				case 'A':
					retorno = utn_getInt(&auxSerie,"Seleccione el Numero de Serie: \n 1-Rojo\n 2-Violeta\n 3-Azul\n 4-Negro\n","ERROR.OPCION INVALIDA\n",1,4,7);
					switch(auxSerie)
					{
						case 1:
							strcpy(list[index].serie,"Rojo");
							break;
						case 2:
							strcpy(list[index].serie,"Violeta");
							break;
						case 3:
							strcpy(list[index].serie,"Azul");
							break;
						case 4:
							strcpy(list[index].serie,"Negro");
					}
					break;
				case 'B':
					listarMarcas(listaMarcas, largoMarca);
					retorno = utn_getInt(&list[index].idMarca,"Ingrese el ID actual de la Marca\n","ERROR. NO EXISTE ESE ID", 1000, 1004, 7);
					break;
				case 'C':
					retorno = utn_getInt(&list[index].idModelo,"Ingrese el numero actual del Modelo (2000 a 2020): \n","ERROR. NO EXISTE ESE ID", 2000, 2020, 7);
					break;
				case 'D':
					printf("�Confirma salir? (Y/N): \n");
					utn_myGets(&seguir, sizeof(seguir));
					seguir = tolower(seguir);
					break;
				default:
					printf("No se pudo modificar la informacion\n");
					break;
			}
		} while (seguir == 'n');
	} else {
		printf("No hay una Electro cargada con el ID ingresado\n");
	}

	if (retorno != -1) {
		printf("Se guardaron los cambios!\n");
		retorno = 1;
	}
	return retorno;
}

int eliminarIDElectro(Electro *list, int largoArray,int ID, Marca *listaMarca, int largoMarca)
{
	int retorno = -1;
	int indice;
	char seguir;


	indice = buscarIDElectro(list, largoArray, ID);
	if (indice != -1){
		listarElectro(list[indice], listaMarca,largoMarca);
		utn_getChar(&seguir, "�Seguro que desea eliminar el Electro (Y/N): \n", "ERROR. OPCION INVALIDA\n", 'N', 'Y', 7);
		if(seguir == 'Y')
		{
			list[indice].id = 0;
			retorno = 1;
			printf("Dada de baja con exito.\n");
		} else {
			printf("Accion cancelada\n");
		}
	} else {
		printf("No existe el ID\n");
	}
	return retorno;
}

int ordenarElectro(Electro *list, int largoArray, int order, Marca *listaMarca, int largoMarca)
{
	int auxOrden = order;
	int retorno = -1;
	Electro auxElectro;

	if (list != NULL && largoArray > 0)
	{
		if(auxOrden == 1) // DESC
		{
			for(int m = 0; m < largoArray-1; m++)
			{
				for(int s = m+1; s < largoArray; s++)
				{
					if(list[s].idModelo > list[m].idModelo || (list[s].idModelo == list[m].idModelo && (strcmp(list[s].serie, list[m].serie) > 0)))
					{
						auxElectro = list[m];
						list[m] = list[s];
						list[s] = auxElectro;
					}
						retorno = 1;
				}
			}
		}else if (auxOrden == 0) //ASC
		{
			for(int m = 0; m < largoArray-1; m++)
			{
				for(int s = m+1; s < largoArray; s++)
				{
					if(list[s].idModelo < list[m].idModelo || (list[s].idModelo == list[m].idModelo && (strcmp(list[s].serie, list[m].serie) < 0)))
					{
						auxElectro = list[m];
						list[m] = list[s];
						list[s] = auxElectro;
					}
					retorno = 1;
				}
			}
		}
	}
	listarElectros(list, largoArray, listaMarca, largoMarca);
	return retorno;
}
