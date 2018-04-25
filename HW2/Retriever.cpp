/**
 * @author Thuan Tran
 * @date April 20th, 2018
 * A simple retriever that connect to a server to get a file
 */
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <fstream>

using namespace std;

string FILENAME = "content.txt";


char *serverName;
char *fileName;

/**
 * This function is used to parsed the header information of the response
 * @param socketFileDescriptor file descriptor number that connect to the server
 * @return a string that is one line of each header
 * // For example: Content-Length, Etag,..
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
 * Set up the connection to the socket of the server
 * @param argumentValues The values that contain the server name and file name from the command line
 * @return -1 for failure. Other number is the socket number
 */
int setUpSocket(char *const *argumentValues)
{
    struct addrinfo hints; //define what the getaddrinfo going to do. Define IPV4 or v6, what kind of connection,..etc
    struct addrinfo *serverInfo; // getaddrinfo will put the results in here. And we can go though this to get the address
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_INET; // either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    serverName = argumentValues[ 1 ];
    fileName = argumentValues[ 2 ];
    // use default port 80 for http
    // Change this back after testing
    int addrInfoStatus = getaddrinfo(serverName , argumentValues[ 3 ] , &hints , &serverInfo);
    if ( addrInfoStatus != 0 )
    {
        cout << "Unable to connect";
        cout << gai_strerror(addrInfoStatus); // print out error message
        return -1;
    }
    struct addrinfo *possibleConnection;
    int socketFileDescriptor;
    int socketConnectionResult;
    // Go through all connection that was found and connect to the first one
    for ( possibleConnection = serverInfo;
          possibleConnection != NULL; possibleConnection = possibleConnection->ai_next )
    {
        socketFileDescriptor = socket(possibleConnection->ai_family , possibleConnection->ai_socktype ,
                                      possibleConnection->ai_protocol);
        if ( socketFileDescriptor == -1 )
        {
            cout << "Invalid one socket file descriptor detected. Looking for next one";
            continue;
        }
        socketConnectionResult = connect(socketFileDescriptor , possibleConnection->ai_addr ,
                                         possibleConnection->ai_addrlen);
        if ( socketConnectionResult == -1 )
        {
            cout << "Invalid one socket connection result detected. Looking for next one";
            continue;
        }
        cout << "Found a connection. Breaking out" << endl;
        break;
    }
    // If still null, then it means that we went through all possible connections but none satisfied
    if ( possibleConnection == NULL )
    {
        cout << "Unable to connect or empty result was given";
        return -1;
    }
    freeaddrinfo(serverInfo);
    return socketFileDescriptor;
}

/**
 * This method is used to send a get request to the server. Receive its response and write to a text file
 * @param socketFileDescriptor The socket number that is connecting to the server
 * @return -1 for failure and 0 for success
 */
int processGetRequest(int socketFileDescriptor)
{
    string request = string("GET " + string(fileName) + " HTTP/1.1\r\n" +
                            "Host: " + string(serverName) + "\r\n" +
                            "\r\n"); // a get request is ended with a "\r\n\r\n"
    cout << "This request was made : " << endl;
    cout << request << endl;
    int sendResult = send(socketFileDescriptor , request.c_str() , strlen(request.c_str()) , 0);
    if ( sendResult <= 0 )
    {
        cout << "Unable to send the request";
        return -1;
    }
    int length = 0;
    while ( true )
    {
        string responseHeader = parseHeaderInfo(socketFileDescriptor);
        if ( responseHeader == "" ) break; // This can only happen when double \r\n\r\n that represent the end of header
        cout << responseHeader << endl;
        if ( responseHeader.substr(0 , 15) == "Content-Length:" )
        {
            length = atoi(responseHeader.substr(
                    16 , responseHeader.length()).c_str()); // Parse the number of byte that will be in the body of the message
        }
    }
    cout << "printing out the body of the response and writing the content to " + FILENAME << endl;
    ofstream outputFile;
    outputFile.open(FILENAME);
    char buffer[length];
    recv(socketFileDescriptor , &buffer , length , 0);
    for ( int i = 0; i < length; i++ )
    {
        outputFile << buffer[ i ];
    }
    close(socketFileDescriptor);
    outputFile.close();
    return 0;

}

/**
 * Main entry point of the program
 * @param argumentNumber The number of argument. Expected 3
 * @param argumentValues The values from the command line. Server name, file path and port number
 * @return -1 for failure and 0 for success
 */
int main(int argumentNumber , char *argumentValues[])
{
    if ( argumentNumber != 4 )
    {
        cout << "Incorrect number of argument provided. Expected to receive server address and web page ";
    }
    int socketFileDescriptor = setUpSocket(argumentValues);
    if ( socketFileDescriptor == -1 )
    {
        cout << "Unable to create a socket";
        return -1;
    }
    return processGetRequest(socketFileDescriptor);
}
