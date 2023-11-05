# TCP Echo Server

A basic multithreaded TCP echo server written in C. For each client connection, the server spawns a new thread to handle
the client's request. The server reads lines from the client and sends back a response in the format: "You wrote {client
message}".

## Building and Running

### Prerequisites

- CMake (minimum version 3.10)
- GCC or another C compiler

### Building

1. Clone the repository:

```bash
git clone https://github.com/bidlako/psi_01.git
cd psi_01
```

2. Create a build directory and navigate to it:

```bash
mkdir build
cd build
```

3. Run CMake to configure the project and make to build:

```bash
cmake ..
make
```

4. You'll find the server binary in the build directory.

### Running

Execute the server binary with the desired port:

```bash
./tcp_echo_server <port>
```

Replace `<port>` with the desired port number, e.g., `8080`.


