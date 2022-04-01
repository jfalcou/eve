//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/views/zip.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/concept/simd_allocator.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/module/core.hpp>
#include <eve/product_type.hpp>
#include <cstddef>
#include <type_traits>
#include <memory>

namespace eve::algo::detail
{
  struct memory_helper
  {
    static void copy_all_aligned(std::byte const* src, std::byte* dst, std::size_t size)
    {
      auto aligned_src = eve::as_aligned(reinterpret_cast<std::uint8_t const*>(src), lane<64>);
      auto aligned_dst = eve::as_aligned(reinterpret_cast<std::uint8_t*>(dst), lane<64>);
      eve::algo::copy(as_range(aligned_src, aligned_src+size), aligned_dst);
    }

    template<typename T> static EVE_FORCEINLINE auto as_aligned_pointer(T* ptr)
    {
      return eve::as_aligned(ptr, eve::detail::cache_line_cardinal<T>{});
    }

    template<typename T>
    static  auto realign(std::size_t n) { return eve::align(sizeof(T)*n, eve::over{64}); }

    template<typename Storage>
    static auto allocate(Storage const& s, std::size_t n)
    {
      using storage_t = typename Storage::storage_t;
      auto a = s.get_allocator();
      return storage_t{ (typename Storage::byte_t*)(a.allocate_aligned(n,64)), a};
     }
  };

  template<eve::product_type Type, eve::simd_allocator Allocator>
  struct soa_storage
  {
    using is_product_type = void;
    using value_type = Type;

    soa_storage() noexcept
            : indexes_{}, storage_( nullptr, aligned_deleter{Allocator{}} ), capacity_{}
    {}

    explicit  soa_storage(Allocator a) noexcept
            : indexes_{}, storage_( nullptr, aligned_deleter{a} ), capacity_{}
    {}

    soa_storage(Allocator a, std::size_t c) : soa_storage(a)
    {
      // Strong guarantee on allocation
      auto local = memory_helper::allocate(*this, byte_size(c));
      storage_.swap(local);

      capacity_ = aligned_capacity(c);

      auto        sub     = storage_.get();
      std::size_t offset  = 0ULL;

      kumi::for_each_index( [&]<typename Idx>(Idx, auto& s)
                            {
                              // Start current sub-span data lifetime
                              using type  = kumi::element_t<Idx::value,Type>;
                              auto sz     = memory_helper::realign<type>(c);
                              std::memmove(reinterpret_cast<type*>(sub+offset), sub+offset, sz);

                              // Update the index
                              s       = offset;
                              offset += sz;
                            }
                          , indexes_
                          );
    }

    soa_storage(soa_storage const& src) : soa_storage(src.storage_.get_deleter())
    {
      auto sz = byte_size(src.capacity_);

      // Strong guarantee on allocation
      auto local  = memory_helper::allocate(*this,sz);
      memory_helper::copy_all_aligned(src.storage_.get(), local.get(), sz );
      storage_.swap(local);

      indexes_  = src.indexes_;
      capacity_ = src.capacity_;
    }

    soa_storage& operator=(soa_storage const& src)
    {
      *this = soa_storage(src);
      return *this;
    }

    soa_storage(soa_storage&&)            = default;
    soa_storage& operator=(soa_storage&&) = default;

    EVE_FORCEINLINE auto data_aligned()
    {
      auto ptrs = kumi::map([]( auto p) { return memory_helper::as_aligned_pointer( p ); }, *this);
      return kumi::apply(eve::algo::views::zip, ptrs);
    }

    EVE_FORCEINLINE auto data_aligned() const
    {
      auto ptrs = kumi::map([]( auto p) { return memory_helper::as_aligned_pointer( p ); }, *this);
      return kumi::apply(eve::algo::views::zip, ptrs);
    }

    EVE_FORCEINLINE auto data()       { return eve::unalign(data_aligned()); }
    EVE_FORCEINLINE auto data() const { return eve::unalign(data_aligned()); }

    void swap(soa_storage& other) noexcept
    {
      storage_.swap(other.storage_);
      std::swap(indexes_  , other.indexes_  );
      std::swap(capacity_ , other.capacity_ );
    }

    friend void swap(soa_storage& a, soa_storage& b ) noexcept { a.swap(b); }

    //==============================================================================================
    // Static helpers
    //==============================================================================================
    static auto aligned_capacity(std::size_t n) noexcept
    {
      // Capacity is the smallest gap possible, ie the one in the largest type
      constexpr std::size_t largest = max_scalar_size_v<Type>;
      return eve::align(largest*n, eve::over{64})/largest;
    }

    static auto byte_size(std::size_t n) noexcept
    {
      return  kumi::fold_left ( [n]<typename S>(auto a,S) { return a + memory_helper::realign<S>(n); }
                              , flat_t{}
                              , 0ULL
                              );
    }

    //==============================================================================================
    // Tuple interface
    //==============================================================================================
    template<std::size_t I>
    friend decltype(auto) get(soa_storage& s) noexcept
    {
      return reinterpret_cast<kumi::element_t<I,Type>*>(s.storage_.get() + get<I>(s.indexes_));
    }

    template<std::size_t I>
    friend decltype(auto) get(soa_storage const& s) noexcept
    {
      return reinterpret_cast<kumi::element_t<I,Type> const*>(s.storage_.get() + get<I>(s.indexes_));
    }

    //==============================================================================================
    template<typename U> struct as_index { using type = std::size_t; };

    struct aligned_deleter : Allocator
    {
      aligned_deleter(Allocator a) : Allocator(a) {}
      void operator()(void* p) { Allocator::deallocate_aligned(p); }
    };

    Allocator get_allocator() const { return storage_.get_deleter(); }

    //==============================================================================================
    using byte_t    = std::byte;
    using storage_t = std::unique_ptr<byte_t, aligned_deleter>;
    using flat_t    = kumi::result::flatten_all_t<Type>;
    using indexes_t = kumi::as_tuple_t<flat_t, as_index>;

    indexes_t   indexes_;
    storage_t   storage_;
    std::size_t capacity_;
  };
}

template <eve::product_type Type, typename Allocator>
struct  std::tuple_size<eve::algo::detail::soa_storage<Type,Allocator>>
      : kumi::size<Type>
{};

template <std::size_t I, eve::product_type Type, typename Allocator>
struct  std::tuple_element<I, eve::algo::detail::soa_storage<Type,Allocator>>
      : std::add_pointer<kumi::element<I, Type>>
{};
