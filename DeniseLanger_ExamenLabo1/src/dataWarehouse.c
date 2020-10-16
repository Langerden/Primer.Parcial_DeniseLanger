
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataWarehouse.h"
#include "Electro.h"
#include "Reparacion.h"


// 10 Electros

int idElectros[] = {1,2,3,4,5,6,7,8,9,10};
char serie[][20] = {"Rojo", "Azul", "Negro", "Azul", "Violeta", "Negro", "Rojo", "Rojo", "Violeta", "Violeta"};
int idMarca[] = {1000,1001,1002,1003,1003,1002,1001,1000,1002,1003};
int idModelo[] = {2000,2002,2004,2006,2008,2010,2012,2014,2016,2020};

// 10 Reparacion

int idReparacion[] = {1,2,3,4,5,6,7,8,9,10};
int idServicio[] = {20000,20001,20002,20003,20003,20002,20001,20000,20001,20002};
Fecha fecha[] = {{10,10,2020},{10,10,2020},{12,10,2020},{12,10,2020},{9,10,2020},{8,10,2020},{30,9,2020},{25,9,2020},{25,8,2020},{25,7,2020}};


int hardcodearDatos(Electro *electro, int largoElectro, Reparacion *reparacion, int largoReparacion, int *flag)
{
	int okElectro = 0;
	int okReparacion = 0;
	int retorno = 0;
	Electro auxElectro;
	Reparacion auxReparacion;

	for(int i = 0;i<largoElectro;i++)
	{
		auxElectro.id = idElectros[i];
		auxElectro.idMarca = idMarca[i];
		auxElectro.idModelo = idModelo[i];
		strcpy(auxElectro.serie,serie[i]);
		electro[i] = auxElectro;
		okElectro = 1;
	}

	for(int i = 0;i<largoReparacion;i++)
	{
		auxReparacion.id = idReparacion[i];
		strcpy(auxReparacion.serie,serie[i]);
		auxReparacion.idServicio = idServicio[i];
		auxReparacion.fechaReparacion.dia = fecha[i].dia;
		auxReparacion.fechaReparacion.mes = fecha[i].mes;
		auxReparacion.fechaReparacion.anio = fecha[i].anio;
		reparacion[i] = auxReparacion;
		okReparacion = 1;
	}

	if(okElectro && okReparacion)
	{
		retorno = 1;
		*flag = 10;
	}
	return retorno;
}

