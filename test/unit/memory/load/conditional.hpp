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
#include <eve/memory/soa_ptr.hpp>

#include <list>
#include <vector>

//==================================================================================================
// A page is a block of memory aligned on its own size, so that loads near its edges cannot cross into
// a neighbouring page. It is passed as an aligned_ptr, or as a soa_ptr of aligned_ptrs, to the block
// start, and its size is the alignment in elements.
//==================================================================================================
template<typename T, std::ptrdiff_t Size>
using page_storage = std::vector<T, eve::aligned_allocator<T, Size>>;

template<typename T, std::ptrdiff_t Size> page_storage<T, Size> make_page()
{
  page_storage<T, Size> data(Size);

  for( std::ptrdiff_t i = 0; i < Size; ++i )
  {
    if constexpr( eve::logical_value<T> ) data[i] = (i % 3 == 0);
    else                                  data[i] = T(i % 100 + 1);
  }

  return data;
}

namespace load_test
{
  template<typename T, std::ptrdiff_t N> constexpr std::ptrdiff_t page_size(eve::aligned_ptr<T, N>) { return N; }

  template<typename... Ps> constexpr std::ptrdiff_t page_size(eve::soa_ptr<Ps...> p)
  {
    return page_size(get<0>(p));
  }

  template<std::ptrdiff_t N, typename T> auto aligned(T* p) { return eve::as_aligned(p, eve::lanes<N>); }

  template<std::ptrdiff_t N, typename... Ps> auto aligned(eve::soa_ptr<Ps...> p)
  {
    return kumi::apply([](auto... f) { return eve::soa_ptr {aligned<N>(f)...}; }, p.storage);
  }

  template<typename T> auto as_const(T* p) { return static_cast<T const*>(p); }

  template<typename T, std::ptrdiff_t N> auto as_const(eve::aligned_ptr<T, N> p)
  {
    return eve::aligned_ptr<T const, N> {p};
  }

  template<typename... Ps> auto as_const(eve::soa_ptr<Ps...> p)
  {
    return kumi::apply([](auto... f) { return eve::soa_ptr {as_const(f)...}; }, p.storage);
  }
}

template<typename W, typename Page> void check_loads(W alt, Page page)
{
  constexpr std::ptrdiff_t n = W::size();

  auto begin = eve::unalign(page);
  auto end   = begin + load_test::page_size(page);

  using ptr_t = decltype(begin);

  test_ignores_for<n>([&](auto c)
  {
    std::ptrdiff_t first = c.offset(eve::as<W> {});
    std::ptrdiff_t last  = first + c.count(eve::as<W> {});

    auto check = [&](auto base, auto ptr)
    {
      W expected = [&](auto i, auto) { return (i >= first && i < last) ? eve::read(base + i) : alt.get(i); };

      TTS_EQUAL(eve::load[c.else_(alt)](ptr, eve::as<W> {}), expected) << c;
      TTS_EQUAL(eve::replace_ignored(eve::load[c](ptr, eve::as<W> {}), c, eve::zero),
                eve::replace_ignored(expected, c, eve::zero)) << c;

      if constexpr( std::same_as<decltype(eve::load(ptr)), W> )
      {
        TTS_EQUAL(eve::load[c.else_(alt)](ptr), expected) << c;
      }
    };

    auto check_const = [&](auto base, auto ptr)
    {
      check(base, ptr);
      check(base, load_test::as_const(ptr));
    };

    check_const(begin - first, begin - first);
    check_const(end - last, end - last);
    check_const(begin, load_test::aligned<n>(begin));
    check_const(end - n, load_test::aligned<n>(end - n));

    if constexpr( std::is_pointer_v<ptr_t> )
    {
      std::list<std::remove_pointer_t<ptr_t>> list(begin, begin + n);
      check(begin, list.begin());
    }

    if( first == last )
    {
      check(begin, load_test::as_const(ptr_t {}));
      check(begin, load_test::as_const(load_test::aligned<n>(ptr_t {})));
    }
  });
}

template<typename W> void check_loads(W alt)
{
  constexpr std::ptrdiff_t size = 4096 / sizeof(eve::element_type_t<W>);

  auto page = make_page<eve::element_type_t<W>, size>();
  check_loads(alt, eve::as_aligned(page.data(), eve::lanes<size>));
}
