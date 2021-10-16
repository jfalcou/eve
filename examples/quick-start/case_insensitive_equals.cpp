#include <eve/algo/equal.hpp>
#include <eve/function/sub.hpp>

#include <cstdint>
#include <iostream>
#include <string_view>

namespace ascii
{
  struct
  {
    // This accepts both std::uint8_t and eve::wide<std::uint8_t>
    EVE_FORCEINLINE auto operator()(eve::like<std::uint8_t> auto c) const
    {
      // if C - 'a' is less than 26, then C is uppercased, otherwide it's lowercased
      return eve::sub[c - 'a' <= 26](c, ('a' - 'A'));
    }

  } inline constexpr our_to_upper;

  bool iequals(std::string_view a, std::string_view b)
  {
    using namespace eve::algo; // for eve::algo::equals and eve::algo::as_range

    // converting them to uint8_t; because our to upper algorithm relies on unsigned integers.
    auto *f1 = reinterpret_cast<std::uint8_t const *>(a.begin());
    auto *l1 = reinterpret_cast<std::uint8_t const *>(a.end());
    auto *f2 = reinterpret_cast<std::uint8_t const *>(b.begin());

    return equal(as_range(f1, l1),
                 f2,
                 [](eve::wide<std::uint8_t> a, eve::wide<std::uint8_t> b)
                 {
                   // convert both to uppercase and then check if they're equal
                   return our_to_upper(a) == our_to_upper(b);
                 });
  }

}

int
main()
{
  using namespace std;

  bool t0 = ascii::iequals("123456 onez", "123456 oneZ");
  bool t1 = ascii::iequals("123456 one", "123456 oNE");
  bool t2 = ascii::iequals("123456 two", "123456 OnE");

  cout << boolalpha  // activate printing booleans
       << t0 << '\n' // should be true
       << t1 << '\n' // should be true too
       << t2         // should be false
       << endl;

  return 0;
}
