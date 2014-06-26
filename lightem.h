/*
 * lightem - light 'em up! a library to control RGB LED's
 */

#ifndef LIGHTEM_H_
#define LIGHTEM_H_

#include <stdint.h>

#ifdef __cplusplus
class lightem {
public:

  static const size_t sz_frame = 7;

  lightem();
  ~lightem();

  uint32_t color(uint8_t r, uint8_t g, uint8_t b);

  void setColor(uint32_t color);
  inline void setColor(uint8_t r, uint8_t g, uint8_t b) { setColor(color(r,g,b)); }
  void setAddr(int led);

  int isPixelValue(void);
  int isValid(void);

  uint8_t* getAddr(size_t* psz);
  int getAddr(void);
  uint32_t getColor(void);

  /**
   * This method will copy the first 7 octets from f to the internal buffer
   *
   * \param f   pointer to a min 7 octet wide buffer
   *
   * \return 0  The frame is considered as invalid
   * \return 1  The frame is valid
   */
  int setFrame(const void* f);
  /**
   * This method will return a copy of the current frame.
   *
   * You have to free the pointer returned by yourself.
   */
  void* getFrame(size_t *psz);

private:

  uint8_t frame[7];

  uint8_t _csum(uint8_t* p);
  void createCsum(void);

};
extern "C" {
#endif /* __cplusplus */

  /**
   * This method creates a frame and returns a copy of it.
   *
   * You have to free the pointer returned by yourself.
   */
  void* lightem_c (int addr, uint8_t r, uint8_t g, uint8_t b, size_t *psz);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* LIGHTEM_H_ */
