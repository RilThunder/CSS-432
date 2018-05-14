//
// Created by Thuan on 5/9/2018.
//

#include "udphw3case4.h"

using namespace std;


/**
 * client side for the sliding window algorithm
 * Same function like in udphw3
 */
int udphw3case4::clientSlidingWindow(UdpSocket &sock, const int max, int *message, int windowSize) {
    udphw3 hw3;
    return hw3.clientSlidingWindow(sock, max, message, windowSize);
}


/**
 * Similar function like the server side implementation for sliding algorithm
 * in udphw3. The only difference is that packet will be randomly dropped
 * @param sock The socket to send and receive data
 * @param max  the maximum number of packets to receive
 * @param message  the message buffer
 * @param windowSize the window size of the packets. Was not used within the server side
 * @param dropRate the drop rate of packet. By not returning an ack
 */
void udphw3case4::serverEarlyRetrans(UdpSocket &sock, const int max, int *message, int windowSize, int dropRate) {

    // Will use the index i as the expected number within the message
    // Can only advance the loop if the data is received in correct order

    for (int i = 0; i < max; i++) {
        while (true) {
            if (sock.pollRecvFrom() > 0) {
                int percentage = rand() % 101; // Generate a random number from 0 -100;
                if (percentage < dropRate) {
                    continue;
                }
                sock.recvFrom((char *) message, MSGSIZE);
                sock.ackTo((char *) &i, sizeof(i));
                if (message[0] == i) {
                    break; // Can advance and receive the next data
                }
            }
        }

    }
}




