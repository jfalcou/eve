#include <eve/eve.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/load.hpp>

std::size_t strlen_example(const char* s_) {
  const auto* s = reinterpret_cast<const std::uint8_t*>(s_);
  using wide = eve::wide<std::uint8_t>;

  const wide zeroes{0};

  eve::aligned_ptr aligned_s = eve::previous_aligned_address(s);

  wide cur = eve::unsafe(eve::load)(aligned_s);
  eve::ignore_first ignore{s - aligned_s.get()};

  std::optional match = eve::first_true[ignore](cur == zeroes);

  while (!match) {
    aligned_s += wide::size();
    cur = eve::unsafe(eve::load)(aligned_s);
    match = eve::first_true(cur == zeroes);
  }

  return static_cast<std::size_t>(aligned_s.get() + *match - s);
}
