/**
 * @author Thuan Tran
 * @date May 11th,2018
 * CSS 432: HW3 Sliding Window
 * Header file for the class that will implement the stop and wait algorithm and the sliding window
 * For both client and server
 */
#ifndef HW3_UDPHW3_H
#define HW3_UDPHW3_H

#include "UdpSocket.h"
#include "Timer.h"

class udphw3 {
public:

    int clientStopWait( UdpSocket &sock, const int max, int message[] );
    void serverReliable( UdpSocket &sock, const int max, int message[] );
    int clientSlidingWindow( UdpSocket &sock, const int max, int message[], int windowSize );
    void serverEarlyRetrans( UdpSocket &sock, const int max, int message[], int windowSize );

private:
};

#endif //HW3_UDPHW3_H
