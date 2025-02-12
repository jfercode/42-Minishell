# 42-Minishell

## Funciones

### 1. Gestión de memoria 🗂️ 

**`malloc(size_t size)`***: Reserva `size` bytes de memoria y devuelve un puntero al bloque reservado.

**`free(void *ptr)`**: Libera el bloque de memoria reservado previamente por `malloc`.

```c
#include <stdlib.h>
#include <stdio.h>

int main() 
{
	char	*buffer;

	buffer = (char *)malloc(20);
	if (!buffer)
		free(buffer);
	return (0);
}
```

### 2. Salida Estándar 🖨️ 
**`write`**(int fd, const void *buf, size_t count): Escribe `count` bytes desde `buf` hacia el descriptor de archivo `fd`.

```sh
#include <unistd.h>

int main() 
{
    write(1, "Hello from write!\n", 18); 
    return 0;
}

```
**`printf(const char *format, ...)`**: Imprime texto formateado en la salida estándar.

```c
#include <stdio.h>

int main() 
{
    printf("Hello world with printf!\n");
    return 0;
}
```



### 4. Manejo de Archivos 🔐
**`access(const char *pathname, int mode)`**: Verifica permisos de acceso a un archivo (lectura, escritura, ejecución).

```sh
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	if (access("file.txt", F_OK) == 0)
		write(STDOUT_FILENO, "file.txt exist\n", 16);
	else
		write (STDERR_FILENO, "Error: Not exist file.txt\n", 37);
	return (0);
}
```
**`open(const char *pathname, int flags)`**: Abre un archivo y devuelve su descriptor.

**`close(int fd)`**: Cierra un descriptor de archivo abierto.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	close(fd);
	write(STDOUT_FILENO, "file.txt is closed\n", 17);
	return (0);
}
```

**`read(int fd, void *buf, size_t count)`**: Lee `count` bytes del descriptor de archivo `fd` en `buf`.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_readed;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	bytes_readed = read(fd, buffer, 1024);
	if (bytes_readed != -1)
		write (STDOUT_FILENO, buffer, bytes_readed);
	else
		write (STDERR_FILENO, "Error: Failed read\n", 20);
	close(fd);
	write(STDOUT_FILENO, "\nfile.txt is closed\n", 18);
	return (0);
}
```
**`unlink(const char *pathname)`**: Elimina un archivo del sistema de archivos.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_readed;

	fd = open("source/file.txt", O_RDONLY);
	if (fd != -1)
		write(STDOUT_FILENO, "file.txt is open\n", 17);
	else
		write (STDERR_FILENO, "Error: Cannot open file.txt\n", 37);
	bytes_readed = read(fd, buffer, 1024);
	if (bytes_readed != -1)
		write (STDOUT_FILENO, buffer, bytes_readed);
	else
		write (STDERR_FILENO, "Error: Failed read\n", 20);
	close(fd);
	write(STDOUT_FILENO, "\nfile.txt is closed\n", 18);
	unlink("source/file.txt");
	write(STDOUT_FILENO, "\nfile.txt is deleted\n", 22);
	return (0);
}
```

### 5. Manejo de Errores ⚠️
**`strerror(int errnum)`**: Devuelve una cadena descriptiva del error asociado con 
`errnum`.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
	int fd;
	
	fd = open("not_found.txt", O_RDONLY);
	if (fd == -1)
		printf("Error: Cannot open file: %s\n", strerror(errno));
	return (0);
}
```
**`perror(const char *s)`**: Imprime un mensaje de error en la salida estándar de errores.

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
	int fd;
	
	fd = open("not_found.txt", O_RDONLY);
	if (fd == -1)
		perror("Error: Cannot open file");
	return (0);
}
```

### 6. Gestión de procesos 👥
**`fork()`**: Crea un nuevo proceso `(hijo)` duplicando el proceso actual.
```c
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	__pid_t pid;

	pid = fork();
	if (pid == 0)
		printf("Children process (PID: %d)\n", getpid());
	else
		printf("Parent process(PID: %d)\n", getpid());
	return (0);
}
```

**`wait(int *status)`**: Espera a que termine un proceso hijo.

**`waitpid(pid_t pid, int *status, int options)`**: Espera de forma selectiva por un proceso hijo específico.

**`wait3(int *status, int options, struct rusage *rusage) / wait4(pid_t pid, int *status, int options, struct rusage *rusage)`**: Variantes de waitpid con información de uso de recursos.

```c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	__pid_t pid;

	pid = fork();
	if (pid == 0)
		printf("Children process (PID: %d)\n", getpid());
	else
	{
		wait(NULL); // Wait for all process to be finished
		waitpid(pid, NULL, 0); // Wait only the pid process
		write(STDOUT_FILENO, "Children process finished.\n", 28);
	}
	return (0);
}
```

**`execve(const char *pathname, char *const argv[], char *const envp[])`**: Reemplaza el proceso actual con uno nuevo.
```sh
#include <unistd.h>
#include <stdio.h>

int	main(void) 
{
	char *args[] = {"/bin/ls", "-l", NULL};
	execve("/bin/ls", args, NULL);
	write(STDERR, "execve failed", 15);
	return (1);
}
```
**`exit(int status)`**: Termina el proceso actual devolviendo status al sistema operativo.
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void) 
{
	while (1)
	{
		write(STDOUT_FILENO, "Exit after this write\n", 23);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
```

### 7. Señales 🚦

**`signal(int signum, void (*handler)(int))`**: Establece un manejador para una señal específica.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int sig)
{
	printf("Signal %d received!\n", sig);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	signal(SIGINT, handler);
	while (1)
		;
	return (0);
}
```

**`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**: Configura el comportamiento detallado para señales.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int sig)
{
	printf("Signal %d received!\n", sig);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	struct	sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror ("Error: falied sigaction");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for signal SIGINT (Ctrl+C)...\n");
	while (1)
		sleep(1);
	return (0);
}

```

**`kill(pid_t pid, int sig)`**: Envía una señal sig a un proceso pid.
```sh
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <signal.h>

int main() 
{
    pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Falied in fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Children process (PID: %d)\n", getpid());
		while (1)
			sleep(1);
	}
	else
	{
		printf("Parent process(PID: %d)\n", getpid());
		sleep(2);
		printf("Parent sendig SIGKILL to children.\n");
		kill(pid, SIGKILL);
		printf("Children process finished\n");
	}
	return (0);
}
```

### 8. Manejo de entrada de usuario 📚

- **`readline(const char *prompt)`**: Lee una línea desde la entrada estándar con una interfaz interactiva (permite edición de línea, historial, etc.).

```c
#include <unistd.h> 
#include <readline/readline.h>

int main(void) 
{
	char	*line;#include <stdio.h>

	line = readline("Input line> ");
	if (!line)
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	free(line);
	return (0);
}
```

- **`add_history(const char *line)`**: Añade la línea leída al historial de comandos.

```c
#include <unistd.h> 
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) 
{
	char	*input

	input = readline("History> ");
	if (input) 
	{
		add_history(input);
		printf("Added to history: %s\n", input);
	}
	else
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	free(line);
	return (0);
}
```

- **`rl_clear_history()`**: Limpia el historial de comandos almacenado en la sesión actual.

```c
#include <unistd.h> 
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) 
{
	char	*input

	input = readline("History> ");
	if (input) 
	{
		add_history(input);
		printf("Added to history: %s\n", input);
	}
	else
	{
		write(stderr, "Error: failed to read the line.\n", 34);
		exit (EXIT_FAILURE);
	}
	rl_clear_history();
	free(line);
	return (0);
}
```

- **`rl_on_new_line()`**: Informa a readline que se ha iniciado una nueva línea.
- **`rl_replace_line(const char *text, int clear_undo)`**: Reemplaza el contenido actual de la línea por `text`.
- **`rl_redisplay()`**: Vuelve a mostrar la línea actual en el terminal.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	input = readline("Input: ");
	if (!input)
	{
		write(STDERR_FILENO, "Error: failed to read the line.\n", 34);
		exit(EXIT_FAILURE);
	}
	if (*line != '\0')
		add_history(input);
	printf("Input readed: %s\nNew input: ", input);
	rl_replace_line(readline(""), 0);
	rl_on_new_line();
	rl_redisplay();
	rl_clear_history();
	free(input);
	return (0);
}
```

### 9. Directorios 📁
- **`getcwd(char *buf, size_t size)`**: Obtiene el directorio de trabajo actual.

```c
#include <unistd.h>
#include <stdio.h>

int main() 
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)))
        printf("Actual directory: %s\n", cwd);
    return 0;
}
```
- **`chdir(const char *path)`**: Cambia el directorio de trabajo actual.
opendir(const char *name): Abre un directorio y devuelve un puntero al mismo.
- **`readdir(DIR *dirp)`**: Lee la siguiente entrada de un directorio abierto.
- **`closedir(DIR *dirp)`**: Cierra un directorio abierto.
```c
#include <unistd.h>
#include <stdio.h>

int main() 
{
    chdir("..");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("New actual directory: %s\n", cwd);
    return 0;
}
```

### 10. Información de Archivos 🗃️
- **`stat(const char *path, struct stat *buf)`**: Obtiene información del archivo.
- **`lstat(const char *path, struct stat *buf)`**: Igual que `stat`, pero sigue enlaces simbólicos.
- **`fstat(int fd, struct stat *buf)`**: Obtiene información del archivo usando su descriptor de archivo.
```c
#include <sys/stat.h>
#include <stdio.h>

int main() 
{
    struct stat info;
    if (stat("File.txt", &info) == 0)
        printf("Size: %ld bytes\n", info.st_size);
    else
        perror("stat");
    return 0;
}
```



### 10. Duplicación de Descriptores de Archivo 🔗
- **`dup(int oldfd)`**: Duplica un descriptor de archivo.
- **`dup2(int oldfd, int newfd)`**: Duplica `oldfd` en `newfd`, cerrando `newfd` si está abierto.
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() 
{
    int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
    dup2(fd, STDOUT_FILENO);
    printf("Text redirected to 'out.txt'\n");
    close(fd);
    return 0;
}
```

### 11. Terminal y TTY 📞
- **`isatty(int fd)`**: Verifica si un descriptor de archivo es un terminal.
- **`ttyname(int fd)`**: Devuelve el nombre del terminal asociado al descriptor `fd`.
- **`ttyslot()`**: Devuelve el número de terminal de la sesión actual.
ioctl(int fd, unsigned long request, ...): Controla dispositivos I/O.

### 12. Variables de Entorno 🌍
- **`getenv(const char *name)`**: Obtiene el valor de una variable de entorno.

### 13. Configuración de la Terminal (termcap/terminfo) 🎛️
- **`tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`**: Configura los atributos de la terminal.
- **`tcgetattr(int fd, struct termios *termios_p)`**: Obtiene los atributos de la terminal.
- **`tgetent(char *bp, const char *name)`**: Inicializa la base de datos de capacidades de la terminal.
- **`tgetflag(char *id)`**, **`tgetnum(char *id)`**, **`tgetstr(char *id, char **area)`**: Obtienen diferentes tipos de capacidades de la terminal.
- **`tgoto(const char *cap, int col, int row)`**: Calcula la secuencia de control para moverse en la terminal.
- **`tputs(const char *str, int affcnt, int (*putc)(int))`**: Imprime cadenas de control en la terminal.