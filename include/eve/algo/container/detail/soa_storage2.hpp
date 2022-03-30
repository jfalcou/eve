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
#include <eve/memory/aligned_allocator.hpp>
#include <eve/concept/simd_allocator.hpp>
#include <eve/product_type.hpp>
#include <type_traits>
#include <memory>

namespace eve::algo::detail
{
  template<eve::product_type Type, eve::simd_allocator Allocator>
  struct soa_storage
  {
    using is_product_type = void;

    explicit  soa_storage(Allocator const& a = {}) noexcept
            : indexes_{}, storage_( nullptr, aligned_deleter{a} ), capacity_{}
    {}

    soa_storage(Allocator const& a, std::size_t c) : soa_storage(a)
    {
      // Strong guarantee on allocation
      auto local = allocate(a, byte_size(c));
      storage_.swap(local);

      capacity_ = aligned_capacity(c);

      auto sub    = storage_.get();
      auto offset = 0;

      kumi::for_each_index( [&]<typename Idx>(Idx, auto& s)
                            {
                              // How many things
                              auto sz = realign<kumi::element_t<Idx::value,Type>>(c);

                              // Start current sub-span data lifetime
                              using type = kumi::element_t<Idx::value,Type>;
                              std::memmove(reinterpret_cast<type*>(sub+offset), sub+offset, sz);

                              // update the index
                              s       = offset;
                              offset += sz;
                            }
                          , indexes_
                          );
    }

    soa_storage(soa_storage const& src) : soa_storage()
    {
      auto sz     = byte_size(src.capacity_);

      // Strong guarantee on allocation
      auto local  = allocate(src.storage_.get_deleter(), sz);
      std::copy(src.storage_.get(), src.storage_.get()+sz, local.get());
      storage_.swap(local);

      indexes_  = src.indexes_;
      capacity_ = src.capacity_;
    }

    soa_storage& operator=(soa_storage const& src)
    {
      *this = soa_storage(src);
      return *this;
    }

    soa_storage(soa_storage&&)            =default;
    soa_storage& operator=(soa_storage&&) =default;

    EVE_FORCEINLINE auto data_aligned()
    {
      auto ptrs = kumi::map([]( auto p) { return as_aligned_pointer( p ); }, *this);
      return kumi::apply(eve::algo::views::zip, ptrs);
    }

    EVE_FORCEINLINE auto data_aligned() const
    {
      auto ptrs = kumi::map([]( auto p) { return as_aligned_pointer( p ); }, *this);
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
    template<typename T> static EVE_FORCEINLINE auto as_aligned_pointer(T* ptr)
    {
      return eve::as_aligned(ptr, eve::detail::cache_line_cardinal<T>{});
    }

    template<typename T>
    static  auto realign(std::size_t n) { return eve::align(sizeof(T)*n, eve::over{64}); }

    static auto allocate(Allocator const& a,std::size_t n)
    {
      aligned_deleter d{a};
      return storage_t{ reinterpret_cast<byte_t*>(d.allocate_aligned(n,64)), d};
    }

    static auto aligned_capacity(std::size_t n) noexcept
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
      aligned_deleter(Allocator const& a) : Allocator(a) {}
      void operator()(void* p) { if(p) Allocator::deallocate_aligned(p); }
    };

    Allocator& get_allocator() { return storage_.get_deleter(); }

    //==============================================================================================
    using byte_t    = std::byte;
    using storage_t = std::unique_ptr<byte_t, aligned_deleter>;
    using flat_t    = kumi::result::flatten_all_t<Type>;
    using indexes_t = kumi::as_tuple_t<flat_t, as_index>;
    using alloc_t   = typename std::allocator_traits<Allocator>::template rebind_alloc<byte_t>;

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
