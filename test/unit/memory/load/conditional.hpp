//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include "unit/memory/never_empty_test.hpp"
#include <eve/module/core.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>

#include <vector>

//==================================================================================================
// Calls f(c, first, last) for every relative conditional over n lanes, [first, last) being the
// kept lanes.
//==================================================================================================
template<typename F> void for_each_relative_conditional(std::ptrdiff_t n, F f)
{
  f(eve::ignore_none, 0, n);
  f(eve::ignore_all, 0, 0);

  for( std::ptrdiff_t k = 0; k <= n; ++k )
  {
    f(eve::ignore_first(k), k, n);
    f(eve::keep_last(n - k), k, n);
    f(eve::ignore_last(k), 0, n - k);
    f(eve::keep_first(n - k), 0, n - k);
  }

  for( std::ptrdiff_t first = 0; first <= n; ++first )
  {
    for( std::ptrdiff_t last = first; last <= n; ++last )
    {
      f(eve::ignore_extrema(first, n - last), first, last);
      f(eve::keep_between(first, last), first, last);
    }
  }
}

//==================================================================================================
// Loads from a page, with and without an alternative, from unaligned pointers placing the kept
// lanes at the beginning and at the end of the page, so the ignored lanes are outside of it, and
// from aligned pointers.
//==================================================================================================
template<typename W> void check_conditional_loads(W alt)
{
  using e_t                        = eve::element_type_t<W>;
  constexpr std::ptrdiff_t n      = W::size();
  constexpr std::ptrdiff_t page_n = 4096 / sizeof(e_t);

  std::vector<e_t, eve::aligned_allocator<e_t, page_n>> page(page_n);

  for( std::ptrdiff_t i = 0; i < page_n; ++i )
  {
    if constexpr( eve::logical_value<e_t> ) page[i] = (i % 3 == 0);
    else                                    page[i] = e_t(i % 100 + 1);
  }

  e_t const* begin = page.data();
  e_t const* end   = begin + page_n;

  for_each_relative_conditional(n, [&](auto c, std::ptrdiff_t first, std::ptrdiff_t last)
  {
    auto check = [&](e_t const* p, auto ptr)
    {
      W expected = [&](auto i, auto) { return (i >= first && i < last) ? p[i] : alt.get(i); };

      TTS_EQUAL(test_load[c.else_(alt)](ptr, eve::as<W> {}), expected);
      TTS_EQUAL(eve::replace_ignored(test_load[c](ptr, eve::as<W> {}), c, eve::zero),
                eve::replace_ignored(expected, c, eve::zero));
    };

    for( e_t const* p : {begin - first, end - last} ) check(p, p);

    check(begin, eve::as_aligned(begin, eve::lanes<n>));
    check(end - n, eve::as_aligned(end - n, eve::lanes<n>));
  });
}

//==================================================================================================
// When no lane is kept at runtime, nothing is read: loading from nullptr is fine.
//==================================================================================================
template<typename W> void check_empty_loads_from_nullptr(W alt)
{
  using e_t                   = eve::element_type_t<W>;
  constexpr std::ptrdiff_t n = W::size();

  e_t const* p = nullptr;

  for_each_relative_conditional(n, [&](auto c, std::ptrdiff_t first, std::ptrdiff_t last)
  {
    if constexpr( !std::same_as<decltype(c), eve::ignore_all_> )
    {
      if( first != last ) return;

      auto check = [&](auto ptr)
      {
        TTS_EQUAL(test_load[c.else_(alt)](ptr, eve::as<W> {}), alt);
        TTS_EQUAL(eve::replace_ignored(test_load[c](ptr, eve::as<W> {}), c, eve::zero),
                  eve::replace_ignored(alt, c, eve::zero));
      };

      check(p);
      check(eve::as_aligned(p, eve::lanes<n>));
    }
  });
}
