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
#include <netdb.h>
#include <fcntl.h>
using namespace std;

char data[256];

///split function
///uses stringstreams to break apart strings based on spaces
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

///tells server to execute get command
void Get(int socket)
{

    ///get all input arguments
    vector<string> args = Split(string(data));

    //incorrect amount of arguments
    if (args.size() != 3)
    {
        printf( "Usage: get <remote-file> <local-file>\n");
        close(socket);
        return;
    }

    ///borrowed from example21.client.c
    int nsend = send( socket, data, strlen(data), 0 );
    if (nsend < 0)
    {
        perror( "send" );
        exit( 5 );
    }

    ///open new file
    int newF = open((args.at(2)).c_str(), O_TRUNC|O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
    if(newF < 0)
    {
        printf("Could not open file");
        return;
    }
    for(;;)
    {///loop until no more arguments to parse
        int nrecv = recv(socket, data, 256, 0);
        bzero(data, 256);
        if(nrecv == 0)
        {
            close(socket);
            break;
        }
        else if(nrecv < 0 )
        {
            perror("recv");
            exit(4);
        }
        else
        {
            write(newF, data, nrecv);
        }
    }
}
void ParseData(char *hostname, int port)
{

    ///clear buffer
    bzero(data, 256);

    ///get data from the host using the system stream
    for(int i=0;; i++) //loop which gets command from user buffer
    {
        cin.getline(data, 256);
        printf(data);
        if(i>0)
        {
            printf("\n");
        }

        int sd = socket( AF_INET, SOCK_STREAM, 0 );
        if (sd < 0)
        {
            perror( "socket" );
            exit( 2 );
        }

        ///borrowed from example21.client.c
        struct hostent * server = gethostbyname( hostname );
        if (server == NULL)
        {
            printf( "Error: no such host %s\n", hostname );
            exit( 3 );
        }

        struct sockaddr_in saddr;

        bzero( &saddr, sizeof(saddr) );
        saddr.sin_family = AF_INET;
        bcopy( server->h_addr, &saddr.sin_addr.s_addr, server->h_length );
        saddr.sin_port = htons( port );
        int stat = connect( sd, (struct sockaddr *) &saddr, sizeof(saddr) );
        if (stat < 0)
        {
            perror( "connect" );
            exit( 4 );
        }

        printf( "\nServer connected on fd %d\n\n", sd );

        string dataStr(data);
        cout << dataStr;
        if(dataStr == "get")
        {///execute get command
            Get(sd); //get function
        }
        else if(dataStr == "quit")
        {///execute quit///
            return; //return so it will run quit function
        }
    }
}
void Quit(char * hostname, int port)
{///borrowed from example21.client.c


    ///connect back to the host
    int sd = socket( AF_INET, SOCK_STREAM, 0 );
    if (sd < 0)
    {
        perror( "socket" );
        exit( 2 );
    }
    struct hostent * server = gethostbyname( hostname );
    if (server == NULL)
    {
        printf( "Error: no such host %s\n", hostname );
        exit( 3 );
    }
    struct sockaddr_in saddr;
    bzero( &saddr, sizeof(saddr) );
    saddr.sin_family = AF_INET;
    bcopy( server->h_addr, &saddr.sin_addr.s_addr, server->h_length );
    saddr.sin_port = htons( port );
    int stat = connect( sd, (struct sockaddr *) &saddr, sizeof(saddr) );
    if (stat < 0)
    {
        perror( "connect" );
        exit( 4 );
    }

    ///tell server to quit
    int nsend = send(sd, "quit", 4, 0);
    if (nsend < 0)
    {
        perror("send");
        exit(5);
    }
    //close the socket
    close(sd);
}
int main( int argc, char **argv )
{
    if (argc != 3)
    {//incorrect args were provided
        printf( "Usage: %s <host> <port>\n", argv[0] );
        exit( 1 );
    }
    ///get the host name
    char *hostname = argv[1];

    /// and the port number
    int port = atoi( argv[2] );

    ///parse the data from the server
    ParseData(hostname, port);
    Quit(hostname, port);
}