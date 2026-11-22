//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/arch.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/logical.hpp>
#include <cstdint>
#include <memory>
#include <new>
#include <numeric>
#include <vector>

template<typename T, auto N> auto page()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::wide<T, N>>;
  using alloc_t = eve::aligned_allocator<T, N>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt, N);
  std::vector<T, alloc_t> ref(nb_elem);

  T k = T {1};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

template<typename T, auto N> auto logical_page()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::logical<eve::wide<T, N>>>;
  using alloc_t = eve::aligned_allocator<eve::logical<T>, N>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt, N);
  std::vector<eve::logical<T>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start-1;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}

template<typename T, auto N> auto arithmetic_logical_page()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::wide<T, N>>;
  using alloc_t = eve::aligned_allocator<T, N>;

  auto nb_elem  = 4096 / sizeof(T);
  auto start    = nb_elem - std::max(algt, N);
  std::vector<T, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i = start - 1; i < nb_elem; ++i) ref[i] = (k = !k);

  return std::pair{ ref, start };
}

#if __has_include(<sys/mman.h>)
#include <sys/mman.h>
#include <unistd.h>
#define EVE_TEST_GUARD_PAGES
#endif

struct raw_guarded_test_page
{
  static constexpr std::ptrdiff_t size() { return min_page_size; }

#if defined(EVE_TEST_GUARD_PAGES)
  std::uint8_t* data() { return base.get() + actual_page_size(); }

  private:
  static constexpr std::ptrdiff_t min_page_size = eve::platform::min_page_size;
  static std::ptrdiff_t actual_page_size() { return sysconf(_SC_PAGESIZE); }
  static std::ptrdiff_t mapped_size() { return min_page_size + 2 * actual_page_size(); }

  struct deleter
  {
    void operator()(std::uint8_t* p) const { munmap(p, mapped_size()); }
  };

  static std::uint8_t* allocate()
  {
    auto* p = (std::uint8_t*)mmap(nullptr, mapped_size(), PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if( p == MAP_FAILED ) throw std::bad_alloc {};
    std::unique_ptr<std::uint8_t, deleter> res {p};
    if( mprotect(p + actual_page_size(), min_page_size, PROT_READ | PROT_WRITE) != 0 )
      throw std::bad_alloc {};
    return res.release();
  }
#else
  std::uint8_t* data() { return base.get(); }

  private:
  static constexpr std::ptrdiff_t min_page_size = eve::platform::min_page_size;
  using alloc_t = eve::aligned_allocator<std::uint8_t, min_page_size>;

  struct deleter
  {
    void operator()(std::uint8_t* p) const { alloc_t {}.deallocate(p, min_page_size); }
  };

  static std::uint8_t* allocate() { return alloc_t {}.allocate(min_page_size); }
#endif

  std::unique_ptr<std::uint8_t, deleter> base {allocate()};
};

template<typename T> struct guarded_test_page
{
  static constexpr std::ptrdiff_t size() { return raw_guarded_test_page::size() / sizeof(T); }

  T* data()                       { return (T*)raw.data(); }
  T& operator[](std::ptrdiff_t i) { return data()[i]; }

  private:
  raw_guarded_test_page raw;
};
