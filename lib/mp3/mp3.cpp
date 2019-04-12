#include "mp3/mp3.h"
#include <ao/ao.h>
#include <mpg123.h>
#include <stdint.h>

#define BITS 8

mp3_player::mp3_player()
{
  ao_initialize();
  driver = ao_default_driver_id();
  mpg123_init();
  mh = mpg123_new(NULL, &err);
  buffer_size = mpg123_outblock(mh);
  buffer = (char *)malloc(buffer_size * sizeof(char));
  count = 0;
}

mp3_player::~mp3_player()
{
  free(buffer);
  ao_close(dev);
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();
  ao_shutdown();
}

int mp3_player::play(char *filename)
{
  /* open the file and get the decoding format */

  mpg123_open(mh, filename);
  mpg123_getformat(mh, &rate, &channels, &encoding);

  /* set the output format and open the output device */
  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  dev = ao_open_live(driver, &format, NULL);

  /* decode and play */
  while (mpg123_read(mh, (unsigned char *)buffer, buffer_size, &done) ==
         MPG123_OK)
    ao_play(dev, buffer, done);

  return 0;
}
