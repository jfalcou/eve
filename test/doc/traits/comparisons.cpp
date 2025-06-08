#include <iostream>
#include <eve/eve.hpp>

namespace udt
{
  struct point : kumi::tuple<int, float> {};
}

template<>  struct std::tuple_size<udt::point>       : std::integral_constant<std::size_t, 2> {};
template<>  struct std::tuple_element<0,udt::point>  { using type = int; };
template<>  struct std::tuple_element<1,udt::point>  { using type = float; };

// Specialize eve::comparisons so that only position is used for equality
template<> struct eve::comparisons<udt::point>
{
  static constexpr auto equal(auto const& o, auto const& a, auto const& b) noexcept
  {
    return eve::is_equal[o](get<0>(a),get<0>(b));
  }

  static constexpr auto not_equal(auto const& o, auto const& a, auto const& b) noexcept
  {
    return !equal(o, a, b);
  }
};

int main()
{
  eve::wide<float> a{1,2,3,4,5,6,7,8}, b{2,2,4,4,6,6,7,7};
  eve::wide<int>   i{1,2,3,4,5,6,7,8};

  eve::wide<udt::point> p1{i,a}, p2{i,b};
  std::cout << p1         << "\n";
  std::cout << p2         << "\n";
  std::cout << (p1 == p2) << "\n";
}