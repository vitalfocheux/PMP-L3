#include <gtest/gtest.h>

#include "Shared.h"
#include "Weak.h"
#include "Unique.h"

#include <climits>
#include <math.h>
#include <vector>
#include <numeric>

class Hello {
public:
    void printMessage() {
        std::cout << "Hello World!" << std::endl;
    }
};

// TEST(test, test) {
//   sp::Shared<int> shared;
//   sp::Weak<int> weak;
//   sp::Unique<int> unique;
// }

TEST(Unique, Init){
  // sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  EXPECT_TRUE(*unique == 42u);
  EXPECT_TRUE(unique.exists());
  EXPECT_TRUE(unique.get() != nullptr);
  EXPECT_TRUE(*unique.get() == 42u);
}

TEST(Unique, Arrow){
  Hello h;
  // sp::Unique<Hello> unique(new Hello());
  sp::Unique<Hello> unique = sp::makeUnique<Hello>(h);
  EXPECT_TRUE(unique.exists());
  unique->printMessage();
}

TEST(Unique, Move_Constructor){
  // sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2(std::move(unique));
  std::cout << *unique2 << std::endl;
  EXPECT_TRUE(*unique2 == 42u);
  EXPECT_FALSE(unique.exists());
  EXPECT_TRUE(unique2.exists());
}

TEST(Unique, Move_Assignement){
  // sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2;
  unique2 = std::move(unique);
  EXPECT_TRUE(*unique2 == 42u);
  // EXPECT_FALSE(unique.exists());
  EXPECT_FALSE(unique);
  EXPECT_TRUE(unique2.exists());
}

TEST(Unique, Simple_Operation){
  // sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  ++(*unique);
  EXPECT_TRUE(*unique == 43u);
  *unique /= 43;
  EXPECT_TRUE(*unique == 1u);
  *unique *= 42;
  EXPECT_TRUE(*unique == 42u);
  *unique -= 42;
  EXPECT_TRUE(*unique == 0u);
  *unique = 2;
  EXPECT_TRUE(*unique == 2u);
}

TEST(Unique, Logical_Operation){
  // sp::Unique<int> unique(new int(42));
  // sp::Unique<int> unique2(new int(42));
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2 = sp::makeUnique<int>(42);
  EXPECT_TRUE(*unique == *unique2);
  EXPECT_FALSE(*unique != *unique2);
  EXPECT_FALSE(*unique < *unique2);
  EXPECT_FALSE(*unique > *unique2);
  EXPECT_TRUE(*unique <= *unique2);
  EXPECT_TRUE(*unique >= *unique2);
  unique2 = std::move(unique);
  EXPECT_TRUE(unique2.exists());
  EXPECT_TRUE(unique.exists());
}

TEST(Unique, Logical_Or_Operation){
  // sp::Unique<bool> unique(new bool(true));
  // sp::Unique<bool> unique2(new bool(false));
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE(*unique || *unique2);
  EXPECT_TRUE(*unique || *unique);
  EXPECT_FALSE(*unique2 || *unique2);
}

TEST(Unique, Logical_And_Operation){
  // sp::Unique<bool> unique(new bool(true));
  // sp::Unique<bool> unique2(new bool(false));
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_FALSE(*unique && *unique2);
  EXPECT_TRUE(*unique && *unique);
  EXPECT_FALSE(*unique2 && *unique2);
}

TEST(Unique, Logical_Not_Operation){
  // sp::Unique<bool> unique(new bool(true));
  // sp::Unique<bool> unique2(new bool(false));
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_FALSE(!*unique);
  EXPECT_TRUE(!*unique2);
}

TEST(Unique, Logical_XOR_Operation){
  // sp::Unique<bool> unique(new bool(true));
  // sp::Unique<bool> unique2(new bool(false));
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE(*unique ^ *unique2);
  EXPECT_FALSE(*unique ^ *unique);
  EXPECT_FALSE(*unique2 ^ *unique2);
}

TEST(Unique, Multiple_Logical_Operation){
  // sp::Unique<bool> unique(new bool(true));
  // sp::Unique<bool> unique2(new bool(false));
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE((*unique || *unique2) && (*unique ^ *unique2));
}

TEST(Unique, iMAX){
  // sp::Unique<int> unique(new int(INT_MAX));
  sp::Unique<int> unique = sp::makeUnique<int>(INT_MAX);
  EXPECT_TRUE(*unique == INT_MAX);
  ++(*unique);
  EXPECT_TRUE(*unique == INT_MIN);
}

TEST(Unique, iMIN){
  // sp::Unique<int> unique(new int(INT_MIN));
  sp::Unique<int> unique = sp::makeUnique<int>(INT_MIN);
  EXPECT_TRUE(*unique == INT_MIN);
  --(*unique);
  EXPECT_TRUE(*unique == INT_MAX);
}

TEST(Unique, Pow){
  // sp::Unique<int> unique(new int(2));
  sp::Unique<int> unique = sp::makeUnique<int>(2);
  *unique = pow(*unique, 10);
  EXPECT_TRUE(*unique == 1024);
}

TEST(Unique, String){
  // sp::Unique<std::string> unique(new std::string("Hello"));
  sp::Unique<std::string> unique = sp::makeUnique<std::string>("Hello");
  EXPECT_TRUE(*unique == "Hello");
  *unique += " World!";
  EXPECT_TRUE(*unique == "Hello World!");
}

TEST(Unique, Char){
  // sp::Unique<char> unique(new char('a'));
  sp::Unique<char> unique = sp::makeUnique<char>('a');
  EXPECT_TRUE(*unique == 'a');
  ++(*unique);
  EXPECT_TRUE(*unique == 'b');
}

TEST(Unique, Vector_Int){
  // sp::Unique<std::vector<int>> unique(new std::vector<int>{1, 2, 3});
  std::vector<int> v{1,2,3};
  sp::Unique<std::vector<int>> unique = sp::makeUnique<std::vector<int>>(v);
  EXPECT_TRUE((*unique)[0] == 1);
  EXPECT_TRUE((*unique)[1] == 2);
  EXPECT_TRUE((*unique)[2] == 3);
  (*unique)[0] = 4;
  (*unique)[1] = 5;
  (*unique)[2] = 6;
  EXPECT_TRUE((*unique)[0] == 4);
  EXPECT_TRUE((*unique)[1] == 5);
  EXPECT_TRUE((*unique)[2] == 6);
}

TEST(Unique, Vector_String){
  std::vector<std::string> v{"Hello", " ", "World", "!"};
  // sp::Unique<std::vector<std::string>> unique(new std::vector<std::string>{"Hello", " ", "World", "!"});
  sp::Unique<std::vector<std::string>> unique = sp::makeUnique<std::vector<std::string>>(v);
  std::string str = "";
  for(std::size_t i = 0; i < unique->size(); ++i){
    str += (*unique)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
}

TEST(Unique, Vector_Char){
  std::vector<char> v{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  // sp::Unique<std::vector<char>> unique(new std::vector<char>{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'});
  sp::Unique<std::vector<char>> unique = sp::makeUnique<std::vector<char>>(v);
  std::string str = "";
  for(std::size_t i = 0; i < unique->size(); ++i){
    str += (*unique)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
}

/**
 * Calcul de la différence d'adjacence d'éléments d'un vecteur
 * Référence: https://adventofcode.com/2023/day/9
*/
TEST(Unique, Adjacent_Difference){
  std::vector<int> v{10, 13, 16, 21, 30, 45};
  // sp::Unique<std::vector<int>> unique(new std::vector<int>({10, 13, 16, 21, 30, 45}));
  sp::Unique<std::vector<int>> unique = sp::makeUnique<std::vector<int>>(v);
  // sp::Unique<std::vector<int>> differences(new std::vector<int>(unique->size()));
  std::vector<int> v2(unique->size());
  sp::Unique<std::vector<int>> differences = sp::makeUnique<std::vector<int>>(v2);
  while(unique->size() > 1){
    std::adjacent_difference(unique->begin(), unique->end(), differences->begin());
    *differences->erase(differences->begin());
    for(std::size_t i = 0; i < unique->size()-1; ++i){
      EXPECT_TRUE((*differences)[i] == (*unique)[i+1] - (*unique)[i]);
    }
    *unique = *differences;
  }
  for(const auto& diff : *differences){
    EXPECT_TRUE(diff == 0u);
  }
}

// TEST(Shared, test){
//   sp::Shared<int> shared = new int(42);
//   sp::Shared<int> shared2 = shared;
//   sp::Shared<int> shared3;
//   {
//     shared3 = shared;
//     EXPECT_TRUE(shared.count() == 3u);
//     EXPECT_TRUE(shared2.count() == 3u);
//     EXPECT_TRUE(shared3.count() == 3u);
//     ++(*shared3);
//   }
//   EXPECT_TRUE(*shared3 == 43u);
//   EXPECT_TRUE(*shared2 == 43u);
//   EXPECT_TRUE(*shared == 43u);
//   {
//     sp::Shared<int> shared4(std::move(shared3));
//     shared4 = std::move(shared2);
//     shared4 = std::move(shared);
//   }
//   EXPECT_TRUE(shared.count() == 2u);
// }

TEST(Shared, Init){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared.exists());
  EXPECT_TRUE(shared.get() != nullptr);
  EXPECT_TRUE(*shared.get() == 42u);
}

TEST(Shared, Arrow){
  // sp::Shared<Hello> shared(new Hello());
  Hello h;
  sp::Shared<Hello> shared = sp::makeShared<Hello>(h);
  EXPECT_TRUE(shared.exists());
  shared->printMessage();
}

TEST(Shared, Copy_Constructor){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2(shared);
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared.exists());
  EXPECT_TRUE(shared2.exists());
  EXPECT_TRUE(shared.count() == 2u);
  EXPECT_TRUE(shared2.count() == 2u);
}

TEST(Shared, Move_Constructor){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2(std::move(shared));
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_FALSE(shared.exists());
  EXPECT_TRUE(shared2.exists());
  EXPECT_TRUE(shared2.count() == 1u);
}

TEST(Shared, Copy_Assignment){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2;
  shared2 = shared;
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared.exists());
  EXPECT_TRUE(shared2.exists());
  EXPECT_TRUE(shared.count() == 2u);
  EXPECT_TRUE(shared2.count() == 2u);
}

TEST(Shared, Move_Assignment){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2;
  shared2 = std::move(shared);
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(shared2.exists());
  EXPECT_TRUE(shared2.count() == 1u);
}

TEST(Shared, nullptr_){
  sp::Shared<int> shared;
  sp::Shared<int> shared2;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared.exists());
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2.exists());
}

TEST(Shared, nullptr_Copy_Assignement){
  sp::Shared<int> shared;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared.exists());
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2.exists());
}

TEST(Shared, nullptr_Move_Assignment){
  sp::Shared<int> shared;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared.exists());
  sp::Shared<int> shared2 = std::move(shared);
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2.exists());
}

TEST(Shared, Simple_Operation){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  EXPECT_TRUE(shared.exists());
  EXPECT_TRUE(shared.count() == 1u);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared2.exists());
  EXPECT_TRUE(shared2.count() == 2u);
  EXPECT_TRUE(shared.count() == 2u);
  EXPECT_TRUE(*shared == 42);
  EXPECT_TRUE(*shared2 == 42);
  *shared += 1;
  EXPECT_TRUE(*shared == 43);
  EXPECT_TRUE(*shared2 == 43);
  *shared2 /= 43;
  EXPECT_TRUE(*shared == 1);
  EXPECT_TRUE(*shared2 == 1);
  *shared *= 42;
  EXPECT_TRUE(*shared == 42);
  EXPECT_TRUE(*shared2 == 42);
  *shared2 -= 42;
  EXPECT_TRUE(*shared == 0);
  EXPECT_TRUE(*shared2 == 0);
  *shared = 2;
  EXPECT_TRUE(*shared == 2);
  EXPECT_TRUE(*shared2 == 2);
}

TEST(Shared, get){
  // sp::Shared<int> shared(new int(42));
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared.get() == shared2.get());
  EXPECT_TRUE(shared.get() != nullptr);
  EXPECT_TRUE(shared2.get() != nullptr);
}

TEST(Exemple, Exemple){
  // sp::Unique<int> unique(new int(0));
  auto unique = sp::makeUnique<int>(0);

  if(unique){
    ++(*unique);
  }

  EXPECT_TRUE(*unique == 1u);

  unique.reset();

  EXPECT_FALSE(unique);

  sp::Shared<int> shared = sp::makeShared<int>(42);
  // EXPECT_TRUE(*shared == 42);

  if(shared.exists()){
    EXPECT_EQ(*shared, 42u);
  }

  sp::Weak<int> weak1(shared);
  {
    auto tmp = weak1.lock();
    EXPECT_TRUE(tmp.exists());
    (*tmp) /= 2;
    EXPECT_TRUE(*tmp == 21);
  }

  shared = sp::makeShared<int>(1337);
  sp::Weak<int> weak2(shared);
  {
    auto tmp = weak1.lock();
    EXPECT_FALSE(tmp.exists());
    
    tmp = weak2.lock();
    EXPECT_TRUE(*tmp == 1337u);
  }
}

// TEST(t,t){
//   std::vector<int> v{1, 2, 3};
//   sp::Unique<std::vector<int>> t = sp::makeUnique<std::vector<int>>(v);
//   sp::Unique<std::vector<int>> t2 = sp::makeUnique<std::vector<int>>(std::move(t));
//   sp::Unique<std::vector<int>> t3 = std::move(t2);
// }

TEST(Weak, Lock){
  sp::Weak<int> weak;
  EXPECT_FALSE(weak.lock());
}

TEST(Weak, Lock_True){
  sp::Shared<int> shared = sp::makeShared<int>(1);
  sp::Weak<int> weak(shared);
  EXPECT_TRUE(weak.lock());
  weak.reset();
  EXPECT_FALSE(weak.lock());
}

TEST(Weak, Copy_Constructor){
  sp::Shared<int> shared = sp::makeShared<int>(1);
  sp::Weak<int> weak(shared);
  sp::Weak<int> weak2(weak);
  EXPECT_TRUE(weak.lock());
  EXPECT_TRUE(weak2.lock());
  auto tmp = weak.lock();
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(*tmp, 1u);
  auto tmp2 = weak2.lock();
  EXPECT_EQ(tmp2.count(), 3u);
  EXPECT_EQ(*tmp2, 1u);
}

TEST(Weak, Move_Construtor){
  sp::Shared<int> shared = sp::makeShared<int>(1);
  sp::Weak<int> weak(shared);
  sp::Weak<int> weak2(std::move(weak));
  EXPECT_FALSE(weak.lock());
  EXPECT_TRUE(weak2.lock());
}

TEST(Weak, Copy_Assignment){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Shared<int> sp2 = sp::makeShared<int>(2);
  sp::Weak<int> wp1(sp1);
  sp::Weak<int> wp2(sp2);
  sp::Weak<int> wp3;
  wp3 = wp1;
  EXPECT_TRUE(wp1.lock());
  EXPECT_TRUE(wp3.lock());
  wp3 = wp2;
  EXPECT_TRUE(wp2.lock());
  EXPECT_TRUE(wp3.lock());
}

TEST(Weak, Move_Assignment){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Shared<int> sp2 = sp::makeShared<int>(1);
  sp::Weak<int> wp1(sp1);
  sp::Weak<int> wp2(sp1);
  sp::Weak<int> wp3;
  wp3 = std::move(wp1);
  EXPECT_FALSE(wp1.lock());
  EXPECT_TRUE(wp3.lock());
  wp3 = std::move(wp2);
  EXPECT_FALSE(wp2.lock());
  EXPECT_TRUE(wp3.lock());
}

TEST(Weak, Reset){
   sp::Shared<int> sp1 = sp::makeShared<int>(1);
    sp::Weak<int> wp(sp1);
    {
        auto sp2 = wp.lock();
        EXPECT_TRUE(sp2);
    }
    sp1.reset();
    EXPECT_FALSE(wp.lock());
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
