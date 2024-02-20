#include <gtest/gtest.h>

#include "Any.h"
#include "Optional.h"

/*
 * Any
 */

TEST(AnyTest, DefaultCtor) {
  voc::Any any;
  EXPECT_FALSE(any.hasValue());
}

TEST(AnyTest, Get_Type){
  voc::Any any;
  EXPECT_EQ(any.getType(), typeid(void));
}

TEST(AnyTest, Get_Type_Change) {
  voc::Any any = 42;
  EXPECT_EQ(any.getType(), typeid(int));
  any = 3.14;
  EXPECT_EQ(any.getType(), typeid(double));
}

TEST(AnyTest, AnyCast){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<char>(any);
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  // EXPECT_EQ(i, 42);
}

// /*
//  * Optional
//  */

// TEST(OptionalTest, DefaultCtor) {
//   voc::Optional<int> opt;
//   EXPECT_FALSE(opt.hasValue());
// }

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
