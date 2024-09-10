#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <span>
#include <vector>

#include <string_view>
#include <iostream>

std::ptrdiff_t
substring_in_string(std::string_view haystack, std::string_view needle)
{
  // NOTE: eve is not supporting `char` directly, you need to use int8_t or uint8_t
  std::span h(reinterpret_cast<const std::uint8_t *>(haystack.data()), haystack.size());
  std::span n(reinterpret_cast<const std::uint8_t *>(needle.data()), needle.size());

  auto res = eve::algo::search(h, n);
  return res - h.begin();
}

void
basic_example()
{
  std::cout << __func__ << std::endl;
  std::string_view haystack("one two three");

  std::cout << "empty: " << substring_in_string(haystack, "") << std::endl;
  std::cout << "one: " << substring_in_string(haystack, "one") << std::endl;
  std::cout << "two: " << substring_in_string(haystack, "two") << std::endl;
  std::cout << "three: " << substring_in_string(haystack, "three") << std::endl;
  std::cout << "not there: " << substring_in_string(haystack, "not there") << std::endl;

  std::cout << "<<<<<<<\n" << std::endl;
}

void
implicit_conversions()
{
  std::cout << "<<< " << __func__ << " <<<" << std::endl;

  std::vector<double>      haystack {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<std::int8_t> needle {2, 3};

  std::cout << "chars in doubles: " << (eve::algo::search(haystack, needle) - haystack.begin())
            << std::endl;

  std::cout << "<<<<<<<\n" << std::endl;
}

std::ptrdiff_t
substring_in_string_case_insensitive(std::string_view haystack, std::string_view needle)
{
  // NOTE: eve is not supporting `char` directly, you need to use int8_t or uint8_t
  std::span h(reinterpret_cast<const std::uint8_t *>(haystack.data()), haystack.size());
  std::span n(reinterpret_cast<const std::uint8_t *>(needle.data()), needle.size());

  // @the-moisrex provided this. See `case_insensitive_equals.cpp` for details.
  auto to_upper = [](eve::like<std::uint8_t> auto c)
  {
    constexpr std::uint8_t alphabet_length = 'z' - 'a';
    constexpr std::uint8_t a_A_offset      = 'a' - 'A';

    return eve::sub[(c - std::uint8_t('a')) <= alphabet_length](c, a_A_offset);
  };

  // NOTE: we could also use views::map
  return eve::algo::search(h, n, [&](auto x, auto y) { return to_upper(x) == to_upper(y); })
         - h.begin();
}

void
custom_predicates()
{
  std::cout << "<<< " << __func__ << " <<<" << std::endl;

  std::cout << "substring_in_string_case_insensitive: "
            << substring_in_string_case_insensitive("Uabc Ab", "C A") << std::endl;
  std::cout << "substring_in_string_case_insensitive: "
            << substring_in_string_case_insensitive("Uabc Ab", "Ab") << std::endl;

  std::cout << "<<<<<<<\n" << std::endl;
}

int
main()
{
  basic_example();
  implicit_conversions();
  custom_predicates();
}
