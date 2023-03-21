/**
 * @file main.cpp
 * @author Matus Hubinsky
 * @brief main
 */

#include "../inc/main.h"
#include "../inc/udp.h"
#include "../inc/tcp.h"


/**
 * @brief process arguments and choose TCP or UDP depending on user's choice
 *
 * @return 0 if success
 */
int main(int argc, char *argv[]) {
	// detect OS
	if (strcmp(OS, "linux") != 0) {
        fprintf(stderr, "ERROR: Program is NOT supported on this OS!\n");
        exit(1);
	}
        
	// process tokens
	int port = atoi(argv[4]);
	char *host_adress = argv[2];
	char *mode = argv[6];

  	// choose type of communication
  	if (strcmp(mode, "udp") == 0) {
    	udp(host_adress, port);
    }
    else if (strcmp(mode, "tcp") == 0) {
        tcp(host_adress, port);
    }
    else {
        fprintf(stderr, "Wrong protocol type\n");
        return 1;
    }
    return 0;
}

/* End of file main.cpp */