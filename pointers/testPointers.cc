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
  sp::Unique<int> unique(new int(42));
  EXPECT_TRUE(*unique == 42u);
  EXPECT_TRUE(unique.exists());
  EXPECT_TRUE(unique.get() != nullptr);
  EXPECT_TRUE(*unique.get() == 42u);
}

TEST(Unique, Arrow){
  sp::Unique<Hello> unique(new Hello());
  EXPECT_TRUE(unique.exists());
  unique->printMessage();
}

TEST(Unique, Move_Constructor){
  sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique2(std::move(unique));
  EXPECT_TRUE(*unique2 == 42u);
  EXPECT_FALSE(unique.exists());
  EXPECT_TRUE(unique2.exists());
}

TEST(Unique, Move_Assignement){
  sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique2;
  unique2 = std::move(unique);
  EXPECT_TRUE(*unique2 == 42u);
  EXPECT_FALSE(unique.exists());
  EXPECT_TRUE(unique2.exists());
}

TEST(Unique, Simple_Operation){
  sp::Unique<int> unique(new int(42));
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
  sp::Unique<int> unique(new int(42));
  sp::Unique<int> unique2(new int(42));
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
  sp::Unique<bool> unique(new bool(true));
  sp::Unique<bool> unique2(new bool(false));
  EXPECT_TRUE(*unique || *unique2);
  EXPECT_TRUE(*unique || *unique);
  EXPECT_FALSE(*unique2 || *unique2);
}

TEST(Unique, Logical_And_Operation){
  sp::Unique<bool> unique(new bool(true));
  sp::Unique<bool> unique2(new bool(false));
  EXPECT_FALSE(*unique && *unique2);
  EXPECT_TRUE(*unique && *unique);
  EXPECT_FALSE(*unique2 && *unique2);
}

TEST(Unique, Logical_Not_Operation){
  sp::Unique<bool> unique(new bool(true));
  sp::Unique<bool> unique2(new bool(false));
  EXPECT_FALSE(!*unique);
  EXPECT_TRUE(!*unique2);
}

TEST(Unique, Logical_XOR_Operation){
  sp::Unique<bool> unique(new bool(true));
  sp::Unique<bool> unique2(new bool(false));
  EXPECT_TRUE(*unique ^ *unique2);
  EXPECT_FALSE(*unique ^ *unique);
  EXPECT_FALSE(*unique2 ^ *unique2);
}

TEST(Unique, Multiple_Logical_Operation){
  sp::Unique<bool> unique(new bool(true));
  sp::Unique<bool> unique2(new bool(false));
  EXPECT_TRUE((*unique || *unique2) && (*unique ^ *unique2));
}

TEST(Unique, iMAX){
  sp::Unique<int> unique(new int(INT_MAX));
  EXPECT_TRUE(*unique == INT_MAX);
  ++(*unique);
  EXPECT_TRUE(*unique == INT_MIN);
}

TEST(Unique, iMIN){
  sp::Unique<int> unique(new int(INT_MIN));
  EXPECT_TRUE(*unique == INT_MIN);
  --(*unique);
  EXPECT_TRUE(*unique == INT_MAX);
}

TEST(Unique, Pow){
  sp::Unique<int> unique(new int(2));
  *unique = pow(*unique, 10);
  EXPECT_TRUE(*unique == 1024);
}

TEST(Unique, String){
  sp::Unique<std::string> unique(new std::string("Hello"));
  EXPECT_TRUE(*unique == "Hello");
  *unique += " World!";
  EXPECT_TRUE(*unique == "Hello World!");
}

TEST(Unique, Char){
  sp::Unique<char> unique(new char('a'));
  EXPECT_TRUE(*unique == 'a');
  ++(*unique);
  EXPECT_TRUE(*unique == 'b');
}

TEST(Unique, Vector_Int){
  sp::Unique<std::vector<int>> unique(new std::vector<int>{1, 2, 3});
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
  sp::Unique<std::vector<std::string>> unique(new std::vector<std::string>{"Hello", " ", "World", "!"});
  std::string str = "";
  for(std::size_t i = 0; i < unique->size(); ++i){
    str += (*unique)[i];
  }
  EXPECT_TRUE(str == "Hello World!");
}

TEST(Unique, Vector_Char){
  sp::Unique<std::vector<char>> unique(new std::vector<char>{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'});
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
  sp::Unique<std::vector<int>> unique(new std::vector<int>({10, 13, 16, 21, 30, 45}));
  sp::Unique<std::vector<int>> differences(new std::vector<int>(unique->size()));
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

TEST(Exemple, Exemple){
  sp::Unique<int> unique(new int(0));
  ++(*unique);
  EXPECT_TRUE(*unique == 1u);

  sp::Shared<int> shared(new int(42));
  EXPECT_TRUE(*shared == 42);

//   sp::Weak<int> weak1(shared);
//   {
//     auto tmp = weak1.lock();
//     EXPECT_TRUE(tmp.exists());
//     (*tmp) /= 2;
//     EXPECT_TRUE(*tmp == 21);
//   }

//   shared = sp::Shared<int>(new int(1337));
//   sp::Weak<int> weak2(shared);
//   {
//     auto tmp = weak1.lock();
//     EXPECT_FALSE(tmp.exists());
    
//     tmp = weak2.lock();
//     EXPECT_TRUE(*tmp == 1337u);
//   }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
