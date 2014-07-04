#include <string.h>
#include <gtest/gtest.h>
#include "lightem.h"

using ::testing::TestWithParam;
using ::testing::Values;

class checksumTest
{
public:
  const uint8_t* d;

  checksumTest(const uint8_t* d)
  {
    this->d = d;
  }
};

class test_lightem_checksum : public testing::TestWithParam<checksumTest>
{ };

TEST_P(test_lightem_checksum, cmpSet) {
  lightem l;
  checksumTest tc = GetParam();
  EXPECT_TRUE(l.setFrame(tc.d));
}

INSTANTIATE_TEST_CASE_P(
    cmpSet,
    test_lightem_checksum,
    Values(
         checksumTest( (const uint8_t[]){ 254, 128, 1, 0, 1, 0, 128 } ),

         checksumTest( (const uint8_t[]){ 254, 128, 2, 0, 1, 0, 127 } ),

         checksumTest( (const uint8_t[]){ 254, 5, 3, 14, 1, 0, 235 } ),

         checksumTest( (const uint8_t[]){ 254, 255, 4, 3, 1, 0, 251 } ),

         checksumTest( (const uint8_t[]){ 254, 176, 5, 0, 1, 0, 76 } ),

         checksumTest( (const uint8_t[]){ 254, 255, 6, 255, 1, 0, 253 } ),

         checksumTest( (const uint8_t[]){ 254, 128, 7, 0, 1, 0, 122 } ),

         checksumTest( (const uint8_t[]){ 254, 128, 8, 0, 1, 0, 121 } )
    ));


#ifdef LIGHTEM_TESTING


#endif
