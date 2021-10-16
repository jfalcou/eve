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
      // 'a' < c < 'z' is equivalent to (c - 'a') < 26 because of the underflow
      return eve::sub[c - 'a' <= 26](c, ('a' - 'A'));
    }

  } inline constexpr our_to_upper;

  bool iequals(std::string_view a, std::string_view b)
  {
    // if they're not the same size, whay bother converting them both to uppercase and then check?
    if( a.size() != b.size() )
      return false;

    // converting them to uint8_t; because our to upper algorithm relies on unsigned integers.
    auto *f1 = reinterpret_cast<std::uint8_t const *>(a.begin());
    auto *l1 = reinterpret_cast<std::uint8_t const *>(a.end());
    auto *f2 = reinterpret_cast<std::uint8_t const *>(b.begin());

    return eve::algo::equal(eve::algo::as_range(f1, l1),
                            f2,
                            [](eve::wide<std::uint8_t> a, eve::wide<std::uint8_t> b)
                            {
                              // convert both to uppercase and then check if they're equal
                              return our_to_upper(a) == our_to_upper(b);
                            });
  }

}

TTS_CASE("IEquals, basics")
{
  TTS_EQUAL(ascii::iequals("123 One Two aZ", "123 oNe TWo Az"), true);
  TTS_EQUAL(ascii::iequals("103 One Two aZ", "123 oNe TWo Az"), false);
  TTS_EQUAL(ascii::iequals("not the same size as", "123 oNe TWo Az"), false);
  TTS_EQUAL(ascii::iequals("Short", "SHorT"), true);
};
