/*
 Spencer D Cassetta

 Cse 325

 Project 11

*/


#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <bitset>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
using namespace std;

///to prevent rand from generating same number



char buffer[256];
struct sockaddr_in saddr;
int listen_sd;
//split function to split by spaces
//arg::str is the string to split
vector<string> Split(string str)
{

    //returns a vector
    vector<string> res;

    //uses streams to get rid of spaces
    istringstream iss(str);
    for(string s; iss >> s; )
    {
        res.push_back(s);
    }
    return res;
}

///function to get data from client
///\param socket
void Get(int socket){

    ///get filename from the client
    vector<string> args = Split(buffer);
    string file = args[1];

    int fd = open(file.c_str(), 0);

    if(fd < 0)
    {///could not open file
        printf("Error, could not find the requested file");
        close(socket);
        return;
    }

    ///clear the buffer
    bzero(buffer, 256);
    for(int fOpen = 0;;)
    {
        fOpen = read(fd, buffer, 256);
        if(fOpen <= 0)
        { // could not open file
            break;
        }

        int nsend = send( socket, buffer, strlen(buffer), 0 );
        if (nsend < 0)
        {//error sending
            perror( "send" );
            exit( 9 );
        }
    }

    ///close the socket when we are done
    printf( "Server closed fd %d\n\n", socket );

    close(socket);
}

///function to parse interaction between server and client
void ParseClientInfo()
{
    for(;;) {//run until there is a quit or an error

        ///most code borrowed from example21.server.c
        struct sockaddr_in caddr;
        unsigned int clen = sizeof(caddr);

        ///connect to server
        int comm_sd = accept(listen_sd, (struct sockaddr *) &caddr, &clen);
        if (comm_sd < 0) {
            perror("accept");
            exit(5);
        }

        printf("Server connected on fd %d\n\n", comm_sd);

        ///connect to host
        struct hostent *host_info = gethostbyaddr(
                (const char *) &caddr.sin_addr.s_addr,
                sizeof(caddr.sin_addr.s_addr), AF_INET);

        if (host_info == NULL) {///bad host given
            perror("gethostbyaddr");
            exit(6);
        }

        char *host = inet_ntoa(caddr.sin_addr);
        if (host == NULL) {
            perror("inet_ntoa");
            exit(7);
        }

        printf("Server connected to %s (%s)\n\n", host_info->h_name, host);


        bzero(buffer, 256);
        int nrecv = recv(comm_sd, buffer, 256, 0);
        if (nrecv < 0) {
            perror("recv");
            exit(8);
        }
        printf("Server received %d bytes\n", nrecv);

        string bufStr(buffer);

        if (bufStr == "get")
        {///get data from the client
            Get(comm_sd);
        }
        else if (bufStr == "quit") {
            ///quit
            close(comm_sd);
            return;
        }
    }
}

///connects to specified port
void Connect(int port)
{
    ///code from example21.server.c
    listen_sd = socket( AF_INET, SOCK_STREAM, 0 );
    if (listen_sd < 0)
    {//error
        perror( "socket" );
        exit( 2 );
    }

    bzero( &saddr, sizeof(saddr) );
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl( INADDR_ANY );
    saddr.sin_port = htons( (unsigned short) port );

    char temp[1024];
    gethostname(temp, 1023); ///get the name of the host we are connected too
    printf("%s.cse.msu.edu %i \n", temp, port);

    ///bind to the socket
    int bstat = bind( listen_sd, (struct sockaddr *) &saddr, sizeof(saddr) );
    if (bstat < 0)
    {//error
        perror( "bind" );
        exit( 3 );
    }

    int lstat = listen( listen_sd, 5 );
    if (lstat < 0)
    {//error
        perror( "listen" );
        exit( 4 );
    }
    //print that we are listening
    printf( "Server listening on fd %d\n\n", listen_sd );
}

///outputs random value between two numbers
int Random(int num1, int num2)
{
    return (rand()%(num2-num1) + num1);
}
int main()
{
    srand(time(NULL));
    ///get port number from user input
    int port = Random(49152, 65535);

    ///connect to the specified port
    Connect(port);

    ///parse the data sent from the client
    ParseClientInfo();
}