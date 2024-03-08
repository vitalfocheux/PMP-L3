#include <gtest/gtest.h>

#include "Any.h"
#include "Optional.h"

#include <cmath>
#include <vector>

/**
 * By defining the variable NON_COPYABLE, it enables tests related to 
 * handling non-copyable objects with voc::Optional. The issue is that 
 * I didn't have time to handle this case, but thanks to the structure 
 * voc::is_copyable<T>::value, which allows determining if an object is 
 * copyable, I could have managed this case.
*/

// #define NON_COPYABLE

namespace {

  voc::Optional<double> my_sqrt(double value) {
    if (value < 0) {
      return voc::Optional<double>();
    }
    return voc::Optional<double>(std::sqrt(value));
  }

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

voc::Optional<Point> couldCreatePoint(bool create){
  if(create){
    return voc::Optional<Point>(voc::InPlace, 42, 24);
  }
  return voc::Optional<Point>();
}

/*
 * Any
 */

TEST(AnyTest, DefaultCtor) {
  voc::Any any;
  EXPECT_FALSE(any);
}

TEST(AnyTest, ConstructorWithValue){
  voc::Any any(42);
  EXPECT_TRUE(any);
  EXPECT_EQ(voc::anyCast<int>(any), 42);
  EXPECT_EQ(any.getType(), typeid(int));
  EXPECT_TRUE(any);
}

TEST(AnyTest, CopyConstructor){
  voc::Any any(42);
  voc::Any any2(any);
  EXPECT_TRUE(any2);
  EXPECT_TRUE(any);
  EXPECT_EQ(voc::anyCast<int>(any2), 42);
  EXPECT_EQ(voc::anyCast<int>(any), 42);
  EXPECT_EQ(any2.getType(), typeid(int));
  EXPECT_EQ(any.getType(), typeid(int));
  EXPECT_TRUE(any2);
  EXPECT_TRUE(any);
}

TEST(AnyTest, MoveConstructor){
  voc::Any any(42);
  voc::Any any2(std::move(any));
  EXPECT_TRUE(any2);
  EXPECT_FALSE(any);
  EXPECT_EQ(voc::anyCast<int>(any2), 42);
  EXPECT_EQ(any2.getType(), typeid(int));
  EXPECT_TRUE(any2);
  EXPECT_FALSE(any);
}

TEST(AnyTest, CopyAssignment){
  voc::Any any(42);
  voc::Any any2;
  any2 = any;
  EXPECT_TRUE(any2);
  EXPECT_TRUE(any);
  EXPECT_EQ(voc::anyCast<int>(any2), 42);
  EXPECT_EQ(voc::anyCast<int>(any), 42);
  EXPECT_EQ(any2.getType(), typeid(int));
  EXPECT_EQ(any.getType(), typeid(int));
  EXPECT_TRUE(any2);
  EXPECT_TRUE(any);
}

TEST(AnyTest, MoveAssignment){
  voc::Any any(42);
  voc::Any any2;
  any2 = std::move(any);
  EXPECT_TRUE(any2);
  EXPECT_FALSE(any);
  EXPECT_EQ(voc::anyCast<int>(any2), 42);
  EXPECT_EQ(any2.getType(), typeid(int));
  EXPECT_TRUE(any2);
  EXPECT_FALSE(any);
}

TEST(AnyTest, ValueAssignment){
  voc::Any any;
  any = 42;
  EXPECT_TRUE(any);
  EXPECT_EQ(voc::anyCast<int>(any), 42);
  EXPECT_EQ(any.getType(), typeid(int));
  EXPECT_TRUE(any);
}

TEST(AnyTest, Hasvalue){
  voc::Any any;
  EXPECT_FALSE(any.hasValue());
  any = 42;
  EXPECT_TRUE(any.hasValue());
}

TEST(AnyTest, Get_Type){
  voc::Any any;
  EXPECT_EQ(any.getType(), typeid(void));
  EXPECT_FALSE(any);
}

TEST(AnyTest, Get_Type_Change) {
  voc::Any any = 42;
  EXPECT_EQ(any.getType(), typeid(int));
  EXPECT_TRUE(any);
  any = 3.14;
  EXPECT_EQ(any.getType(), typeid(double));
  EXPECT_TRUE(any);
}

TEST(AnyTest, AnyCastConst){
  const voc::Any any = 42;
  try{
    auto c = voc::anyCast<int>(any);
    EXPECT_EQ(c, 42);
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);  
}

TEST(AnyTest, BadAnyCastConst){
  const voc::Any any = 42;
  try{
    auto c = voc::anyCast<double>(any);
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastConstEmpty){
  const voc::Any any;
  try{
    auto c = voc::anyCast<int>(any);
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_FALSE(any);
}

TEST(AnyTest, AnyCastMove){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<int>(std::move(any));
    EXPECT_EQ(c, 42);
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastMove){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<double>(std::move(any));
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastMoveEmpty){
  voc::Any any;
  try{
    auto c = voc::anyCast<int>(std::move(any));
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_FALSE(any);
}

TEST(AnyTest, AnyCast){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<int>(any);
    EXPECT_EQ(c, 42);
  }catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCast){
  voc::Any any = 42;
  try{
    auto c = voc::anyCast<double>(any);
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastEmpty){
  voc::Any any;
  try{
    auto c = voc::anyCast<int>(any);
    EXPECT_EQ(c, 42);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_FALSE(any);
}

TEST(AnyTest, AnyCastConstPointer){
  const voc::Any any = 42;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(*c, 42);
  EXPECT_TRUE(any);  
}

TEST(AnyTest, BadAnyCastConstPointer){
  const voc::Any any = 42;
  auto c = voc::anyCast<double>(&any);
  EXPECT_EQ(c, nullptr);
  
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastConstPointerEmpty){
  const voc::Any any;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(c, nullptr);
  EXPECT_FALSE(any);
}

TEST(AnyTest, AnyCastPointer){
  voc::Any any = 42;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(*c, 42);
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastPointer){
  voc::Any any = 42;
  auto c = voc::anyCast<double>(&any);
  EXPECT_EQ(c, nullptr);
  EXPECT_TRUE(any);
}

TEST(AnyTest, BadAnyCastPointerEmpty){
  voc::Any any;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(c, nullptr);
  EXPECT_FALSE(any);
}

TEST(AnyTest, ConstructorWithString){
  voc::Any any(std::string("Hello"));
  EXPECT_EQ(any.getType(), typeid(std::string));
  EXPECT_TRUE(any);
}

TEST(AnyTest, ConstructorWithVector){
  voc::Any any(std::vector<int>{1, 2, 3});
  try{
    auto c = voc::anyCast<std::vector<int>>(any);
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c[0], 1);
    EXPECT_EQ(c[1], 2);
    EXPECT_EQ(c[2], 3);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
  EXPECT_TRUE(any);
  EXPECT_EQ(any.getType(), typeid(std::vector<int>));
}

TEST(AnyTest, CopyAssignmentOfAny){
  voc::Any any = 42;
  voc::Any any2;
  any2 = any;
  try{
    auto c = voc::anyCast<int>(any2);
    auto c2 = voc::anyCast<int>(any);
    EXPECT_EQ(c, 42);
    EXPECT_EQ(c2, 42);
    EXPECT_EQ(c, c2);
  } catch(const std::bad_cast& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(AnyTest, Astérisque){
  voc::Any any = 42;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(*c, 42);
  EXPECT_TRUE(any);
}

TEST(AnyTest, AstérisqueEmpty){
  voc::Any any;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(c, nullptr);
  EXPECT_FALSE(any);
}

TEST(AnyTest, AstérisqueConst){
  const voc::Any any = 42;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(*c, 42);
  EXPECT_TRUE(any);
}

TEST(AnyTest, AstérisqueConstEmpty){
  const voc::Any any;
  auto c = voc::anyCast<int>(&any);
  EXPECT_EQ(c, nullptr);
  EXPECT_FALSE(any);
}

TEST(AnyTest, Clear){
  voc::Any any = 42;
  any.clear();
  EXPECT_FALSE(any);
}

TEST(AnyTest, ClearEmpty){
  voc::Any any;
  any.clear();
  EXPECT_FALSE(any);
}

/*
 * Optional
 */

TEST(OptionalTest, DefaultCtor) {
  voc::Optional<int> opt;
  EXPECT_FALSE(opt.hasValue());
}

TEST(OptionalTest, ConstructorWithValue){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt);
  EXPECT_EQ(opt.getValue(), 42);
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, CopyConstructor){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2(opt);
  EXPECT_TRUE(opt2);
  EXPECT_TRUE(opt);
  EXPECT_EQ(opt2.getValue(), 42);
  EXPECT_EQ(opt.getValue(), 42);
  EXPECT_TRUE(opt2);
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, MoveConstructor){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2(std::move(opt));
  EXPECT_TRUE(opt2);
  EXPECT_FALSE(opt);
  EXPECT_EQ(opt2.getValue(), 42);
  EXPECT_TRUE(opt2);
  EXPECT_FALSE(opt);
}

TEST(OptionalTest, CopyAssignment){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  opt2 = opt;
  EXPECT_TRUE(opt2);
  EXPECT_TRUE(opt);
  EXPECT_EQ(opt2.getValue(), 42);
  EXPECT_EQ(opt.getValue(), 42);
  EXPECT_TRUE(opt2);
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, MoveAssignment){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  opt2 = std::move(opt);
  EXPECT_TRUE(opt2);
  EXPECT_FALSE(opt);
  EXPECT_EQ(opt2.getValue(), 42);
  EXPECT_TRUE(opt2);
  EXPECT_FALSE(opt);
}

TEST(OptionalTest, ValueAssignment){
  voc::Optional<int> opt;
  opt = 42;
  EXPECT_TRUE(opt);
  EXPECT_EQ(opt.getValue(), 42);
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, GetValueEmpty){
  voc::Optional<int> opt;
  try{
    auto c = opt.getValue();
    std::cout << c << std::endl;
  }catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(OptionalTest, GetValue){
  voc::Optional<int> opt(42);
  try{
    auto c = opt.getValue();
    EXPECT_EQ(c, 42);
  }catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
}

TEST(OptionalTest, GetValueOrEmpty){
  voc::Optional<int> opt;
  auto c = opt.getValueOr(-1);
  EXPECT_EQ(c, -1);
}

TEST(OptionalTest, GetValueOr){
  voc::Optional<int> opt(42);
  auto c = opt.getValueOr(-1);
  EXPECT_EQ(c, 42);
}

TEST(OptionalTest, GetValueOrConst){
  const voc::Optional<int> opt(42);
  auto c = opt.getValueOr(-1);
  EXPECT_EQ(c, 42);
}

TEST(OptionalTest, GetValueOrConstEmpty){
  const voc::Optional<int> opt;
  auto c = opt.getValueOr(-1);
  EXPECT_EQ(c, -1);
}

TEST(OptionalTest, Astérisque){
  voc::Optional<int> opt(42);
  auto c = *opt;
  EXPECT_EQ(c, 42);
}


TEST(OptionalTest, AstérisqueConst){
  const voc::Optional<int> opt(42);
  auto c = *opt;
  EXPECT_EQ(c, 42);
}

TEST(OptionalTest, Arrow){
  voc::Optional<Point> opt(Point{42, 24});
  auto c = opt->x;
  EXPECT_EQ(c, 42);
}

TEST(OptionalTest, ArrowConst){
  const voc::Optional<Point> opt(Point{42, 24});
  auto c = opt->x;
  EXPECT_EQ(c, 42);
}

TEST(OptionalTest, EqualEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt == opt2);
}

TEST(OptionalTest, EqualLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_FALSE(opt == opt2);
}

TEST(OptionalTest, EqualLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt == opt2);
}

TEST(OptionalTest, Equal){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt == opt2);
}

TEST(OptionalTest, EqualOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt == 42);
  EXPECT_TRUE(42 == opt);
  EXPECT_FALSE(opt == 12);
  EXPECT_FALSE(12 == opt);
}

TEST(OptionalTest, NotEqualEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt != opt2);
}

TEST(OptionalTest, NotEqualLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt != opt2);
}

TEST(OptionalTest, NotEqualLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt != opt2);
}

TEST(OptionalTest, NotEqual){
  voc::Optional<int> opt(12);
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt != opt2);
  EXPECT_TRUE(opt2 != opt);
  EXPECT_FALSE(opt != opt);
}

TEST(OptionalTest, NotEqualOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_FALSE(opt != 42);
  EXPECT_FALSE(42 != opt);
  EXPECT_TRUE(opt != 12);
  EXPECT_TRUE(12 != opt);
}

TEST(OptionalTest, LessThanEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt < opt2);
  EXPECT_FALSE(opt2 < opt);
}

TEST(OptionalTest, LessThanLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt < opt2);
  EXPECT_FALSE(opt2 < opt);
}

TEST(OptionalTest, LessThanLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt < opt2);
  EXPECT_TRUE(opt2 < opt);
}

TEST(OptionalTest, LessThan){
  voc::Optional<int> opt(12);
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt < opt2);
  EXPECT_FALSE(opt2 < opt);
  EXPECT_FALSE(opt < opt);
}

TEST(OptionalTest, LessThanOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_FALSE(opt < 42);
  EXPECT_TRUE(12 < opt);
  EXPECT_TRUE(opt < 69);
  EXPECT_FALSE(69 < opt);
}

TEST(OptionalTest, LessThanOrEqualEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt <= opt2);
  EXPECT_TRUE(opt2 <= opt);
}

TEST(OptionalTest, LessThanOrEqualLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt <= opt2);
  EXPECT_FALSE(opt2 <= opt);
}

TEST(OptionalTest, LessThanOrEqualLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt <= opt2);
  EXPECT_TRUE(opt2 <= opt);
}

TEST(OptionalTest, LessThanOrEqual){
  voc::Optional<int> opt(12);
  voc::Optional<int> opt2(42);
  EXPECT_TRUE(opt <= opt2);
  EXPECT_FALSE(opt2 <= opt);
  EXPECT_TRUE(opt <= opt);
}

TEST(OptionalTest, LessThanOrEqualOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt <= 42);
  EXPECT_TRUE(12 <= opt);
  EXPECT_TRUE(opt <= 69);
  EXPECT_FALSE(69 <= opt);
}

TEST(OptionalTest, GreaterThanEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_FALSE(opt > opt2);
  EXPECT_FALSE(opt2 > opt);
}

TEST(OptionalTest, GreaterThanLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_FALSE(opt > opt2);
  EXPECT_TRUE(opt2 > opt);
}

TEST(OptionalTest, GreaterThanLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt > opt2);
  EXPECT_FALSE(opt2 > opt);
}

TEST(OptionalTest, GreaterThan){
  voc::Optional<int> opt(12);
  voc::Optional<int> opt2(42);
  EXPECT_FALSE(opt > opt2);
  EXPECT_TRUE(opt2 > opt);
  EXPECT_FALSE(opt > opt);
}

TEST(OptionalTest, GreaterThanOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_FALSE(opt > 42);
  EXPECT_FALSE(12 > opt);
  EXPECT_FALSE(opt > 69);
  EXPECT_TRUE(69 > opt);
}

TEST(OptionalTest, GreaterThanOrEqualEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt >= opt2);
  EXPECT_TRUE(opt2 >= opt);
}

TEST(OptionalTest, GreaterThanOrEqualLhsEmptyRhsNotEmpty){
  voc::Optional<int> opt;
  voc::Optional<int> opt2(42);
  EXPECT_FALSE(opt >= opt2);
  EXPECT_TRUE(opt2 >= opt);
}

TEST(OptionalTest, GreaterThanOrEqualLhsNotEmptyRhsEmpty){
  voc::Optional<int> opt(42);
  voc::Optional<int> opt2;
  EXPECT_TRUE(opt >= opt2);
  EXPECT_FALSE(opt2 >= opt);
}

TEST(OptionalTest, GreaterThanOrEqual){
  voc::Optional<int> opt(12);
  voc::Optional<int> opt2(42);
  EXPECT_FALSE(opt >= opt2);
  EXPECT_TRUE(opt2 >= opt);
  EXPECT_TRUE(opt >= opt);
}

TEST(OptionalTest, GreaterThanOrEqualOptWithValue){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt >= 42);
  EXPECT_FALSE(12 >= opt);
  EXPECT_FALSE(opt >= 69);
  EXPECT_TRUE(69 >= opt);
}

TEST(OptionalTest, Clear){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt);
  opt.clear();
  EXPECT_FALSE(opt);
}

TEST(OptionalTest, Hasvalue){
  voc::Optional<int> opt(42);
  EXPECT_TRUE(opt.hasValue());
  opt.clear();
  EXPECT_FALSE(opt.hasValue());
}

TEST(OptionalTest, Optional){
  voc::Optional<int> opt(42);
  voc::Optional<voc::Optional<int>> opt2(opt);
  EXPECT_TRUE(opt2);
  EXPECT_TRUE(opt);
  EXPECT_EQ(opt2.getValue(), 42);
}

#ifdef NON_COPYABLE

TEST(OptionalTest, UniquePtrCopyConstructor){
  std::unique_ptr<int> ptr = std::make_unique<int>(42);
  voc::Optional<std::unique_ptr<int>> opt(ptr);
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, UniquePtrMoveConstructor){
  std::unique_ptr<int> ptr = std::make_unique<int>(42);
  voc::Optional<std::unique_ptr<int>> opt(std::move(ptr));
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, UniquePtrCopyAssignment){
  std::unique_ptr<int> ptr = std::make_unique<int>(42);
  voc::Optional<std::unique_ptr<int>> opt;
  opt = ptr;
  EXPECT_TRUE(opt);
}

TEST(OptionalTest, UniquePtrMoveAssignment){
  std::unique_ptr<int> ptr = std::make_unique<int>(42);
  voc::Optional<std::unique_ptr<int>> opt;
  opt = std::move(ptr);
  EXPECT_TRUE(opt);
}



TEST(OptionalTest, NonCopyable){
  std::unique_ptr<int> ptr = std::make_unique<int>(42);

  std::optional<std::unique_ptr<int>> opt1 = std::make_optional(std::move(ptr));

  if (opt1.has_value()) {
    std::cout << "opt1 contient une valeur." << std::endl;
    auto p = std::move(*opt1);
    std::cout << "opt1 contient " << *p << std::endl;
    EXPECT_EQ(*p, 42);
  } else {
    std::cout << "opt1 est vide." << std::endl;
  }
}

TEST(OptionalTest, NonCopyable2){
  voc::Optional<std::unique_ptr<int>> opt1;

  {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    opt1 = voc::makeOptional(std::move(ptr));
    try{
      auto p = std::move(*opt1);
      std::cout << "opt1 contient " << *p << std::endl;
      EXPECT_EQ(*p, 42);
    } catch(const std::bad_optional_access& e){
      std::cout << e.what() << std::endl;
    }
  }

  try{
    if(opt1){
      std::cout << "opt1 contient une valeur." << std::endl;
      auto p = std::move(*opt1);
      if(p){
        std::cout << "opt1 contient " << *p << std::endl;
      }else{
        std::cout << "opt1 contient une valeur vide." << std::endl;
      }
      auto c = p.get();
      // std::cout << "opt1 contient " << *c << std::endl;
      EXPECT_EQ(c, nullptr);
    }
  } catch(const std::bad_optional_access& e){
    std::cout << e.what() << std::endl;
  }
 
}

#endif // NON_COPYABLE

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

  voc::Optional<double> opt = my_sqrt(-1.0);
  EXPECT_EQ(opt.getValueOr(-1.0), -1.0);

  opt = my_sqrt(9.0);
  EXPECT_EQ(opt.getValueOr(-1.0), 3.0);

  voc::Optional<Point> optPoint = couldCreatePoint(true);
  p = optPoint.getValue();

  EXPECT_EQ(p.x, 42);
  EXPECT_EQ(p.y, 24);

  auto opt2 = voc::makeOptional<Point>(42, 24);
  EXPECT_TRUE(p == opt2.getValue());

  EXPECT_TRUE(opt2 == optPoint);

  opt2.clear();
  EXPECT_FALSE(opt2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
