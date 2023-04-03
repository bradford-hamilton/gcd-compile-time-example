#include <iostream>

int gcd_func(int num1, int num2)
{
  if (num2 == 0) { return num1; }
  return gcd_func(num2, num1%num2);
}

template<int num1, int num2>
struct gcd {
  inline static constexpr int value = gcd<num2, num1%num2>::value;
};

// Covers the if (b == 0) portion of code:
template<int num1>
struct gcd <num1, 0> {
  inline static constexpr int value = num1;
};

int main() {
  // Using gcd_func
  std::cout << "gcd_func(5, 15) == " << gcd_func(5, 15) << std::endl;
  std::cout << "gcd_func(21, 31) == " << gcd_func(21, 31) << std::endl;
  std::cout << "gcd_func(6, 21) == " << gcd_func(6, 21) << std::endl;

  // Using templates
  static_assert(gcd<5, 15>::value == 5);
  static_assert(gcd<21, 31>::value == 1);
  static_assert(gcd<6, 21>::value == 3);
  
  // Compile time failure
  // static_assert(gcd<5, 15>::value == 7); // static_assert failed due to requirement 'gcd<5, 15>::value == 7'

  return 0;
}
