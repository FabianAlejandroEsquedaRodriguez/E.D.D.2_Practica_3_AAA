/*
-> Domínguez Martínez Edder Emmanuel
-> Esqueda Rodríguez, Fabián Alejandro.
-> Godoy Rodríguez, Berenice.
-> Gómez Jiménez, Ángel Armando.
-> Gómez Ramírez, Eduardo Fabián.

Sección: D05
Calendario: 2021-A
*/ 

#include <iostream>
#include <fstream>
#include <iomanip>
#include "cliente.h"

using namespace std;

int main(){
    system("cls");
    system("color F1");
    
    //Atributos que tenemos en la clase
    int numeroCuenta;
    char apellido[15];
    char primerNombre[10];
    double saldo;

    size_t opc;
    Cliente cliente;//Objeto de la clase Cliente

    //Menu de opciones
    do{
        cout<<"\t\t\t\t\tMENU - INVESTIGACION DE CREDITOS\n\n";
        
        cout<<"1) Consulta individual (numero de cuenta)"<<endl;
        cout<<"2) Consultas generales"<<endl;
        cout<<"3) Salir"<<endl<<endl;

        cout<<"Digita una opcion: ";
        cin>>opc;

        //Este objeto me va a servir para leer datos en el archivo
        ifstream creditoEntrada("credito.dat", ios::in | ios::binary);//Modo binario para la salida de los datos
                                                            //Esto es requerido para escribir registros de longitud fija
    
        if(!creditoEntrada){
            cerr<<"EL ARCHIVO NO SE PUDO ABRIR DE FORMA CORRECTA\n";
            exit(1);
        }

        system("cls");

        if(opc == 1){
            cout<<"\t\t\t\tCONSULTA INDIVIDUAL (NUMERO DE CUENTA)\n\n";

            cout<<"Teclea el numero de cuenta del cliente: ";
            cin>>numeroCuenta;

            cliente.establecerNumeroCuenta(numeroCuenta);

            //buscar en la posición en el archivo del registro especificado por el usuario
            creditoEntrada.seekg((cliente.obtenerNumeroCuenta()-1) * sizeof(Cliente));//seekg(n, ios::beg)

            //Leer la información especificada por el usuario en el archivo
            creditoEntrada.read(reinterpret_cast <char *>(&cliente), sizeof(Cliente));

            if(numeroCuenta != cliente.obtenerNumeroCuenta()){
                cout<<"\n\n\n\t\t\tEL NUMERO DE CUENTA NO EXISTE...\n\n\n";
            }

            else{
                cout<<endl;
                cout<<"CUENTA       : "<<cliente.obtenerNumeroCuenta()<<endl;
                cout<<"APELLIDO     : "<<cliente.obtenerApellido()<<endl;
                cout<<"PRIMER NOMBRE: "<<cliente.obtenerPrimerNombre()<<endl;
                cout<<"SALDO        : $ "<<cliente.obtenerSaldo()<<endl;
            }
            
        }

        else if(opc == 2){
            cout<<"\t\t\t\tCONSULTA GENERAL\n\n";
            
            //Esta linea me esta leyendo el primero registro del archivo
            creditoEntrada.read(reinterpret_cast<char *> (&cliente), sizeof(Cliente));
            
            cout<<left<<setw(10)<<"CUENTA"<<setw(16)<<"APELLIDO"<<setw(11)<<"NOMBRE"<<left<<
            setw(10)<<right<<"SALDO"<<endl;


            //Mientras el archvivo se haya abierto (esté bien) y no sea el final del archivo
            while(creditoEntrada && !creditoEntrada.eof()){ 
                //Imprimir el primer registro
                if(cliente.obtenerNumeroCuenta() != 0){
                    cout<<left<<setw(10)<<cliente.obtenerNumeroCuenta()
                    << setw(16)<<cliente.obtenerApellido()
                    << setw(11)<<cliente.obtenerPrimerNombre()<<left
                    << setw(10)<<setprecision(2)<<right<<fixed<<showpoint<<cliente.obtenerSaldo()<<endl;
                }
                //Leyendo el siguiente registro en el archivo
                creditoEntrada.read(reinterpret_cast<char *>(&cliente), sizeof(Cliente));
            }//Fin del while()
        }//Fin del else if()

        else{
            break;
        }

        creditoEntrada.close();

        cout<<"\n\n\n"; system("pause"); system("cls"); 

    }while(opc != 3);

    return 0;
    
}//fin del main