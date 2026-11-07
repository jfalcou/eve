//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include "unit/ignores_test.hpp"
#include <eve/module/core.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>

#include <vector>

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

  test_ignores_for<n>([&](auto c)
  {
    std::ptrdiff_t first = c.offset(eve::as<W> {});
    std::ptrdiff_t last  = first + c.count(eve::as<W> {});

    auto check = [&](e_t const* p, auto ptr)
    {
      W expected = [&](auto i, auto) { return (i >= first && i < last) ? p[i] : alt.get(i); };

      TTS_EQUAL(eve::load[c.else_(alt)](ptr, eve::as<W> {}), expected) << c;
      TTS_EQUAL(eve::replace_ignored(eve::load[c](ptr, eve::as<W> {}), c, eve::zero),
                eve::replace_ignored(expected, c, eve::zero)) << c;
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

  test_ignores_for<n>([&](auto c)
  {
    if constexpr( std::same_as<decltype(c), decltype(eve::drop_never_empty(c))> )
    {
      if( c.count(eve::as<W> {}) != 0 ) return;

      auto check = [&](auto ptr)
      {
        TTS_EQUAL(eve::load[c.else_(alt)](ptr, eve::as<W> {}), alt) << c;
        TTS_EQUAL(eve::replace_ignored(eve::load[c](ptr, eve::as<W> {}), c, eve::zero),
                  eve::replace_ignored(alt, c, eve::zero)) << c;
      };

      check(p);
      check(eve::as_aligned(p, eve::lanes<n>));
    }
  });
}
