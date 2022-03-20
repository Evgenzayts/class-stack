// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#include <gtest/gtest.h>

#include <stack_1.hpp>
#include <stack_2.hpp>


class Example {
 public:
  int _one;
  int _two;
  char _three;

 public:
  Example() = default;
  Example(int one, int two, char three) : _one(one), _two(two), _three(three) {}
  Example(Example&& obj) noexcept = default;
  explicit Example(const Example& obj) = delete;

  auto operator=(Example&& obj) noexcept -> Example& = default;
  auto operator=(const Example& obj) = delete;
};


TEST(ClassStack, CopyConstr) {
  EXPECT_FALSE(std::is_copy_constructible<Stack_1<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack_2<int>>::value);
}

TEST(ClassStack, CopyAssign) {
  EXPECT_FALSE(std::is_copy_assignable<Stack_1<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack_2<int>>::value);
}

TEST(ClassStack, MoveConstr) {
  EXPECT_TRUE(std::is_move_constructible<Stack_1<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack_2<int>>::value);
}

TEST(ClassStack, MoveAssign) {
  EXPECT_TRUE(std::is_move_assignable<Stack_1<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack_2<int>>::value);
}

TEST(ClassStack, PushPop1) {
  Stack_1<int> obj(20);
  obj.push(30);
  obj.pop();
  obj.pop();
  EXPECT_EQ(&obj.head(), nullptr);
}

TEST(ClassStack, Push2) {
  Stack_2<Example> obj;
  obj.push_emplace(10, 20, 'a');
  EXPECT_EQ(obj.head()._one, 10);
  EXPECT_EQ(obj.head()._two, 20);
  EXPECT_EQ(obj.head()._three, 'a');
}

TEST(ClassStack, Pop2) {
  Example var(10, 20, 'a');
  Stack_2<Example> obj;
  obj.push(std::move(var));
  //EXPECT_EQ(obj.pop(), var);
  obj.pop();
  EXPECT_EQ(&obj.head(), nullptr);
}
