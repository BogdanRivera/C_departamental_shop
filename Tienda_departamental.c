
/*PROYECTO GARCIA RIVERA BOGDAN KALEB
INGENIERIA MECATRONICA
GRUPO: 114-D
PROGRAMACION ESTRUCTURADA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int dia,mes,anio; 
	double ganancias; 
}VENTASDIA;


typedef struct{ //ESTRUCTURA PARA LOS DEPARTAMENTOS  
	char cod_dep[15]; 
	char nombre[30]; 
	int cant_prod_mov; 
}DEPARTAMENTOS;

typedef struct { //ESTRUCTURA DE LOS PRODUCTOS  
	char clave_prod[15]; 
	char nom_prod[25];
	int cant_exis; 
	char codigo_dep[15]; 
	float precio;  
	int cant_sug; 
	char nom_dep[30]; 
	int movimiento; 
}PRODUCTOS;


void funcion_principal(PRODUCTOS *, DEPARTAMENTOS *,char *,char *,char *,FILE *,FILE *,FILE *); 
int main (){
	FILE *a; //FICHERO DE DEPARTAMENTOS
	FILE *b; //FICHERO DE PRODUCTOS
	FILE *c; //FICHERO DEL RECIBO
	char direccion[50] = "C:\\Users\\bogdan\\Desktop\\"; //DIRECCIONES DEL ARCHIVO DE PRODUCTOS (ERA UNA PRUEBA)
	char direccion2[50]= "C:\\Users\\bogdan\\Desktop\\";
	char direccion3[50] = "C:\\Users\\bogdan\\Desktop\\";
	PRODUCTOS cosas[6000]; //ARREGLO DE LOS PRODUCTOS
	DEPARTAMENTOS departamento[80]; //ARREGLO DE LOS DEPARTAMENTOS
	funcion_principal(cosas,departamento,direccion,direccion2,direccion3,a,b,c);
	
	
	
	 
	return 0; 
}

/*FUNCION PRINCIPAL*/
void funcion_principal(PRODUCTOS *cosas,DEPARTAMENTOS *departamento,char *direccion,char *direccion2,char *direccion3,FILE *a,FILE *b,FILE *c){
	/*PROTOTIPOS DE LA FUNCION*/
	void menu1(void); 
	void leerdep(DEPARTAMENTOS*,FILE*,int*); 
	void leerprod(PRODUCTOS*,FILE*,int*); 
	void imprimedep(DEPARTAMENTOS*,int); 
	void agregadep(DEPARTAMENTOS *,int *); 
	void agregaprod(PRODUCTOS *,int *); 
	void administra(PRODUCTOS *,int *,DEPARTAMENTOS *,int *,char *,FILE *); 
	void guardar(FILE *,FILE *,DEPARTAMENTOS *,PRODUCTOS *,int*,int*); 
	int opcAr; //OPCIONES PARA REALIZAR CON EL ARCHIVOS
	char nombre[30]; //NOMBRE DEL ARCHIVO DE PRODUCTOS 
	int tam_prod,tam_dep; //TAMAÑO DE LOS PRODUCTOS Y DE LOS DEPARTAMENTOS
	char nombre2[30]; 
	tam_prod = 0; //CUANTOS PRODUCTOS EXISTEN INICIALMENTE
	tam_dep = 0;  //CUANTOS DEPARTAMENTOS EXISTEN INICIALMENTE
	int opc; 
	do{
		system("cls"); 
		menu1(); 
		scanf("%d",&opcAr); 
	}while(opcAr!=1 && opcAr!=2); 
	switch(opcAr){
		case 1: //CASO 1. LEE LOS ARCHIVOS
		system("cls"); 
		printf ("DAME EL NOMBRE Y FORMATO DEL ARCHIVO DE DEPARTAMENTOS: "); 
		fflush(stdin); 
		gets(nombre); 
		printf ("\nDAME EL NOMBRE Y FORMATO DEL ARCHIVO DE PRODUCTOS: "); 
		fflush(stdin); 
		gets(nombre2); 
		strcat(direccion,nombre); //CONCATENA EL NOMBRE DEL ARCHIVO DE DEPARTAMENTOS CON LA DIRECCION 
		strcat(direccion2,nombre2); //CONCATENA EL NOMBRE DEL ARCHIVO DE PRODUCTOS CON LA DIRECCION
		a = fopen(nombre,"r"); 
		b = fopen(nombre2,"r"); 
		if (a!=NULL && b!=NULL){
			leerdep(departamento,a,&tam_dep); //RECIBE LOS PRODUCTOS Y LOS ALMACENA EN UNA ESTRUCTURA
			leerprod(cosas,b,&tam_prod);  //RECIBE LOS DEPARTAMENTOS Y LOS ALMACENA EN UNA ESTRUCTURA
			administra(cosas,&tam_prod,departamento,&tam_dep,direccion3,c); //FUNCION DE MENUS Y OPCIONES
			rewind(a); 
			rewind(b); 
			fclose(a); 
			fclose(b);
			system("cls"); 
			printf ("DESEA GUARDAR CAMBIOS?\n1.SI\n2.NO\nOPCION: "); 
			scanf("%d",&opc); 
			if (opc==1){ //OPCION PARA GUARDAR EL ARCHIVO
				a = fopen(nombre,"w");
				b = fopen(nombre2,"w");  
				guardar(a,b,departamento,cosas,&tam_dep,&tam_prod);	
			}
			 
		break;
		case 2://CASO 2. CREA UN ARCHIVO Y COMIENZA DESDE CERO
			system("cls"); 
		printf ("DAME EL NOMBRE Y FORMATO DEL ARCHIVO DE DEPARTAMENTOS: "); 
		fflush(stdin); 
		gets(nombre); 
		printf ("\nDAME EL NOMBRE Y FORMATO DEL ARCHIVO DE PRODUCTOS: "); 
		fflush(stdin); 
		gets(nombre2); 
		strcat(direccion,nombre); 
		strcat(direccion2,nombre2); 
		a = fopen(nombre,"w"); 
		b = fopen(nombre2,"w"); 
		if (a!=NULL && b!=NULL){
			agregadep(departamento,&tam_dep); 
			agregaprod(cosas,&tam_prod);
			administra(cosas,&tam_prod,departamento,&tam_dep,direccion3,c); 
			guardar(a,b,departamento,cosas,&tam_dep,&tam_prod); 
		}else {
			printf ("NO SE ENCONTRO ALGUNO DE LOS ARCHIVOS\n"); 
			return; 
		} 
		
		
		break;  
		}else{ printf ("NO SE ENCONTRO ALGUNO DE LOS ARCHIVOS\n"); 
		return;
		}
		
		
		break;  
		
		
		
	}
	
}
/*MENU DE CREACION O LECTURA DE ARCHIVO*/
void menu1(){
	printf ("¿QUE DESEA REALIZAR?\n1.LEER ARCHIVO\n2.CREAR ARCHIVO\nOPCION: ");
}
/*FUNCION DE LECTURA DE LOS DEPARTAMENTOS
A TRAVES DE UN ARCHIVO*/
void leerdep(DEPARTAMENTOS *dep,FILE *a,int *tam){
	int i,aux; //CONTADORES
	fscanf(a,"%d\n",&aux);
	*tam = aux;  //PASO POR REFERENCIA PARA CONTAR CUANTOS DEPARTAMENTOS EXISTEN
	for (i=0;i<*tam;i++){
		fscanf(a,"%s",&(dep[i].cod_dep)); 
		fscanf(a,"%s",&(dep[i].nombre)); 
	}
}
/*FUNCION DE LECTURA DE LOS PRODUCTOS
A TRAVES DE UN ARCHIVO*/
void leerprod(PRODUCTOS *a,FILE *b,int *tampro){
	int i,aux; //CONTADORES 
	fscanf(b,"%d\n",&aux); 
	*tampro = aux; //PASO POR REFERENCIA PARA CONTAR CUANTOS PRODUCTOS EXITEN
	for (i=0;i<*tampro;i++){
		fscanf(b,"%s",&(a[i].clave_prod)); 
		fscanf(b,"%s",&(a[i].nom_prod));
		fscanf(b,"%d",&(a[i].cant_exis));
		fscanf(b,"%s",&(a[i].codigo_dep)); 
		fscanf(b,"%f",&(a[i].precio));
		a[i].cant_sug = (a[i].cant_exis*.70);
		a[i].movimiento = 0;     	
	}
}
/*IMPRIME EL LISTADO DE LOS PRODUCTOS*/
void imprimeprod(PRODUCTOS *cosas,int t,DEPARTAMENTOS *b,int tamdep){
	void busqueda(PRODUCTOS*,int,DEPARTAMENTOS*,int); //PROTOTIPO DE LA FUNCION
	int i; 
	busqueda(cosas,t,b,tamdep); //LLAMADA DE LA FUNCION. BUSCA LOS CODIGOS Y LOS COMPARA CON LOS DEPARTAMENTOS
	printf ("%s\t%s%15s%15s%15s%15s%15s%15s\n\n","NUMERO","DEPARTAMENTO","CLAVE","PRODUCTO","CANT.EX","CODDEP","PRECIO","CANT.SUG");
	for (i=0;i<t;i++){
		printf ("%d\t%s ",i,cosas[i].nom_dep); 
		printf ("%15s ",cosas[i].clave_prod); 
		printf ("%15s ",cosas[i].nom_prod); 
		printf ("%15d ",cosas[i].cant_exis); 
		printf ("%15s ",cosas[i].codigo_dep);  
		printf ("%15.2f ",cosas[i].precio);
		printf ("%15d ",cosas[i].cant_sug); 
		if ((cosas[i].cant_exis)<5) printf ("\t\tRESURTIR EN ALMACEN"); 
		if (cosas[i].movimiento==1) printf ("\t\tLENTO MOVIMIENTO"); 
		printf ("\n"); 
	}

}
/*FUNCION DE BUSQUEDA Y COMPARACION DE LOS CODIGOS
DE DEPARTAMENTOS Y PRODUCTOS*/
void busqueda(PRODUCTOS *a,int tamprod,DEPARTAMENTOS *b,int tamdep){
	int i,j; //i = CONTADOR DE PRODUCTOS. j= CONTADOR DE DEPARTAMENTOS 
	for (i=0;i<tamprod;i++)
		for (j=0;j<tamdep;j++)
			if(strcmp(a[i].codigo_dep,b[j].cod_dep)==0){
				strcpy(a[i].nom_dep,b[j].nombre); 
				break; 
			}else strcpy(a[i].nom_dep,"SINDEPARTAMENTO"); 
	
	
}
/*FUNCION. IMPRIME LOS DATOS DE LOS DEPARTAMENTOS*/
void imprimedep(DEPARTAMENTOS *dep,int t){
	int i; //CONTADOR
	printf ("NUMERO\tCLAVE\t\t  DEPARTAMENTO\n\n");
	for (i=0;i<t;i++){
		printf ("%d	%s\t\t",i,dep[i].cod_dep); 
		printf ("%s\n",dep[i].nombre); 
	} 
}

/*FUNCION DEL MENU PRINCIPAL DEL PROGRAMA
PARA LA ELECCION DE LAS ACCIONES*/
void menu2(void){
	printf ("\tBIENVENIDO AL ADMINISTRADOR DE LA TIENDA\t\n"); 
	printf ("1.ADMINISTRAR PRODUCTOS\n2.ADMINISTRAR DEPARTAMENTOS\n3.COMPRAR PRODUCTOS\n4.MOSTRAR PRODUCTOS\n5.REPORTES DE VENTAS\n6.SALIR\nOPCION:  ");
}

/*FUNCION PRINCIPAL DE MENU
ELECCION DE ACCIONES*/
void administra(PRODUCTOS *a,int *tamprod,DEPARTAMENTOS *b,int *tamdep,char *direccion,FILE *c){
	void menu2(void);
	/*PROTOTIPOS DE FUNCION*/
	void administraprod(PRODUCTOS *,int *,DEPARTAMENTOS *,int *);  
	void administradep(DEPARTAMENTOS *,int*); 
	void administrarp(PRODUCTOS*,int*,DEPARTAMENTOS *,int *);
	void imprimeprod(PRODUCTOS*,int,DEPARTAMENTOS*,int); 
	void compras(PRODUCTOS *,int,FILE *,char *,DEPARTAMENTOS *,int,int*,VENTASDIA*);  
	void reportes(VENTASDIA*,int); 
	VENTASDIA nventas[3000]; //ARREGLO QUE CUENTA EL NUMERO DE VENTAS EN EL DIA
	int n = 0;   //VENTAS DEL DIA. INICIALIZADO EN CERO
	int i,opc; 
	do{
	do{
		system("cls"); 
		menu2(); 
		scanf("%d",&opc); 
	}while(opc<1 || opc>6); 
		switch(opc){
			case 1: 
			administrarp(a,tamprod,b,tamdep); //LLAMADAS DE LA FUNCION
			break; 
			case 2: 
			administradep(b,tamdep); break;  
			case 3: compras(a,*tamprod,c,direccion,b,*tamdep,&n,nventas); break; 
			case 4: 
			system("cls"); 
			imprimeprod(a,*tamprod,b,*tamdep);
		printf("\nPRESIONA UNA TECLA PARA REGRESAR\n");
			getch();  
			break; 
			case 5: reportes(nventas,n); 
			break; 
		}
	}while(opc!=6); 
	}
/*FUNCION DE MENUS DE ADMINISTRACION
DE LOS DEPARTAMENTOS*/
void menu4(void){
	system("cls"); 
	printf ("\tADMINISTRACION DE DEPARTAMENTOS\n1.DAR DE ALTA UN DEPARTAMENTO\n2.DAR DE BAJA UN DEPARTAMENTO\n3.MODIFICAR UN DEPARTAMENTO\n4.MOSTRAR DEPARTAMENTOS\n5.REGRESAR\nOPCION: "); 
}
/*FUNCION ADMINISTRADORA
DE LOS DEPARTAMENTOS*/
void administradep(DEPARTAMENTOS *b,int *tamdep){
	/*PROTOTIPOS DE LA FUNCION*/
	void modificadep(DEPARTAMENTOS *,int *);
	void menu4(); 
	void agregadep(DEPARTAMENTOS *a,int *); 
	void imprimedep(DEPARTAMENTOS *,int ); 
	void borradep(DEPARTAMENTOS *a,int *); 
	int opc; //opc = OPCION DE ADMINISTRACION DE DEPARTAMENTOS
	do{
	do{
		menu4(); 
		scanf("%d",&opc); 
	}while(opc>5); 
	switch(opc){
	case 1: agregadep(b,tamdep); //LLAMADAS DE LA FUNCION 
	break; 
	case 2: borradep(b,tamdep);
	break;  
	case 3: modificadep(b,tamdep); 
	break; 
	case 4: system("cls"); 
	imprimedep(b,*tamdep); 
	printf("PRESIONA UNA TECLA PARA REGRESAR\n"); 
	getch(); 
	break;  
}
}while(opc!=5); 
}
/*FUNCION ENCARGADA DE BORRAR LOS DEPARTAMENTOS*/
void borradep(DEPARTAMENTOS *a,int *t){
	int opc,i,opcg;  //opc = OPCION PARA BORRAR DEPARTAMENTO. opcg = OPCION DE REPETICION
	do{
	do{
		system("cls"); 
		imprimedep(a,*t);
		printf ("DIGITE EL NUMERO DEL DEPARTAMENTO A BORRAR: "); 
		scanf("%d",&opc); 
	}while(opc<0 || opc>*t-1); 
	i = opc; 
	for (i;i<*(t)-1;i++){
		strcpy(a[i].cod_dep,a[i+1].cod_dep); 
		strcpy(a[i].nombre,a[i+1].nombre);  
	}
	 	
	*t = *t-1; 
	system("cls"); 
	printf ("EL DEPARTAMENTO SE HA BORRADO CON EXITO\n\n"); 
	printf ("DESEA SEGUIR ELIMINANDO DEPARTAMENTOS?\n1.SI\n2.NO\nOPCION: "); 
	scanf("%d",&opcg); 
	}while(opcg==1); 
	printf ("AHORA SON %d DEPARTAMENTOS\n",*t); 
	getch(); 
}
/*FUNCION. MODIFICA LOS DEPARTAMENTOS*/
void modificadep(DEPARTAMENTOS *a,int *t){
	/*PROTOTIPOS DE LA FUNCION*/
	void men (void);  
	void imprimedep(DEPARTAMENTOS *,int);
	void modificanomdep(DEPARTAMENTOS *,int );  
	int opcdep,opcg; //opcdep = OPCION PARA MODIFICAR EL DEPARTAMENTO. opcg = OPCION DE REPETICION 
	do{
	do{
		system("cls");
		imprimedep(a,*t); //LLAMADAS DE LA FUNCION 
	printf ("QUE DEPARTAMENTO DESEA MODIFICAR\nOPCION: ");
	scanf("%d",&opcdep);  
}while(opcdep<0 || opcdep>(*t)-1);
	system("cls"); 
	printf ("UNICAMENTE SE PUEDE MODIFICAR EL NOMBRE DEL DEPARTAMENTO\n");
	modificanomdep(a,opcdep); 
	printf ("DESEA CONTINUAR MODIFICANDO?\n1.SI\n2.NO\nOPCION: "); 
	scanf("%d",&opcg); 
	}while(opcg==1); 
	
}
/*MODIFICA EL NOMBRE DEL DEPARTAMENTO*/
void modificanomdep(DEPARTAMENTOS *a,int i){
	printf ("ESCRIBE EL NUEVO NOMBRE DEL DEPARTAMENTO: "); 
	fflush(stdin); 
	scanf("%s",&(a[i].nombre));
	strupr(a[i].nombre);  
}
/*ADMINISTRA LOS PRODUCTOS*/
void administrarp(PRODUCTOS *a, int *tamprod,DEPARTAMENTOS *b,int *tamdep){
	void modificaprod(PRODUCTOS *,int *,DEPARTAMENTOS *,int *);
	void agregaprod(PRODUCTOS *,int*);
	void borraprod(PRODUCTOS *,int*,DEPARTAMENTOS*,int*);  
	int opc;
	do{
	do{
	system("cls");
	printf ("\tADMINISTRACION DE PRODUCTOS\n1.DAR DE ALTA UN PRODUCTO\n2.DAR DE BAJA UN PRODUCTO\n3.MODIFICAR UN PRODUCTO\n4.REGRESAR\nOPCION: ");
	scanf("%d",&opc);
}while(opc<1 | opc>4);
	switch(opc){
		case 1: agregaprod(a,tamprod); break; //LLAMADAS DE LA FUNCION
		case 2:  borraprod(a,tamprod,b,tamdep);     break; 
		case 3: modificaprod(a,tamprod,b,tamdep); break;
	}
	}while(opc!=4); 
}
/*ELIMINA PRODUCTOS DE LA LISTA*/
void borraprod(PRODUCTOS *a,int *t,DEPARTAMENTOS *b,int *tamdep){
	int i,opc,opcg; //opc = OPCION PARA BORRAR PRODUCTOS. opcg = OPCION DE REPETICION
	void imprimeprod(PRODUCTOS *,int,DEPARTAMENTOS *b,int);  //PROTOTIPO DE LA FUNCION
	
	do{
	do{
		system("cls"); 
		imprimeprod(a,*t,b,*tamdep);
		printf ("DIGITE EL NUMERO DEL PRODUCTO A BORRAR: "); 
		scanf("%d",&opc); 
	}while(opc<0 || opc>*t-1); 
	i = opc; 
	for (i;i<*(t)-1;i++){
		strcpy(a[i].clave_prod,a[i+1].clave_prod); 
		strcpy(a[i].nom_prod,a[i+1].nom_prod); 
		a[i].cant_exis = a[i+1].cant_exis; 
		strcpy(a[i].codigo_dep,a[i+1].codigo_dep); 
		a[i].precio = a[i+1].precio; 
		a[i].cant_sug = a[i+1].cant_sug; 
		a[i].movimiento = a[i+1].movimiento; 
			
	}
	*t -= 1; 
	system("cls"); 
	printf ("EL PRODUCTO SE ELIMINO DE LA LISTA CON EXITO\n\n"); 
	printf ("DESEA SEGUIR ELIMINANDO PRODUCTOS?\n1.SI\n2.NO\nOPCION: "); 
	scanf("%d",&opcg); 
	}while(opcg==1); 
	
}
/*MODIFICA ALGUNA DE LAS OPCIONES DE LOS PRODUCTOS*/
void modificaprod(PRODUCTOS *a,int *tamprod,DEPARTAMENTOS *b,int *tamdep){
	/*PROTOTIPOS DE LA FUNCION*/
	void menu3(void); 
	void modificanom(PRODUCTOS *,int );  
	void modificacant(PRODUCTOS*,int ); 
	void modificacodep(PRODUCTOS *a,int); 
	void modificaprecio(PRODUCTOS *a,int); 
	
	int opcprod,opc,opcg; //opcprod = OPCION DEL PRODUCTO A MODIFICAR, opc = QUE DESEA MODIFICAR, opcg = OPCION DE REPETICION
	do{
	do{
		system("cls");
			imprimeprod(a,*tamprod,b,*tamdep);  
	printf ("QUE PRODUCTO DESEA MODIFICAR\nOPCION: ");
	scanf("%d",&opcprod);  
}while(opcprod<0 || opcprod>(*tamprod)-1); 
	do{
		system("cls"); 
		menu3(); 
		scanf("%d",&opc); 
	}while(opc<1 || opc>4);
	switch (opc){
		case 1: 
		modificanom(a,opcprod); //LLAMADAS DE LA FUNCION
		break; 
		case 2: 
		modificacant(a,opcprod); 
		break; 
		case 3: 
		modificacodep(a,opcprod);
		break; 
		case 4:
		modificaprecio(a,opcprod); 
		break;  
} 
	printf ("DESEA CONTINUAR MODIFICANDO?\n1.SI\n2.NO\nOPCION: "); 
	scanf("%d",&opcg); 
	}while(opcg==1); 
}
/*MENU DE MODIFICACION DE LOS DATOS DE UN PRODUCTO*/
void menu3(){
	system("cls"); 
	printf ("QUE DESEA MODIFICAR\n1.NOMBRE\n2.CANTIDAD EN EXISTENCIA\n3.CODIGO DEL DEPARTAMENTO\n4.PRECIO\nOPCION: ");
}
/*MODIFICA EL NOMBRE DE UN PRODUCTO*/
void modificanom(PRODUCTOS *a,int i){
	system("cls"); 
	printf ("DAME EL NUEVO NOMBRE PARA MODIFICARLO: ");
	fflush(stdin); 
	scanf("%s",&(a[i].nom_prod)); 
	strupr(a[i].nom_prod); 
}
/*MODIFICA LA CANTIDAD DE UN PRODUCTO*/
void modificacant(PRODUCTOS *a,int i){
	system("cls"); 
	printf ("DAME LA NUEVA CANTIDAD EN EXISTENCIA DEL PRODUCTO: "); 
	scanf("%d",&(a[i].cant_exis));
	a[i].cant_sug = (a[i].cant_exis)*.70; 
}
/*MODIFICA EL CODIGO DEL DEPARTAMENTO PERTENECIENTE
DE UN PRODUCTO*/
void modificacodep(PRODUCTOS *a,int i){
	system("cls");
	printf ("DAME EL NUEVO CODIGO DE DEPARTAMENTO PERTENECIENTE: "); 
	fflush(stdin); 
	scanf("%s",&(a[i].codigo_dep)); 
	strupr(a[i].codigo_dep); 
}
/*MODIFICA EL PRECIO DE UN PRODUCTO*/
void modificaprecio(PRODUCTOS *a,int i){
	system("cls"); 
	printf ("DAME EL NUEVO PRECIO DEL PRODUCTO: "); 
	scanf("%f",&(a[i].precio)); 
}
/*AGREGA DEPARTAMENTOS A LA LISTA*/
void agregadep(DEPARTAMENTOS *a,int *t){
	int i = *t+1; //VALOR MAXIMO AL MOMENTO DE AGREGAR
	int j = *t,opc; // j = CONTADOR INICIAL DEL CICLO. opc = OPCION DE REPETICION 
	do{
	for (j;j<i;j++){
		system ("cls"); 
		printf ("\t\tAGREGA DEPARTAMENTOS\t\t\n\n"); 
		printf ("\nDAME EL CODIGO DEL DEPARTAMENTO: "); 
		fflush(stdin); 
		scanf("%s",&(a[j].cod_dep));
		strupr(a[j].cod_dep);  
		printf ("\nDAME EL NOMBRE DEL DEPARTAMENTO: ");
		fflush(stdin); 
		scanf("%s",&(a[j].nombre));
		strupr(a[j].nombre);  
		printf ("DESEA AGREGAR MAS DEPARTAMENTOS?\n1.SI\n2.NO\nOPCION: "); 
		scanf("%d",&opc); 
		if (opc==1){
			i++;
		}
	}
	}while(opc==1); 
	*t = j; //MODIFICA LA CANTIDAD DE DEPARTAMENTOS
	printf ("AHORA SON %d DEPARTAMENTOS\n",*t); 
	getch(); 
	return; 
	
	
	
}
/*AGREGA PRODUCTOS A LA LISTA*/
void agregaprod(PRODUCTOS *a,int *t){
	int i = *t+1; //VALOR MAXIMO AL MOMENTO DE AGREGAR
	int j = *t,opc; // j = CONTADOR INICIAL DEL CICLO. opc = OPCION DE REPETICION 
	do{
	for (j;j<i;j++){
		system ("cls");
		printf ("\t\t AGREGA PRODUCTOS\t\t\n\n");  
		printf ("\nDAME LA CLAVE DEL PRODUCTO: "); 
		fflush(stdin); 
		scanf("%s",&(a[j].clave_prod)); 
		strupr(a[j].clave_prod);  
		printf ("\nDAME EL NOMBRE DEL PRODUCTO: ");
		fflush(stdin); 
		scanf("%s",&(a[j].nom_prod)); 
		strupr(a[j].nom_prod); 
		printf ("\nCANTIDAD EN EXISTENCIA: "); 
		scanf("%d",&(a[j].cant_exis)); 
		printf ("\nCODIGO DEL DEPARTAMENTO DEL PRODUCTO: "); 
		fflush(stdin); 
		scanf("%s",&(a[j].codigo_dep));
		strupr(a[j].codigo_dep);  
		printf ("\nPRECIO DEL PRODUCTO: ");
		scanf ("%f",&(a[j].precio)); 
		a[j].cant_sug = (a[j].cant_exis)*.70;
		a[j].movimiento = 0;  
		printf ("DESEA AGREGAR MÁS PRODUCTOS?\n1.SI\n2.NO\nOPCION: "); 
		scanf("%d",&opc);
		
		if (opc==1){
			i++; 
		}  
	}
	}while(opc==1); 
	*t = j; //MODIFICA EL NUMERO DE PRODUCTOS EXISTENTES
	printf ("AHORA SON %d PRODUCTOS\n",*t); getch(); 
	return; 
}
/*FUNCION EN CASO DE QUE SE COMPRE UN PRODUCTO*/
void compras(PRODUCTOS *a,int t,FILE *c,char *direccion3,DEPARTAMENTOS *b,int tamdep,int *n,VENTASDIA *ventas){ 
	int opc,opcom=0,cont,cant;  //opc = OPCION PARA SEGUIR COMPRANDO PRODUCTOS. opcom = OPCION DEL PRODUCTO A COMPRAR
	//cont = CONTADOR DEL NUMERO DE PRODUCTOS TOTALES. cant = CANTIDAD DE PRODUCTOS QUE SE DESEA COMPRAR DE UN SOLO TIPO. 
	double desc; //VARIABLE PARA APLICAR EL DESCUENTO
	double prec;  //VARIABLE ENCARGADA DE SUMAR EL PRECIO TOTAL
	char nombre[]="RECIBO.txt";  
	int dia,mes,anio; 
	printf ("DAME LA FECHA EN FORMATO dd/mm/aaaa: "); 
	fflush(stdin); 
	scanf("%d %d %d",&dia,&mes,&anio);    
	c = fopen(nombre,"w+");
	if (c!=NULL){
		fprintf (c,"%s\n","RECIBO");
		fprintf (c,"CANTIDAD\tDESCRIPCION  PRECIO c/u\t\tDESCUENTO\n");  
	do{
		do{
		system("cls"); 
		imprimeprod(a,t,b,tamdep); //LLAMADA DE LA FUNCION
		printf ("SELECCIONA UN PRODUCTO POR SU NUMERO PARA COMPRAR\n");   
		scanf("%d",&opcom);
	}while(opcom>t-1); 
	printf ("CUANTOS PRODUCTOS DESEA COMPRAR?: ");
	scanf("%d",&cant); 
	if (cant>a[opcom].cant_sug) a[opcom].movimiento = 1; 
	else a[opcom].movimiento = 0; 
	if (cant>a[opcom].cant_exis) printf ("NO HAY CANTIDAD SUFICIENTE DE PRODUCTOS\n"); 
	else{
			fprintf (c,"%d\t\t",cant); 
			fprintf (c,"%s\t\t",a[opcom].nom_prod);
			fprintf (c,"%.2lf\t\t",a[opcom].precio);
		if(cant>5){ 
			desc = (((a[opcom].precio)*cant) * .10);
			fprintf (c,"%.2lf\t",desc); 
			prec += ((a[opcom].precio)*cant)-desc; 
			a[opcom].cant_exis = a[opcom].cant_exis - cant;  
			cont += cant;
			 
		}else{
			fprintf (c,"%.2lf\t",0); 
			prec += (a[opcom].precio)*cant;
			a[opcom].cant_exis = a[opcom].cant_exis - cant; 
			cont += cant; 
		}
	} 
	fprintf (c,"\n");
		system("cls");
		printf ("DESEA COMPRAR MAS PRODUCTOS\n1.SI\n2.NO\nOPCION: ");
		scanf("%d",&opc);  
	}while(opc==1); 
}else printf ("NO SE ENCUENTRA LA DIRECCION DE LA CARPETA\n"); 
	
	
	fprintf (c,"PRECIO TOTAL: ");
	fprintf (c,"%.2lf\n",prec); 
	prec = prec + (prec*.16);
	fprintf(c,"PRECIO CON IVA: "); 
	fprintf(c,"%.2lf\n",prec);   
	fprintf(c,"FECHA: "); 
	fprintf(c,"%2d/%2d/%2d",dia,mes,anio); 
	printf ("El RECIBO SE GUARDO COMO: %s\n",nombre);
	ventas[*n].dia = dia; 
	ventas[*n].mes = mes; 
	ventas[*n].anio = anio;
	ventas[*n].ganancias = prec;
	*n += 1;   
	getch();  
	fclose(c); 
	return; 
}
/*MUESTRA LOS REPORTES DE LAS VENTAS EN EL DIA*/ 
void reportes(VENTASDIA *a,int t){
	int i;
	double totaldia = 0; //SUMA LAS GANANCIAS TOTALES DEL DIA
	system("cls");  
	printf ("NUMERO\tDIA\tMES\tAÑO\tVENTA TOTAL DEL RECIBO\n"); 
	for (i=0;i<t;i++){
	printf ("\n%d\t",i+1); 
	printf ("%d\t",a[i].dia); 
	printf ("%d\t",a[i].mes); 
	printf ("%d\t",a[i].anio); 	
	printf ("%.2lf\n",a[i].ganancias); 
	totaldia+= a[i].ganancias; 
	}
	printf ("\n\nEL TOTAL DEL DIA ES %.2lf\n",totaldia); 
	printf ("\n\nPRESIONA UNA TECLA PARA REGRESAR\n\n"); 
	getch(); 
	
}
/*GUARDA LOS CAMBIOS REALIZADOS 
EN UN ARCHIVO*/
void guardar(FILE *a,FILE *b,DEPARTAMENTOS *dep,PRODUCTOS *prod,int *tamdep,int *tamprod){
	int i;  //CONTADOR
	if (a!=NULL && b!=NULL){
		fprintf(a,"%d\n",*tamdep); 
		for (i=0;i<*tamdep;i++){
			fprintf(a,"%s\t",dep[i].cod_dep); 
			fprintf(a,"%s\n",dep[i].nombre); 
		}
		fprintf(b,"%d\n",*tamprod);
		for (i=0;i<*tamprod;i++){
			fprintf(b,"%s\t",prod[i].clave_prod); 
			fprintf(b,"%s\t",prod[i].nom_prod); 
			fprintf(b,"%d\t",prod[i].cant_exis); 
			fprintf (b,"%s\t",prod[i].codigo_dep); 
			fprintf (b,"%f\n",prod[i].precio); 	
		}
		system("cls"); 
		printf ("SE HA GUARDADO CON EXITO\n");
		getch();   
		
	}else printf ("NO SE GUARDARON LOS CAMBIOS\n"); 
	fclose(a); 
	fclose(b); 
}
