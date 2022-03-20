// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#ifndef INCLUDE_STACK_2_HPP_
#define INCLUDE_STACK_2_HPP_

#include <utility>
#include <stdexcept>

template <typename T>
class Stack_2 {
 private:
  stack_ex<T> *my_stack = nullptr;

 public:
  Stack_2() = default;
  Stack_2(Stack_2&& obj) noexcept = default;
  explicit Stack_2(const Stack_2& obj) = delete;
  explicit Stack_2(T&& value);
  explicit Stack_2(const T& value) = delete;

  auto operator=(Stack_2&& obj) noexcept -> Stack_2& = default;
  auto operator=(const Stack_2& obj) = delete;

 public:
  template <typename ... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();

  ~Stack_2();
};

template <typename T>
Stack_2<T>::Stack_2(T&& value) {
  this->push(std::move(value));
}

template <typename T>
template <typename ... Args>
void Stack_2<T>::push_emplace(Args&&... value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::runtime_error("Wrong type of value");
  }

  auto new_prev = my_stack;
  my_stack = new stack_ex<T>;
  my_stack->prev_addr = new_prev;
  my_stack->value = {std::forward<Args>(value) ...};
}

template <typename T>
void Stack_2<T>::push(T&& value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::runtime_error("Wrong type of value");
  }

  auto new_prev = my_stack;
  my_stack = new stack_ex<T>;
  my_stack->prev_addr = new_prev;
  my_stack->value = std::move(value);
}

template <typename T>
T Stack_2<T>::pop() {
  auto this_adr = my_stack;
  auto this_value = std::move(my_stack->value);
  my_stack = my_stack->prev_addr;
  delete this_adr;
  return this_value;
}

template <typename T>
const T& Stack_2<T>::head() const {
  return my_stack->value;
}

template <typename T>
Stack_2<T>::~Stack_2() {
  while (my_stack) {
    this->pop();
  }
}

#endif  // INCLUDE_STACK_2_HPP_
