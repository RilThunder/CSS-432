/**
 * @author Thuan Tran
 * @date April 21st, 2018
 * A server that can accept and return get request
 */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
const string THREAD_MESSAGE = "Creating new thread with count: ";
const int CONNECTION_REQUEST_SIZE = 10;
const string OK_RESPONSE = "HTTP/1.1 200 OK\r\n";
const string DOES_NOT_EXIST_RESPONSE = "HTTP/1.1 404 Not Found\r\n";
const string UNAUTHORIZED_RESPONSE = "HTTP/1.1 401 Unauthorized\r\n";
const string FORBIDDEN_RESPONSE = "HTTP/1.1 403 Forbidden OK\r\n";
const string BAD_REQUEST_RESPONSE = "HTTP/1.1 400 Bad Request\r\n";

struct thread_data
{
    int thread_id;
    int clientFileDescriptor;
};
/**
 *
 * @param socketFileDescriptor
 * @return
 */
string parseHeaderInfo(int socketFileDescriptor)
{
    string responseHeader = "";
    char lastChar = 0;
    while ( true )
    {
        char currentChar = 0;
        recv(socketFileDescriptor , &currentChar , 1 , 0);
        if ( currentChar == '\n' || currentChar == '\r' )
        {
            if ( lastChar == '\r' && currentChar == '\n' ) // For each header, it is ended with a \r\n
                break;
        }
        else responseHeader += currentChar;
        lastChar = currentChar;
    }
    return responseHeader;
}
/**
 * This method is used to process the GET Request from client
 * @param threadData that data that the thread is gonna use (client file descriptor and id)
 * @return
 */
void *processGETRequest(void *threadData) {
    struct thread_data *data;
    data = (struct thread_data *) threadData;
    string filePath="";
    bool isGET = true;
    while (true)
    {
        // Read a newline-terminated string:
        string header =parseHeaderInfo(data->clientFileDescriptor);
        if (header =="") break;

        std::cout<<"	Header: "<< header<<"\n";
        if (header.substr(0,3) == "GET") {
            filePath=header.substr(4);
            cout<<"GOT URL!  "<< filePath <<"\n";
        }
        else
        {   isGET = false;
            cout << "Only support GET request";
            break;
        }

    }

    /* Send the client back a web page. */
    if (isGET)
    {
        int fileDescriptor;
        fileDescriptor = open(filePath, O_RDONLY );
        string content = "";
        fstream fileStream;
        fileStream.open(filePath,fstream::out);
        if (fileStream.fail()) {

        }
        fileStream >> content;
        string page_length = to_string(content.size());

        string response =
                "HTTP/1.1 200 OK\r\n"  // status code, e.g., 404 not found
                "Content-Length: " + page_length + "\r\n" // bytes in message
                                                   "Content-Type: text/plain\r\n" // MIME type
                                                   "\r\n" // blank line == end of HTTP request
                + content;

        send(data->clientFileDescriptor , &response[ 0 ] , response.size() , 0);
    }
    close(data->clientFileDescriptor);

}


/**
 *
 * @param argumentNumber
 * @param argumentValues
 * @return
 */
int main(int argumentNumber, char *argumentValues[]) {
    if (argumentNumber != 1) {
        cout << "Invalid number of argument. The program does not accept any argument at all";
        return -1;
    }
    struct addrinfo hints; // define how the server will be configure
    struct addrinfo *serverInfo; // used to store all the connections that the server can use
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPv4 or v6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int addressInfoStatus = getaddrinfo(nullptr , to_string(8080).c_str() , &hints , &serverInfo);
    if ( addressInfoStatus != 0 )
    {
        cout << "Unable to connect";
        cout << gai_strerror(addressInfoStatus); // print out error message
        return -1;
    }
    int socketFileDescriptor;
    int serverBindResult;
    struct addrinfo *possibleConnection;
    // go through all possible connection server can use. Use the first one that is appropriate
    for ( possibleConnection = serverInfo;
          possibleConnection != nullptr; possibleConnection = possibleConnection->ai_next )
    {
        socketFileDescriptor = socket(possibleConnection->ai_family , possibleConnection->ai_socktype ,
                                      possibleConnection->ai_protocol);
        if ( socketFileDescriptor == -1 )
        {
            cout << "Invalid one socket file descriptor detected. Looking for next one";
            continue;
        }
        serverBindResult = bind(socketFileDescriptor , possibleConnection->ai_addr , possibleConnection->ai_addrlen);
        if ( serverBindResult == -1 )
        {
            cout << "Unable to bind to the socket using this file descriptior";
            close(socketFileDescriptor);
            continue;
        }
        break; // at this point, have successfully bind to a socket
    }
    if ( possibleConnection == NULL )
    {
        cout << "Unable to connect or empty result was given";
        return -1;
    }
    freeaddrinfo(serverInfo);
    int optionValue = 1;
    setsockopt(socketFileDescriptor,SOL_SOCKET,SO_REUSEADDR, &optionValue, sizeof(optionValue)  );
    int listenUsingSocketResult = listen(socketFileDescriptor , CONNECTION_REQUEST_SIZE);
    if ( listenUsingSocketResult != 0 )
    {
        cout << "Unable to listen using the socket file descriptor";
        return -1;
    }
    int count = 1;
    // Keep looping and listening to possible connection
    while ( true )
    {
        struct sockaddr_storage clientSocket;
        socklen_t clientSocketSize = sizeof(clientSocket);
        int clientFileDescriptor = accept(socketFileDescriptor , (struct sockaddr *) &clientSocket , &clientSocketSize);
        if ( clientFileDescriptor == -1 )
        {
            cout << "Unable to connect to client. Trying again";
            continue;
        }
        pthread_t new_thread;
        struct thread_data data;
        data.thread_id = count;
        data.clientFileDescriptor = clientFileDescriptor;
        cout << THREAD_MESSAGE + to_string(count) << endl;
        // Spawn a thread to do the work
        int threadResult = pthread_create(&new_thread , nullptr , processGETRequest , (void *) &data);
        if ( threadResult != 0 )
        {
            cout << "Unable to create thread. Trying again";
            continue;
        }
        count++;
    }

}