
#ifdef LIGHTEM_TESTING

#include <string.h>
#include <gtest/gtest.h>
#include "lightem.h"

using ::testing::TestWithParam;
using ::testing::Values;

class addressTest
{
public:
  int addr, start, num, steps;

  /**
   * \param     addr    The address that should be resolved
   * \param     start   Where the resolved address range should start
   * \param     num     The number of resolved addresses
   * \param     steps   The number of steps between two addresses
   */
  addressTest(int addr, int start, int num, int steps)
  {
    this->addr = addr;
    this->start = start;
    this->num = num;
    this->steps = steps;
  }
};

class test_lightem_addresses : public testing::TestWithParam<addressTest>
{ };

TEST_P(test_lightem_addresses, cmpSet) {
  lightem l;
  addressTest tc = GetParam();
  l.setAddr(tc.addr);
  uint8_t* pi;
  size_t sz;
  EXPECT_TRUE((pi = l.getAddr(&sz)));
  EXPECT_EQ(tc.num, sz);
  int start = tc.start;
  for (unsigned int i = 0; i < sz; ++i) {
      EXPECT_EQ(start, pi[i]);
      start += tc.steps;
  }
  if (pi)
    free(pi);
}

INSTANTIATE_TEST_CASE_P(
    cmpSet,
    test_lightem_addresses,
    Values(
         addressTest(0,   0,   1,   0 ),

         addressTest(127, 127, 1,   0 ),

         addressTest(128, 0,   16,  1 ),
         addressTest(129, 16,  16,  1 ),
         addressTest(130, 32,  16,  1 ),
         addressTest(131, 48,  16,  1 ),
         addressTest(132, 64,  16,  1 ),
         addressTest(133, 80,  16,  1 ),
         addressTest(134, 96,  16,  1 ),
         addressTest(135, 112, 16,  1 ),

         addressTest(144, 0,   8,   16 ),
         addressTest(145, 1,   8,   16 ),
         addressTest(146, 2,   8,   16 ),
         addressTest(147, 3,   8,   16 ),
         addressTest(148, 4,   8,   16 ),
         addressTest(149, 5,   8,   16 ),
         addressTest(150, 6,   8,   16 ),
         addressTest(151, 7,   8,   16 ),
         addressTest(152, 8,   8,   16 ),
         addressTest(153, 9,   8,   16 ),
         addressTest(154, 10,  8,   16 ),
         addressTest(155, 11,  8,   16 ),
         addressTest(156, 12,  8,   16 ),
         addressTest(157, 13,  8,   16 ),
         addressTest(158, 14,  8,   16 ),
         addressTest(159, 15,  8,   16 ),

         addressTest(255, 0,   128, 1 )
    ));

#endif /* LIGHTEM_TESTING */
