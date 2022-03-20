// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include <utility>

template <typename T>
struct stack_ex{
  T value;
  stack_ex* prev_addr;
};

template <typename T>
class Stack_1 {
 private:
  stack_ex<T> *my_stack = nullptr;

 public:
  Stack_1() = default;
  Stack_1(Stack_1<T>&& obj) noexcept = default;
  explicit Stack_1(const Stack_1<T>& obj) = delete;
  explicit Stack_1(T&& value);
  explicit Stack_1(const T& value);

  auto operator=(Stack_1<T>&& obj) noexcept -> Stack_1& = default;
  auto operator=(const Stack_1<T>& obj) = delete;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

  ~Stack_1();
};

template <typename T>
Stack_1<T>::Stack_1(T&& value) {
  this->push(std::move(value));
}

template <typename T>
Stack_1<T>::Stack_1(const T& value) {
  this->push(value);
}

template <typename T>
void Stack_1<T>::push(T&& value) {
  auto prev_adr = my_stack;
  my_stack = new stack_ex<T>();
  my_stack->prev_addr = prev_adr;
  my_stack->value = std::move(value);
}

template <typename T>
void Stack_1<T>::push(const T& value) {
  auto prev_adr = my_stack;
  my_stack = new stack_ex<T>;
  my_stack->prev_addr = prev_adr;
  my_stack->value = value;
}

template <typename T>
void Stack_1<T>::pop() {
  auto this_adr = my_stack;
  my_stack = my_stack->prev_addr;
  delete this_adr;
}

template <typename T>
const T& Stack_1<T>::head() const {
  return my_stack->value;
}

template <typename T>
Stack_1<T>::~Stack_1() {
  while(my_stack) {
    this->pop();
  }
}

#endif  // INCLUDE_STACK_HPP_
