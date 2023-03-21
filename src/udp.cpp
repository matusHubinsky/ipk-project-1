/**
 * @file udp.cpp
 * @author Matus Hubinsky
 * @brief communication via udp
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/udp.h"
#include "../inc/main.h"

#define UDP_BUFFER_SIZE 512
char udp_buffer[UDP_BUFFER_SIZE];
std::string str;
//TODO: thow exeptions
//TODO: comments
//TODO: time out
//TODO: set IP to localhost in case of locahost name........

int client_socket;


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
static void udp_setup_adress(struct sockaddr_in *server_address, char server_ip[], int port_number) { 
    struct in_addr adress;
    inet_aton(server_ip, &adress);
    memset(server_address,0, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port_number);
    server_address->sin_addr = adress;
    // printf("INFO: Server socket: %s : %d \n", inet_ntoa(server_address->sin_addr), ntohs(server_address->sin_port));}
}

/**
 * @brief create socket with parameters AF_INET and SOCK_DGRAM for UDP
 *
 * @return none
 */
static void udp_create_socket() {
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket <= 0) {
        perror("<errror> UDP: socket\n");
        exit(1);
    }
    // fprintf(stderr, "UDP: socket created!\n");
}


/**
 * @brief send message to server
 *
 * Save the message from the user. Set first character of the message to server 
 * to 0 and next byte to user message length
 *
 * @param server_address IP adress of sderver in struct sockaddr_in
 * @param serverlen sizeof() server_adress but in socklen_t datatype
 * @return int 0 if success
 */
static void udp_send_message(struct sockaddr_in *server_address, socklen_t serverlen, bool resend) {
    if (!resend) {
        std::getline(std::cin, str);
        char code = 0;
        char length = str.length();
        str.insert(0, 1, code);
        str.insert(1, 1, length);
    }

    int result = sendto(client_socket, str.c_str(), str.length(), 0, (struct sockaddr *) server_address, serverlen);
    if (result < 0) {
        perror("<errror> UDP: sendto");
    }
    // fprintf(stderr, "UDP: message sent!\n");
}


/**
 * @brief recieve data from server, print message data part to stdou and return st_code from the message
 *
 * @param server_address IP adress of sderver in struct sockaddr_in
 * @param serverlen sizeof() server_adress but in socklen_t datatype
 * @return st_code from the message
 */
static int udp_recieve_data(struct sockaddr_in *server_address, socklen_t serverlen) {
    memset(udp_buffer, 1, UDP_BUFFER_SIZE);
    struct pollfd pfd = {.fd = client_socket, .events = POLLIN};

    int res = poll(&pfd, 1, 2000);
    if (res == 0) {
        // timeout message needs to be resend
        udp_send_message(server_address, serverlen, true);
    } 
    else if (res == -1) {
        perror("<errror> UDP: recvfrom");
    } 
    else {
        // message can be recieved
        recvfrom(client_socket, udp_buffer, UDP_BUFFER_SIZE, 0, (struct sockaddr *) server_address, &serverlen);
    }
    int st_code = udp_buffer[1];
    int payload = udp_buffer[2];

    if (st_code == 0) {
        printf("OK:");
    } else {
        printf("ERR:");
    }
    
    for (int i = 0; i < payload; i++) {
        printf("%c", udp_buffer[i + 3]);
    }
    printf("\n");

    return st_code;
}


/**
 * @brief UDP communication
 *
 * At first, setup adress and port of the server. Then create socket and send message from user (stdin).
 * Wait 1 second for reply. If st_code of reply is 1 (OK) request another message from user 
 *
 * @param server_hostname name of the server
 * @param port_number port number of the server
 * @return int 0 if success
 */
extern int udp(char server_ip[], int port_number) {
    struct sockaddr_in server_address;
    udp_setup_adress(&server_address, server_ip, port_number);
    udp_create_socket();

    do {
        udp_send_message(&server_address, sizeof(server_address), false);
    } while (udp_recieve_data(&server_address, sizeof(server_address)) != 1);

    return 0;
}

/* End of file udp.cpp */