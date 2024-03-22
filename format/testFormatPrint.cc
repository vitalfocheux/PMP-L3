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

std::string to_string(const std::string& s){
  return s;
}

std::string to_string(const char* s){
  return s;
}

TEST(Integer, Simple){
  auto str = fp::format("%d", 42);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLong){
  auto str = fp::format("%d", 42L);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLongLong){
  auto str = fp::format("%d", 42LL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsigned){
  auto str = fp::format("%d", 42U);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLong){
  auto str = fp::format("%d", 42UL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLongLong){
  auto str = fp::format("%d", 42ULL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimple){
  const int i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLong){
  const long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLongLong){
  const long long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsigned){
  const unsigned i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLong){
  const unsigned long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLongLong){
  const unsigned long long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, Simple2){
  auto str = fp::format("%i", 42);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLong2){
  auto str = fp::format("%i", 42L);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLongLong2){
  auto str = fp::format("%i", 42LL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsigned2){
  auto str = fp::format("%i", 42U);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLong2){
  auto str = fp::format("%i", 42UL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLongLong2){
  auto str = fp::format("%i", 42ULL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimple2){
  const int i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLong2){
  const long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLongLong2){
  const long long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsigned2){
  const unsigned i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLong2){
  const unsigned long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLongLong2){
  const unsigned long long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, Negative){
  auto str = fp::format("%d", -42);
  EXPECT_EQ(str, "-42");
}

TEST(Integer, Negative2){
  auto str = fp::format("%i", -42);
  EXPECT_EQ(str, "-42");
}

TEST(Hexadecimal, Simple){
  auto str = fp::format("%x", 42);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleLong){
  auto str = fp::format("%x", 42L);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleLongLong){
  auto str = fp::format("%x", 42LL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsigned){
  auto str = fp::format("%x", 42U);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsignedLong){
  auto str = fp::format("%x", 42UL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsignedLongLong){
  auto str = fp::format("%x", 42ULL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimple){
  const int i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleLong){
  const long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleLongLong){
  const long long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsigned){
  const unsigned i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsignedLong){
  const unsigned long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsignedLongLong){
  const unsigned long long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, Zero){
  auto str = fp::format("%x", 0);
  EXPECT_EQ(str, "0x0");
}

TEST(Hexadecimal, Negative){
  auto str = fp::format("%x", -1);
  EXPECT_EQ(str, "0xffffffff");
}

TEST(Float, Simple){
  auto str = fp::format("%f", 3.141592);
  EXPECT_EQ(str, "3.141592");
}

TEST(Float, Simple2){
  float pi = 3.141592;
  auto str = fp::format("%f", pi);
  EXPECT_EQ(str, "3.141592");
}

TEST(Float, Simple3){
  double pi = 3.141592;
  auto str = fp::format("%f", pi);
  EXPECT_EQ(str, "3.141592");
}

TEST(Float, Negative){
  auto str = fp::format("%f", -3.141592);
  EXPECT_EQ(str, "-3.141592");
}

TEST(Float, Approx){
  auto str = fp::format("%f", 3.1415927);
  EXPECT_EQ(str, "3.141593");
}

TEST(Float, Without6Decimal){
  auto str = fp::format("%f", 42.0);
  EXPECT_EQ(str, "42.000000");
}

TEST(Boolean, True){
  auto str = fp::format("%b", true);
  EXPECT_EQ(str, "true");
}

TEST(Boolean, True2){
  bool b = true;
  auto str = fp::format("%b", b);
  EXPECT_EQ(str, "true");
}

TEST(Boolean, False){
  auto str = fp::format("%b", false);
  EXPECT_EQ(str, "false");
}

TEST(Boolean, False2){
  bool b = false;
  auto str = fp::format("%b", b);
  EXPECT_EQ(str, "false");
}

TEST(String, Simple){
  auto str = fp::format("%s", "Hello");
  EXPECT_EQ(str, "Hello");
}

TEST(String, Simple2){
  std::string s = "Hello";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "Hello");
}

TEST(String, Simple3){
  char s[6] = "Hello";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "Hello");
}

TEST(String, Null){
  auto str = fp::format("%s", "");
  EXPECT_EQ(str, "(null)");
}

TEST(String, Null2){
  std::string s = "";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "(null)");
}

TEST(String, Null3){
  char s[1] = "";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "(null)");
}

TEST(String, ConstSimple){
  const char* s = "Hello";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "Hello");
}

TEST(String, ConstSimple2){
  const std::string s = "Hello";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "Hello");
}

TEST(String, ConstSimple3){
  const char s[6] = "Hello";
  auto str = fp::format("%s", s);
  EXPECT_EQ(str, "Hello");
}

TEST(Char, Simple){
  auto str = fp::format("%c", 'A');
  EXPECT_EQ(str, "A");
}

TEST(Char, Simple2){
  char c = 'A';
  auto str = fp::format("%c", c);
  EXPECT_EQ(str, "A");
}

TEST(Char, Const){
  const char c = 'A';
  auto str = fp::format("%c", c);
  EXPECT_EQ(str, "A");
}

TEST(Pointer, Null){
  int *p = nullptr;
  auto str = fp::format("%p", p);
  EXPECT_EQ(str, "0x0");
}

TEST(Pointer, Integer){
  int i = 42;
  auto str = fp::format("%p", &i);
  std::ostringstream oss;
  oss << &i;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstInteger){
  const int i = 42;
  auto str = fp::format("%p", &i);
  std::ostringstream oss;
  oss << &i;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, Long){
  long l = 42;
  auto str = fp::format("%p", &l);
  std::ostringstream oss;
  oss << &l;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstLong){
  const long l = 42;
  auto str = fp::format("%p", &l);
  std::ostringstream oss;
  oss << &l;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, LongLong){
  long long ll = 42;
  auto str = fp::format("%p", &ll);
  std::ostringstream oss;
  oss << &ll;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstLongLong){
  const long long ll = 42;
  auto str = fp::format("%p", &ll);
  std::ostringstream oss;
  oss << &ll;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, Unsigned){
  unsigned u = 42;
  auto str = fp::format("%p", &u);
  std::ostringstream oss;
  oss << &u;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstUnsigned){
  const unsigned u = 42;
  auto str = fp::format("%p", &u);
  std::ostringstream oss;
  oss << &u;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, UnsignedLong){
  unsigned long ul = 42;
  auto str = fp::format("%p", &ul);
  std::ostringstream oss;
  oss << &ul;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstUnsignedLong){
  const unsigned long ul = 42;
  auto str = fp::format("%p", &ul);
  std::ostringstream oss;
  oss << &ul;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, UnsignedLongLong){
  unsigned long long ull = 42;
  auto str = fp::format("%p", &ull);
  std::ostringstream oss;
  oss << &ull;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstUnsignedLongLong){
  const unsigned long long ull = 42;
  auto str = fp::format("%p", &ull);
  std::ostringstream oss;
  oss << &ull;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, Float){
  float f = 3.14;
  auto str = fp::format("%p", &f);
  std::ostringstream oss;
  oss << &f;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstFloat){
  const float f = 3.14;
  auto str = fp::format("%p", &f);
  std::ostringstream oss;
  oss << &f;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, Double){
  double d = 3.14;
  auto str = fp::format("%p", &d);
  std::ostringstream oss;
  oss << &d;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstDouble){
  const double d = 3.14;
  auto str = fp::format("%p", &d);
  std::ostringstream oss;
  oss << &d;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, LongDouble){
  long double ld = 3.14;
  auto str = fp::format("%p", &ld);
  std::ostringstream oss;
  oss << &ld;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstLongDouble){
  const long double ld = 3.14;
  auto str = fp::format("%p", &ld);
  std::ostringstream oss;
  oss << &ld;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, String){
  std::string s = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstString){
  const std::string s = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstString2){
  const char *s = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, String3){
  char s[6] = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstString3){
  const char s[6] = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

// TEST(Pointer, Char){
//   char c = 'A';
//   auto str = fp::format("%p", &c);
//   std::ostringstream oss;
//   oss << &c;
//   std::string expectedAddress = oss.str();
//   EXPECT_EQ(str, expectedAddress);
// }

// TEST(Pointer, ConstChar){
//   const char c = 'A';
//   auto str = fp::format("%p", &c);
//   std::ostringstream oss;
//   oss << &c;
//   std::string expectedAddress = oss.str();
//   EXPECT_EQ(str, expectedAddress);
// }

TEST(Pointer, Boolean){
  bool b = true;
  auto str = fp::format("%p", &b);
  std::ostringstream oss;
  oss << &b;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstBoolean){
  const bool b = true;
  auto str = fp::format("%p", &b);
  std::ostringstream oss;
  oss << &b;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, CustomType){
  my::Foo foo = {8};
  auto str = fp::format("%p", &foo);
  std::ostringstream oss;
  oss << &foo;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, ConstCustomType){
  const my::Foo foo = {8};
  auto str = fp::format("%p", &foo);
  std::ostringstream oss;
  oss << &foo;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Generic, CustomType){
  my::Foo foo = {8};
  auto str = fp::format("%o", foo);
  EXPECT_EQ(str, "8");
}

TEST(Generic, Integer){
  try{
    auto str = fp::format("%o", 42);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Long){
  try{
    auto str = fp::format("%o", 42L);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, LongLong){
  try{
    auto str = fp::format("%o", 42LL);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Unsigned){
  try{
    auto str = fp::format("%o", 42U);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, UnsignedLong){
  try{
    auto str = fp::format("%o", 42UL);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, UnsignedLongLong){
  try{
    auto str = fp::format("%o", 42ULL);
    EXPECT_EQ(str, "42");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Float){
  try{
    auto str = fp::format("%o", 3.141592f);
    EXPECT_EQ(str, "3.141592");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Double){
  try{
    auto str = fp::format("%o", 3.141592);
    EXPECT_EQ(str, "3.141592");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, LongDouble){
  try{
    auto str = fp::format("%o", 3.141592l);
    EXPECT_EQ(str, "3.141592");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Boolean){
  try{
    auto str = fp::format("%o", true);
    EXPECT_EQ(str, "true");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, String){
  try{
    auto str = fp::format("%o", "Hello");
    EXPECT_EQ(str, "Hello");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, String2){
  std::string s = "Hello";
  try{
    auto str = fp::format("%o", s);
    EXPECT_EQ(str, "Hello");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, String3){
  char s[6] = "Hello";
  try{
    auto str = fp::format("%o", s);
    EXPECT_EQ(str, "Hello");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, String4){
  const char *s = "Hello";
  try{
    auto str = fp::format("%o", s);
    EXPECT_EQ(str, "Hello");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Char){
  try{
    auto str = fp::format("%o", 'A');
    EXPECT_EQ(str, "A");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Generic, Pointer){
  int i = 42;
  try{
    auto str = fp::format("%o", &i);
    std::ostringstream oss;
    oss << &i;
    std::string expectedAddress = oss.str();
    EXPECT_EQ(str, expectedAddress);
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Substitution, None){
  auto str = fp::format("No substitution");
  EXPECT_EQ(str, "No substitution");
}

TEST(Substitution, One){
  auto str = fp::format("%s", "Hello");
  EXPECT_EQ(str, "Hello");
}

TEST(Substitution, Two){
  auto str = fp::format("Two %s %s", "Hello", "World");
  EXPECT_EQ(str, "Two Hello World");
}

TEST(Substitution, MultipleDifferent){
  auto str = fp::format("%s %d %f %b", "Hello", 42, 3.14, true);
  EXPECT_EQ(str, "Hello 42 3.140000 true");
}

TEST(Substitution, Echappement){
  auto str = fp::format("%%");
  EXPECT_EQ(str, "%");
}

TEST(Substitution, Echappement2){
  auto str = fp::format("%%i");
  EXPECT_EQ(str, "%i");
}

TEST(Substitution, Echappement3){
  auto str = fp::format("%%d");
  EXPECT_EQ(str, "%d");
}

TEST(Substitution, Echappement4){
  auto str = fp::format("%%x");
  EXPECT_EQ(str, "%x");
}

TEST(Substitution, Echappement5){
  auto str = fp::format("%%f");
  EXPECT_EQ(str, "%f");
}

TEST(Substitution, Echappement6){
  auto str = fp::format("%%b");
  EXPECT_EQ(str, "%b");
}

TEST(Substitution, Echappement7){
  auto str = fp::format("%%s");
  EXPECT_EQ(str, "%s");
}

TEST(Substitution, Echappement8){
  auto str = fp::format("%%c");
  EXPECT_EQ(str, "%c");
}

TEST(Substitution, Echappement9){
  auto str = fp::format("%%p");
  EXPECT_EQ(str, "%p");
}

TEST(Substitution, Echappement10){
  auto str = fp::format("%%o");
  EXPECT_EQ(str, "%o");
}

TEST(Substitution, Echappement11){
  auto str = fp::format("%%i%%d%%x%%f%%b%%s%%c%%p%%o");
  EXPECT_EQ(str, "%i%d%x%f%b%s%c%p%o");
}

TEST(Substitution, Echappement12){
  auto str = fp::format("%%%%%%%%");
  EXPECT_EQ(str, "%%%%");
}

TEST(Substitution, Echappement13){
  auto str = fp::format("%%%%%%%%i");
  EXPECT_EQ(str, "%%%%i");
}

TEST(Substitution, Echappement14){
  auto str = fp::format("%%%%%%%%%i", 42);
  EXPECT_EQ(str, "%%%%42");
}

TEST(Substitution, 100Percent){
  auto str = fp::format("%i%%", 100);
  EXPECT_EQ(str, "100%");
}

TEST(Substitution, Bad){
  for(char c = 'a'; c <= 'z'; ++c){
    try{
      auto str = fp::format("%" + std::string(1, c));
      auto s = "%" + std::string(1, c);
      EXPECT_EQ(str, s);
    } catch (const std::runtime_error& e){
      std::cout << "Bad substitution with %" << c << std::endl;
    }
  }
}

TEST(BadType, IntegerChar){
  try{
    auto str = fp::format("%i", 'v');
    EXPECT_EQ(str, "v");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(BadType, IntegerChar2){
  try{
    auto str = fp::format("%d", 'v');
    EXPECT_EQ(str, "v");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(BadType, IntegerChar3){
  try{
    auto str = fp::format("%x", 'v');
    EXPECT_EQ(str, "v");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(BadType, IntegerBool){
  try{
    auto str = fp::format("%i", true);
    EXPECT_EQ(str, "true");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(BadType, IntegerBool2){
  try{
    auto str = fp::format("%d", true);
    EXPECT_EQ(str, "true");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(BadType, IntegerBool3){
  try{
    auto str = fp::format("%x", true);
    EXPECT_EQ(str, "true");
  } catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(Exemple, Exemple){
  auto str = fp::format("%s %s!", "Hello", "World");
  EXPECT_EQ(str, "Hello World!");

  str = fp::format("The cake is lie!");
  EXPECT_EQ(str, "The cake is lie!");

  str = fp::format("The Answer is %d", 42);
  EXPECT_EQ(str, "The Answer is 42");

  str = fp::format("Approx of %s is %f", "Pi", 3.141592);
  EXPECT_EQ(str, "Approx of Pi is 3.141592");

  str = fp::format("%d in hexadecimal %x", 42, 42);
  EXPECT_EQ(str, "42 in hexadecimal 0x2a");

  str = fp::format("'%c' is the 1st alphabet letter", 'A');
  EXPECT_EQ(str, "'A' is the 1st alphabet letter");

  str = fp::format("This sentence is %b", false);
  EXPECT_EQ(str, "This sentence is false");

  my::Foo foo = {8};
  str = fp::format("%o", foo);
  EXPECT_EQ(str, "8");

  str = fp::format("%p", &foo);
  std::ostringstream oss;
  oss << &foo;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);

  str = fp::format("No substitution: %%i");
  EXPECT_EQ(str, "No substitution: %i");

  try{
    str = fp::format("Too many arguments", 10);
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }

  try{
    str = fp::format("Missing argument: %d");
  } catch (const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
