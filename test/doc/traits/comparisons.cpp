#include <iostream>
#include <eve/eve.hpp>

namespace udt
{
  struct point : eve::struct_support<point, int, float> {};
}

// Specialize eve::comparisons so that only position is used for equality
template<> struct eve::comparisons<udt::point>
{
  static constexpr auto equal(auto const& a, auto const& b) noexcept
  {
    return eve::is_equal(get<0>(a), get<0>(b));
  }

  static constexpr auto not_equal(auto const& a, auto const& b) noexcept
  {
    return eve::is_not_equal(get<0>(a), get<0>(b));
  }
};

int main()
{
  eve::wide<float, eve::fixed<8>> a{1.2,2.3,3.4,4.5,5.6,6.7,7.8,8.9}, b{0.2,0.2,0.4,0.4,0.6,0.6,0.7,0.7};
  eve::wide<int  , eve::fixed<8>> i{1,2,3,4,5,6,7,8};

  auto p1 = eve::zip(i,a);
  auto p2 = eve::zip(i,b);
  std::cout << p1         << "\n";
  std::cout << p2         << "\n";
  std::cout << (p1 == p2) << "\n";
}
