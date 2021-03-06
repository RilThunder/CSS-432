//
// Created by thuan on 30/03/18.
//

#include <iostream>
#include <netdb.h>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

const int TOTAL_SIZE = 1500;
const int MULTIPLE_WRITE = 1;
const int WRITEV = 2;
const int SINGLE_WRITE = 3;

ofstream myfile;
int port;
int repetition;
int numberBuffer;
int bufferSize;
char *serverIPName;
int type;

/**
 * This function is used to check for valid input from the command line arguments
 * Valid port should be between 1024 and 65535
 * Repetition should be at least 0
 * Number Buffer * buffer size should be 1500
 * Only allow 3 type of input
 * @param argumentValues The command line argument parsed from main
 * @return -1 for invalid input and 0 for valid input
 */
int checkValidInput(char *argumentValues[])
{
    // stoi is better than atoi since it will throw exception if it cannot convert
    try
    {
        port = stoi(argumentValues[ 1 ]);
        repetition = stoi(argumentValues[ 2 ]);
        numberBuffer = stoi(argumentValues[ 3 ]);
        bufferSize = stoi(argumentValues[ 4 ]);
        type = stoi(argumentValues[ 6 ]);
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
    serverIPName = argumentValues[ 5 ];
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
    if ( numberBuffer * bufferSize != TOTAL_SIZE )
    {
        cout << "Invalid number of data buffer or data buffer size. When multiply, should be equal " +
                to_string(TOTAL_SIZE);
        return -1;
    }
    if ( string(serverIPName).empty())
    {
        cout << "Empty string detected as server name";
        return -1;
    }
    if ( type < 1 || type > 3 )
    {
        cout << "Invalid transfer scenario. Only accept " + to_string(MULTIPLE_WRITE) + ", " + to_string(WRITEV)
                + " or " + to_string(SINGLE_WRITE);
        return -1;
    }
    return 0;
}

/**
 * This function is used to print out the result for sending data from the client to server and from server back to client
 * It will print out the time it took to send to server (from start until it write to server)
 * It will print out the time it took to receive response back from server (from start until it read back data from server)
 * @param start Starting time that it begin to prepare the data depending on different type
 * @param lap Time that it send the data to the server
 * @param end Time that it receive data back from the server
 * @param numberOfRead The number of read the server receives
 */
void printResult(struct timeval start , struct timeval lap , struct timeval end , int numberOfRead)
{
    // Second to microsecond needs to multiply by 1000000
    long dataSendingTime = (lap.tv_sec - start.tv_sec) * 1000000 + lap.tv_usec - start.tv_usec;
    long roundTripTime = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    // write the data to text file
    myfile << to_string(dataSendingTime) + " " + to_string(roundTripTime) + " " << to_string(numberOfRead) << endl;
    return;
}

/**
 * Main method of the client. Take in input from the command line and make a connection to the server
 * @param argumentNumber The number of arguments that it received
 * @param argumentValues a char array that contains the data at each index
 * @return -1 for failure and 0 for success
 */
int Fakemain(int argumentNumber , char *argumentValues[])
{
    // Expected to receive 6 arguments plus the invocation name of the program which make it 7
    if ( argumentNumber != 7 )
    {
        cout << "Incorrect number of arguments provided";
        return -1;
    }
    int checkResult = checkValidInput(argumentValues);
    if ( checkResult == -1 )
    {
        cout << "Invalid argument supplied. Please enter argument values";
        return -1;
    }
    char databuf[numberBuffer][bufferSize];
    struct addrinfo hints; //define what the getaddrinfo going to do. Define IPV4 or v6, what kind of connection,..etc
    struct addrinfo *serverInfo; // getaddrinfo will put the results in here. And we can go though this to get the address
    memset(&hints , 0 , sizeof(hints));
    hints.ai_family = AF_UNSPEC; // either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;
    int addrInfoStatus = getaddrinfo(serverIPName , argumentValues[ 1 ] , &hints , &serverInfo);
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
    struct timeval start , lap , end;
    // having one repetition mean it will do at least 1 time. repetition = 1 mean it will do first time, then repeat one time
    // having 0 repetition. Means it will not only do one time. But no repeat
    gettimeofday(&start , NULL);
    for ( int i = 0; i <= repetition; i++ )
    {
        if ( type == 1 )
        {
            for ( int j = 0; j < numberBuffer; j++ )
            {
                write(socketFileDescriptor , databuf[ j ] , bufferSize);    // sd: socket descriptor
            }
        }
        if ( type == WRITEV )
        {
            struct iovec vector[numberBuffer];
            for ( int j = 0; j < numberBuffer; j++ )
            {
                vector[ j ].iov_base = databuf[ j ];
                vector[ j ].iov_len = bufferSize;
            }
            writev(socketFileDescriptor , vector , numberBuffer);           // sd: socket descriptor
        }
        if ( type == SINGLE_WRITE )
        {
            write(socketFileDescriptor , databuf , numberBuffer * bufferSize); // sd: socket descriptor
        }
    }
    gettimeofday(&lap , nullptr);
    int numberOfRead;
    read(socketFileDescriptor , &numberOfRead , sizeof(numberOfRead));
    gettimeofday(&end , nullptr);
    printResult(start , lap , end , numberOfRead);
    return 0;
}

/**
 * Take in port number and server ip name
 * @param argumentNumber
 * @param argumentValues
 * @return
 */
int main(int argumentNumber , char *argumentValues[])
{
    argumentNumber = 7;
    char *data[7];
    data[ 1 ] = argumentValues[ 1 ]; //set the port number
    data[ 5 ] = argumentValues[ 2 ]; //set the server ip name
    data[ 2 ] = argumentValues[ 3 ]; // set the repetition
    data[ 0 ] = argumentValues[ 0 ];
    myfile.open("ClientBenchMark.txt");
    for ( int i = 15; i <= 60; i = i * 2 )
    {
        myfile << "Number Buffer: " + to_string(i) << endl;
        myfile << "Buffer size: " + to_string(1500 / i) << endl;
        for ( int transferType = 1; transferType <= 3; transferType++ )
        {
            myfile << "Type: " + to_string(transferType) <<endl;
            string Buffer = to_string(i);
            string size = to_string(1500 / i);
            string operationType = to_string(transferType);
            char *numBuffer = new char[Buffer.length() + 1];
            char *buffSize = new char[size.length() + 1];
            char *type = new char[operationType.length() + 1];
            strcpy(numBuffer , Buffer.c_str());
            strcpy(buffSize , size.c_str());
            strcpy(type , operationType.c_str());
            data[ 3 ] = numBuffer;
            data[ 4 ] = buffSize;
            data[ 6 ] = type;
            // repeat the experiement for same number buffer, buffer size and type 5 types
            for ( int k = 0; k < 5; k++ )
            {
                Fakemain(argumentNumber , data);
            }
            delete[] numBuffer;
            delete[] buffSize;
            delete[] type;
        }
    }
    myfile.close();
}




