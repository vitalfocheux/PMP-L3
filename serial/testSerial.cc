#include "Serial.h"

#include <gtest/gtest.h>

TEST(test, test_test_Test){
  
  int8_t i8 = 127;

  {
    serial::OBinaryFile out("foo.bin");
    out << i8;
  }

  int8_t copy = 0;

  {
    serial::IBinaryFile in("foo.bin");
    in >> copy;
  }

  std::cout << "i8: " << (int)copy << std::endl;

  EXPECT_EQ(i8, copy);

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}