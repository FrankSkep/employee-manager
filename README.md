# EmpleadosApp

EmpleadosApp es una aplicación de gestión de empleados desarrollada en C++ utilizando el paradigma de orientacion a objetos, y la biblioteca wxWidgets para la interfaz gráfica.

## Archivos Principales

- `EmployeeManager.cpp`: Contiene la clase principal `EmployeeManager` que inicia la aplicación.
- `include/MainFrame.h`: Define la clase `MainFrame` que maneja la interfaz gráfica principal.
- `src/MainFrame.cpp`: Implementa la lógica de la interfaz gráfica y las funcionalidades de gestión de empleados.
- `include/Empleado.h`: Define la clase base abstracta `Empleado` y el enumerado `TipoEmpleado`.
- `src/Empleado.cpp`: Implementa la clase `Empleado`.
- `include/EmpleadoAsalariado.h`: Define la clase `EmpleadoAsalariado` que hereda de `Empleado`.
- `src/EmpleadoAsalariado.cpp`: Implementa la clase `EmpleadoAsalariado`.
- `include/EmpleadoPorComision.h`: Define la clase `EmpleadoPorComision` que hereda de `EmpleadoAsalariado`.
- `src/EmpleadoPorComision.cpp`: Implementa la clase `EmpleadoPorComision`.
- `include/EmpleadoPorHoras.h`: Define la clase `EmpleadoPorHoras` que hereda de `Empleado`.
- `src/EmpleadoPorHoras.cpp`: Implementa la clase `EmpleadoPorHoras`.
- `include/Empresa.h`: Define la clase `Empresa` que maneja una lista de empleados.
- `src/Empresa.cpp`: Implementa la clase `Empresa`.
- `utils.h`: Contiene funciones utilitarias como `convMayus` y `isNumeric`.

## Aspectos Técnicos

### Clases Abstractas

La clase `Empleado` es una clase abstracta que define la interfaz común para todos los tipos de empleados. Esta clase incluye métodos virtuales puros como `calcularSalario` y `getInfo`, que deben ser implementados por las clases derivadas.

### Herencia

El proyecto utiliza herencia para definir diferentes tipos de empleados:

- `EmpleadoAsalariado` hereda de `Empleado`.
- `EmpleadoPorComision` hereda de `EmpleadoAsalariado`.
- `EmpleadoPorHoras` hereda de `Empleado`.

### Polimorfismo

El proyecto hace uso de polimorfismo para manejar diferentes tipos de empleados a través de punteros a la clase base `Empleado`. Esto permite que la aplicación trate a todos los empleados de manera uniforme, independientemente de su tipo específico.

### Interfaz Gráfica

La interfaz gráfica está construida utilizando wxWidgets. La clase `MainFrame` maneja la mayoría de las interacciones del usuario, incluyendo la adición, edición, eliminación y búsqueda de empleados.

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

- **Windows**: Usar la tarea definida en `tasks.json`. Abre la paleta de comandos en Visual Studio Code (`Ctrl+Shift+P`) y ejecuta ./EmployeeManager