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
// A page of memory to load N lanes from. unaligned(p), aligned(p), iterators() and nulls() are the
// sources to load from: unaligned(p) and aligned(p) read the same lanes as p, iterators() the ones
// at begin(), nulls() none.
//==================================================================================================
template<typename T, std::ptrdiff_t N> struct load_page
{
  static constexpr std::ptrdiff_t size = 4096 / sizeof(T);

  std::vector<T, eve::aligned_allocator<T, size>> data;
  std::list<T>                                    list;

  load_page() : data(size)
  {
    for( std::ptrdiff_t i = 0; i < size; ++i )
    {
      if constexpr( eve::logical_value<T> ) data[i] = (i % 3 == 0);
      else                                  data[i] = T(i % 100 + 1);
    }

    list.assign(begin(), begin() + N);
  }

  T* begin() { return data.data(); }
  T* end()   { return data.data() + size; }

  auto unaligned(T* p) const { return kumi::tuple {p, static_cast<T const*>(p)}; }

  auto aligned(T* p) const
  {
    return kumi::tuple {eve::as_aligned(p, eve::lanes<N>), eve::as_aligned(static_cast<T const*>(p), eve::lanes<N>)};
  }

  auto iterators() { return kumi::tuple {list.begin()}; }

  auto nulls() const
  {
    return kumi::tuple {static_cast<T const*>(nullptr), eve::as_aligned(static_cast<T const*>(nullptr), eve::lanes<N>)};
  }
};

//==================================================================================================
// One load_page per field, loaded through soa_ptr.
//==================================================================================================
template<std::ptrdiff_t N, typename... Ts> struct soa_page
{
  kumi::tuple<load_page<Ts, N>...> fields;

  auto begin() { return kumi::apply([](auto&... f) { return eve::soa_ptr {f.begin()...}; }, fields); }
  auto end()   { return kumi::apply([](auto&... f) { return eve::soa_ptr {f.end()...}; }, fields); }

  auto unaligned(auto p) const { return kumi::tuple {p}; }

  auto aligned(auto p) const
  {
    auto all   = kumi::apply([](auto... f) { return eve::soa_ptr {eve::as_aligned(f, eve::lanes<N>)...}; }, p.storage);
    auto first = kumi::apply([](auto f, auto... fs) { return eve::soa_ptr {eve::as_aligned(f, eve::lanes<N>), fs...}; },
                             p.storage);
    return kumi::tuple {all, first};
  }

  auto iterators() const { return kumi::tuple {}; }

  auto nulls()
  {
    return kumi::tuple {kumi::apply([](auto&... f) { return eve::soa_ptr {decltype(f.begin()) {}...}; }, fields)};
  }
};

template<typename W, typename Page> void check_loads(W alt, Page& page)
{
  constexpr std::ptrdiff_t n = W::size();

  auto begin = page.begin();
  auto end   = page.end();

  test_ignores_for<n>([&](auto c)
  {
    std::ptrdiff_t first = c.offset(eve::as<W> {});
    std::ptrdiff_t last  = first + c.count(eve::as<W> {});

    auto check_one = [&](W const& expected, auto ptr)
    {
      TTS_EQUAL(eve::load[c.else_(alt)](ptr, eve::as<W> {}), expected) << c;
      TTS_EQUAL(eve::replace_ignored(eve::load[c](ptr, eve::as<W> {}), c, eve::zero),
                eve::replace_ignored(expected, c, eve::zero)) << c;

      if constexpr( std::same_as<decltype(eve::load(ptr)), W> )
      {
        TTS_EQUAL(eve::load[c.else_(alt)](ptr), expected) << c;
      }
    };

    auto check = [&](auto base, auto ptrs)
    {
      W expected = [&](auto i, auto) { return (i >= first && i < last) ? eve::read(base + i) : alt.get(i); };
      kumi::for_each([&](auto ptr) { check_one(expected, ptr); }, ptrs);
    };

    check(begin - first, page.unaligned(begin - first));
    check(end - last, page.unaligned(end - last));
    check(begin, page.aligned(begin));
    check(end - n, page.aligned(end - n));
    check(begin, page.iterators());

    if( first == last ) check(begin, page.nulls());
  });
}

template<typename W> void check_loads(W alt)
{
  load_page<eve::element_type_t<W>, W::size()> page;
  check_loads(alt, page);
}
