#include "Serial.h"

#include <gtest/gtest.h>

std::string file = "foo.bin";

TEST(UINT8, Write) {
  uint8_t x = 0x12;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
  }

  EXPECT_EQ(size, 1u);
}

TEST(UINT8, Write_Max){
  uint8_t x = 0xFF;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
  }
  
  EXPECT_EQ(size, 1u);
}

TEST(UINT8, Equal){
  uint8_t x = 0x12;
  std::size_t size;
  
  serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
  size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));

  EXPECT_EQ(size, 1u);
  
  serial::OBinaryFile copy("copy.bin", serial::OBinaryFile::Mode::Truncate);

  copy = std::move(f);

  size = copy.write(reinterpret_cast<std::byte*>(&x), sizeof(x));
  EXPECT_EQ(size, 1u);
}

TEST(UINT8, Equal2){
  
  uint8_t x = 0x12;
  std::size_t size;
  
  serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
  size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));

  EXPECT_EQ(size, 1u);
  
  serial::OBinaryFile copy(std::move(f));

  size = copy.write(reinterpret_cast<std::byte*>(&x), sizeof(x));
  // EXPECT_EQ(size, 1u);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}