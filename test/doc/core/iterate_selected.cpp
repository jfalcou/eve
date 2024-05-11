#include <eve/module/core.hpp>

#include <iostream>
#include <vector>

void outputFor(auto l) {
  std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
  std::cout << "l: " << l << '\n';

  bool was_interupted = false;

  std::cout << "all selected: [ ";
  was_interupted = eve::iterate_selected(l,
    [](std::ptrdiff_t i) {
      std::cout << i << ' ';
      return false;
    });
  std::cout << "] was interupted: " << was_interupted << '\n';

  std::cout << "ignore first: [ ";
  was_interupted = eve::iterate_selected[eve::ignore_first(1)](l,
    [](std::ptrdiff_t i) {
      std::cout << i << ' ';
      return false;
    });
  std::cout << "] was interupted: " << was_interupted << '\n';

  std::cout << "break after second: [ ";
  was_interupted = eve::iterate_selected(l, [count = 0](std::ptrdiff_t i) mutable {
    std::cout << i << ' ';
    return ++count == 2;
  });
  std::cout << "] was interupted: " << was_interupted << '\n';
}

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;

  outputFor(eve::logical<w_t>{ true, false, true, true });
  outputFor(eve::top_bits{eve::logical<w_t>{ true, false, true, true }});
  outputFor(true);
}
