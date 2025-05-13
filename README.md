# LinuxShells

**LinuxShells** is a collection of minimalist Linux shell implementations written in C. This project serves as an educational resource, demonstrating the core functionalities of Unix-like shells. Each shell variant—`femtoshell`, `nanoshell`, `picoshell`, and `simpleshell`—offers incremental features, providing insights into shell design and system programming concepts.

## Features

* **femtoshell.c**:

* **nanoshell.c**:

* **picoshell.c**:

* **simpleshell.c**:



### Usage

After compilation, run the shell executable:

```bash
./simpleshell
```

Once inside the shell, you can execute commands as you would in a standard Unix shell. For example:

```bash
ls -l
```

To exit the shell, use:

```bash
exit
```

## Examples

* **Executing a Command**:

  ```bash
  $ ./simpleshell
  > echo "Hello, World!"
  Hello, World!
  > exit
  ```

* **Input/Output Redirection**:

  ```bash
  > ls > files.txt
  > cat < files.txt
  ```

* **Piping Commands**:

  ```bash
  > ls -l | grep ".c"
  ```

