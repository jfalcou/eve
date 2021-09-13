//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/zip.hpp>
#include <eve/algo/convert.hpp>

#include <eve/detail/kumi.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/product_type.hpp>

namespace eve::algo::detail
{
  template<typename T> struct soa_field_storage
  {
    using type = std::vector<T, aligned_allocator<T,eve::detail::cache_line_cardinal<T>>>;
  };

  template <typename Type>
  using soa_vector_tuple = kumi::as_tuple_t<kumi::result::flatten_all_t<Type>, soa_field_storage>;

  template <eve::product_type Type>
  struct soa_storage : soa_vector_tuple<Type>
  {
    private:
      template<typename T> static auto as_aligned_pointer(T* ptr)
      {
        return eve::as_aligned(ptr, eve::detail::cache_line_cardinal<T>{});
      }

      template<typename Self>
      EVE_FORCEINLINE static auto data_aligned_impl(Self& self)
      {
        auto ptrs    = kumi::map([](auto& m) { return as_aligned_pointer(m.data()); }, self);
        return kumi::apply(eve::algo::zip, ptrs);
      }

    public:

      EVE_FORCEINLINE std::size_t size()  const noexcept { return kumi::get<0>(*this).size(); }

      EVE_FORCEINLINE auto data_aligned()        { return data_aligned_impl(*this); }
      EVE_FORCEINLINE auto data_aligned()  const { return data_aligned_impl(*this); }

      EVE_FORCEINLINE auto data()       { return eve::algo::unalign(data_aligned()); }
      EVE_FORCEINLINE auto data() const { return eve::algo::unalign(data_aligned()); }

      EVE_FORCEINLINE auto begin_aligned()        { return eve::algo::convert(data_aligned(), eve::as<Type>{}); }
      EVE_FORCEINLINE auto begin_aligned()  const { return eve::algo::convert(data_aligned(), eve::as<Type>{}); }
      EVE_FORCEINLINE auto cbegin_aligned() const { return eve::algo::convert(data_aligned(), eve::as<Type>{}); }

      EVE_FORCEINLINE auto begin()        { return eve::algo::convert(data(), eve::as<Type>{}); }
      EVE_FORCEINLINE auto begin()  const { return eve::algo::convert(data(), eve::as<Type>{}); }
      EVE_FORCEINLINE auto cbegin() const { return begin(); }

      EVE_FORCEINLINE auto end()  { return begin() + size(); }
      EVE_FORCEINLINE auto end()  const { return begin() + size(); }
      EVE_FORCEINLINE auto cend() const { return end(); }
  };
}

template <eve::product_type Type>
struct std::tuple_size<eve::algo::detail::soa_storage<Type>> :
  std::tuple_size<eve::algo::detail::soa_vector_tuple<Type>> {};

template <std::size_t I, eve::product_type Type>
struct std::tuple_element<I, eve::algo::detail::soa_storage<Type>> :
  std::tuple_element<I, eve::algo::detail::soa_vector_tuple<Type>> {};
