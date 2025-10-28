/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/overload.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct bit_cast_t : callable<bit_cast_t, Options>
  {
    template<typename T, typename Target>
    requires (sizeof(T) == sizeof(Target))
    EVE_FORCEINLINE constexpr Target operator()(T const& a, as<Target> tgt) const noexcept
    {
      return detail::bit_cast_impl(current_api, a, tgt);
    }

    EVE_CALLABLE_OBJECT(bit_cast_t, bit_cast_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_cast
//!   @brief Computes a bitwise reinterpretation of an object.
//!
//!   @groupheader{Header file}
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
//!      constexpr auto bit_cast operator()(value x, as<scalar_value> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the result.
//!
//!  **Template parameters**
//!
//!     * To: scalar type to which each element of `x` is casted
//!
//!    **Return value**
//!
//!    The bits of x of type From reinterpreted as being those of a variable of type To
//!    is returned.
//!
//!    Every bit in the value representation of the returned To object is equal to the
//!    corresponding bit in the object representation of from.
//!    The values of padding bits in the returned To object are unspecified.
//!
//!    If there is no value of type To corresponding to the value
//!    representation produced, the behavior is undefined. If there are multiple
//!    such values, which value is produced is unspecified.
//!
//!  @groupheader{External reference}
//!   * [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/bit_cast)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_cast.cpp}
//================================================================================================
  inline constexpr auto bit_cast = functor<bit_cast_t>;
//================================================================================================
//! @}
//================================================================================================

template<simd_value Src, simd_value Tgt>
constexpr EVE_FORCEINLINE Tgt inner_bit_cast(Src const& src, as<Tgt>) noexcept
  requires (sizeof(element_type_t<Src>) * Src::size() == sizeof(element_type_t<Tgt>) * Tgt::size())
{
  if constexpr (has_emulated_abi_v<Src> || has_emulated_abi_v<Tgt>)
  {
    if constexpr (sizeof(element_type_t<Src>) == sizeof(element_type_t<Tgt>)) return map(bit_cast, src, as_element<Tgt>{});
    else
    {
      Tgt res;

      std::memcpy(reinterpret_cast<unsigned char*>(&res.storage()),
                  reinterpret_cast<unsigned char const*>(&src.storage()),
                  std::min(sizeof(src.storage()), sizeof(res.storage())));

      return res;
    }
  }
  else return bit_cast(src, as<Tgt>{});
}
}
