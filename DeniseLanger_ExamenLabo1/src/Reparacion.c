#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn_getDato.h"
#include "Servicio.h"
#include "Electro.h"
#include "Reparacion.h"

void listarReparacion (Reparacion list, Servicio *listaServicio, int largoServicio)
{
	char aServicios [25];
	cargarDescripcionServicio(listaServicio, largoServicio, list.idServicio, aServicios);
	printf("ID:%d  Serie:%s Servicio:%s Fecha:%d/%d/%d\n",list.id,list.serie,aServicios,list.fechaReparacion.dia,list.fechaReparacion.mes,list.fechaReparacion.anio);
}

int listarReparaciones (Reparacion *list, int largoArray, Servicio *listaServicio, int largoServicio)
{
	int retorno = -1;

	for (int i = 0; i < largoArray; i++)
	{
		if(list[i].id>0){
			listarReparacion(list[i], listaServicio, largoServicio);
			retorno = 0;
		}
	}
	return retorno;
}

int initReparacion(Reparacion *list, int largoArray)
{
	int retorno = -1;

	for (int i = 0; i < largoArray; i++)
	{
		list[i].id = 0;
		retorno = 0;
	}
	return retorno;
}

int buscarReparacionLibre(Reparacion *list, int largoArray)
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

int altaReparacion (Reparacion *list, int largoArray, int *IDReparacion, Electro *listElectro, int largoElectro, Servicio *listServ, int largoServicio, Marca *listaMarca, int largoMarca)
{
	int retorno = -1;
	int indexReparacion;
	int indexElectro;
	int auxIDReparacion;
	int auxIDElectro;
	int auxIDServicio;
	Reparacion auxReparacion;

	indexReparacion = buscarReparacionLibre(list, largoArray);
	if(indexReparacion != -1)
	{
		auxIDReparacion = *IDReparacion;
		listarElectros(listElectro, largoElectro, listaMarca, largoMarca);
		utn_getInt(&auxIDElectro, "Ingrese el Numero de ID del Electro\n", "ERROR. Numero de ID Incorrecto\n", 1, 1050, 7);
		indexElectro = buscarIDElectro(listElectro, largoElectro, auxIDElectro);
		if(indexElectro >= 0)
		{
			listarServicios(listServ, largoServicio);
			if(!(utn_getInt(&auxIDServicio, "Ingrese el Numero de ID del Servicio\n", "ERROR. Numero de ID Incorrecto\n", 20000, 20003, 7)))
			{
				printf("Ingrese la Fecha de cuando se realizo la Reparacion\n");
				utn_getInt(&auxReparacion.fechaReparacion.anio, "Ingrese el anio (2000 al 2020): \n","ERROR. ANIO INVALIDO\n",2000, 2020, 7);
				utn_getInt(&auxReparacion.fechaReparacion.mes, "Ingrese el numero del Mes (1 al 12): \n", "ERROR. MES INVALIDO\n", 1, 12, 7);
				utn_getInt(&auxReparacion.fechaReparacion.dia, "Ingrese el dia (1 al 31): \n", "ERROR. DIA INVALIDO\n", 1, 31, 7);
				strcpy(auxReparacion.serie, listElectro[indexElectro].serie);
				auxReparacion.idServicio = auxIDServicio;
				auxReparacion.id = auxIDReparacion;

				list[indexReparacion] = auxReparacion;

				auxIDReparacion++;
				*IDReparacion = auxIDReparacion;
				retorno = 1;
			}
		} else {
			printf("No existe el ID ingresado\n");
		}
	} else {
		printf("No hay mas lugar\n");
	}
	return retorno;
}
