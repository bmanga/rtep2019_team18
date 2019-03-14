#include "fsr_reader.h"
#include "telemetry/server.h"
#include <thread>
#include <iostream>

using namespace std;


struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};


int main(void)
{

    tel::server server;
    server.run_on_thread(9004);
    
    sensors_data fsr_data = {};


    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int i = 20;
    int a2dVal = 0;
    int a2dChannel = 0;
    unsigned char data[3];

    while(1)
    {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10'000'000; // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

        a2d.spiWriteRead(data, sizeof(data) );

        a2dVal = 0;
                a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
                a2dVal |=  (data[2] & 0xff);
        
        cout << "The Result is: " << a2dVal << endl;
        fsr_data.ax = a2dVal/512;

        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10'010'000; // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care

        a2d.spiWriteRead(data, sizeof(data) );

        a2dVal = 0;
                a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
                a2dVal |=  (data[2] & 0xff);
        
        cout << "The Result is: " << a2dVal << endl;
        fsr_data.ay = a2dVal/512;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        server.broadcast(&fsr_data, sizeof(fsr_data));
    }
    return 0;
}
