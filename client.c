#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dcp.h"

int main( int argc, char* argv[]) {
    int sock;
    struct sockaddr_in addr_cl = {0}, addr_sr = {0};

    struct msg_heartbeat hb;

    addr_cl.sin_family = AF_INET;
    addr_cl.sin_port = htons(0);
    addr_cl.sin_addr.s_addr = INADDR_ANY;

    addr_sr.sin_family = AF_INET;
    addr_sr.sin_port = htons(51000);
    inet_aton("62.76.179.84", &addr_sr.sin_addr); 

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sock, &addr_cl, sizeof(struct sockaddr_in));
    srand( time( NULL));

    {
        hb.msg.proto = Proto_Dispatcher; 
        hb.msg.type = Msg_Heartbeat;
        hb.msg.num = atoi( argv[argc-1]);
        hb.msg.checksum = 0xdeadbeef;

        hb.st.longitude = 97.6 * rand()/RAND_MAX;
        hb.st.latitude = 98.13 * rand()/RAND_MAX;
        hb.st.heading = 1;
        hb.st.baroaltabs = 10;
        hb.st.baroaltrel = 20;
        hb.st.gpsalt = 16;
        hb.st.temperature = 100;
        hb.st.voltage = 5;
        hb.st.current = 2;
        hb.st.boardtime = 1<<13;
        hb.st.gsmlevel = 80;
        hb.st.last_msgnum = 0;
        hb.st.denial = 1;
        hb.st.gpsspeed = 30;
        hb.st.airspeed = 10;
        hb.st.status = 1;
        hb.st.srv.channel[0] = 1; 
        hb.st.srv.channel[1] = 1; 
        hb.st.srv.channel[2] = 1; 
        hb.st.srv.channel[3] = 1; 
        hb.st.srv.channel[4] = 1; 
        hb.st.srv.channel[5] = 1; 
        hb.st.cpt.position.longitude = 1e-2;
        hb.st.cpt.position.latitude = .3;
        hb.st.cpt.emergency.longitude = 1e+3;
        hb.st.cpt.emergency.latitude = 4.2e4;
        hb.st.cpt.speed = 100;
        hb.st.cpt.altitude = 200;
    }

    sendto(sock, &hb, sizeof(hb), 0, &addr_sr, sizeof(addr_sr));

    return 0;
}
