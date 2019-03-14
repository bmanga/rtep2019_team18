#ifndef MCP3008SPI_H
    #define MCP3008SPI_H
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>

class mcp3008Spi{

public:
    mcp3008Spi();
    mcp3008Spi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
    ~mcp3008Spi();
    int spiWriteRead( unsigned char *data, int length);

private:
    unsigned char mode;
    unsigned char bitsPerWord;
    unsigned int speed;
    int spifd;

    int spiOpen(std::string devspi);
    int spiClose();

};

#endif