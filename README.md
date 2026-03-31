# TCP Port 1080 Listener

[![Build and Verify](https://github.com/<OWNER>/<REPOSITORY>/actions/workflows/build.yml/badge.svg)](https://github.com/<OWNER>/<REPOSITORY>/actions/workflows/build.yml)

A simple Linux C program that listens on port 1080 and prints incoming data to the console.

## Quick Install (Linux)

To install the latest pre-compiled binary directly to your system:
```bash
curl -fsSL https://raw.githubusercontent.com/bahramiem/test-project/refs/heads/main/install.sh | sudo bash
```


## Features
- Listens on TCP port 1080.
- Prints client connection and disconnection status.
- Directly prints raw data to the standard output.
- Graceful shutdown with `Ctrl+C`.

## Building
Run `make` to compile the project:
```bash
make
```

## Running
Run the compiled executable:
```bash
./port_listener
```

## Testing
You can test the server from another terminal using `nc` (Netcat):
```bash
echo "Hello from the other side!" | nc localhost 1080
```

## Prerequisites
- Linux or a POSIX-compatible system (WSL, MacOS, etc.).
- `gcc` compiler.
- `make` build tool.
