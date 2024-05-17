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
#include <unistd.h>

#define DEFAULT_NUM_EVENTS 16

#define PORT 5000

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

   port = port >= 1024 && port <= 49151 ? port : PORT;
   num_events = num_events > 0 ? num_events : DEFAULT_NUM_EVENTS;
}
