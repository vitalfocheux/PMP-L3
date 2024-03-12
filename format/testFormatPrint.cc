#include <gtest/gtest.h>

#include "Format.h"


namespace my {
  struct Foo {
    int i;
  };

  std::string to_string(const Foo& foo){
    return std::to_string(foo.i);
  }
}

TEST(FormetPrint, HelloWorld){
  auto str = fp::format("%s %s!", "Hello", "World");
  EXPECT_EQ(str, "Hello World!");
}

TEST(FormatPrint, String){
  auto str = fp::format("The cake is lie!");
  EXPECT_EQ(str, "The cake is lie!");
}

TEST(FormatPrint, NullString){
  auto str = fp::format("%s", "");
  EXPECT_EQ(str, "(null)");
}

TEST(FormatPrint, Int){
  auto str = fp::format("The Answer is %d", 42);
  EXPECT_EQ(str, "The Answer is 42");
}

TEST(FormatPrint, Float){
  auto str = fp::format("Approx of %s is %f", "Pi", 3.141592);
  EXPECT_EQ(str, "Approx of Pi is 3.141592");
}

TEST(FormatPrint, Hexadecimal){
  auto str = fp::format("%d in hexadecimal %x", 42, 42);
  EXPECT_EQ(str, "42 in hexadecimal 0x2a");
}

TEST(FormatPrint, Character){
  auto str = fp::format("'%c' is the 1st alphabet letter", 'A');
  EXPECT_EQ(str, "'A' is the 1st alphabet letter");
}

TEST(FormatPrint, Boolean){
  auto str = fp::format("This sentence is %b", false);
  EXPECT_EQ(str, "This sentence is false");
}

// TEST(FormatPrint, CustomType){
//   my::Foo foo = {8};
//   auto str = fp::format("%o", foo);
//   EXPECT_EQ(str, "8");
// }

TEST(FormatPrint, CustomTypeAddress){
  my::Foo foo = {8};
  auto str = fp::format("%p", &foo);
  std::ostringstream oss;
  oss << &foo;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(FormatPrint, Oui){
  auto str = fp::format("%d%%i", 100);
  EXPECT_EQ(str, "100%i");
}

TEST(FormatPrint, NoSibsistution){
  auto str = fp::format("No substitution: %%i");
  EXPECT_EQ(str, "No substitution: %i");
}

TEST(FormatPrint, ManyArguments){
  try{
    auto str = fp::format("Too many arguments", 10);
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(FormatPrint, MissingArgument){
  try{
    auto str = fp::format("Missing argument: %d");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
