#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    struct addrinfo hints = { 0 };
    struct addrinfo *results, *result;
    int error;
    char tmp[128];
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    for(int i = 1 ; i < argc ; i++) {
        printf("Trying to resolve: %s\n", argv[i]);
        error = getaddrinfo(argv[i], NULL, &hints, &results);
        if(error) {
            perror("    getaddrinfo errno");
            printf("    getaddrinfo() return value: %d (%s)\n", error, gai_strerror(error));
            continue;
        }
        for(result = results ; result != NULL ; result = result->ai_next) {
            int af = result->ai_family;
            if(af == AF_INET) {
                struct sockaddr_in* addr = (struct sockaddr_in*) result->ai_addr;
                inet_ntop(af, &addr->sin_addr, tmp, 128);
                printf("    Address: %s\n", tmp);
            } else if(af == AF_INET6) {
                struct sockaddr_in6* addr = (struct sockaddr_in6*) result->ai_addr;
                inet_ntop(af, &addr->sin6_addr, tmp, 128);
                printf("    Address: %s\n", tmp);
            }
        }
        freeaddrinfo(results);
    }
    return 0;
}
