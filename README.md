# C++ HTTP Server

A lightweight HTTP server written from scratch in modern C++.

The goal of this project is to understand how web servers work at a lower level, including TCP sockets, HTTP request parsing, routing, responses, and connection handling.

## Goals

- Build a TCP server using C++ sockets
- Understand the HTTP/1.1 protocol
- Parse HTTP requests manually
- Generate valid HTTP responses
- Implement basic routing
- Serve static files
- Handle multiple client connections
- Learn about networking and systems programming in C++

## Example

Request:

```http
GET /hello HTTP/1.1
Host: localhost:8080
```

The structure may change as the project develops.

## Build

Requirements:

- C++17 or newer
- CMake
- A C++ compiler such as GCC or Clang

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

```bash
./http_server
```

The server will listen on:

```text
http://localhost:8080
```

You can test it using a browser or `curl`:

```bash
curl http://localhost:8080/
```

## What I Want to Learn

This project is primarily educational. Instead of relying on an existing HTTP server library, the core networking and HTTP logic will be implemented manually.

Topics explored include:

- TCP/IP networking
- Berkeley sockets
- HTTP/1.1
- Buffers
- Request parsing
- C++ memory management
- RAII
- Error handling
- Concurrency
- Basic server architecture

🚧 **Work in progress**

The project is being built incrementally while learning C++ networking and HTTP internals.

This is intentionally a v0. It handles one request at a time, reads a small request buffer, supports IPv4 only, and does not serve files, parse request bodies, or use HTTPS.
