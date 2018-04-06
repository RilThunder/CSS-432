/**
 * @author Thuan Tran
 * HW1: Intro to network programming
 * This is a server class that will receive the data from the client and count how many time it need to read. Then
 * return the number of read back to the client
 */
using namespace std;

#include <iostream>
#include <sys/socket.h>   // socket, bind, listen, inet_ntoa
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

const int CONNECTION_REQUEST_SIZE = 10;
const int BUFFSIZE = 1500;
const string THREAD_MESSAGE = "Creating new thread with count: ";

int port;
int repetition;

// Used to pass data to the thread
struct thread_data
{
    int thread_id;
    int clientFileDescriptor;
};

/**
 * Used to check for valid input from the command line which take in a port number and number of repetition
 * @param argumentValues the values from the command line
 * @return -1 for failure and 0 for success
 */
int checkValidInput(char *argumentValues[])
{
    // stoi is better than atoi since it will throw exception if it cannot convert
    try
    {
        port = stoi(argumentValues[ 1 ]);
        repetition = stoi(argumentValues[ 2 ]);
    }
    catch ( invalid_argument &exception )
    {
        cout << "Incorrect data was entered. Should enter valid integer only";
        cout << exception.what();
        return -1;
    }
    catch ( out_of_range &exception )
    {
        cout << "Incorrect range of data was entered. Should only entere within the range of integer";
        cout << exception.what();
        return -1;
    }
    if ( port < 1024 || port > 65535 )
    {
        cout << "Invalid port number defined. Need to be between 1024 and 65535";
        return -1;
    }
    if ( repetition < 0 )
    {
        cout << " Invalid number of repetition entered. Should be at least 0 (no repetition)";
        return -1;
    }
    return 0;

}

/**
 * This function is used to read data from a client and calculate the elapsed time it takes to finish that
 * @param threadData the data that the thread is gonna use (client file descriptor and id)
 * @return Nothing
 */
void *benchMark(void *threadData)
{
    char databuf[BUFFSIZE];
    struct thread_data *data;
    data = (struct thread_data *) threadData;
    struct timeval start;
    struct timeval stop;
    int count = 0;
    gettimeofday(&start , nullptr);
    //
    for ( int i = 0; i <= repetition; i++ )
    {
        for ( int numberRead = 0;
              (numberRead += read(data->clientFileDescriptor , databuf , BUFFSIZE - numberRead)) < BUFFSIZE;
              ++count );
    }
    gettimeofday(&stop , nullptr);
    long totalTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    write(data->clientFileDescriptor , &count , sizeof(count));
    cout << "Data-receiving time for thread " + to_string(data->thread_id) + " = " + to_string(totalTime) + " usec"
         << endl;
    cout << "Finish with thread " + to_string(data->thread_id) << endl;
    // finish with this client. close it
    close(data->clientFileDescriptor);
}


/**
 * Main entry point of the program. Take in a port number and the number of repetition
 * @param argumentNumber number of arguments passed in the command line
 * @param argumentValues char array represent the argument at each index
 * @return -1 for failure. Else keep running
 */
int main(int argumentNumber , char *argumentValues[])
{
    // C++ count the name of the program a.out as the first value
    if ( argumentNumber != 3 )
    {
        cout << "Incorrect number of argument entered. Need to enter a port number and also the number of repetition";
        return -1;
    }
    int checkResult = checkValidInput(argumentValues);
    if ( checkResult == -1 )
    {
        cout << "Invalid argument supplied. Please enter argument values";
        return -1;
    }
    struct addrinfo hints; // define how the server will be configure
    struct addrinfo *serverInfo; // used to store all the connections that the server can use
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPv4 or v6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int addressInfoStatus = getaddrinfo(nullptr , argumentValues[ 1 ] , &hints , &serverInfo);
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
        int threadResult = pthread_create(&new_thread , nullptr , benchMark , (void *) &data);
        if ( threadResult != 0 )
        {
            cout << "Unable to create thread. Trying again";
            continue;
        }
        count++;
    }
}

