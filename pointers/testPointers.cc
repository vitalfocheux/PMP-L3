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

TEST(Unique, Init){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  EXPECT_TRUE(*unique == 42u);
  EXPECT_TRUE(unique);
  EXPECT_TRUE(unique.get() != nullptr);
  EXPECT_TRUE(*unique.get() == 42u);
}

TEST(Unique, Arrow){
  Hello h;
  sp::Unique<Hello> unique = sp::makeUnique<Hello>(h);
  EXPECT_TRUE(unique);
  unique->printMessage();
}

TEST(Unique, Reset){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  EXPECT_TRUE(unique);
  unique.reset();
  EXPECT_FALSE(unique);
}

TEST(Unique, Get){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  EXPECT_TRUE(unique.get() != nullptr);
  EXPECT_EQ(*(unique.get()), 42u);
  unique.reset();
  EXPECT_TRUE(unique.get() == nullptr);
}

TEST(Unique, Get_Reference){
  int *i = new int(42);
  sp::Unique<int> unique(i);
  EXPECT_TRUE(unique.get() == i);
}

TEST(Unique, Exists){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  EXPECT_TRUE(unique.exists());
  unique.reset();
  EXPECT_FALSE(unique.exists());
}

TEST(Unique, Move_Constructor){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2(std::move(unique));
  std::cout << *unique2 << std::endl;
  EXPECT_TRUE(*unique2 == 42u);
  EXPECT_FALSE(unique);
  EXPECT_TRUE(unique2);
}

TEST(Unique, Move_Assignement){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2;
  unique2 = std::move(unique);
  EXPECT_TRUE(*unique2 == 42u);
  EXPECT_FALSE(unique);
  EXPECT_TRUE(unique2);
}

TEST(Unique, Reset_And_Move_Constructor){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  unique.reset();
  sp::Unique<int> unique2(std::move(unique));
  EXPECT_FALSE(unique);
  EXPECT_FALSE(unique2);
}

TEST(Unique, Reset_And_Move_Assignment){
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  unique.reset();
  sp::Unique<int> unique2;
  unique2 = std::move(unique);
  EXPECT_FALSE(unique);
  EXPECT_FALSE(unique2);
}

TEST(Unique, Simple_Operation){
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
  sp::Unique<int> unique = sp::makeUnique<int>(42);
  sp::Unique<int> unique2 = sp::makeUnique<int>(42);
  EXPECT_TRUE(*unique == *unique2);
  EXPECT_FALSE(*unique != *unique2);
  EXPECT_FALSE(*unique < *unique2);
  EXPECT_FALSE(*unique > *unique2);
  EXPECT_TRUE(*unique <= *unique2);
  EXPECT_TRUE(*unique >= *unique2);
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, Logical_Or_Operation){
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE(*unique || *unique2);
  EXPECT_TRUE(*unique || *unique);
  EXPECT_FALSE(*unique2 || *unique2);
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, Logical_And_Operation){
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_FALSE(*unique && *unique2);
  EXPECT_TRUE(*unique && *unique);
  EXPECT_FALSE(*unique2 && *unique2);
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, Logical_Not_Operation){
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_FALSE(!*unique);
  EXPECT_TRUE(!*unique2);
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, Logical_XOR_Operation){
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE(*unique ^ *unique2);
  EXPECT_FALSE(*unique ^ *unique);
  EXPECT_FALSE(*unique2 ^ *unique2);
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, Multiple_Logical_Operation){
  sp::Unique<bool> unique = sp::makeUnique<bool>(true);
  sp::Unique<bool> unique2 = sp::makeUnique<bool>(false);
  EXPECT_TRUE((*unique || *unique2) && (*unique ^ *unique2));
  EXPECT_TRUE(unique2);
  EXPECT_TRUE(unique);
}

TEST(Unique, iMAX){
  sp::Unique<int> unique = sp::makeUnique<int>(INT_MAX);
  EXPECT_TRUE(*unique == INT_MAX);
  ++(*unique);
  EXPECT_TRUE(*unique == INT_MIN);
}

TEST(Unique, iMIN){
  sp::Unique<int> unique = sp::makeUnique<int>(INT_MIN);
  EXPECT_TRUE(*unique == INT_MIN);
  --(*unique);
  EXPECT_TRUE(*unique == INT_MAX);
}

TEST(Unique, Pow){
  sp::Unique<int> unique = sp::makeUnique<int>(2);
  *unique = pow(*unique, 10);
  EXPECT_TRUE(*unique == 1024);
  EXPECT_TRUE(unique);
}

TEST(Unique, String){
  sp::Unique<std::string> unique = sp::makeUnique<std::string>("Hello");
  EXPECT_TRUE(*unique == "Hello");
  *unique += " World!";
  EXPECT_TRUE(*unique == "Hello World!");
  EXPECT_TRUE(unique);
}

TEST(Unique, Char){
  sp::Unique<char> unique = sp::makeUnique<char>('a');
  EXPECT_TRUE(*unique == 'a');
  ++(*unique);
  EXPECT_TRUE(*unique == 'b');
  EXPECT_TRUE(unique);
}

TEST(Unique, Vector_Int){
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
  EXPECT_TRUE(unique);
}

TEST(Unique, Vector_String){
  std::vector<std::string> v{"Hello", " ", "World", "!"};
  sp::Unique<std::vector<std::string>> unique = sp::makeUnique<std::vector<std::string>>(v);
  std::string str = "";
  for(std::size_t i = 0; i < unique->size(); ++i){
    str += (*unique)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  EXPECT_TRUE(unique);
}

TEST(Unique, Vector_Char){
  std::vector<char> v{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  sp::Unique<std::vector<char>> unique = sp::makeUnique<std::vector<char>>(v);
  std::string str = "";
  for(std::size_t i = 0; i < unique->size(); ++i){
    str += (*unique)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  EXPECT_TRUE(unique);
}

/**
 * Calcul de la différence d'adjacence d'éléments d'un vecteur
 * Référence: https://adventofcode.com/2023/day/9
*/
TEST(Unique, Adjacent_Difference){
  std::vector<int> v{10, 13, 16, 21, 30, 45};
  sp::Unique<std::vector<int>> unique = sp::makeUnique<std::vector<int>>(v);
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
  EXPECT_TRUE(unique);
  EXPECT_TRUE(differences);
}

TEST(Shared, Init){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared.get() != nullptr);
  EXPECT_TRUE(*shared.get() == 42u);
}

TEST(Shared, Arrow){
  Hello h;
  sp::Shared<Hello> shared = sp::makeShared<Hello>(h);
  EXPECT_TRUE(shared);
  shared->printMessage();
}

TEST(Shared, Copy_Constructor){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2(shared);
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared.count() == 2u);
  EXPECT_TRUE(shared2.count() == 2u);
}

TEST(Shared, Move_Constructor){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2(std::move(shared));
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_FALSE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared2.count() == 1u);
}

TEST(Shared, Copy_Assignment){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2;
  shared2 = shared;
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(*shared == 42u);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared.count() == 2u);
  EXPECT_TRUE(shared2.count() == 2u);
}

TEST(Shared, Move_Assignment){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2;
  shared2 = std::move(shared);
  EXPECT_TRUE(*shared2 == 42u);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared2.count() == 1u);
}

TEST(Shared, nullptr_){
  sp::Shared<int> shared;
  sp::Shared<int> shared2;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared);
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2);
}

TEST(Shared, nullptr_Copy_Assignement){
  sp::Shared<int> shared;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2);
}

TEST(Shared, nullptr_Move_Assignment){
  sp::Shared<int> shared;
  EXPECT_TRUE(shared.count() == 0u);
  EXPECT_FALSE(shared);
  sp::Shared<int> shared2 = std::move(shared);
  EXPECT_TRUE(shared2.count() == 0u);
  EXPECT_FALSE(shared2);
}

TEST(Shared, Simple_Operation){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared.count() == 1u);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared2);
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
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
}

TEST(Shared, Logical_Operation){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2 = sp::makeShared<int>(42);
  EXPECT_TRUE(*shared == *shared2);
  EXPECT_FALSE(*shared != *shared2);
  EXPECT_FALSE(*shared < *shared2);
  EXPECT_FALSE(*shared > *shared2);
  EXPECT_TRUE(*shared <= *shared2);
  EXPECT_TRUE(*shared >= *shared2);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Logical_Or_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  EXPECT_TRUE(*shared || *shared2);
  EXPECT_TRUE(*shared || *shared);
  EXPECT_FALSE(*shared2 || *shared2);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Logical_And_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  EXPECT_FALSE(*shared && *shared2);
  EXPECT_TRUE(*shared && *shared);
  EXPECT_FALSE(*shared2 && *shared2);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Logical_Not_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  EXPECT_FALSE(!*shared);
  EXPECT_TRUE(!*shared2);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Logical_XOR_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  EXPECT_TRUE(*shared ^ *shared2);
  EXPECT_FALSE(*shared ^ *shared);
  EXPECT_FALSE(*shared2 ^ *shared2);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Multiple_Logical_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  EXPECT_TRUE((*shared || *shared2) && (*shared ^ *shared2));
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 1u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Pow){
  sp::Shared<int> shared = sp::makeShared<int>(2);
  sp::Shared<int> shared2 = shared;
  *shared = pow(*shared, 10);
  EXPECT_TRUE(*shared == 1024);
  EXPECT_TRUE(*shared2 == 1024);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, String){
  sp::Shared<std::string> shared = sp::makeShared<std::string>("Hello");
  sp::Shared<std::string> shared2 = shared;
  EXPECT_TRUE(*shared == "Hello");
  EXPECT_TRUE(*shared2 == "Hello");
  *shared += " World!";
  EXPECT_TRUE(*shared == "Hello World!");
  EXPECT_TRUE(*shared2 == "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, Char){
  sp::Shared<char> shared = sp::makeShared<char>('a');
  sp::Shared<char> shared2 = shared;
  EXPECT_TRUE(*shared == 'a');
  EXPECT_TRUE(*shared2 == 'a');
  ++(*shared);
  EXPECT_TRUE(*shared == 'b');
  EXPECT_TRUE(*shared2 == 'b');
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, Vector_Int){
  std::vector<int> v{1,2,3};
  sp::Shared<std::vector<int>> shared = sp::makeShared<std::vector<int>>(v);
  sp::Shared<std::vector<int>> shared2 = shared;
  EXPECT_TRUE((*shared)[0] == 1);
  EXPECT_TRUE((*shared)[1] == 2);
  EXPECT_TRUE((*shared)[2] == 3);
  EXPECT_TRUE((*shared2)[0] == 1);
  EXPECT_TRUE((*shared2)[1] == 2);
  EXPECT_TRUE((*shared2)[2] == 3);
  (*shared)[0] = 4;
  (*shared)[1] = 5;
  (*shared)[2] = 6;
  EXPECT_TRUE((*shared)[0] == 4);
  EXPECT_TRUE((*shared)[1] == 5);
  EXPECT_TRUE((*shared)[2] == 6);
  EXPECT_TRUE((*shared2)[0] == 4);
  EXPECT_TRUE((*shared2)[1] == 5);
  EXPECT_TRUE((*shared2)[2] == 6);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, Vector_String){
  std::vector<std::string> v{"Hello", " ", "World", "!"};
  sp::Shared<std::vector<std::string>> shared = sp::makeShared<std::vector<std::string>>(v);
  sp::Shared<std::vector<std::string>> shared2 = shared;
  std::string str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared2)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, Vector_Char){
  std::vector<char> v{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  sp::Shared<std::vector<char>> shared = sp::makeShared<std::vector<char>>(v);
  sp::Shared<std::vector<char>> shared2 = shared;
  std::string str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared2)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
}

TEST(Shared, Get){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared.get() == shared2.get());
  EXPECT_TRUE(shared.get() != nullptr);
  EXPECT_TRUE(shared2.get() != nullptr);
  EXPECT_EQ(*shared.get(), 42u);
  EXPECT_EQ(*shared2.get(), 42u);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
}

TEST(Shared, Get_Reference){
  int *i = new int(42);
  sp::Shared<int> shared(i);
  sp::Shared<int> shared2(shared);
  EXPECT_EQ(shared.get(), shared2.get());
  EXPECT_EQ(shared.get(), i);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
}

TEST(Shared, Reset){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Shared<int> shared2 = shared;
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  shared.reset();
  EXPECT_FALSE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_EQ(shared.count(), 0u);
  EXPECT_EQ(shared2.count(), 1u);
}

TEST(Shared, Reset_And_Copy_Constructor){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  shared.reset();
  sp::Shared<int> shared2(shared);
  EXPECT_FALSE(shared);
  EXPECT_FALSE(shared2);
}

TEST(Shared, Reset_And_Move_Constructor){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  shared.reset();
  sp::Shared<int> shared2(std::move(shared));
  EXPECT_FALSE(shared);
  EXPECT_FALSE(shared2);
}

TEST(Shared, Reset_And_Copy_Assignment){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  shared.reset();
  sp::Shared<int> shared2;
  shared2 = shared;
  EXPECT_FALSE(shared);
  EXPECT_FALSE(shared2);
}

TEST(Shared, Reset_And_Move_Assignment){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  shared.reset();
  sp::Shared<int> shared2;
  shared2 = std::move(shared);
  EXPECT_FALSE(shared);
  EXPECT_FALSE(shared2);
}

TEST(Exemple, Exemple){
  auto unique = sp::makeUnique<int>(0);

  if(unique){
    ++(*unique);
  }

  EXPECT_TRUE(*unique == 1u);

  unique.reset();

  EXPECT_FALSE(unique);

  sp::Shared<int> shared = sp::makeShared<int>(42);

  if(shared.exists()){
    EXPECT_EQ(*shared, 42u);
  }

  sp::Weak<int> weak1(shared);
  {
    auto tmp = weak1.lock();
    EXPECT_TRUE(tmp);
    (*tmp) /= 2;
    EXPECT_TRUE(*tmp == 21);
  }

  shared = sp::makeShared<int>(1337);
  sp::Weak<int> weak2(shared);
  {
    auto tmp = weak1.lock();
    EXPECT_FALSE(tmp);
    
    tmp = weak2.lock();
    EXPECT_TRUE(*tmp == 1337u);
  }
}

TEST(Weak, Lock_False){
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

TEST(Weak, Reset_Shared){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);
  {
    auto sp2 = wp.lock();
    EXPECT_TRUE(sp2);
    EXPECT_EQ(sp2.count(), 2u);
    EXPECT_EQ(*sp2, 1u);
  }
  sp1.reset();
  EXPECT_FALSE(wp.lock());
}

TEST(Weak, Reset_Weak){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);
  wp.reset();
  EXPECT_FALSE(wp.lock());
}

TEST(Weak, Reset_Weak_And_Copy_Constructor){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);  
  wp.reset();
  sp::Weak<int> wp2(wp);
  EXPECT_FALSE(wp.lock());
  EXPECT_FALSE(wp2.lock());
}

TEST(Weak, Reset_Weak_And_Move_Constructor){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);  
  wp.reset();
  sp::Weak<int> wp2(std::move(wp));
  EXPECT_FALSE(wp.lock());
  EXPECT_FALSE(wp2.lock());
}

TEST(Weak, Reset_Weak_And_Copy_Assignment){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);  
  wp.reset();
  sp::Weak<int> wp2;
  wp2 = wp;
  EXPECT_FALSE(wp.lock());
  EXPECT_FALSE(wp2.lock());
}

TEST(Weak, Reset_Weak_And_Move_Assignment){
  sp::Shared<int> sp1 = sp::makeShared<int>(1);
  sp::Weak<int> wp(sp1);  
  wp.reset();
  sp::Weak<int> wp2;
  wp2 = std::move(wp);
  EXPECT_FALSE(wp.lock());
  EXPECT_FALSE(wp2.lock());
}

TEST(Weak, Arrow){
  Hello h;
  sp::Shared<Hello> shared = sp::makeShared<Hello>(h);
  sp::Weak<Hello> weak(shared);
  auto tmp = weak.lock();
  EXPECT_TRUE(tmp);
  weak.lock()->printMessage();
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Get){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Weak<int> weak(shared);
  auto tmp = weak.lock();
  EXPECT_EQ(tmp.get(), shared.get());
  EXPECT_NE(tmp.get(), nullptr);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Get_Reference){
  int *i = new int(42);
  sp::Shared<int> shared(i);
  sp::Weak<int> weak(shared);
  auto tmp = weak.lock();
  EXPECT_EQ(tmp.get(), shared.get());
  EXPECT_EQ(tmp.get(), i);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Simple_Operation){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Weak<int> weak(shared);
  auto tmp = weak.lock();
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(shared);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_TRUE(*tmp == 42);
  *tmp += 1;
  EXPECT_TRUE(*tmp == 43);
  EXPECT_TRUE(*shared == 43);
  *tmp /= 43;
  EXPECT_TRUE(*tmp == 1);
  EXPECT_TRUE(*shared == 1);
  *tmp *= 42;
  EXPECT_TRUE(*tmp == 42);
  EXPECT_TRUE(*shared == 42);
  *tmp -= 42;
  EXPECT_TRUE(*tmp == 0);
  EXPECT_TRUE(*shared == 0);
  *tmp = 2;
  EXPECT_TRUE(*tmp == 2);
  EXPECT_TRUE(*shared == 2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Logical_Operation){
  sp::Shared<int> shared = sp::makeShared<int>(42);
  sp::Weak<int> weak(shared);
  sp::Weak<int> weak2(shared);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_TRUE(*tmp == *tmp2);
  EXPECT_FALSE(*tmp != *tmp2);
  EXPECT_FALSE(*tmp < *tmp2);
  EXPECT_FALSE(*tmp > *tmp2);
  EXPECT_TRUE(*tmp <= *tmp2);
  EXPECT_TRUE(*tmp >= *tmp2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 3u);
  EXPECT_EQ(tmp.count(), 3u);
  EXPECT_EQ(tmp2.count(), 3u);
}

TEST(Weak, Logical_Or_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  sp::Weak<bool> weak(shared);
  sp::Weak<bool> weak2(shared2);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_TRUE(*tmp || *tmp2);
  EXPECT_TRUE(*tmp || *tmp);
  EXPECT_FALSE(*tmp2 || *tmp2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(tmp2.count(), 2u);
}

TEST(Weak, Logical_And_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  sp::Weak<bool> weak(shared);
  sp::Weak<bool> weak2(shared2);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_FALSE(*tmp && *tmp2);
  EXPECT_TRUE(*tmp && *tmp);
  EXPECT_FALSE(*tmp2 && *tmp2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(tmp2.count(), 2u);
}

TEST(Weak, Logical_Not_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  sp::Weak<bool> weak(shared);
  sp::Weak<bool> weak2(shared2);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_FALSE(!*tmp);
  EXPECT_TRUE(!*tmp2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(tmp2.count(), 2u);
}

TEST(Weak, Logical_XOR_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  sp::Weak<bool> weak(shared);
  sp::Weak<bool> weak2(shared2);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_TRUE(*tmp ^ *tmp2);
  EXPECT_FALSE(*tmp ^ *tmp);
  EXPECT_FALSE(*tmp2 ^ *tmp2);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(tmp2.count(), 2u);
}

TEST(Weak, Multiple_Logical_Operation){
  sp::Shared<bool> shared = sp::makeShared<bool>(true);
  sp::Shared<bool> shared2 = sp::makeShared<bool>(false);
  sp::Weak<bool> weak(shared);
  sp::Weak<bool> weak2(shared2);
  auto tmp = weak.lock();
  auto tmp2 = weak2.lock();
  EXPECT_TRUE((*tmp || *tmp2) && (*tmp ^ *tmp2));
  EXPECT_TRUE(shared);
  EXPECT_TRUE(shared2);
  EXPECT_TRUE(tmp);
  EXPECT_TRUE(tmp2);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(shared2.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
  EXPECT_EQ(tmp2.count(), 2u);
}

TEST(Weak, Pow){
  sp::Shared<int> shared = sp::makeShared<int>(2);
  sp::Weak<int> weak(shared);
  auto tmp = weak.lock();
  *tmp = pow(*tmp, 10);
  EXPECT_TRUE(*tmp == 1024);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, String){
  sp::Shared<std::string> shared = sp::makeShared<std::string>("Hello");
  sp::Weak<std::string> weak(shared);
  auto tmp = weak.lock();
  EXPECT_EQ(*tmp, "Hello");
  *tmp += " World!";
  EXPECT_EQ(*tmp, "Hello World!");
  EXPECT_EQ(*shared, "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Char){
  sp::Shared<char> shared = sp::makeShared<char>('a');
  sp::Weak<char> weak(shared);
  auto tmp = weak.lock();
  EXPECT_EQ(*tmp, 'a');
  ++(*tmp);
  EXPECT_EQ(*tmp, 'b');
  EXPECT_EQ(*shared, 'b');
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Vector_Int){
  std::vector<int> v{1,2,3};
  sp::Shared<std::vector<int>> shared = sp::makeShared<std::vector<int>>(v);
  sp::Weak<std::vector<int>> weak(shared);
  auto tmp = weak.lock();
  EXPECT_EQ((*tmp)[0], 1);
  EXPECT_EQ((*tmp)[1], 2);
  EXPECT_EQ((*tmp)[2], 3);
  (*tmp)[0] = 4;
  (*tmp)[1] = 5;
  (*tmp)[2] = 6;
  EXPECT_EQ((*tmp)[0], 4);
  EXPECT_EQ((*tmp)[1], 5);
  EXPECT_EQ((*tmp)[2], 6);
  EXPECT_EQ((*shared)[0], 4);
  EXPECT_EQ((*shared)[1], 5);
  EXPECT_EQ((*shared)[2], 6);
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Vector_String){
  std::vector<std::string> v{"Hello", " ", "World", "!"};
  sp::Shared<std::vector<std::string>> shared = sp::makeShared<std::vector<std::string>>(v);
  sp::Weak<std::vector<std::string>> weak(shared);
  auto tmp = weak.lock();
  std::string str = "";
  for(std::size_t i = 0; i < tmp->size(); ++i){
    str += (*tmp)[i];
  }
  EXPECT_EQ(str, "Hello World!");
  str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared)[i];
  }
  EXPECT_EQ(str, "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}

TEST(Weak, Vector_Char){
  std::vector<char> v{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  sp::Shared<std::vector<char>> shared = sp::makeShared<std::vector<char>>(v);
  sp::Weak<std::vector<char>> weak(shared);
  auto tmp = weak.lock();
  std::string str = "";
  for(std::size_t i = 0; i < tmp->size(); ++i){
    str += (*tmp)[i];
  }
  EXPECT_EQ(str, "Hello World!");
  str = "";
  for(std::size_t i = 0; i < shared->size(); ++i){
    str += (*shared)[i];
  }
  EXPECT_EQ(str, "Hello World!");
  EXPECT_TRUE(shared);
  EXPECT_TRUE(tmp);
  EXPECT_EQ(shared.count(), 2u);
  EXPECT_EQ(tmp.count(), 2u);
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
