#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include <string>

#include "html.hpp"

namespace {
constexpr int kPort = 8080;
volatile std::sig_atomic_t keep_running = 1;

/// Stops the server when a shutdown signal is received.
void stop_server(int) {
     keep_running = 0;
}

/// Installs signal handlers for graceful shutdown.
void install_shutdown_handlers() {
    struct sigaction action {};
    action.sa_handler = stop_server;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;  // Interrupt accept() when Ctrl+C is pressed.
    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGTERM, &action, nullptr);
}

/// Builds a complete HTTP response from a status, headers, and response body.
/// The content type defaults to HTML, but routes can provide another type such as JSON.
std::string response(const int status,
                     const std::string& reason,
                     const std::string& body,
                     const std::string& content_type = "text/html; charset=utf-8") {
    std::ostringstream out;

    out << "HTTP/1.1 " << status << ' ' << reason << "\r\n";
    out << "Content-Type: " << content_type << "\r\n";
    out << "Content-Length: " << body.size() << "\r\n";
    out << "Connection: close\r\n";
    out << "X-Content-Type-Options: nosniff\r\n\r\n";
    return out.str() + body;
}

/// Sends every byte in data through the socket.
/// Returns true when the full response was sent, or false if sending fails.
bool send_all(const int socket_fd, const std::string& data) {
    std::size_t bytes_sent = 0;

    while (bytes_sent < data.size()) {
        const auto bytes = send(
            socket_fd,
            data.data() + bytes_sent,
            data.size() - bytes_sent,
            0
        );

        if (bytes <= 0) {
            return false;
        }

        bytes_sent += static_cast<std::size_t>(bytes);
    }

    return true;
}

/// Handles one client connection from start to finish.
///
/// Reads the incoming HTTP request, validates its method and path, creates the
/// appropriate HTTP response, sends it back to the client, and logs the result.
/// This v0 server supports GET and HEAD requests for the "/" route only.

void handle_client(int client_fd, const sockaddr_in& client_address) {
    char buffer[4096];
    const auto bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0)
        return;

    buffer[bytes] = '\0';

    std::istringstream request(buffer);
    std::string method, target, version;
    request >> method >> target >> version;

    int status = 200;
    std::string reason = "OK";
    std::string body;
    const std::string content_type = "text/html; charset=utf-8";

    if (method.empty() || target.empty() || version.rfind("HTTP/", 0) != 0) {
        status = 400;
        reason = "Bad Request";
        body = html::page("Bad request", "Send a valid HTTP request.");
    }

    else if (method != "GET" && method != "HEAD") {
        status = 405;
        reason = "Method Not Allowed";
        body = html::page("Method not allowed", "This server accepts GET and HEAD requests.");
    }

    else if (target == "/") {
        body = html::page("It worked!", "Your server is running.");
    }

    else {
        status = 404;
        reason = "Not Found";
        body = html::page("Not found", "The route you requested does not exist.");
    }

    std::string full_response = response(status, reason, body, content_type);
    if (method == "HEAD") {
        full_response.resize(full_response.size() - body.size());
    }
    send_all(client_fd, full_response);

    char address[INET_ADDRSTRLEN]{};
    inet_ntop(AF_INET, &client_address.sin_addr, address, sizeof(address));
    std::cout << address << " \"" << method << ' ' << target << "\" " << status << '\n';
}
}  // namespace

/// Starts the server, accepts clients until Ctrl+C, then closes the socket.
int main() {
    install_shutdown_handlers();

    const int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd < 0) {
        std::cerr << "Could not create socket: " << std::strerror(errno) << '\n';
        return 1;
    }

    int enable = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(kPort);

    if (bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        std::cerr << "Could not bind to port " << kPort << ": " << std::strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 16) < 0) {
        std::cerr << "Could not listen for connections: " << std::strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    std::cout << "Server ready at http://127.0.0.1:" << kPort << " (Ctrl+C to stop)\n";
    while (keep_running) {
        sockaddr_in client_address{};
        socklen_t client_length = sizeof(client_address);

        const int client_fd = accept(server_fd,
            reinterpret_cast<sockaddr*>(&client_address),
            &client_length
            );

        if (client_fd < 0) {
            if (errno == EINTR)
                continue;

            std::cerr << "Could not accept connection: " << std::strerror(errno) << '\n';
            break;
        }
        handle_client(client_fd, client_address);
        close(client_fd);
    }
    close(server_fd);
    std::cout << "Server stopped.\n";
    return 0;
}
