/**
 * @author Thuan Tran
 * @date May 11th, 2018
 * Header file for implementation of sliding algorithm where packet will be
 * randomly dropped
 */

#ifndef HW3_UDPHW3CASE4_H
#define HW3_UDPHW3CASE4_H

#include "UdpSocket.h"
#include "Timer.h"
#include "udphw3.h"

class udphw3case4
{
public:
    int clientSlidingWindow( UdpSocket &sock, const int max, int message[], int windowSize );
    void serverEarlyRetrans( UdpSocket &sock, const int max, int message[], int windowSize ,int dropRate);
private:
};

#endif //HW3_UDPHW3CASE4_H