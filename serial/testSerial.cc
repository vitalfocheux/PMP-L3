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

  EXPECT_EQ(x, 0x12);
  EXPECT_EQ(size, 1u);
}

TEST(UINT8, Read){
  uint8_t x = 0x12;
  uint8_t y;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
  }

  EXPECT_EQ(x, 0x12);
  EXPECT_EQ(size, 1u);

  size = 0;

  {
    serial::IBinaryFile f(file);
    size = f.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
  }

  EXPECT_EQ(size, 1u);
  EXPECT_EQ(x, 0x12);
  EXPECT_EQ(y, 0x12);
  EXPECT_EQ(x, y);
}

TEST(UINT8, Write_Max){
  uint8_t x = 0xFF;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
  }
  
  EXPECT_EQ(x, 0xFF);
  EXPECT_EQ(size, 1u);
}

TEST(UINT8, Read_Max){
  uint8_t x = 0xFF;
  uint8_t y;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
  }
  
  EXPECT_EQ(x, 0xFF);
  EXPECT_EQ(size, 1u);

  size = 0;

  {
    serial::IBinaryFile f(file);
    size = f.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
  }

  EXPECT_EQ(size, 1u);
  EXPECT_EQ(x, 0xFF);
  EXPECT_EQ(y, 0xFF);
  EXPECT_EQ(x, y);
}

TEST(UINT8, Equal_Move_Assignment){
  uint8_t x = 0x12;
  std::size_t size;

  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));

    EXPECT_EQ(x, 0x12);
    EXPECT_EQ(size, 1u);
    
    serial::OBinaryFile copy("copy.bin", serial::OBinaryFile::Mode::Truncate);

    copy = std::move(f);

    size = copy.write(reinterpret_cast<std::byte*>(&x), sizeof(x));

    EXPECT_EQ(x, 0x12);
    EXPECT_EQ(size, 1u);
  }
  
  
}

TEST(UINT8, Equal_Move_Constructor){
  uint8_t x = 0x12;
  std::size_t size;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));

    EXPECT_EQ(x, 0x12);
    EXPECT_EQ(size, 1u);
    
    serial::OBinaryFile copy = std::move(f);

    size = copy.write(reinterpret_cast<std::byte*>(&x), sizeof(x));

    EXPECT_EQ(x, 0x12);
    EXPECT_EQ(size, 1u);
  }
  
}

TEST(UINT8, Write_Simple_Read_Simple){
  uint8_t x = 0x12;
  uint8_t y;
  std::size_t size;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    size = f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
    EXPECT_EQ(size, 1u);
  }

  {
    serial::IBinaryFile r(file);
    size = r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
    EXPECT_EQ(size, 1u);
    EXPECT_EQ(x, y);
  }
}

TEST(UINT8, Write_Multiple_Same_Read_Multiple_Same){
  uint8_t x = 0x12;
  uint8_t y;
  std::size_t size = 0;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    for(std::size_t i = 0; i < 0x42; ++i){
      size += f.write(reinterpret_cast<const std::byte*>(&x), sizeof(x));
      EXPECT_EQ(x, 0x12);
      EXPECT_EQ(size, (i+1));
    }
  }

  size = 0;

  {
    serial::IBinaryFile r(file);
    for(std::size_t i = 0; i < 0x42; ++i){
      size += r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, 0x12);
      EXPECT_EQ(size, (i+1));
    }
  }

}

TEST(UINT8, Write_Multiple_Different_Read_Multiple_Different){
  std::vector<uint8_t> x = {0x12, 0x34, 0x56, 0x78};
  uint8_t y;
  std::size_t size = 0;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    for(std::size_t i = 0; i < 4; ++i){
      size += f.write(reinterpret_cast<const std::byte*>(&x[i]), sizeof(x[i]));
      EXPECT_EQ(size, (i+1));
    }
  }

  size = 0;

  {
    serial::IBinaryFile r(file);
    for(std::size_t i = 0; i < 4; ++i){
      size += r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, x[i]);
      EXPECT_EQ(size, (i+1));
    }
  }
}

TEST(UINT8, Write_Multiple_Different_Read_Multiple_Different_With_Move_Constructor){
  std::vector<uint8_t> x = {0x12, 0x34, 0x56, 0x78};
  uint8_t y;
  std::size_t size = 0;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    for(std::size_t i = 0; i < 4; ++i){
      size += f.write(reinterpret_cast<const std::byte*>(&x[i]), sizeof(x[i]));
      EXPECT_EQ(size, (i+1));
    }
  }

  size = 0;

  {
    serial::IBinaryFile r(file);
    for(std::size_t i = 0; i < 2; ++i){
      size += r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, x[i]);
      EXPECT_EQ(size, (i+1));
    }

    serial::IBinaryFile copy = std::move(r);
    for(std::size_t i = 2; i < 4; ++i){
      size += copy.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, x[i]);
      EXPECT_EQ(size, (i+1));
    }
  }
}

TEST(UINT8, Write_Multiple_Different_Read_Multiple_Different_With_Move_Assignment){
  std::vector<uint8_t> x = {0x12, 0x34, 0x56, 0x78};
  uint8_t y;
  std::size_t size = 0;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    for(std::size_t i = 0; i < 4; ++i){
      size += f.write(reinterpret_cast<const std::byte*>(&x[i]), sizeof(x[i]));
      EXPECT_EQ(size, (i+1));
    }
  }

  size = 0;

  {
    serial::IBinaryFile r(file);
    for(std::size_t i = 0; i < 2; ++i){
      size += r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, x[i]);
      EXPECT_EQ(size, (i+1));
    }

    serial::IBinaryFile copy(file); 
    copy = std::move(r);
    for(std::size_t i = 2; i < 4; ++i){
      size += copy.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      EXPECT_EQ(y, x[i]);
      EXPECT_EQ(size, (i+1));
    }
  }
}

TEST(UINT8, Write_Multiple_Different_Read_Multiple_Different_With_INT8){
  std::vector<uint8_t> x = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF};
  int8_t y;
  std::size_t size = 0;
  
  {
    serial::OBinaryFile f(file, serial::OBinaryFile::Mode::Truncate);
    for(std::size_t i = 0; i < x.size(); ++i){
      size += f.write(reinterpret_cast<const std::byte*>(&x[i]), sizeof(x[i]));
      EXPECT_EQ(size, (i+1));
    }
  }

  size = 0;

  {
    serial::IBinaryFile r(file);
    for(std::size_t i = 0; i < x.size(); ++i){
      size += r.read(reinterpret_cast<std::byte*>(&y), sizeof(y));
      if(x[i] > 0x7F){
        EXPECT_NE(y, x[i]);
        EXPECT_EQ(y, (x[i] - 0x100));
      }else{
        EXPECT_EQ(y, x[i]);
      }
      EXPECT_EQ(size, (i+1));
    }
  }

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}