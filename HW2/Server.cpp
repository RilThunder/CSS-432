/**
 * @author Thuan Tran
 * @date April 21st, 2018
 * A server that can accept and return get request
 */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fstream>

using namespace std;
const string THREAD_MESSAGE = "Creating new thread with count: ";
const int CONNECTION_REQUEST_SIZE = 10;
const string OK_RESPONSE = "HTTP/1.1 200 OK\r\n";
const string DOES_NOT_EXIST_RESPONSE = "HTTP/1.1 404 Not Found\r\n";
const string UNAUTHORIZED_RESPONSE = "HTTP/1.1 401 Unauthorized\r\n";
const string FORBIDDEN_RESPONSE = "HTTP/1.1 403 Forbidden\r\n";
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
void *processGETRequest(void *threadData)
{
    struct thread_data *data;
    data = (struct thread_data *) threadData;
    string filePath = "";
    bool isGET = false;
    while ( true )
    {
        // Read a newline-terminated string:
        string header = parseHeaderInfo(data->clientFileDescriptor);
        if ( header == "" ) break;

        // split a string into space and get the file nae
        std::cout << "	Header: " << header << "\n";
        if ( header.substr(0 , 3) == "GET" )
        {
            // Number 13 is for for " HTTP/1.1\r\n"
            filePath = header.substr(4,header.length()-13);
            cout << "GOT file!  " << filePath << "\n";
            isGET = true;
            break;
        }


    }
    string statusCode;
    string fileContent = "";
    /* Send the client back a web page. */
    if ( isGET )
    {
        // Trying to access a file that is above the directory the server is running
        if ( filePath.substr(0 , 2) == ".." )
        {
            fileContent = "Does not allow";
            statusCode = FORBIDDEN_RESPONSE;
        }
        else if (filePath.substr(1,filePath.length()) == "SecretFile.html") {
            fileContent = "";
            statusCode = UNAUTHORIZED_RESPONSE;
        }
        else
        {
            // Need to append a . in front to know start to search from current path
            filePath = "." + filePath;

            cout << filePath << endl;
            FILE *file = fopen(filePath.c_str() , "r");
            // Could not open the file because either it doesn't exist to read or do not have permsiion
            if ( file == nullptr )
            {
                cout << "Unable to open the file for reading";
                if ( errno == EACCES )
                {
                    cout << "Does not have sufficient access for the file";
                    fileContent = "No permission";
                    statusCode = UNAUTHORIZED_RESPONSE;
                }
                else
                {
                    fileContent = "Does not exist";
                    statusCode = DOES_NOT_EXIST_RESPONSE;
                }
            }
            else
            {

                while ( !feof(file))
                {
                    string line;
                    char c = fgetc(file);
                    if ( c < 0 )
                    {
                        continue;
                        // Encountered not supported character. Skip that character
                    }
                    if ( c == '\n' )
                    {


                        fileContent += '\n';
                        continue;
                    }
                    else if ( c == '\r' )
                    {
                        fileContent += "\r";
                        continue;
                    }
                    fileContent += c;
                }
                fclose(file);
                statusCode = OK_RESPONSE;
            }
        }
    }
    else
    {
        // Could not recognize the get request
        fileContent = "Bad request";
        statusCode = BAD_REQUEST_RESPONSE;
    }
    string pageLength = to_string(fileContent.size());
    string response =
            statusCode +  // status code, e.g., 404 not found +
                         "Content-Length: " + pageLength + "\r\n" // bytes in message+
                                                           "Content-Type: text/plain\r\n" +// MIME type
                                                           "\r\n" // blank line == end of HTTP request
            + fileContent;
    cout << response;
    send(data->clientFileDescriptor , &response[ 0 ] , response.size() , 0);
    close(data->clientFileDescriptor);
}

/**
 *
 * @param argumentNumber
 * @param argumentValues
 * @return
 */
int main(int argumentNumber , char *argumentValues[])
{
    if ( argumentNumber != 2 ) // Change this to
    {
        cout << "Invalid number of argument. The program does not accept any argument at all";
        return -1;
    }
    struct addrinfo hints; // define how the server will be configure
    struct addrinfo *serverInfo; // used to store all the connections that the server can use
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_INET; // IPv4 or v6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    // CHANGE THIS BACK AFTER TESTING 1646 to 8080
    int addressInfoStatus = getaddrinfo(nullptr , argumentValues[1] , &hints , &serverInfo);
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
        int optionValue = 1;
        setsockopt(socketFileDescriptor , SOL_SOCKET , SO_REUSEADDR , &optionValue , sizeof(optionValue));
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