#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <iostream>
#include <vector>

#include <span>
#include <string_view>
#include <tts/tts.hpp>

std::vector<std::string_view>
split_by(std::string_view s, char by)
{
  std::vector<std::string_view> res;
  std::string_view::iterator    last = s.begin();

  auto maybe_add_a_string = [&](std::string_view::iterator it) {
    // skipping empty
    if( it != last ) res.push_back({last, it});
  };

  // arm has weird char type, so we cast.
  std::span<const std::uint8_t> us{ (const std::uint8_t*) s.data(), s.size() };

  eve::algo::for_each_selected(
      us,
      [&](auto x) { return x == (std::uint8_t)by; },
      [&](std::span<const std::uint8_t>::iterator us_it)
      {
        auto it = s.begin() + (us_it - us.begin());
        maybe_add_a_string(it);
        last = it + 1;
        return false;  // return true here if you want to break.
      });
  maybe_add_a_string(s.end());

  return res;
}

int
main()
{
  std::string_view in = "Words shall be    split   !";
  std::cout << " -> in    = "
            << in
            << "\n";
  std::cout << " -> split = "
            << tts::as_string(split_by(in, ' '))
            << "\n";
}
