// Modified using smart pointer version.

/*
 * C++ Design Patterns: State
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>
#include <memory>

/*
 * State
 * defines an interface for encapsulating the behavior associated
 * with a particular state of the Context
 */
class State {
 public:
  virtual ~State() = default;
  virtual void handle() = 0;
};

/*
 * Concrete States
 * each subclass implements a behavior associated with a state
 * of the Context
 */
class ConcreteStateA : public State {
 public:
  ~ConcreteStateA() {}

  void handle() override { std::cout << "State A handled." << std::endl; }
};

class ConcreteStateB : public State {
 public:
  ~ConcreteStateB() {}

  void handle() override { std::cout << "State B handled." << std::endl; }
};

/*
 * Context
 * defines the interface of interest to clients
 */
class Context {
 public:
  Context() : state(nullptr) {}
  ~Context() {}
  void request() { state->handle(); }
  void setState(std::unique_ptr<State> s) {
    if (state) {
      state.release();
    }
    state = std::move(s);
  }

 private:
  std::unique_ptr<State> state;
};

int main() {
  std::unique_ptr<Context> ptr = std::make_unique<Context>();
  ptr->setState(std::make_unique<ConcreteStateA>());
  ptr->request();
  ptr->setState(std::make_unique<ConcreteStateB>());
  ptr->request();

  return 0;
}