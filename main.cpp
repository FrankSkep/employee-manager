
// /* Programa de gestion de empleados, usando herencia encadenada, y polimorfismo */

// #include <cstdlib>
// #include <vector>
// #include <memory>
// #include <time.h>

// #include "EmpleadoPorHoras.h"
// #include "EmpleadoAsalariado.h"
// #include "EmpleadoPorComision.h"

// #include "utils.h"

// #define AUTO 10

// // Funciones principales
// int menu();
// int menuEmpleados();
// void agregarEmpleado(vector<shared_ptr<Empleado>> &empleados);
// void listaEmpleados(vector<shared_ptr<Empleado>> &empleados);
// void consultarYmodificar(vector<shared_ptr<Empleado>> &empleados);
// shared_ptr<Empleado> *buscar(vector<shared_ptr<Empleado>> &empleados, int num);
// int leerNumEmpleado();
// void agregarAleatorios(vector<shared_ptr<Empleado>> &empleados);

// int main()
// {
//     srand(time(NULL));
//     vector<shared_ptr<Empleado>> empleados;
//     agregarAleatorios(empleados); // Agrego datos aleatorios de muestra

//     int op;
//     do
//     {
//         system("cls");
//         op = menu();

//         switch (op)
//         {
//         case 1: // Agregar un empleado
//             agregarEmpleado(empleados);
//             continue;

//         case 2: // Mostrar lista de empleados
//             listaEmpleados(empleados);
//             break;

//         case 3: // Buscar un empleado y modificar detalles
//             consultarYmodificar(empleados);
//             break;

//         case 4: // Calcular y mostrar salarios de cada tipo de empleado (Con polimorfismo)
//         {
//             system("cls");
//             cout << "+----------------------- Salarios Empleados --------------------+" << endl;
//             cout << "| No. Empleado |    Nombre    |      Apellidos      |  Salario  |" << endl;
//             cout << "+---------------------------------------------------------------+" << endl;
//             for (const auto emp : empleados)
//             {
//                 cout << left << "| " << setw(13) << emp->getNumEmp() << "|";
//                 cout << left << " " << setw(13) << emp->getNombre() << "|";
//                 cout << left << " " << setw(20) << emp->getApellidos() << "|";
//                 cout << left << " " << setw(10) << fixed << setprecision(2) << emp->calcularSalario() << "|" << endl;
//             }
//             cout << "+---------------------------------------------------------------+" << endl;
//         }
//         break;
//         }

//         if (op != 0)
//         {
//             system("pause");
//         }
//     } while (op != 0);
// }

// int menu()
// {
//     cout << "+-- Menu de operaciones --+" << endl;
//     cout << "1. Agregar empleado" << endl;
//     cout << "2. Ver lista de empleados" << endl;
//     cout << "3. Consultar y modificar datos" << endl;
//     cout << "4. Calcular y mostrar salarios de empleados" << endl;
//     cout << "0. Salir" << endl;
//     return getNum<int>("> Elija una opcion: ");
// }

// int menuEmpleados()
// {
//     cout << "+---- Agregar empleado ----+" << endl;
//     cout << "1. Empleado por hora" << endl;
//     cout << "2. Empleado Asalariado" << endl;
//     cout << "3. Empleado por comision" << endl;
//     cout << "0. Salir" << endl;
//     return getNum<int>("> Elija una opcion: ");
// }

// // Agrega un empleado de cualquier tipo
// void agregarEmpleado(vector<shared_ptr<Empleado>> &empleados)
// {
//     string nombre, apellidos;
//     int numEmp;
//     double salBase;

//     int op;
//     do
//     {
//         system("cls");
//         op = menuEmpleados();
//         cout << endl;

//         switch (op)
//         {
//         case 1: // EMPLEADO POR HORAS
//             cout << "> Ingrese nombre: ";
//             getline(cin, nombre);
//             cout << "> Ingrese apellidos: ";
//             getline(cin, apellidos);
//             cout << "> Ingrese numero de empleado [10000, 90000]: ";
//             numEmp = leerNumEmpleado();

//             {
//                 int horasTrabajadas;
//                 float tarifaHora;

//                 horasTrabajadas = getNum<int>("> Ingrese horas trabajadas: ");
//                 tarifaHora = getNum<double>("> Ingrese tarifa por hora: ");

//                 empleados.push_back(make_shared<EmpleadoPorHoras>(nombre, apellidos, numEmp, 0, horasTrabajadas, tarifaHora));
//             }
//             break;

//         case 2: // EMPLEADO ASALARIADO
//             cout << "> Ingrese nombre: ";
//             getline(cin, nombre);
//             cout << "> Ingrese apellidos: ";
//             getline(cin, apellidos);
//             cout << "> Ingrese numero de empleado [10000, 90000]: ";
//             numEmp = leerNumEmpleado();
//             salBase = getNum<double>("> Ingrese salario anual: ");

//             {
//                 int semanasTrab;

//                 semanasTrab = getNum<int>("> Ingrese semanas trabajadas en el anio: ");

//                 empleados.push_back(make_shared<EmpleadoAsalariado>(nombre, apellidos, numEmp, salBase, semanasTrab));
//             }
//             break;

//         case 3: // EMPLEADO POR COMISION
//             cout << "> Ingrese nombre: ";
//             getline(cin, nombre);
//             cout << "> Ingrese apellidos: ";
//             getline(cin, apellidos);
//             cout << "> Ingrese numero de empleado [10000, 90000]: ";
//             numEmp = leerNumEmpleado();
//             salBase = getNum<double>("> Ingrese salario base: ");

//             {
//                 int semanasTrab;
//                 float porcentaje;
//                 double montoVentas;

//                 semanasTrab = getNum<int>("> Ingrese semanas trabajadas en el anio: ");
//                 montoVentas = getNum<double>("> Ingrese monto de ventas total: ");
//                 porcentaje = getNum<double>("> Ingrese porcentaje de comision: ");

//                 empleados.push_back(make_shared<EmpleadoPorComision>(nombre, apellidos, numEmp, salBase, semanasTrab, montoVentas, porcentaje));
//             }
//             break;

//         case 0:
//             break;

//         default:
//             continue;
//         }

//         if (op != 0)
//         {
//             cout << "\n* Empleado agregado. *" << endl;
//             system("pause");
//         }
//     } while (op != 0);
// }

// // Muestra todos los empleados
// void listaEmpleados(vector<shared_ptr<Empleado>> &empleados)
// {
//     system("cls");
//     cout << "+----------------- Lista de Empleados --------------+" << endl;
//     cout << "| No. Empleado |    Nombre    |      Apellidos      |" << endl;
//     cout << "+---------------------------------------------------+" << endl;
//     for (const auto &emp : empleados)
//     {
//         cout << left << "| " << setw(13) << emp->getNumEmp() << "|";
//         cout << left << " " << setw(13) << emp->getNombre() << "|";
//         cout << left << " " << setw(20) << emp->getApellidos() << "|" << endl;
//     }
//     cout << "+---------------------------------------------------+" << endl;
// }

// // Busca, muestra y permite modificar informacion de un empleado
// void consultarYmodificar(vector<shared_ptr<Empleado>> &empleados)
// {
//     int num;
//     num = getNum<int>("> Ingresa numero de empleado a consultar: ");
//     cout << endl;
//     system("cls");

//     shared_ptr<Empleado> *empleado = buscar(empleados, num);

//     if (empleado == nullptr)
//     {
//         cout << "* Empleado no encontrado. *" << endl;
//         return;
//     }

//     int opcion;
//     do
//     {
//         system("cls");
//         (*empleado)->mostrarInformacion();

//         cout << "\n> Que deseas modificar: " << endl;
//         cout << "1. Nombre" << endl;
//         cout << "2. Apellido" << endl;

//         // Determinar el tipo de empleado y mostrar opciones adaptadas al tipo
//         if (auto empPorHoras = dynamic_cast<EmpleadoPorHoras *>(empleado->get()))
//         {
//             cout << "3. Horas trabajadas" << endl;
//             cout << "4. Tarifa por hora" << endl;
//         }
//         else if (auto empAsalariado = dynamic_cast<EmpleadoAsalariado *>(empleado->get()))
//         {
//             cout << "3. Semanas anuales" << endl;
//         }
//         else if (auto empPorComision = dynamic_cast<EmpleadoPorComision *>(empleado->get()))
//         {
//             cout << "3. Semanas anuales" << endl;
//             cout << "4. Monto total ventas" << endl;
//             cout << "5. Porcentaje comision" << endl;
//         }
//         cout << "0. Salir" << endl;
//         opcion = getNum<int>("> Elije una opcion: ");
//         cout << endl;

//         bool modifico = false;

//         // Realizar la modificación basada en la opción seleccionada
//         switch (opcion)
//         {
//         case 1:
//         {
//             cout << "> Ingrese nuevo nombre: ";
//             string nuevoNombre;
//             getline(cin, nuevoNombre);
//             (*empleado)->setNombre(nuevoNombre);
//             modifico = true;
//         }
//         break;

//         case 2:
//         {
//             cout << "> Ingrese nuevo apellido: ";
//             string nuevoApellido;
//             getline(cin, nuevoApellido);
//             (*empleado)->setApellidos(nuevoApellido);
//             modifico = true;
//         }
//         break;

//         case 3:
//             if (auto empPorHoras = dynamic_cast<EmpleadoPorHoras *>(empleado->get()))
//             {
//                 int horas = getNum<int>("> Ingrese horas trabajadas: ");
//                 empPorHoras->setHoras(horas);
//                 modifico = true;
//             }
//             else if (auto empAsalariado = dynamic_cast<EmpleadoAsalariado *>(empleado->get()))
//             {
//                 int semanas = getNum<int>("> Ingrese semanas anuales: ");
//                 empAsalariado->setSemanas(semanas);
//                 modifico = true;
//             }
//             else if (auto empPorComision = dynamic_cast<EmpleadoPorComision *>(empleado->get()))
//             {
//                 int semanas = getNum<int>("> Ingrese semanas anuales: ");
//                 empPorComision->setSemanas(semanas);
//                 modifico = true;
//             }
//             break;
//         case 4:
//             if (auto empPorHoras = dynamic_cast<EmpleadoPorHoras *>(empleado->get()))
//             {
//                 int tarifa = getNum<int>("> Ingrese tarifa por hora: ");
//                 empPorHoras->setTarifa(tarifa);
//                 modifico = true;
//             }
//             else if (auto empPorComision = dynamic_cast<EmpleadoPorComision *>(empleado->get()))
//             {
//                 int ventas = getNum<int>("> Ingrese nuevo total de ventas: ");
//                 empPorComision->setVentas(ventas);
//                 modifico = true;
//             }
//             break;
//         case 5:
//             if (auto empPorComision = dynamic_cast<EmpleadoPorComision *>(empleado->get()))
//             {
//                 double porcentaje = getNum<double>("Ingrese nuevo porcentaje de comisión: ");
//                 empPorComision->setPorcenComision(porcentaje);
//                 modifico = true;
//             }
//             break;

//         case 0:
//             break;

//         default:
//             break;
//         }
//         if (opcion != 0)
//         {
//             if (modifico)
//             {
//                 cout << "\n* Datos actualizados. *" << endl;
//             }
//             system("pause");
//         }
//     } while (opcion != 0);
// }

// // Busqueda secuencial en un vector de objetos, retorna direccion al objeto
// shared_ptr<Empleado> *buscar(vector<shared_ptr<Empleado>> &empleados, int num)
// {
//     for (auto &emp : empleados)
//     {
//         if (emp->getNumEmp() == num)
//         {
//             return &emp;
//         }
//     }
//     return nullptr;
// }

// int leerNumEmpleado()
// {
//     int num;
//     do
//     {
//         num = getNum<int>("");
//     } while (num < 10000 || num > 90000);
//     return num;
// }

// void agregarAleatorios(vector<shared_ptr<Empleado>> &empleados)
// {
//     const string nombres[] = {"MARIA", "ANA", "LAURA", "LUISA", "SOFIA", "ISABEL", "CARMEN", "ROSA", "ELENA", "LUCIA",
//                               "PATRICIA", "LOURDES", "MARTA", "RAQUEL", "JULIA", "ANDREA", "NATALIA", "CRISTINA", "SARA",
//                               "DANIELA", "PAULA", "CAROLINA", "JULIANA", "DIEGO", "JAVIER", "RICARDO", "ALBERTO", "MARIO"};

//     const string apellidos[] = {"FUENTES", "GARZA", "LOPEZ", "GONZALES", "CEVALLOS", "TRUJILLO",
//                                 "MOLINA", "CARDENAS", "PEREZ", "MORALES", "GARCIA", "ORTEGA", "SILVA", "PACHECO", "CORNEJO",
//                                 "ANDRADE", "DIAZ", "TORRES", "VARGAS", "RUIZ", "SANCHEZ", "ALVAREZ", "RODRIGUEZ"};

//     shared_ptr<Empleado> empleado;

//     for (int i = 0; i < AUTO; i++) // Genero AUTO * 3
//     {
//         // Empleado por horas
//         empleado = make_shared<EmpleadoPorHoras>(nombres[numAleatorio(0, 27)], apellidos[numAleatorio(0, 22)], numAleatorio(10000, 90000), (double)numAleatorio(3000, 15000), numAleatorio(40, 80), (float)numAleatorio(100, 300));
//         empleados.push_back(empleado);

//         // Empleado Asalariado
//         empleado = make_shared<EmpleadoAsalariado>(nombres[numAleatorio(0, 27)], apellidos[numAleatorio(0, 22)], numAleatorio(10000, 90000), (double)numAleatorio(3000, 15000), numAleatorio(20, 52));
//         empleados.push_back(empleado);

//         // Empleado Por Comision
//         empleado = make_shared<EmpleadoPorComision>(nombres[numAleatorio(0, 27)], apellidos[numAleatorio(0, 22)], numAleatorio(10000, 90000), (double)numAleatorio(3000, 15000), numAleatorio(20, 52), (double)numAleatorio(5000, 15000), (double)numAleatorio(1, 99) / 100);
//         empleados.push_back(empleado);
//     }
// }
