/*Grupo #1
Juan Luis Vásquez López 0909-20-6391
Mercy Salome Vásquez Ortiz 0909-20-5202
Hugo Andreé Argueta Rodas 0909-20-4492 
Maderlaine Vanessa Aldana Martínez 0909-20-6881
Christopher Enrique Berganza Zepeda 0909-20-21504
 */

// Declaramos la s librerias
#include<iostream>
#include<mysql.h>
#include<locale.h>
#include<conio.h>
	
using namespace std;

// Realizamos la conexion con la Base de Datos
	class conne{
		
		public:
		MYSQL *obj;
		
		char* conectar(char *server, char *user, char *pw, char *database){
			
				if(!(obj=mysql_init(0))){
						return "Error al crear el objeto"; // Mostramos un mensaje de error
					}
					if(!mysql_real_connect(obj,server,user,pw,database, 3306,NULL,0)){
						return (char*)mysql_error(obj); }
					else {
						return "******** Base de Datos en Uso ********"; // Mostramos un mensaje al usuario
					}
		}// Finalizamos el char
		
		void desconectar(){
			mysql_close(obj);
    	}// Finalizamos el void
	};// Finalizamos la funcion clase conne
	
	conne conexion;
	
	// Declaramos los datos de las comlumnas para la base de datos
	struct stalumno_3{
	char id[3];
	char nombre[50];
	char apellido[50];
	char numero[8];
	char curso[50];	
	}alu;
	
	// Conectamos a la entidad clalumno_3
	class clalumno_3{
		public:
			char *resultado;
			
			// Definimos una funcion para ingresar datos en la entidad
			void insertar(struct stalumno_3 x){
				
				try{ //Direccion, Usario,Contraseña, Nombre de la entidad
				conexion.conectar("localhost","root","","alumno_3"); 
				char *consulta;  //Sentencia en SQL
				char sentencia[]="INSERT INTO ALUMNO_3 (id,nombre,apellido,numero,curso) VALUES (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')";
				consulta=new char[strlen(sentencia)+sizeof(stalumno_3)]-sizeof(int);
				sprintf(consulta,sentencia,alu.id,alu.nombre,alu.apellido,alu.numero,alu.curso);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj); }
					
				resultado="* Registro Ingresado Correctamente *\n"; } //Mostramos mensaje al usuario
				
				catch(const char* msg){
					cout<<msg;
					conexion.desconectar();	}
			}// Finalizamos la funcion insertar
			
			// Definimos la funcion para modificar en la entidad
			void modificar(struct stalumno_3 x){
				
				try{//Direccion, Usario,Contraseña, Nombre de la entidad
				conexion.conectar("localhost","root","","alumno_3");
				char *consulta; //Sentencia en SQL
				char sentencia[]="UPDATE alumno_3 SET nombre=\'%s\',apellido=\'%s\',numero=\'%s\',curso=\'%s\' WHERE id=\'%s\'"; 
				consulta=new char[strlen(sentencia)+sizeof(stalumno_3)]-sizeof(int);
				sprintf(consulta,sentencia,alu.nombre,alu.apellido,alu.numero,alu.curso,alu.id);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj); }
				
				resultado="* Registro Modificado *\n"; } //Mostramos mensaje al usuario
				
				catch(const char* msg){
					cout<<msg;
					conexion.desconectar(); }
			}// Finalizamos la funcion modificar
			
			// Definimos la funcion para eliminar en la entidad
			void eliminar(struct stalumno_3 x){
				
				try{//Direccion, Usario,Contraseña, Nombre de la entidad
				conexion.conectar("localhost","root","","alumno_3");
				char *consulta;
				char sentencia[]="DELETE from ALUMNO_3 WHERE ID=\'%s\'"; // Sentencia en SQL
				consulta=new char[strlen(sentencia)+sizeof(stalumno_3)]-sizeof(int);
				sprintf(consulta,sentencia,alu.id);
				int aux=mysql_query(conexion.obj,consulta);
				if(!aux==0){
					throw mysql_error(conexion.obj); }
					
				resultado="Registro ELiminado Correctamente\n"; } //Mostramos mensaje al usuario
				
				catch(const char* msg){
					cout<<msg;
					conexion.desconectar(); }
			}// Finalizamos la funcion eliminar
			
			// Definimos la funcion la mostrar datos de la entidadvoid para mostrar datos de la tabla
			void mostrar(){ //Esta es Otra Forma en un solo metodo
				   MYSQL           *objDatos;
				   MYSQL_RES       *res;
				   MYSQL_ROW        row;
				   MYSQL_FIELD     *columna;
				   int              i, j, k, l;
				   unsigned long   *lon;
				   MYSQL_ROW_OFFSET pos;
				   
				   if(!(objDatos = mysql_init(0))) {
				   	
				      cout<<"Error Objeto"<<endl; //Mostramos mensaje al usuario
				      
				      rewind(stdin);
				      getchar();	      
					}                          //Direccion, Usario,Contraseña, Nombre de la tabla
				   if(!mysql_real_connect(objDatos,"localhost", "root", "", "alumno_3", 3306, NULL, 0)) {
				      cout<<"Error BD"<<MYSQL_PORT<<" Error: "<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				   if(mysql_select_db(objDatos, "alumno_3")) {
				      cout<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				   if(mysql_query(objDatos, "SELECT * FROM ALUMNO_3")) {
				      cout<<mysql_error(objDatos)<<endl;
				      mysql_close(objDatos);
				      rewind(stdin);
				      getchar();
				   }
				if((res=mysql_store_result(objDatos))){
					i=(int)mysql_num_rows(res);
					j=(int)mysql_num_fields(res);
					cout<<endl<<"		Datos de los Alumnos"<<endl;
					l=1;
					for(l=0;l<i;l++){
						row=mysql_fetch_row(res);
						lon=mysql_fetch_lengths(res);
						cout<<endl;
						for(k=0;k<j;k++){
						cout<<"	"<<((row[k]==NULL)?"NULL":row[k])<<"	";
					}
				}cout<<endl;
			    mysql_free_result(res);
			   }
			   mysql_close(objDatos);
			   rewind(stdin);
			   cout<<endl;
			}// Finalizamos la funcion mostrar
	};// Finalizamos la funcion Clase alumno
	
	void salir(){
		cout<<"Programa Finalizado\n"; //Mostramos mensaje al usuario
	}
	
	void menu(){ // Definimos la funcion menu
		int opcion=0; // Definimos la variable opcion
		clalumno_3 op;
		do{
		//Mostramos un menu al usuaio
		cout << "\n\t**************************************";
		cout << "\n\t*     Base de Datos  Alumnos         *";
		cout << "\n\t**************************************";
		cout << "\n\t* 1. Ingrese informacion de alumnos  *";
		cout << "\n\t* 2. Eliminar datos de alumnos       *";
		cout << "\n\t* 3. Actualizar datos de alumnos     *";
		cout << "\n\t* 4. Observar datos de alumnos       *";
		cout << "\n\t* 5. Salir                           *";
		cout << "\n\t**************************************";
		cout << "\n\tIngrese la opcion: ";
		
		clalumno_3 x;
		cin>>opcion; // Leemos la opción de menú
		system("cls"); // Limpiamos la pantalla
		
		switch(opcion){
				case 1:		
					cout<<"Ingrese Datos de Alumnos \n";
					cout<<"Ingrese Carnet : ";
					cin>>alu.id;
					cout<<"Ingrese Nombre: ";
					cin>>alu.nombre;
					cout<<"Ingrese Apellido: ";
					cin>>alu.apellido;
					cout<<"Ingrese Numero Celular: ";
					cin>>alu.numero;
					cout<<"Ingrese Curso: ";
					cin>>alu.curso;
					op.insertar(alu); // Llamamos a la funcion insertar
					cout<<op.resultado; 
					system("cls"); // Limpiamos la pantalla
					break;
				
				case 2:		
					clalumno_3 op;
					cout<<"Ingrese Carnet de Alumno a Eliminar: ";
					cin>>alu.id;
					op.eliminar(alu); // Llamamos a la funcion eliminar
					cout<<op.resultado;
					_getch();
					system("cls"); // Limpiamos la pantalla
					break;
				
				case 3:
					cout<<"Modificar Datos de Alumno\n";
					cout<<"Ingrese Carnet : ";
					cin>>alu.id;
					cout<<"\nModificará Registros del Alumno con Carnet "<<alu.id<<endl;
					cout<<"\nIngrese Nuevo Nombre: ";
					cin>>alu.nombre;
					cout<<"Ingrese Nuevo Apellido: ";
					cin>>alu.apellido;
					cout<<"Ingrese Numero Celular: ";
					cin>>alu.numero;
					cout<<"Ingrese Curso: ";
					cin>>alu.curso;
					op.modificar(alu); // Llamamos a la funcion modificar
					cout<<op.resultado;
					system("cls"); // Limpiamos la pantalla
					break;
				
				case 4:
					op.mostrar(); // Llamamos a la funcion mostrar
					_getch(); //Detenemos programa para visualizar los datos
					system("cls"); // Limpiamos la pantalla
					break;
				
				case 5: 
					salir(); //Llamamos a la fucion salir
					_getch(); //Detenemos programa para visualizar los datos
					system("cls"); // Limpiamos la pantalla
					break;
				
				default:
					cout<<"Opción Incorrecta\n"; // Mostrarmos mensaje de error	
					system("cls"); // Limpiamos la pantalla
		} //Finalizamos el Switch
	}while(opcion!=5); // Finalizamos el DO While
	} // Finalizamos la funcion menu
	
int main() { // Definimos la funcion principal
	system("color 01"); // Cambiamos el color 
	setlocale(LC_CTYPE,"Spanish");
	menu(); // Llamamos a la funcion menu
	return 0;
}
