#ifndef LIBMP3PLAYER_H
#define LIBMP3PLAYER_H

#include <ao/ao.h>
#include <mpg123.h>
#include <stdint.h>

class mp3_player {
 public:
  mp3_player();
  ~mp3_player();

  int play(char *filename);

 private:
  mpg123_handle *mh;
  char *buffer;
  size_t buffer_size;
  size_t done;
  int err;
  int driver;
  ao_device *dev;
  ao_sample_format format;
  int channels, encoding;
  long rate;
  int count;
};

#endif