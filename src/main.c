#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_NUM_EVENTS 16

#define DEFAULT_PORT 5000

int main(int argc, char **argv) {
    int opt;
    int port;
    int num_events;

    while ((opt = getopt(argc, argv, "n:p:")) != -1) {
      switch (opt) {
      case 'n': num_events = atoi(optarg); break;
      case 'p': port = atoi(optarg); break;
      default:
	fprintf(stderr, "Usage: %s [-n NUM_EVENTS] [-p PORT]\n", argv[0]);
	exit(EXIT_FAILURE);
      }
    }

   port = port >= 1024 && port <= 49151 ? port : DEFAULT_PORT;
   num_events = num_events > 0 ? num_events : DEFAULT_NUM_EVENTS;

   int listening_socket;
   int socket_option_value = 1;
   struct sockaddr_in sin;

   // socket(2):
   // https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/socket.2.html
   listening_socket = socket(AF_INET, SOCK_STREAM, 0);

   // setsockopt(2):
   // https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/setsockopt.2.html
   if (setsockopt(
	 listening_socket,
	 SOL_SOCKET,
	 SO_REUSEADDR,
	 &socket_option_value,
	 sizeof(socket_option_value)
	 ) == -1 ) {
     perror("setsockopt");
     exit(1);
   }

   sin.sin_family = AF_INET;
   sin.sin_port = htons(port);
   sin.sin_addr.s_addr = htonl(INADDR_ANY);

   // bind(2):
   // https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/bind.2.html
   if (bind(
	 listening_socket,
	 (struct sockaddr *)&sin,
	 sizeof(sin)
	 ) == -1) {
     perror("bind");
     exit(1);
   }

   // listen(2):
   // https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/listen.2.html
   if (listen(
	 listening_socket,
	 SOMAXCONN
	 ) == -1) {
     perror("listen");
     exit(1);
   }
}
