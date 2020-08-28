/*
 * C++ Design Patterns: Abstract Factory
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
 * Product A
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */
class ProductA {
 public:
  virtual ~ProductA() {}

  virtual const char *getName() = 0;
  // ...
};

/*
 * ConcreteProductAX and ConcreteProductAY
 * define objects to be created by concrete factory
 */
class ConcreteProductAX : public ProductA {
 public:
  ~ConcreteProductAX() {}

  const char *getName() { return "A-X"; }
  // ...
};

class ConcreteProductAY : public ProductA {
 public:
  ~ConcreteProductAY() {}

  const char *getName() { return "A-Y"; }
  // ...
};

/*
 * Product B
 * same as Product A, Product B declares interface for concrete products
 * where each can produce an entire set of products
 */
class ProductB {
 public:
  virtual ~ProductB() {}

  virtual const char *getName() = 0;
  // ...
};

/*
 * ConcreteProductBX and ConcreteProductBY
 * same as previous concrete product classes
 */
class ConcreteProductBX : public ProductB {
 public:
  ~ConcreteProductBX() {}

  const char *getName() { return "B-X"; }
  // ...
};

class ConcreteProductBY : public ProductB {
 public:
  ~ConcreteProductBY() {}

  const char *getName() { return "B-Y"; }
  // ...
};

/*
 * Abstract Factory
 * provides an abstract interface for creating a family of products
 */
class AbstractFactory {
 public:
  virtual ~AbstractFactory() {}

  virtual std::unique_ptr<ProductA> createProductA() = 0;
  virtual std::unique_ptr<ProductB> createProductB() = 0;
};

/*
 * Concrete Factory X and Y
 * each concrete factory create a family of products and client uses
 * one of these factories so it never has to instantiate a product object
 */
class ConcreteFactoryX : public AbstractFactory {
 public:
  ~ConcreteFactoryX() {}

  std::unique_ptr<ProductA> createProductA() {
    return std::move(std::make_unique<ConcreteProductAX>());
  }
  std::unique_ptr<ProductB> createProductB() {
    return std::move(std::make_unique<ConcreteProductBX>());
  }
};

class ConcreteFactoryY : public AbstractFactory {
 public:
  ~ConcreteFactoryY() {}

  std::unique_ptr<ProductA> createProductA() {
    return std::move(std::make_unique<ConcreteProductAY>());
  }
  std::unique_ptr<ProductB> createProductB() {
    return std::move(std::make_unique<ConcreteProductBY>());
  }
};

int main() {
  std::unique_ptr<ConcreteFactoryX> factoryX =
      std::make_unique<ConcreteFactoryX>();
  std::unique_ptr<ConcreteFactoryY> factoryY =
      std::make_unique<ConcreteFactoryY>();

  std::cout << "Product: " << factoryX->createProductA()->getName()
            << std::endl;
  std::cout << "Product: " << factoryY->createProductA()->getName()
            << std::endl;
  std::cout << "Product: " << factoryX->createProductB()->getName()
            << std::endl;
  std::cout << "Product: " << factoryY->createProductB()->getName()
            << std::endl;

  return 0;
}
