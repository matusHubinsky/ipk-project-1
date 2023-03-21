/**
 * @file tcp.cpp
 * @author Matus Hubinsky
 * @brief communication via tcp
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "../inc/tcp.h"
#include "../inc/main.h"

#define TCP_BUFFER_SIZE 1024
#define BYTE 1
char tcp_buffer[TCP_BUFFER_SIZE];

//TODO: thow exeptions
//TODO: limited waiting time for reply

/**
 * @brief gracefully exit the communication with the server, by sending BYE mesasage to the server
 * 
 */
static void gracefully_exit() {
    send(client_socket, "BYE", strlen(tcp_buffer), 0);
    close(client_socket);
    exit(1);
}

/**
 * @brief initialize server adress
 *
 * Set up variable struct sockaddr_in server_address by gethostbyname() function or manually to local 
 * host (127.0.0.1) in case of testing
 *
 * @param server_hostname name of the server
 * @param port_number port number of the server
 * @return none
 */
static void tcp_setup_adress(struct sockaddr_in *server_address, char server_ip[], int port_number) { 
    struct in_addr adress;
    inet_aton(server_ip, &adress);
    memset(server_address,0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port_number);
    server_address->sin_addr = adress;
}

/**
 * @brief create socket with parameters AF_INET SOCK_DGRAM for tcp
 *
 * @return void
 */
static void tcp_create_socket() {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket <= 0) {
        perror("<errror> TCP: socket\n");
        exit(1);
    }
} 


/**
 * @brief send message from the user (stdin) to the server
 *
 * @return void
 */
static void tcp_send_message() {
    memset(tcp_buffer, 0, TCP_BUFFER_SIZE);
    fgets(tcp_buffer, TCP_BUFFER_SIZE, stdin);

    const char *end = "BYE";
    if (strstr(tcp_buffer, end) != NULL) {
        gracefully_exit();
    }

    int bytes_tx = send(client_socket, tcp_buffer, strlen(tcp_buffer), 0);
    if (bytes_tx < 0) {
        perror("<errror> TCP: sendto");
        gracefully_exit();
    }
}


/**
 * @brief conect to socket
 *
 * @param server_address IP adress of sderver in struct sockaddr_in
 * @param serverlen sizeof() server_adress but in socklen_t datatype
 * @return void
 */
static void tcp_connect(struct sockaddr_in server_address, size_t serverlen) {
    if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0) {
		perror("ERROR: connect");
		exit(EXIT_FAILURE);        
    }
}


/**
 * @brief recieve data from server and prints the out to stdout
 *
 * @return void
 */
static int tcp_recieve_data(bool first) {
    int i = 0;
    char message[TCP_BUFFER_SIZE];
    memset(tcp_buffer, 0, TCP_BUFFER_SIZE);
    memset(message, 0, TCP_BUFFER_SIZE);

    do {
        if (recv(client_socket, tcp_buffer, BYTE, 0) < 0) {
            perror("<errror> TCP: recvfrom\n");
        }
        message[i] = *tcp_buffer;
        i++;
    } while (strcmp(tcp_buffer, "\n") != 0);

    fprintf(stdout, "%s", message);

    const char *end = "BYE";
    if (strstr(message, end) != NULL) {
        if (first) {
            gracefully_exit();
        }
        close(client_socket);
        return 1;
    }
    return 0;
}

/**
 * @brief Check if signal is equal to 2 (that means ^C was presed), then gracefully exit
 * 
 */
static void signal_handler(int signal) {
    if (signal == 2) {
        gracefully_exit();
    }
}

/**
 * @brief TCP communication
 * 
 * At first, setup adress and port of the server. Then create socket and send message from user (stdin). 
 * Communication is divaded into three messages: HELLO, SOLVE, BYE
 * HELLO = begining of the communication with the server
 * SOLVE <math problem> = solve the math problem
 * BYE = end of communication with the server
 *
 * @param server_ip IP adress of the server
 * @param port_number port number of the server
 * @return int 0 if success
 */
extern int tcp(char server_ip[], int port_number) {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = signal_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sigIntHandler, NULL);

    struct sockaddr_in server_address;
    tcp_setup_adress(&server_address, server_ip, port_number);
    tcp_create_socket();
    tcp_connect(server_address, sizeof(server_address));
    
    // HELLO message
    tcp_send_message();
    tcp_recieve_data(true);

    // SOLVE message
    do {
        tcp_send_message();
        usleep(1000);
    } while (tcp_recieve_data(false) != 1);


    return 0;
}

/* End of file tcp.cpp */