//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/same_lanes.hpp>

namespace eve
{
  template<typename Options>
  struct zip_t : callable<zip_t, Options>
  {
    template<scalar_value... Vs>
    constexpr EVE_FORCEINLINE kumi::tuple<Vs...> operator()(Vs... vs) const noexcept
    {
      return this->behavior(as<kumi::tuple<Vs...>>{}, eve::current_api, this->options(), vs...);
    }

    template<kumi::product_type Target, scalar_value... Vs>
    constexpr EVE_FORCEINLINE Target operator()(as<Target> const& tgt, Vs... vs) const noexcept
    {
      return this->behavior(as<Target>{}, eve::current_api, this->options(), tgt, vs...);
    }

    template<simd_value V0, simd_value... Vs>
    EVE_FORCEINLINE as_wide_as_t<kumi::tuple<element_type_t<V0>, element_type_t<Vs>...>, V0> operator()(V0 v0, Vs... vs) const noexcept
      requires (same_lanes<V0, Vs...>)
    {
      return this->behavior(as<as_wide_as_t<kumi::tuple<element_type_t<V0>, element_type_t<Vs>...>, V0>>{}, eve::current_api, this->options(), v0, vs...);
    }

    template<kumi::product_type Target, simd_value V0, simd_value... Vs>
    EVE_FORCEINLINE wide<Target, cardinal_t<V0>> operator()(as<Target> const& tgt, V0 v0, Vs... vs) const noexcept
      requires (((sizeof...(Vs) + 1) == kumi::size_v<Target>) && same_lanes<V0, Vs...>)
    {
      return this->behavior(as<wide<Target, cardinal_t<V0>>>{}, eve::current_api, this->options(), tgt, v0, vs...);
    }

    EVE_CALLABLE_OBJECT(zip_t, zip_);

    // Local helper callable with force inlining
    struct to_ptr { EVE_FORCEINLINE auto operator()(auto& m)            const { return &m; } };
    struct filler { EVE_FORCEINLINE auto operator()(auto in, auto *ptr) const { *ptr = in; } };
  };

// TODO DOC
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var zip
//!   @brief Callable for SoA value constructions.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      constexpr auto zip(scalar_value auto... parts)               noexcept; //1
//!      constexpr auto zip(as<Target> t, scalar_value auto... parts) noexcept; //2
//!      constexpr auto zip()(simd_value auto... parts)               noexcept; //3
//!      constexpr auto zip(as<Target> t, simd_value auto... parts)   noexcept; //4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `parts`: Variadic list of [value](@ref eve::value) to zip together.
//!   * `t`:   [Type wrapper](@ref eve::as) instance embedding the type to construct from `parts`.
//!
//!   **Return value**
//!     1. a kumi::tuple made from all the scalars passed as argument.
//!     2. a `Target` instance made from all the scalars passed as argument.
//!     3. a kumi::tuple made from all the SIMD values passed as argument.
//!     4. a `Target` instance made from all the SIMD values passed as argument.
//!
//!   @groupheader{Example}
//!   @godbolt{doc/core/zip.cpp}
//!
//================================================================================================
  inline constexpr auto zip = functor<zip_t>;
//================================================================================================
//! @}
//================================================================================================

/// @brief Type helper to compute tuple-like result-type
  template<typename... Vs>
  using zipped = eve::result_t<zip,Vs...>;
}

namespace eve::detail
{
  template<callable_options O, scalar_value... Vs>
  EVE_FORCEINLINE auto zip_(EVE_REQUIRES(cpu_), O const&, Vs... vs) noexcept
  {
    return kumi::tuple{vs...};
  }

  template<callable_options O, simd_value V0, simd_value... Vs>
  EVE_FORCEINLINE auto
  zip_(EVE_REQUIRES(cpu_), O const&, V0 w0, Vs... ws) noexcept
  {
    using r_t = as_wide_as_t<kumi::tuple<element_type_t<V0>,element_type_t<Vs>...>, V0>;
    return r_t{w0, ws...};
  }

  template<callable_options O, kumi::product_type Target, scalar_value... Vs>
  EVE_FORCEINLINE auto
  zip_(EVE_REQUIRES(cpu_), O const&, as<Target> const&, Vs... vs) noexcept
  {
    Target      res;
    kumi::for_each(tag_t<zip>::filler{}, kumi::tuple{vs...}, kumi::map(tag_t<zip>::to_ptr{}, res));
    return res;
  }

  template<callable_options O, kumi::product_type Target, simd_value V0, simd_value... Vs>
  EVE_FORCEINLINE auto zip_(EVE_REQUIRES(cpu_), O const&, as<Target> const&, V0 v0, Vs... vs) noexcept
  {
    return wide<Target, cardinal_t<V0>>{v0, vs...};
  }
}
