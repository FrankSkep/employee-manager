# EmpleadosApp

EmpleadosApp es una aplicación de gestión de empleados desarrollada en C++ utilizando el paradigma de orientación a objetos y la biblioteca wxWidgets para la interfaz gráfica.

## Funcionalidades del Sistema

### Gestión de Empleados

- **Agregar Empleado**: Permite agregar empleados de diferentes tipos (por horas, asalariados, por comisión) ingresando sus datos en un formulario.
- **Editar Empleado**: Permite editar la información de un empleado seleccionado de la lista.
- **Eliminar Empleado**: Permite eliminar un empleado seleccionado de la lista.
- **Ver Detalles del Empleado**: Muestra los detalles completos de un empleado seleccionado en un cuadro de diálogo.
- **Buscar Empleados**: Permite buscar empleados por nombre o apellido utilizando una barra de búsqueda.

### Gestión de la Empresa

- **Actualizar Información de la Empresa**: Permite actualizar el nombre, dirección y teléfono de la empresa.
- **Mostrar Información de la Empresa**: Muestra la información actual de la empresa, incluyendo el nombre, dirección, teléfono, total de empleados y gastos totales.

### Estadísticas

- **Total de Empleados**: Muestra el total de empleados en la empresa.
- **Empleados por Tipo**: Muestra el número de empleados por tipo (por horas, asalariados, por comisión).
- **Gastos Totales**: Calcula y muestra los gastos totales en salarios de todos los empleados.

## Aspectos de POO

### Clases Abstractas

La clase `Empleado` es una clase abstracta que define la interfaz común para todos los tipos de empleados. Esta clase incluye métodos virtuales puros como `CalcularSalario` y `GetInfo`, que deben ser implementados por las clases derivadas.

### Herencia

El proyecto utiliza herencia para definir diferentes tipos de empleados:

- `EmpleadoAsalariado` hereda de `Empleado`.
- `EmpleadoPorComision` hereda de `EmpleadoAsalariado`.
- `EmpleadoPorHoras` hereda de `Empleado`.

### Polimorfismo

El proyecto utiliza polimorfismo para gestionar diferentes tipos de empleados mediante punteros a la clase base `Empleado`. Esto permite que la aplicación trate a todos los empleados de manera uniforme, independientemente de su tipo específico. 

### Interfaz Gráfica

La interfaz gráfica está construida utilizando la libreria orientada a objetos `wxWidgets`. La clase `MainFrame` maneja la mayoría de las interacciones del usuario, incluyendo la adición, edición, eliminación y búsqueda de empleados.

## Configuración del Entorno

### Requisitos

- wxWidgets 3.2.6
- MinGW (para compilación en Windows)

### Configuración de Visual Studio Code

El proyecto incluye configuraciones para Visual Studio Code en el directorio `.vscode`:

- `c_cpp_properties.json`: Configura las rutas de inclusión y el compilador.
- `settings.json`: Configura las asociaciones de archivos.
- `tasks.json`: Define las tareas de compilación.

### Compilación

- **Windows**: Usar la tarea definida en `tasks.json`. Utiliza el atajo `Ctrl+Shift+P` para compilar y ejecuta en tu terminal `./EmployeeManager` para ejecutar.

- **Linux**: Usar el script build.bash para compilar y ejecutar la aplicacion.