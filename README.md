# TCP Echo Server

A basic multithreaded TCP echo server written in C. For each client connection, the server spawns a new thread to handle the client's request. The server reads lines from the client and sends back a response in the format: "You wrote {client message}".

## Building and Running

### Prerequisites

- GCC or another C compiler

### Building

1. Clone the repository:

```bash
git clone https://github.com/bidlako/psi_01.git
cd psi_01
```

2. Build the project using Make:

```bash
make
```

This command will create a `build` directory and place all build artifacts (object files and executable) in it.

### Running

You can run the server in two ways:

1. Directly execute the server binary with the desired port:

   ```bash
   ./build/psi_01 <port>
   ```

   Replace `<port>` with the desired port number, e.g., `8080`.

2. Alternatively, use the Makefile's `run` target to start the server:

   ```bash
   make run PORT="<port>"
   ```

   This command also runs the executable located in the `build` directory.

### Cleaning the Build

To clean up the build artifacts, simply run:

```bash
make clean
```

This command will remove the `build` directory and all its contents.