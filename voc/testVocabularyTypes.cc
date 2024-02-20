#include <gtest/gtest.h>

#include "Any.h"
#include "Optional.h"

#include <cmath>

namespace {

  struct Point {
    Point(int x1, int y1){
      x = x1;
      y = y1;
    }

    int x;
    int y;

    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
  };
};

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
    auto c = voc::anyCast<int>(std::move(any));
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(AnyTest, AnyCast2){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<int>(any);
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
}

// /*
//  * Optional
//  */

// TEST(OptionalTest, DefaultCtor) {
//   voc::Optional<int> opt;
//   EXPECT_FALSE(opt.hasValue());
// }

TEST(Exemple, Exemple){
  voc::Any any;
  any = 42;
  EXPECT_EQ(voc::anyCast<int>(any), 42);

  any = 3.14;
  EXPECT_EQ(voc::anyCast<double>(any), 3.14);

  any = std::string("The cake is a lie!");
  EXPECT_EQ(voc::anyCast<std::string>(any), "The cake is a lie!");

  try{
    std::cout << voc::anyCast<bool>(any) << std::endl;
  } catch (const std::exception& e){
    EXPECT_STREQ(e.what(), "std::bad_cast");
  }

  voc::Any any_inplace(voc::InPlaceType<Point>, 42, 24);
  auto p = voc::anyCast<Point>(any_inplace);

  EXPECT_EQ(p.x, 42);
  EXPECT_EQ(p.y, 24);

  auto any_cleared = voc::makeAny<Point>(42, 42);
  any_cleared.clear();
  EXPECT_FALSE(any_cleared.hasValue());

  try{
    auto point = voc::anyCast<Point>(any_cleared);
    std::cout << point.x << "x" << point.y << std::endl;
  } catch (const std::exception& e){
    EXPECT_STREQ(e.what(), "std::bad_cast");
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
