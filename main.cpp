#include <iostream>
#include <fstream>
//Proyecto de Andres Marroquin,Santiago Hernández,Victor peñaranda
using namespace std;
struct Lista //estructura que maneja los usuarios
{
    string Usuario;
    string contrasena;
    int tipo;
    int aceptada;
};
struct Inv//estrucutura que maneja el catalago
{
    int codigo;
    string categoria;
    string producto;
    int precio;
};
struct Ventas//estructura que maneja la ventas
{
    string Usuario;
    char tipo;
    int factura;
    int valor;
    char orden;
    char compra;
};
int tamano_lista();
void guardar_lista(Lista lista[],int taman); //Son 3 funciones que se repiten por el cambio de archivo donde tamano nos dice cuantos datos tiene el documento
void arreglo_lista(Lista lista[],int taman);//Guardar es traer los elementos de un arreglo de vuelta al archivo y arreglo es lo contrario
int tamano_producto();
void arreglo_producto(Inv inv[],int taman_2);
void guardar_producto(Inv inv[],int taman_2);
int tamano_ventas();
void arreglo_ventas(Ventas ventas[],int taman_3);
void guardar_ventas(Ventas ventas[],int taman_3);
int main()
{
    int opcion,tipo,aceptada,tipo_n;
    bool valido=true;
    ifstream leer;
    ofstream escribir;
    char respuesta;
    string Usuario,contrasena_n,contrasena,contrasena_1,Usuario_n;
    while(true)//se nos permite un menu para volver aqui
    {
        cout<<"******** Bienvenido a esta tienda virtual ********"<<endl;
        cout<<"(1)Iniciar sesion"<<endl;
        cout<<"(2)Crear Usuario"<<endl;
        cout<<"(3)Salir"<<endl;
        cout<<"**************************************************"<<endl;
        cin>>opcion;
        system("cls");
        switch(opcion)
        {
        case 1:
        {
            int taman=tamano_lista();
            leer.open("Usuarios.txt");
            leer>>Usuario>>contrasena>>tipo>>aceptada;
            cout<<"\nIngrese un usuario:"; //para iniciar sesion se abre el archivo para revisar si este existe
            cin>>Usuario_n;
            valido=false;
            while(!leer.eof())
            {
                if(Usuario_n==Usuario) //si se encuentra el valor pasamos a una seria de mensajes
                {
                    if(aceptada==0)//0 es estado de cuenta pendiente por lo que se informa eso
                    {
                        valido=true;
                        cout<<"El Usuario al que quiere Ingresar le falta confirmacion.Porfavor comuniquese con el administrador para garantizarle un acceso"<<endl;
                    }
                    else if(aceptada==1)//1 es bloqueado por contraseñas por lo que se le informa eso
                    {
                        valido=true;//se maneja un valido para que al final no muestre el mensaje de que el usuario no fue encontrado;
                        cout<<"El Usuario al que quiere Ingresar fue bloqueado por que excedio el limite de errores al momento de digitar la contraseña"<<endl;
                        cout<<"\nPorfavor comuniquese con el administrador para garantizarle un acceso"<<endl;
                    }
                    else if(aceptada==-1)//1 es que fue rechazado por lo que se le informa al usuario
                    {
                        valido=true;
                        int con=0;
                        while(true)
                        {
                            cout<<"Ingrese su contrasena:"<<endl; //como puede haber un cambio se le pide la contraeña
                            cin>>contrasena_n;
                            if(contrasena_n==contrasena)
                            {
                                cout<<"Su Cuenta fue rechazada por el administrador. Desea cambiar su tipo de usuario?(Si=Y)"<<endl;//si la contraseña es valida se le pregunta si quiere crear otra cuenta
                                cin>>respuesta;
                                if((respuesta=='Y')||(respuesta=='y'))//si la respuesta es si pasamos a este menu
                                {
                                    Lista lista[taman];
                                    arreglo_lista(lista,taman); //se pide la informacion de los archivos
                                    for(int i=0; i<taman; i++)
                                    {
                                        if(Usuario_n==lista[i].Usuario) //se encuentra la ubicacion del usuario
                                        {
                                            while(true)
                                            {
                                                cout<<"Ingrese el nuevo tipo de cuenta: (1=Adminstrador)(2=Cliente)(3=Consulta)";
                                                cin>>tipo_n;//se le pregunta el nuevo tipo de cuenta que quiere
                                                if(tipo_n==lista[i].tipo)
                                                {
                                                    cout<<"Esta eligiendo el mismo tipo que una vez le fue rechazado esta seguro de continuar?(Si=Y)"<<endl;
                                                    cin>>respuesta;//si se elige el mismo se le pregunta si desea que sea así
                                                    if((respuesta=='Y')||(respuesta=='y'))
                                                    {
                                                        lista[i].aceptada=0; //se retorno a estado de pendiente y se cierra este guardado
                                                        break;
                                                    }
                                                }
                                                else if((tipo_n>0)&&(tipo_n<4))
                                                {
                                                    cout<<"Se hare el cambio respectivo a una cuenta de tipo "; //si elige otro se mosrtrara lo que eligio
                                                    if(tipo_n==1)
                                                    {
                                                        cout<<"Administrador"<<endl;
                                                    }
                                                    if(tipo_n==2)
                                                    {
                                                        cout<<"Cliente"<<endl;
                                                    }
                                                    if(tipo_n==3)
                                                    {
                                                        cout<<"Consulta"<<endl;
                                                    }
                                                    lista[i].aceptada=0;
                                                    lista[i].tipo=tipo_n;
                                                    break;
                                                }
                                                else
                                                {
                                                    cout<<"Lo sentimos este tipo de cuenta no existe vuelva a ingresar otro"<<endl;
                                                }
                                            }
                                            cout<<"Se actualizaron los datos"<<endl; //se actualizaran los datos por medio del guardar a los archivos
                                            guardar_lista(lista,taman);
                                            system("pause");
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                con++;
                                cout<<"Contraseña incorrecta le quedan "<<3-con<<" intentos"<<endl;//si no se encontro la contraseña pasamos a un estado de error
                                if(con==3)//si llega a 3 se pedira la informacion de los archivos para cambiar el estado de la cuenta
                                {
                                    Lista lista[taman];
                                    cout<<"Ha llegado al limite de intentos su cuenta pasara a estar bloqueada.Contactese con el administrador para cambiar esto"<<endl;
                                    arreglo_lista(lista,taman);
                                    for(int i=0; i<taman; i++)
                                    {
                                        if(Usuario_n==lista[i].Usuario)
                                        {
                                            lista[i].aceptada=0;
                                            guardar_lista(lista,taman);
                                            system("pause");
                                        }
                                    }

                                    break;
                                }
                            }
                        }
                    }
                    else if(aceptada==2)
                    {
                        if(tipo==1)//si la contraseña fue aceptada y es de tipo 1 se hara lo que pide el tipo administrador
                        {
                            int con=0;
                            while(true)
                            {
                                cout<<"Ingrese su contrasena:"<<endl;
                                cin>>contrasena_n;
                                if(contrasena_n==contrasena)
                                {
                                    bool continuar=true;
                                    while(continuar==true)
                                    {
                                        cout<<"\n*****Bienvenido "<<Usuario_n<<"*****"<<endl;
                                        cout<<"Habilitar registro(1)"<<endl;
                                        cout<<"Desbloquear Usuario(2)"<<endl;
                                        cout<<"Administrar categorias(3)"<<endl;
                                        cout<<"Administrar productos(4)"<<endl;
                                        cout<<"Despachar compras(5)"<<endl;
                                        cout<<"Cerrar sesion(6)"<<endl;
                                        cout<<"***************************"<<endl;
                                        cin>>opcion;
                                        system("cls");
                                        switch(opcion)
                                        {
                                        case 1:
                                        {
                                            valido=false;
                                            Lista lista[taman];//si se quiere habilitar registros se pide la informacion
                                            for(int i=0; i<taman; i++)
                                            {
                                                arreglo_lista(lista,taman);
                                                if(lista[i].aceptada==0) //se encuentra los que piden el acceso
                                                {
                                                    valido=true;
                                                    cout<<"El usuario "<<lista[i].Usuario<<" con una cuenta de tipo "<<lista[i].tipo<<" esta pidiendo acceso.Escriba Y para desbloquearla.Otro para bloquearla"<<endl;
                                                    cin>>respuesta;
                                                    if((respuesta=='y')||(respuesta=='Y'))//se le pregunta al administrador si le quiere dar acceso
                                                    {
                                                        lista[i].aceptada=2;//si la respuesta es correcta se le conce acceso y se actualiza el archivo
                                                        cout<<"La cuenta ha sido aceptada"<<endl;
                                                        guardar_lista(lista,taman);
                                                    }
                                                    else
                                                    {
                                                        lista[i].aceptada=-1;//si la respuesta es negativa se actualiza a rechazado y se actualizan los archivos
                                                        cout<<"La cuenta ha sido rechazada"<<endl;
                                                        guardar_lista(lista,taman);
                                                    }
                                                }
                                            }
                                            if(valido==false)
                                            {
                                                cout<<"No hay cuentas pendientes a confirmar"<<endl;//de estar vacio se informa
                                            }
                                            system("pause");
                                            break;
                                        }
                                        case 2://se pregunta por los archivos que esten bloqueados por fallo en la contraseña
                                        {
                                            char cambio;
                                            valido=false;
                                            Lista lista[taman];
                                            arreglo_lista(lista,taman);
                                            for(int i=0; i<taman; i++)
                                            {
                                                if(lista[i].aceptada==1)//se buscan los archivos que tengan esa condicion y se le muestran al administrador
                                                {
                                                    valido=true;
                                                    cout<<"El usuario "<<lista[i].Usuario<<" con una cuenta de tipo "<<lista[i].tipo<<" esta pidiendo desbloqueo.Escriba Y para realizar un cambio.Otro para cerrarla"<<endl;
                                                    cin>>respuesta;
                                                    if((respuesta=='y')||(respuesta=='Y'))
                                                    {
                                                        cout<<"A que estado desea pasar la cuenta aprobada(1) o denegada(otro)"<<endl;
                                                        cin>>cambio;
                                                        if(cambio=='1')//se hace un proceso similar al del codigo pasado
                                                        {
                                                            lista[i].aceptada=2;
                                                            cout<<"La cuenta ha sido aceptada"<<endl;
                                                            guardar_lista(lista,taman);
                                                        }
                                                        else
                                                        {
                                                            lista[i].aceptada=-1;
                                                            cout<<"La cuenta ha sido rechazada"<<endl;
                                                            guardar_lista(lista,taman);
                                                        }
                                                    }
                                                }
                                            }
                                            if(valido==false)
                                            {
                                                cout<<"No hay cuentas pendientes a desbloquear"<<endl;
                                            }
                                            system("pause");
                                            break;
                                        }
                                        case 3://se le piden los cambios a las categorias
                                        {
                                            int taman_2;
                                            string Categoria;
                                            bool continuar_1=true;

                                            while(continuar_1==true)
                                            {
                                                cout<<"Va a modificar las categorias que quiere hacer:"<<endl;
                                                cout<<"(1)Crear una categoria"<<endl;
                                                cout<<"(2)Borrar una categoria"<<endl;
                                                cout<<"(3)Salir"<<endl;
                                                cin>>opcion;
                                                system("cls");
                                                if(opcion==1)
                                                {
                                                    taman_2=tamano_producto();
                                                    Inv inv[taman_2+1];//como se crecera la matriz se declara esta con un espacio extra
                                                    arreglo_producto(inv,taman_2);
                                                    valido=true;
                                                    cout<<"Ingrese una nueva categoria:"<<endl;
                                                    cin>>Categoria;
                                                    for(int i=0; i<taman_2; i++)
                                                    {
                                                        if(Categoria==inv[i].categoria)//se revisa que no este repetida
                                                        {
                                                            valido=false;
                                                        }
                                                    }
                                                    if(valido==false)
                                                    {
                                                        cout<<"La categoria ingresada.Ya existe"<<endl;
                                                    }
                                                    else if(valido==true)
                                                    {
                                                        cout<<"Para crear una categoria esta debe tener como minimo un producto porfavor ingrese los datos:"<<endl;//si existe se le pide que esta contenga almenos un producto
                                                        while(true)
                                                        {
                                                            bool permitido=true;
                                                            cout<<"Ingrese su codigo:"<<endl; //se le pide un codigo y que este no este repetido
                                                            cin>>inv[taman_2].codigo;
                                                            for(int i=0; i<taman_2; i++)
                                                            {
                                                                if(inv[taman_2].codigo==inv[i].codigo)
                                                                {
                                                                    cout<<"El codigo ya existe porfavor cambielo"<<endl;
                                                                    permitido=false;
                                                                    break;
                                                                }
                                                            }
                                                            if(permitido==true)
                                                            {
                                                                break;
                                                            }
                                                        }
                                                        while(true)
                                                        {
                                                            bool permitido=true;
                                                            cout<<"Ingrese el nombre producto:"<<endl; //se le pide un nombre y que no este repetido
                                                            cin>>inv[taman_2].producto;
                                                            for(int i=0; i<taman_2; i++)
                                                            {
                                                                if(inv[taman_2].producto==inv[i].producto)
                                                                {
                                                                    cout<<"Ya existente un producto con ese nombre.Porfavor eliga otro"<<endl;
                                                                    permitido=false;
                                                                    break;
                                                                }
                                                            }
                                                            if(permitido==true)
                                                            {
                                                                break;
                                                            }
                                                        }
                                                        cout<<"Ingrese el precio producto:"<<endl; //se pide el precio y se actualizan los datos en el archivo
                                                        cin>>inv[taman_2].precio;
                                                        inv[taman_2].categoria=Categoria;
                                                        taman_2=taman_2+1;
                                                        guardar_producto(inv,taman_2);
                                                    }
                                                }
                                                else if(opcion==2)
                                                {
                                                    taman_2=tamano_producto(); //se piden encontrar todos los elementos de una categoria para eliminarlos
                                                    Inv inv[taman_2];
                                                    arreglo_producto(inv,taman_2);
                                                    valido=false;
                                                    cout<<"Ingrese una categoria a eliminar:"<<endl;
                                                    cin>>Categoria;
                                                    for(int i=0; i<taman_2; i++)
                                                    {
                                                        if(Categoria==inv[i].categoria) //se busca la categoria y se abre una bandera para indicar que si esta
                                                        {
                                                            valido=true;
                                                        }
                                                    }
                                                    if(valido==false)
                                                    {
                                                        cout<<"La categoria ingresada.No existe.Porvor vuelva a intentarlo o cambie de opcion"<<endl;
                                                    }
                                                    else if(valido==true)
                                                    {
                                                        for(int i=0; i<taman_2; i++)
                                                        {
                                                            if(Categoria==inv[i].categoria)
                                                            {
                                                                inv[i].categoria="Vacio"; //si se encuentra se cambia la categoria por vacio
                                                            }
                                                        }
                                                    }
                                                    string categoria,producto;
                                                    int codigo,precio;
                                                    ofstream escribir;
                                                    int con=0;
                                                    escribir.open("Productos.txt",ios::trunc);
                                                    while(con!=taman_2)
                                                    {
                                                        if(inv[con].categoria=="Vacio")//pasamos a actualizar el archivo con la condicion de que si esta la categoria en vacio se salte los demas datos de esa misma fila
                                                        {
                                                            con++;
                                                        }
                                                        else
                                                        {
                                                            codigo=inv[con].codigo;
                                                            categoria=inv[con].categoria;
                                                            producto=inv[con].producto;
                                                            precio=inv[con].precio;
                                                            escribir<<codigo<<" "<<categoria<<" "<<producto<<" "<<precio<<endl;
                                                            con++;
                                                        }
                                                    }
                                                    escribir.close();
                                                    cout<<"La categoria fue eliminada de manera exitosa"<<endl;
                                                }
                                                else if(opcion==3)
                                                {
                                                    continuar_1=false;
                                                }
                                            }
                                            break;
                                        }
                                        case 4://se le preguntan por los cambios en los productos
                                        {
                                            int taman_2;
                                            string Categoria;
                                            bool continuar_1=true;
                                            while(continuar_1==true)
                                            {
                                                cout<<"Va a modificar los productos que desea hacer:"<<endl;
                                                cout<<"(1)Nuevo producto"<<endl;
                                                cout<<"(2)Eliminar Producto"<<endl;
                                                cout<<"(3)Modificar producto"<<endl;
                                                cout<<"(4)Salir"<<endl;
                                                cin>>opcion;
                                                system("cls");
                                                switch(opcion)
                                                {
                                                case 1:
                                                {
                                                    int con=0;
                                                    taman_2=tamano_producto();
                                                    string categorias[taman_2]; //si se pide un nuevo producto es el mismo caso se le pide al sistema que nos muestre cuales son los datos y se declara con un espacio extra
                                                    Inv inv[taman_2+1];
                                                    arreglo_producto(inv,taman_2);
                                                    for(int i=0; i<taman_2; i++)
                                                    {
                                                        bool revisar=true;
                                                        categorias[con]=inv[i].categoria;
                                                        for(int l=0; l<taman_2; l++)
                                                        {
                                                            if((categorias[con]==categorias[l])&&(con!=l)) //se hace un arreglo categorias para ver cuantas tenemos sin repetir
                                                            {
                                                                revisar=false;
                                                                break;
                                                            }
                                                        }
                                                        if(revisar==true)
                                                        {
                                                            con++;
                                                        }
                                                    }
                                                    while(true)
                                                    {
                                                        cout<<"Eliga una de las categorias disponibles:"<<endl; //se le pide al programa que nos diga unade las categorias ya existentes para crear el programa
                                                        for(int i=0; i<con; i++)
                                                        {
                                                            cout<<"("<<i<<")"<<categorias[i]<<endl;
                                                        }
                                                        cin>>opcion;
                                                        if((opcion>-1)&&(opcion<con))
                                                        {
                                                            inv[taman_2].categoria=categorias[opcion];
                                                            break;
                                                        }
                                                    }
                                                    while(true)
                                                    {
                                                        bool permitido=true;
                                                        cout<<"Ingrese el codigo del producto:"<<endl; //se le pide el codigo y que no se repita
                                                        cin>>inv[taman_2].codigo;
                                                        for(int i=0; i<taman_2; i++)
                                                        {
                                                            if(inv[taman_2].codigo==inv[i].codigo)
                                                            {
                                                                cout<<"El codigo ya existe porfavor cambielo"<<endl;
                                                                permitido=false;
                                                                break;
                                                            }
                                                        }
                                                        if(permitido==true)
                                                        {
                                                            break;
                                                        }
                                                    }
                                                    while(true)
                                                    {
                                                        bool permitido=true;
                                                        cout<<"Ingrese el nombre del producto:"<<endl; //Mismo caso con el nombre
                                                        cin>>inv[taman_2].producto;
                                                        for(int i=0; i<taman_2; i++)
                                                        {
                                                            if(inv[taman_2].producto==inv[i].producto)
                                                            {
                                                                cout<<"Ya existente un producto con ese nombre.Porfavor eliga otro"<<endl;
                                                                permitido=false;
                                                                break;
                                                            }
                                                        }
                                                        if(permitido==true)
                                                        {
                                                            break;
                                                        }
                                                    }
                                                    while(true)
                                                    {
                                                        cout<<"Ingrese el precio del producto:"<<endl;
                                                        cin>>inv[taman_2].precio;
                                                        if(inv[taman_2].precio>50) //Al precio se le pide que no sea inferior a 50 al ser un costo monetario real
                                                        {
                                                            break;
                                                        }
                                                    }
                                                    cout<<"Producto creado de manera exitosa"<<endl;
                                                    system("pause");
                                                    taman_2=taman_2+1;
                                                    guardar_producto(inv,taman_2);
                                                    break;
                                                }
                                                case 2:
                                                {
                                                    int eliminar; //se le pide elimar el producto
                                                    taman_2=tamano_producto();
                                                    Inv inv[taman_2];
                                                    arreglo_producto(inv,taman_2);
                                                    for(int i=0; i<taman_2; i++)
                                                    {
                                                        cout<<"Codigo:"<<inv[i].codigo<<"  Categoria:"<<inv[i].categoria<<"  Producto:"<<inv[i].producto<<endl;
                                                    }
                                                    while(true)
                                                    {
                                                        bool encontrado=false;
                                                        cout<<"\nEscriba el codigo del elemento que quiere eliminar:"; //se hace por medio del codigo y usando el mismo modelo de vacio
                                                        cin>>eliminar;
                                                        for(int i=0; i<taman_2; i++)
                                                        {
                                                            if(eliminar==inv[i].codigo)
                                                            {
                                                                encontrado=true;
                                                                inv[i].categoria="Vacio";
                                                                string categoria,producto;
                                                                int codigo,precio;
                                                                ofstream escribir;
                                                                int con=0;
                                                                escribir.open("Productos.txt",ios::trunc);
                                                                while(con!=taman_2)
                                                                {
                                                                    if(inv[con].categoria=="Vacio")
                                                                    {
                                                                        con++;
                                                                    }
                                                                    else
                                                                    {
                                                                        codigo=inv[con].codigo;
                                                                        categoria=inv[con].categoria;
                                                                        producto=inv[con].producto;
                                                                        precio=inv[con].precio;
                                                                        escribir<<codigo<<" "<<categoria<<" "<<producto<<" "<<precio<<endl;
                                                                        con++;
                                                                    }
                                                                }
                                                                escribir.close();
                                                                cout<<"El Producto fue eliminado de manera exitosa"<<endl;
                                                            }
                                                        }
                                                        if(encontrado==true)
                                                        {
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            cout<<"Codigo no encontrado vuelva a quitarlo"<<endl;
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 3:
                                                {
                                                    int modificar;
                                                    taman_2=tamano_producto();
                                                    Inv inv[taman_2];
                                                    arreglo_producto(inv,taman_2);
                                                    for(int i=0; i<taman_2; i++)
                                                    {
                                                        cout<<"Codigo:"<<inv[i].codigo<<"  Categoria:"<<inv[i].categoria<<"  Producto:"<<inv[i].producto<<"  Precio:"<<inv[i].precio<<endl;
                                                    }
                                                    while(true)
                                                    {
                                                        bool encontrado=false;
                                                        cout<<"\nEscriba el codigo del elemento que quiere modificar:"; //si piden modificar se le muestran al administrador los datos ya existentes
                                                        cin>>modificar;
                                                        for(int i=0; i<taman_2; i++)
                                                        {
                                                            if(modificar==inv[i].codigo)//se encuentra el codigo y se le pide modificar solo codigo y precio siguiendo condiciones similares al anterior
                                                            {
                                                                encontrado=true;
                                                                while(true)
                                                                {
                                                                    bool permitido=true;
                                                                    cout<<"Ingrese el codigo del producto:"<<endl;
                                                                    cin>>inv[i].codigo;
                                                                    cout<<"Ingrese el precio del producto:"<<endl;
                                                                    cin>>inv[i].precio;
                                                                    for(int l=0; i<taman_2; i++)
                                                                    {
                                                                        if((inv[l].codigo==inv[i].codigo)&&(i!=l))
                                                                        {
                                                                            permitido=false;
                                                                            cout<<"El codigo ya existe porfavor cambielo"<<endl;
                                                                            break;
                                                                        }
                                                                        if((inv[i].precio<50))
                                                                        {
                                                                            permitido=false;
                                                                            cout<<"El precio es muy bajo.porfavor cambielo"<<endl;
                                                                            break;
                                                                        }
                                                                    }
                                                                    if(permitido==true)
                                                                    {
                                                                        break;
                                                                    }
                                                                }
                                                                guardar_producto(inv,taman_2);
                                                            }
                                                        }
                                                        if(encontrado==false)
                                                        {
                                                            cout<<"No se encontro el valor porfavor vuelva a escribirlo"<<endl;
                                                        }
                                                        else
                                                        {
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 4:
                                                {
                                                    continuar_1=false;
                                                    break;
                                                }
                                                }
                                            }
                                            break;
                                        }
                                        case 5:
                                        {
                                            int codigo;
                                            int taman_3=tamano_ventas();
                                            Ventas ventas[taman_3];
                                            arreglo_ventas(ventas,taman_3);
                                            for(int i=0; i<tamano_3; i++)
                                            {
                                                if(ventas[i].compra=='1')&&(ventas[i].orden=='1')
                                                {
                                                    cout<<"Falta por despachar la compra de codigo "<<ventas[i].factura<<" de un valor de "<<ventas[i].valor<<endl;//se muestran los valores que faltan por despechar
                                                }
                                            }
                                            bool seguir=true;
                                            while(seguir==true)
                                            {
                                                cout<<"Ingrese el codigo de la que quiere aceptar:"<<endl;
                                                cin>>codigo;
                                                for(int i=0;i<tamano_3;i++)
                                                {
                                                    if(ventas[i].factura==codigo)
                                                    {
                                                        seguir=false;
                                                        ventas[i].orden='2';
                                                        guardar_ventas(ventas,taman_3); //se hacen los respectivos cambios que son necesarios
                                                    }
                                                }
                                                if(seguir==false)
                                                {
                                                 break;
                                                }
                                            }

                                        }
                                        break;
                                        }
                                        case 6:
                                        {
                                            cout<<"Cierre de sesion exitoso.Vuelve pronto"<<endl;
                                            continuar=false;
                                            break;
                                        }
                                    }
                                }
                                valido=true;
                                break;
                            }
                            else
                            {
                                con++;
                                cout<<"Contrasena incorrecta le quedan "<<3-con<<" intentos"<<endl;
                                if(con==3)
                                {
                                    Lista lista[taman];
                                    cout<<"Ha llegado al limite de intentos su cuenta pasara a estar bloqueada.Contactese con el administrador para cambiar esto"<<endl;
                                    arreglo_lista(lista,taman);
                                    for(int i=0; i<taman; i++)
                                    {
                                        if(Usuario_n==lista[i].Usuario)
                                        {
                                            lista[i].aceptada=1;
                                            guardar_lista(lista,taman);
                                            system("pause");
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    else if(tipo==2) //esta es la cuenta de usuario de compra
                    {
                        int con=0;
                        while(true)
                        {
                            cout<<"Ingrese su contrasena:"<<endl;
                            cin>>contrasena_n;
                            if(contrasena_n==contrasena)
                            {
                                bool continuar=true;
                                while(continuar==true)
                                {
                                    cout<<"***** Bienvenido "<<Usuario<<" *******"<<endl;
                                    cout<<"(1)Realizar una compra"<<endl;
                                    cout<<"(2)Cancelar compra"<<endl;
                                    cout<<"(3)Valor total compras realizadas"<<endl;
                                    cout<<"(4)Cantidad de productos comprados"<<endl;
                                    cout<<"(5)Salir"<<endl;
                                    cin>>opcion;
                                    switch(opcion)
                                    {
                                    case 1:
                                    {
                                        int acumulado=0;
                                        int codigo,con=0,cantidad; //si se le pide realizar una compra se le da al programa los valores de la lista de productos y la de ventas
                                        int compras[10];//se declara un carrito de 10 espacios uno que sea el codigo y otro la cantidad
                                        bool valido=false;
                                        int taman_2=tamano_producto();
                                        Inv inv[taman_2];
                                        arreglo_producto(inv,taman_2);
                                        int taman_3=tamano_ventas();
                                        Ventas ventas[taman_3+1];
                                        arreglo_ventas(ventas,taman_3);
                                        while(true)
                                        {
                                            for(int i=0; i<taman_2; i++)
                                            {
                                                cout<<"Codigo:"<<inv[i].codigo<<" Producto:"<<inv[i].producto<<" Precio:"<<inv[i].precio<<endl; //se le muestra el catalogo
                                            }
                                            cout<<"Ingrese el codigo del producto que quiere comprar"<<endl;
                                            cin>>codigo;
                                            for(int i=0; i<taman_2; i++)
                                            {
                                                if(codigo==inv[i].codigo)
                                                {
                                                    valido=true;
                                                    cout<<"Cuantos de este producto quiere comprar (el maximo es 100 el minimo es 1)"<<endl;
                                                    cin>>cantidad;
                                                    if(cantidad<0)
                                                    {
                                                        cantidad=1;
                                                    }
                                                    else if(cantidad>100) //se pone la condicion que los objetos no se vayan de los rangos
                                                    {
                                                        cantidad=100;
                                                    }
                                                    for(int l=0; l<10; l=l+2)
                                                    {
                                                        if(codigo==compras[l])
                                                        {
                                                            compras[l+1]=compras[l+1]+cantidad; //si el producto seleccionado ya estaba en el carrito solo se aumentara su cantidad
                                                            if(compras[l+1]>100)
                                                            {
                                                                compras[l+1]=100; //si esta llega a más de 100 se traera de vuelta a 100
                                                            }
                                                            valido=false;
                                                        }
                                                    }
                                                    if(valido==true)
                                                    {
                                                        compras[con]=codigo;
                                                        compras[con+1]=cantidad; //si es un producto nuevo se guardara en este carrito
                                                        con++;
                                                    }
                                                    break;
                                                }
                                            }
                                            cout<<"Quiero terminar la compra(quedan "<<(5-con)<<") para si (Y)"<<endl;
                                            cin>>respuesta;
                                            if((respuesta=='Y')||(con==5)||(respuesta=='y'))
                                            {
                                                if(taman_3==0)
                                                {
                                                    ventas[taman_3].Usuario=Usuario; //se guardan los datos al ser esta la primera se la añade un valor 1 a factura
                                                    ventas[taman_3].factura=1;
                                                    ventas[taman_3].orden='1';
                                                    ventas[taman_3].compra='1';
                                                    for(int i=0; i<10; i=i+2)
                                                    {
                                                        for(int l=0; l<taman_2; l++)
                                                        {
                                                            if(compras[i]==inv[l].codigo)
                                                            {
                                                                acumulado=inv[l].precio*compras[i+1]+acumulado;
                                                            }
                                                        }
                                                    }
                                                    ventas[taman_3].valor=acumulado;
                                                    cout<<"Que tipo de pago desea hacer(solo inicial"<<endl; //se le pregunta que tipo de pago quiere hacer
                                                    cin>>ventas[taman_3].tipo;
                                                    taman_3=taman_3+1;
                                                    guardar_ventas(ventas,taman_3); //se guardan los datos en el archivo

                                                }
                                                else
                                                {
                                                    ventas[taman_3].Usuario=Usuario;
                                                    ventas[taman_3].factura=ventas[taman_3-1].factura+1;
                                                    ventas[taman_3].orden='1';
                                                    ventas[taman_3].compra='1';
                                                    for(int i=0; i<10; i=i+2)
                                                    {
                                                        for(int l=0; l<taman_2; l++)
                                                        {
                                                            if(compras[i]==inv[l].codigo)
                                                            {
                                                                acumulado=inv[l].precio*compras[i+1]+acumulado;
                                                            }
                                                        }
                                                    }
                                                    ventas[taman_3].valor=acumulado;
                                                    cout<<"Que tipo de pago desea hacer"<<endl;
                                                    cin>>ventas[taman_3].tipo;
                                                    taman_3=taman_3+1;
                                                    guardar_ventas(ventas,taman_3);
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        int codigo;
                                        int taman_3=tamano_ventas();
                                        Ventas ventas[taman_3];
                                        arreglo_ventas(ventas,taman_3);
                                        for(int i=0; i<taman_3; i++)
                                        {
                                            if((ventas[i].Usuario==Usuario)&&(ventas[i].orden=='1'))
                                            {
                                                cout<<"Tiene las compra de codigo "<<ventas[i].factura<<" En estado de aceptado."<<endl;
                                            }
                                        }
                                        while(true)
                                        {
                                            bool valido=false;
                                            cout<<"Ingrese el codigo de compra de la que desea cancelar"<<endl;
                                            cin>>codigo;
                                            for(int i=0; i<taman_3; i++)
                                            {
                                                if((ventas[i].Usuario==Usuario)&&(ventas[i].factura==codigo))
                                                {
                                                    valido=true;
                                                    ventas[i].orden=2;
                                                }
                                            }
                                            if(valido==true)
                                            {
                                                cout<<"Su orden fue cancelada"<<endl;
                                                guardar_ventas(ventas,taman_3);
                                                break;
                                            }
                                            else
                                            {
                                                cout<<"Codigo invalido porfavor ingreselo de nuevo"<<endl;
                                            }
                                        }
                                        break;
                                    }
                                    case 3:
                                    {
                                        int acumulado=0;
                                        int taman_3=tamano_ventas();
                                        Ventas ventas[taman_3];
                                        arreglo_ventas(ventas,taman_3);
                                        for(int i=0; i<taman_3; i++)
                                        {
                                            if((ventas[i].Usuario==Usuario)&&(ventas[i].orden=='1')&&(ventas[i].compra=='1')) //se hace un acumulado con los valores que ya estan registrados y no encuentran cancelados
                                            {
                                                acumulado=ventas[i].valor+acumulado;
                                            }
                                        }
                                        cout<<"El valor de las compras activas es de:"<<acumulado<<endl;
                                        break;
                                    }
                                    case 4:
                                    {
                                        break;
                                    }
                                    case 5:
                                    {
                                        continuar=false;
                                        break;
                                    }
                                    }
                                }
                                break;
                            }
                            else
                            {
                                con++;
                                cout<<"Contrasena incorrecta le quedan "<<3-con<<" intentos"<<endl;
                                if(con==3)
                                {
                                    Lista lista[taman];
                                    cout<<"Ha llegado al limite de intentos su cuenta pasara a estar bloqueada.Contactese con el administrador para cambiar esto"<<endl;
                                    arreglo_lista(lista,taman);
                                    for(int i=0; i<taman; i++)
                                    {
                                        if(Usuario_n==lista[i].Usuario)
                                        {
                                            lista[i].aceptada=1;
                                            guardar_lista(lista,taman);
                                            system("pause");
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            leer>>Usuario>>contrasena>>tipo>>aceptada;
        }
        leer.close();
        if(valido==false)
        {
            cout<<"Usuario no encontrado porfavor revise que escribio bien el usuario o crea un Usuario con ese nombre"<<endl;
        }
        break;
        }
    case 2:
        {
            leer.open("Usuarios.txt");
            leer>>Usuario>>contrasena>>tipo>>aceptada;
            cout<<"\nIngrese un usuario:";
            cin>>Usuario_n;
            valido=true;
            while(!leer.eof())
            {
                if(Usuario_n==Usuario)
                {
                    cout<<"Usuario ya existente porfavor vuelva a intentarlo"<<endl;
                    valido=false;
                }
                leer>>Usuario>>contrasena>>tipo>>aceptada;
            }
            leer.close();
            if(valido==false)
            {
                break;
            }
            else
            {
                cout<<"Valor valido"<<endl;
                while(true)
                {
                    cout<<"Ingrese una contrasena:"<<endl;
                    cin>>contrasena_1;
                    cout<<"Vuelva a escribirla:"<<endl;
                    cin>>contrasena_n;
                    if(contrasena_1!=contrasena_n)
                    {
                        cout<<"\nSus contrasenas no son iguales.vuelva a intentarlo"<<endl;
                    }
                    else
                    {
                        break;
                    }
                }
                while(true)
                {
                    cout<<"Que tipo de cuenta desea crear?"<<endl;
                    cout<<"\n(1)Administrador";
                    cout<<"\n(2)Cliente";
                    cout<<"\n(3)Consulta"<<endl;
                    cin>>tipo_n;
                    if((tipo_n<1)||(tipo_n>3))
                    {
                        cout<<"Valor no valido,vuelva a intentarlo"<<endl;
                    }
                    else
                    {
                        system("cls");
                        break;
                    }
                }
                cout<<"Se va a crear un usuario de nombre "<<Usuario_n<<" de contrasena "<<contrasena_n<<" siendo esta una cuenta de tipo "<<tipo_n<<endl;
                system("pause");
                escribir.open("Usuarios.txt",ios::app);
                Usuario=Usuario_n;
                contrasena=contrasena_n;
                tipo=tipo_n;
                aceptada=0;
                escribir<<Usuario<<" "<<contrasena<<" "<<tipo<<" "<<aceptada<<"\n";
                escribir.close();
                cout<<"Usuario creado de forma exitosa pendiente a confirmacion"<<endl;
                break;
            }
        }
    case 3:
        {
            return 0;
            break;
        }
    }
}
}
int tamano_lista()
{
    string Usuario,contrasena;
    int tipo,aceptada;
    ifstream leer;
    int con=0;
    leer.open("Usuarios.txt");
    leer>>Usuario>>contrasena>>tipo>>aceptada;
    while(!leer.eof())
    {
        leer>>Usuario>>contrasena>>tipo>>aceptada;
        con++;
    }
    return con;
    leer.close();
}
void arreglo_lista(Lista lista[],int taman)
{
    string Usuario,contrasena;
    int tipo,aceptada;
    ifstream leer;
    int con=0;
    leer.open("Usuarios.txt");
    leer>>Usuario>>contrasena>>tipo>>aceptada;
    while(!leer.eof())
    {
        lista[con].Usuario=Usuario;
        lista[con].contrasena=contrasena;
        lista[con].tipo=tipo;
        lista[con].aceptada=aceptada;
        con++;
        leer>>Usuario>>contrasena>>tipo>>aceptada;
    }
    leer.close();
}
void guardar_lista(Lista lista[],int taman)
{
    string Usuario,contrasena;
    int tipo,aceptada;
    ofstream escribir;
    int con=0;
    escribir.open("Usuarios.txt",ios::trunc);
    while(con!=taman)
    {
        Usuario=lista[con].Usuario;
        contrasena=lista[con].contrasena;
        tipo=lista[con].tipo;
        aceptada=lista[con].aceptada;
        escribir<<Usuario<<" "<<contrasena<<" "<<tipo<<" "<<aceptada<<endl;
        con++;
    }
    escribir.close();
}
int tamano_producto()
{
    string categoria,producto;
    int codigo,precio;
    ifstream leer;
    int con=0;
    leer.open("Productos.txt");
    leer>>codigo>>categoria>>producto>>precio;
    while(!leer.eof())
    {
        leer>>codigo>>categoria>>producto>>precio;
        con++;
    }
    return con;
    leer.close();
}
void arreglo_producto(Inv inv[],int taman_2)
{
    string categoria,producto;
    int codigo,precio;
    ifstream leer;
    int con=0;
    leer.open("Productos.txt");
    leer>>codigo>>categoria>>producto>>precio;
    while(!leer.eof())
    {
        inv[con].codigo=codigo;
        inv[con].categoria=categoria;
        inv[con].producto=producto;
        inv[con].precio=precio;
        con++;
        leer>>codigo>>categoria>>producto>>precio;
    }
    leer.close();
}
void guardar_producto(Inv inv[],int taman_2)
{
    string categoria,producto;
    int codigo,precio;
    ofstream escribir;
    int con=0;
    escribir.open("Productos.txt",ios::trunc);
    while(con!=taman_2)
    {
        codigo=inv[con].codigo;
        categoria=inv[con].categoria;
        producto=inv[con].producto;
        precio=inv[con].precio;
        escribir<<codigo<<" "<<categoria<<" "<<producto<<" "<<precio<<endl;
        con++;
    }
    escribir.close();
}
int tamano_ventas()
{
    string Usuario;
    char tipo;
    int factura;
    int valor;
    char orden;
    char compra;
    ifstream leer;
    int con=0;
    leer.open("Ventas.txt");
    leer>>Usuario>>tipo>>factura>>valor>>orden>>compra;
    while(!leer.eof())
    {
        leer>>Usuario>>tipo>>factura>>valor>>orden>>compra;
        con++;
    }
    return con;
    leer.close();
}
void arreglo_ventas(Ventas ventas[],int taman_3)
{
    string Usuario;
    char tipo;
    int factura;
    int valor;
    char orden;
    char compra;
    ifstream leer;
    int con=0;
    leer.open("Ventas.txt");
    leer>>Usuario>>tipo>>factura>>valor>>orden>>compra;
    while(!leer.eof())
    {
        ventas[con].Usuario=Usuario;
        ventas[con].tipo=tipo;
        ventas[con].factura=factura;
        ventas[con].valor=valor;
        ventas[con].orden=orden;
        ventas[con].compra=compra;
        con++;
        leer>>Usuario>>tipo>>factura>>valor>>orden>>compra;
    }
    leer.close();
}
void guardar_ventas(Ventas ventas[],int taman_3)
{
    string Usuario;
    char tipo;
    int factura;
    int valor;
    char orden;
    char compra;
    ifstream leer;
    ofstream escribir;
    int con=0;
    escribir.open("Ventas.txt",ios::trunc);
    while(con!=taman_3)
    {
        Usuario=ventas[con].Usuario;
        tipo=ventas[con].tipo;
        factura=ventas[con].factura;
        valor=ventas[con].valor;
        orden=ventas[con].orden;
        compra=ventas[con].compra;
        escribir<<Usuario<<" "<<tipo<<" "<<factura<<" "<<valor<<" "<<orden<<" "<<compra<<endl;
        con++;
    }
    escribir.close();
}
