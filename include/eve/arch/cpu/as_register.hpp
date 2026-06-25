//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_wide.hpp>
#include <cstring>
#include <array>

namespace eve
{
  template<typename T, size_type N>
  consteval auto find_register_type(as<T>, fixed<N>, eve::emulated_)
  {
    return std::array<T, N>{};
  }

  template<typename T, size_type N>
  consteval auto find_logical_register_type(as<T>, fixed<N>, eve::emulated_)
  {
    return std::array<logical<T>, N>{};
  }

  //================================================================================================
  // Special case : product_type
  //================================================================================================
  namespace _
  {
    template<size_type N>
    struct apply_as_wide
    {
      template<typename T>
      using type = as_wide<T, N>;
    };
  }

  template<typename T, size_type N>
  consteval auto find_register_type(as<T>, fixed<N>, eve::bundle_)
    requires (eve::product_type<T>)
  {
    return kumi::as_tuple_t<T, _::apply_as_wide<N>::template type>{};
  }

  namespace _
  {
    template<typename Type, size_type Size>
    struct blob
    {
      static constexpr auto replication = Size / expected_cardinal_v<Type>;

      using value_type                  = as_wide_t<Type, expected_cardinal_v<Type>>;
      using subvalue_type               = as_wide_t<Type, Size / 2>;
      using storage_type                = kumi::result::fill_t<replication, value_type>;

      storage_type storage;

      EVE_FORCEINLINE void assign_parts(subvalue_type const& l, subvalue_type const& h)
      {
        auto src = reinterpret_cast<std::byte const*>(&l);
        auto dst = reinterpret_cast<std::byte*>(this);
        std::memcpy(dst, src, sizeof(*this) / 2);

        auto src2 = reinterpret_cast<std::byte const*>(&h);
        auto dst2 = dst + sizeof(*this) / 2;
        std::memcpy(dst2, src2, sizeof(*this) / 2);
      }

      EVE_FORCEINLINE auto slice() const
      {
        std::array<subvalue_type, 2> data{};

        auto src = reinterpret_cast<std::byte const*>(this);
        auto dst = &data[0];
        std::memcpy(dst, src, sizeof(*this) / 2);

        auto src2 = src + sizeof(*this) / 2;
        auto dst2 = &data[1];
        std::memcpy(dst2, src2, sizeof(*this) / 2);

        return data;
      }

      // Return a view of the blob as a collection of wide of the expected size for this type.
      EVE_FORCEINLINE auto slice_to_expected() const noexcept { return storage; }

      template<std::size_t I>
      friend EVE_FORCEINLINE auto&        get(blob& b) noexcept       { return kumi::get<I>(b.storage); }

      template<std::size_t I>
      friend EVE_FORCEINLINE auto const&  get(blob const& b) noexcept { return kumi::get<I>(b.storage); }

      template<typename Func>
      EVE_FORCEINLINE void for_each(Func f, auto... w)       { kumi::for_each(f, *this, w.storage()...); }

      template<typename Func>
      EVE_FORCEINLINE void for_each(Func f, auto... w) const { kumi::for_each(f, *this, w.storage()...); }

      template<typename Func>
      EVE_FORCEINLINE decltype(auto) apply(Func f)        { return kumi::apply(f,*this); }

      template<typename Func>
      EVE_FORCEINLINE decltype(auto) apply(Func f) const  { return kumi::apply(f,*this); }
    };

    template<typename T>
    struct is_blob_impl : std::false_type {};

    template<typename Type, auto S>
    struct is_blob_impl<blob<Type, S>> : std::true_type {};

    template<typename T>
    concept is_blob = is_blob_impl<std::remove_cvref_t<T>>::value;
  }

  template<typename T, size_type N>
  consteval auto find_register_type(as<T>, fixed<N>, eve::aggregated_)
  {
    return _::blob<T, N>{};
  }

  template<typename T, size_type N>
  consteval auto find_logical_register_type(as<T>, fixed<N>, eve::aggregated_)
  {
    return _::blob<logical<T>, N>{};
  }
}

template<std::size_t I, typename T, eve::size_type N>
struct std::tuple_element<I, eve::_::blob<T, N>>
{
  using type = typename eve::_::blob<T, N>::value_type;
};

template<typename T, eve::size_type N>
struct  std::tuple_size<eve::_::blob<T, N>>
      : std::integral_constant<std::size_t, eve::_::blob<T, N>::replication>
{
};
