//
// Created by Thuan on 5/5/2018.
//

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
