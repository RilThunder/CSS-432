/**
 * @author Thuan Tran
 * CSS 432: HW3 Sliding Window
 * @date May 10th, 2018
 */

#include "udphw3.h"

#define TIME_OUT 150


/**
 * Implement the stop and wait for the client side
 * Send a message with the sequence number. If not received a reply back within 1500 usec
 * Will re-send the message if time out
 * @param sock the udp socket to send data from
 * @param max the maximum number of time (messages) to send
 * @param message the message buffer
 * @return number of retransmission
 */
int udphw3::clientStopWait(UdpSocket &sock, const int max, int *message) {
    int retransmission = 0;
    for (int i = 0; i < max; i++) {
        message[0] = i;                            // message[0] has a sequence #
        sock.sendTo((char *) message, MSGSIZE);     // udp message send
        bool timeOutFlag = false;
        Timer timer;
        timer.start();
        while (true) {
            int available = sock.pollRecvFrom(); // Check to see if there are any data to receive
            if (available > 0) {
                break;
            }
            if (timer.lap() > TIME_OUT && !timeOutFlag) {
                timeOutFlag = true;
                break;
            }
        }
        if (timeOutFlag) {
            i--; // Go back and send again
            retransmission++;
            continue;
        }
        sock.recvFrom((char *) message, MSGSIZE);   // At this point, did not reach timeout and have data
        if (message[0] != i) { // Did not receive correct ack for the message, will resend it
            i--;
            retransmission++;
            continue;
        }
    }
    return retransmission;

}

/**
 * Implement stop and wait for the server side.
 * Will send the ack message if only the message is number is what it is expecting
 * @param sock the udp socket
 * @param max the maximum number of time (message) to receive
 * @param message  The message buffer to receive
 */
void udphw3::serverReliable(UdpSocket &sock, const int max, int *message) {
    for (int i = 0; i < max; i++) {
        while (true) {
            sock.recvFrom((char *) message, MSGSIZE);
            if (message[0] == i) { // Only send ack if the server is waiting for this message
                sock.ackTo((char *) &i, sizeof(i));
                // Can only break the loop and go forward if it match
                break;
            }
        }
    }
}

/**
 * IMPORTANT: I will explain this in more details within the report
 * This algorithm is a sliding window algorithm that will receive a cumulative ack from the server
 * Because of the nature of the server, there is a very rare chance that it will need to retransmit
 * This is not selective repeat but instead sliding window
 *
 * Client side implementation for sliding window. It will keep sending message until it reach a a window size
 * After that, It will start to receive the package and check the ack number to slide the window
 * @param sock The socket to send data to and receive from
 * @param max the maximum number of messages to send
 * @param message the message buffer
 * @param windowSize the window slide to send the data
 * @return number of retransmission
 */
int udphw3::clientSlidingWindow(UdpSocket &sock, const int max, int *message, int windowSize) {
    int retransmission = 0;
    int recentAck = 0;
    int numberOfUnack = 0;
    for (int i = 0; i < max; i++) {
        // just keep sending the message until it hit window size
        if (numberOfUnack < windowSize) {
            message[0] = i;                            // message[0] has a sequence #
            sock.sendTo((char *) message, MSGSIZE);    // udp message send
            numberOfUnack++;
        }
        if (numberOfUnack == windowSize) {
            Timer timer;
            timer.start();
            // Check within the duration of the timer to see if it receive
            // any ack
            while (true) {
                // keep receiving data if there's data available
                if (sock.pollRecvFrom() > 0) {
                    sock.recvFrom((char *) message, MSGSIZE);
                    if (message[0] == recentAck) {
                        recentAck++; // Increment the recent in order message ack
                        numberOfUnack--;
                        break;
                    }
                }
                // No response meaning time out and no data
                if (timer.lap() > TIME_OUT && numberOfUnack == windowSize) {
                    retransmission = retransmission + (i + windowSize - recentAck);
                    i = recentAck;
                    numberOfUnack = 0; // Reset everything. Will start restransmitting at the lowest sequence number
                    continue;
                }
            }
        }
    }

    return retransmission;
}

/**
 * IMPORTANT: I will explain this in more details within the report
 * The server will only send the ack with the minimum sequence number for every package it receive
 * It will only accept in order package to increment the sequence number
 * It does not follow selective repeat algorithm and professor Peng have verified this
 *
 * Server side implementation for case 3: sliding window
 * @param sock the udp socket to receive data from
 * @param max the maximum number of time (messages) to receive
 * @param message the message buffer
 * @param windowSize the window size for the sliding window
 */
void udphw3::serverEarlyRetrans(UdpSocket &sock, const int max, int *message, int windowSize) {
    // Will use the index i as the expected number within the message
    // Can only advance the loop if the data is received in correct order
    for (int i = 0; i < max; i++) {
        while (true) {
            if (sock.pollRecvFrom() > 0) {
                sock.recvFrom((char *) message, MSGSIZE);
                sock.ackTo((char *) &i, sizeof(i));
                if (message[0] == i) {
                    break; // Can advance and receive the next data
                }
            }
        }
    }
}






/* Ask about window side for case 4
 * Send the ack number for last received message in order
 * If received message out of order, still save it in an array but send the ack of recent order
 * For case 4, packets are dropped N% of time where N is 0 to 10 for window size 1 and window size 30
 * So for each N of each window size. N = 0 for window 1, N =1 for window 2
 * drop N% of the time
 * Ask about how window size have effect on ServerEralyRetrans. For case 4, window 1 and window 30 won't have difference on server ?
 * Since they just ack sequentially
 * Since the server now only ack message that are in order. Did not match the algorithm signature ?
 */



