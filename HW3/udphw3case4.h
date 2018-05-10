//
// Created by Thuan on 5/9/2018.
//

#ifndef HW3_UDPHW3CASE4_H
#define HW3_UDPHW3CASE4_H



class udphw3case4
{
public:
    int clientSlidingWindow( UdpSocket &sock, const int max, int message[], int windowSize );
    void serverEarlyRetrans( UdpSocket &sock, const int max, int message[], int windowSize );

private:
};

#endif //HW3_UDPHW3CASE4_H