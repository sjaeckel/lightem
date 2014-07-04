/*
 * lightem - light 'em up! a library to control RGB LED's
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lightem.h"

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

#define STORE32(x, y)                                                                     \
  do { (y)[3] = (uint8_t)(((x)>>24)&255); (y)[2] = (uint8_t)(((x)>>16)&255);   \
       (y)[1] = (uint8_t)(((x)>>8)&255); (y)[0] = (uint8_t)((x)&255); } while(0)

#define LOAD32(x, y)                            \
  do { x = ((uint32_t)((y)[3] & 255)<<24) | \
           ((uint32_t)((y)[2] & 255)<<16) | \
           ((uint32_t)((y)[1] & 255)<<8)  | \
           ((uint32_t)((y)[0] & 255)); } while(0)

typedef struct __attribute__ ((__packed__)) _lightem_t
{
  uint8_t type;
  uint8_t addr;
  uint8_t data[4];
  uint8_t csum;
} st_lightem_t;

typedef enum _type_t
{
  type_cmd = 254,
  type_data = 255
} en_type_t;

lightem::lightem(void)
{

}

lightem::~lightem()
{

}

uint8_t lightem::_csum(uint8_t* p)
{
  uint8_t *pe, csum = 0;

  if (!p)
    return 0xff;

  pe = p + (sizeof(st_lightem_t)-1);
  while (p != pe) {
    csum -= *p;
    ++p;
  }

  return csum;
}

void lightem::createCsum(void)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  p->csum = _csum(frame);
}

int lightem::isPixelValue(void)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  return p->type == type_data;
}

int lightem::isValid(void)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  return (_csum(frame) == p->csum);
}

uint32_t lightem::color(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void lightem::setColor(uint32_t color)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  p->type = type_data;
  STORE32(color, p->data);
}

uint32_t lightem::getColor(void)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  uint32_t c;
  LOAD32(c, p->data);
  return c;
}

void lightem::setAddr(int addr)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  p->addr = addr;
}

int lightem::getAddr(void)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  return p->addr;
}

uint8_t* lightem::getAddr(size_t* psz)
{
  st_lightem_t* p = (st_lightem_t*)frame;
  uint8_t* r = 0;
  if (psz)
    {
      size_t sz;
      if (p->addr == 0xff)
        {
          sz = 128;
        }
      else if ((p->addr & 0x90) == 0x90)
        {
          sz = 8;
        }
      else if ((p->addr & 0x80) == 0x80)
        {
          sz = 16;
        }
      else
        {
          sz = 1;
        }
      r = (uint8_t*)malloc(sz * sizeof(uint8_t));
      if (r)
          {
            *psz = sz;
            if (p->addr == 0xff)
              {
                for (size_t i = 0; i < sz; ++i)
                  {
                    r[i] = i;
                  }
              }
            else if ((p->addr & 0x90) == 0x90)
              {
                uint8_t a = p->addr & 0x0F;
                for (size_t i = 0; i < sz; ++i)
                  {
                    r[i] = ((uint8_t)i << 4) | a;
                  }
              }
            else if ((p->addr & 0x80) == 0x80)
              {
                uint8_t a = p->addr & 0x70;
                for (size_t i = 0; i < sz; ++i)
                  {
                    r[i] = a + i;
                  }
              }
            else
              {
                *r = p->addr;
              }
        }
    }
  return r;
}

int lightem::setFrame(const void* f)
{
  if (f)
    {
      memcpy(frame, f, sizeof(frame));
      return isValid();
    }
  return 0;
}

void* lightem::getFrame(size_t *psz)
{
  size_t sz = 0;
  void* f = malloc(sizeof(frame));

  if (f)
    {
      createCsum();
      memcpy(f, frame, sizeof(frame));
      sz = sizeof(frame);
    }

  if (psz)
    *psz = sz;

  return f;
}

extern "C" {

void* lightem_c (int addr, uint8_t r, uint8_t g, uint8_t b, size_t *psz) {
  lightem l;
  l.setAddr(addr);
  l.setColor(r, g, b);
  return l.getFrame(psz);
}

}

