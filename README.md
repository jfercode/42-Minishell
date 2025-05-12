## 42-MINISHELL🚀🖥️📘

Minishell es un proyecto del programa 42 cuyo objetivo es desarrollar un intérprete de comandos básico, similar a Bash, utilizando el lenguaje C.

El proyecto sigue el clásico patrón **REPL** (Read-Eval-Print Loop) y cubre tokenización, análisis sintáctico, comandos integrados, redirecciones de E/S, tuberías y manejo de señales. 🎓📂🧠

Es una excelente herramienta para comprender los fundamentos de sistemas Unix y la ejecución de procesos en C.

---

### Tabla de Contenidos 📑📚🔖

1. [Introducción](#introducción-)

2. [Primeros Pasos](#primeros-pasos-)

3. [Visión General de la Arquitectura](#visión-general-de-la-arquitectura-)

4. [Tokenización y Análisis Sintáctico](#tokenización-y-análisis-sintáctico-)

5. [Árbol de Sintaxis Abstracta (AST)](#árbol-de-sintaxis-abstracta-ast-)

6. [Ejecución](#ejecución-)

7. [Comandos Integrados](#comandos-integrados-)

8. [Características Especiales](#características-especiales-)

9. [Estructura del Proyecto](#estructura-del-proyecto-)

10. [Autores](#autores-)

11. [Licencia](#licencia-)

---

## Introducción 🧾🔍📢

Un shell es una interfaz de línea de comandos que permite a los usuarios interactuar con el sistema operativo escribiendo comandos. 
Este proyecto reimplementa características centrales de **bash** para ilustrar cómo un shell lee la entrada, la analiza y ejecuta comandos, manejando tuberías, redirecciones, variables de entorno y comandos integrados. 🛠️🐚🧩

## Primeros Pasos 🧰💻📗

**Requisitos previos**: Un entorno similar a Unix, GCC o Clang y conocimientos básicos de C. 🐧⚙️📘

```bash
# Limpiar
$ make fclean

# Compilar
$ make

# Ejecutar
$ ./minishell
```

## Visión General de la Arquitectura 🏗️🧱🔧

El shell está estructurado en cinco etapas (REPL): 🎯🔁📜

1. **READ**: Leer una línea de entrada del usuario.
2. **EVAL**: Tokenizar y analizar sintácticamente la entrada en comandos y operadores.
3. **PRINT/EXEC**: Ejecutar los comandos analizados o mostrar errores.
4. **LOOP**: Repetir hasta que el usuario salga.

Internamente, el proyecto utiliza la siguiente organización de carpetas y archivos: 🗂️📂🧩

* `include/`: Contiene archivos de cabecera, como `minishell.h`.
* `source/`: Código fuente dividido en submódulos:

  * `builtin/`: Implementación de comandos integrados.
  * `execution/`: Gestión de la ejecución de procesos y `execve()`.
  * `main.c`: Función principal y bucle REPL.
  * `main_utils.c`: Funciones auxiliares para `main.c`.
  * `parsing/`: Análisis sintáctico y construccion de una matriz que servirá para la construcción del AST.
  * `tokenization/`: Construcción dada la matriz anteriormente mencionada de la estructura AST.
  * `envp/`: Gestión de variables de entorno.
  * `libft/`: Funciones reutilizables de apoyo.
  * `signals/`: Manejo de señales (CTRL-C, CTRL-D, etc.).

## Tokenización y Análisis Sintáctico ✂️📖🔡

1. **Línea → Palabras**: La línea de entrada se divide en un arreglo de palabras, contando espacios y manejando cadenas entre comillas. 🧮📝🔠
2. **Análisis**:

   * **Comandos** (p.ej., `ls`, `grep`): el primer token es el programa y los siguientes son los argumentos.
   * **Ejecutables del directorio actual**: comandos que comienzan con `./`.
   * **Caracteres especiales**:

     * Comillas: simples (`'`) y dobles (`"`), con las dobles permitiendo expansión de `$`.
     * Redirecciones: `<`, `>`, `>>`, `<<` (heredoc).
     * Tuberías: `|`.
     * Variables de entorno: `$VAR` y `$?` para el estado de salida.

## Árbol de Sintaxis Abstracta (AST) 🌳🔗📂

Representamos comandos y operadores en una estructura de árbol. Los nodos pueden ser: 🧩📊📐

* **Tubería/Pipes**: `|`
* **Redirecciones**: `<`, `>`, `>>`, `<<`
* **Comando**: externo o integrado con argumentos
* **Archivo/Argumento**: destinos para redirecciones o argumentos

```text
[ROOT]
 ├─ [Pipe |]
 ├─ [Redirections < > >> <<]
 ├─ [Cmd]
 └─ [File/Arg]
```

Un ejemplo sencillo sería:

```c
ls -l | grep ".c" > file.txt
```

```text
[ROOT]
 └─ [PIPE]
     ├─ [CMD] ls -l
     └─ [REDIRECCION] > file.txt
        └─ [CMD] grep ".c"
```

## Ejecución ⚙️🚀📈

* **Comandos**: Para cada comando (integrado o externo), se crea un proceso hijo utilizando fork().

    *   Si el comando es externo, el hijo reemplaza su contexto de ejecución usando **execve()**.
    *   Si es un comando integrado (builtin) y no forma parte de una tubería, puede ejecutarse directamente en el proceso padre para evitar problemas con el estado del shell (por ejemplo, cd, exit).
    
    La salida del comando se controla con el código de retorno, recuperado mediante **wait()** o **waitpid()**.

* **Redirecciones**: Se utilizan las llamadas al sistema **open()**, **dup2()** y **close()** para redirigir adecuadamente la entrada/salida estándar del proceso antes de ejecutar el comando:

    * **Redirección de entrada (<)**: redirige stdin desde un archivo especificado.
    * **Redirección de salida (>)**: redirige stdout a un archivo, truncando su contenido si ya existe, o creándolo si no.
    * **Redirección heredoc (<<)**: se lee entrada del usuario hasta que se encuentra una línea que coincida con un delimitador definido. El contenido se escribe en un archivo temporal, y se redirige stdin a ese archivo.
    * **Redirección de salida en modo append (>>)**: redirige stdout a un archivo en modo append, manteniendo el contenido existente y añadiendo la nueva salida al final.

* **Tuberías(|)**: Se emplea **pipe()** para conectar el stdout de un comando al stdin del siguiente.
Cada comando en una pipeline se ejecuta en un proceso distinto.
Se gestiona cuidadosamente el cierre de los extremos de las tuberías para evitar descriptores colgantes o fugas de recursos.

## Comandos Integrados 📢🧩🛠️

Todos ellos funcionan igual que en bash

* `echo [-n]`: imprime argumentos en stdout.
* `cd [dir]`: cambia el directorio de trabajo actual.
* `pwd`: muestra el directorio actual.
* `export VAR=value`: asigna una variable de entorno.
* `unset VAR`: desasinga una variable de entorno.
* `env`: muestra todas las variables de entorno.
* `exit`: sale del programa.

## Características Especiales 💡🧪🔍

* **Comillas**: comillas simples para texto literal, dobles para permitir expansión de `$`. 🔠📏📌
* **Heredoc** (`<<`): lee hasta una línea delimitadora; no registra en el historial. 📄📥🛑
* **Manejo de errores**: errores de sintaxis, comando no encontrado, fallos en redirecciones. 🚫📛📤

📘 Consulta la documentación técnica completa de funciones en [`docs/FUNCIONES.md`](docs/FUNCIONES.md)

## Estructura del Proyecto 🗂️📐📦

```text
42-MINISHELL
├─ include/
│   └─ minishell.h
├─ source/
│   ├─ builtin/
│   ├─ execution/
│   ├─ main.c
│   ├─ parsing/
│   ├─ tokenization/
│   ├─ envp/
│   ├─ libft/
│   ├─ main_utils.c
│   └─ signals/
└─ Makefile
```

## Autores 🤝💡📬

<div align="center">

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/jfercode">
       <img src="https://github.com/jfercode.png" width="100px" alt="Javier Fernández Correa" />
        <br />
        <sub><b>Javier Fernández Correa</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/pexpalacios">
        <img src="https://github.com/pexpalacios.png" width="100px" alt="Penélope Palacios Alvira" />
        <br />
        <sub><b>Penélope Palacios Alvira</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/ZTerto">
        <img src="https://github.com/ZTerto.png" width="100px" alt="Alberto Jódar Carrasco" />
        <br />
        <sub><b>Alberto Jódar Carrasco</b>
       </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Pabletea">
       <img src="https://github.com/Pabletea.png" width="100px" alt="Pablo Alonso García" />
        <br />
        <sub><b>Pablo Alonso García</b></sub>
      </a>
    </td>
  </tr>
</table>

</div>


## Licencia 📜✅🗝️

Este proyecto está bajo la licencia MIT. ⚖️📄🆓
