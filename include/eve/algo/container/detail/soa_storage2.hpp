//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/views/zip.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/concept/simd_allocator.hpp>
#include <eve/product_type.hpp>
#include <type_traits>
#include <memory>

namespace eve::algo::detail
{
  template<eve::product_type Type, eve::simd_allocator Allocator>
  struct soa_storage : Allocator
  {
    using is_product_type = void;

              soa_storage() : storage_( nullptr ), size_(0) { build(0); }
    explicit  soa_storage( std::size_t n) : soa_storage( n, Type{} ) {}

    soa_storage( std::size_t n, Type const& v)  : soa_storage()
    {
      storage_ = (byte_t*)Allocator::aligned_alloc(byte_size(n), 64);
      size_ = n;
      build(n,v);
    }

    soa_storage(soa_storage const& src) : soa_storage()
    {
      storage_ = (byte_t*)Allocator::aligned_alloc(size_, 64);
      size_ = src.size_;
      std::copy(storage_, storage_+size_, src.storage_);
      reindex(src.size_);
    }

    soa_storage& operator=(soa_storage const& src)
    {
      soa_storage that(src);
      swap(that);
      return *this;
    }

    soa_storage(soa_storage&&)            =default;
    soa_storage& operator=(soa_storage&&) =default;

    ~soa_storage()
    {
      kumi::for_each( [&]<typename T>(T*& s)
                      {
                        for(std::size_t i=0;i<size_;++i) static_cast<T*>(s+i)->~T();
                      }
                    , indexes_
                    );
      Allocator::aligned_dealloc(storage_, size_);
    }

    EVE_FORCEINLINE auto data_aligned()
    {
      auto ptrs = kumi::map([](auto* m) { return as_aligned_pointer(m); }, indexes_);
      return kumi::apply(eve::algo::views::zip, ptrs);
    }

    EVE_FORCEINLINE auto data_aligned() const
    {
      auto ptrs = kumi::map([](auto const* m) { return as_aligned_pointer(m); }, indexes_);
      return kumi::apply(eve::algo::views::zip, ptrs);
    }

    EVE_FORCEINLINE auto data()       { return eve::unalign(data_aligned()); }
    EVE_FORCEINLINE auto data() const { return eve::unalign(data_aligned()); }

    void swap(soa_storage& other) noexcept
    {
      std::swap(storage_,other.storage_);
      std::swap(indexes_,other.indexes_);
      std::swap(size_,other.size_);
    }

    friend void swap(soa_storage& a, soa_storage& b ) noexcept
    {
      a.swap(b);
    }

    void build(std::size_t n, Type v = {})
    {
      auto sub_span = storage_;

      kumi::for_each( [&]<typename T>(T*& s, auto m)
                      {
                        s = reinterpret_cast<T*>(sub_span);
                        for(std::size_t i=0;i<n;++i) new (s+i) T(m);
                        sub_span += realign<T>(n);
                      }
                    , indexes_, v
                    );

      capacity_ = available_elements(n);
    }

    void reindex(std::size_t n)
    {
      auto sub_span = storage_;

      kumi::for_each( [&]<typename T>(T*& s)
                      {
                        s = reinterpret_cast<T*>(sub_span);
                        sub_span += realign<T>(n);
                      }
                    , indexes_
                    );
      capacity_ = available_elements(n);
    }

    //==============================================================================================
    // Static helpers
    //==============================================================================================
    template<typename T> static EVE_FORCEINLINE auto as_aligned_pointer(T* ptr)
    {
      return eve::as_aligned(ptr, eve::detail::cache_line_cardinal<T>{});
    }

    template<typename T>
    static  auto realign(std::size_t n) { return eve::align(sizeof(T)*n, eve::over{64}); }

    static auto available_elements(std::size_t n) noexcept
    {
      // Capacity is the smallest gap possible, ie the one in the largest type
      constexpr std::size_t largest = max_scalar_size_v<Type>;
      return eve::align(largest*n, eve::over{64})/largest;
    }

    static auto byte_size(std::size_t n) noexcept
    {
      return  kumi::fold_left ( [n]<typename S>(auto a, S) { return a + realign<S>(n); }
                              , flat_t{}
                              , 0ULL
                              );
    }

    //==============================================================================================
    // Tuple interface
    //==============================================================================================
    template<std::size_t I>
    friend decltype(auto) get(soa_storage& s) noexcept { return get<I>(s.indexes_); }

    template<std::size_t I>
    friend decltype(auto) get(soa_storage const& s) noexcept { return get<I>(s.indexes_); }

    //==============================================================================================
    using byte_t      = std::byte;
    using flat_t      = kumi::result::flatten_all_t<Type>;
    using sub_span_t  = kumi::as_tuple_t<flat_t, std::add_pointer>;
    using alloc_t     = typename std::allocator_traits<Allocator>::template rebind_alloc<byte_t>;

    byte_t*     storage_;
    sub_span_t  indexes_;
    std::size_t size_;
    std::size_t capacity_;
  };
}

template <eve::product_type Type, typename Allocator>
struct std::tuple_size<eve::algo::detail::soa_storage<Type,Allocator>> :
  std::tuple_size<typename eve::algo::detail::soa_storage<Type,Allocator>::sub_span_t> {};

template <std::size_t I, eve::product_type Type, typename Allocator>
struct std::tuple_element<I, eve::algo::detail::soa_storage<Type,Allocator>> :
  std::tuple_element<I, typename eve::algo::detail::soa_storage<Type,Allocator>::sub_span_t> {};
