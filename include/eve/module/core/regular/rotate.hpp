//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/pattern.hpp>
#include <eve/module/core/regular/slide_right.hpp>
#include <eve/module/core/named_shuffles/swap_adjacent.hpp>

#include <array>

namespace eve
{
  template<typename Options>
  struct rotate_t : callable<rotate_t, Options>
  {
    template<simd_value T, std::ptrdiff_t M>
    EVE_FORCEINLINE constexpr T operator()(T v, index_t<M> m) const noexcept
    {
      static_assert((M >= 0) && (M <= T::size()), "[eve::rotate] Index must be in the range [0, T::size()]");
      return EVE_DISPATCH_CALL(v, m);
    }

    EVE_CALLABLE_OBJECT(rotate_t, rotate_);
  };

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!    @var rotate
  //!    @brief rotates two halves of the register by a chosen number of elements.
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template<simd_value T, std::ptrdiff_t M>
  //!      T rotate(T x, index<N> const &) noexcept;
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` : simd value to rotate
  //!     * `M` : position of the middle.
  //!             In std::rotate(f, m, l) -> this is std::distance(f, m);
  //!
  //!    **Return value**
  //!
  //!    Return T which is a permutation of x such
  //!    that elements x[M: T::size()) come first followed by x[0:M)
  //!    and the relative order in those halves is preserved.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/rotate.cpp}
  //================================================================================================
  inline constexpr auto rotate = functor<rotate_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  template<std::ptrdiff_t M, std::ptrdiff_t N>
  inline constexpr auto rotate_pattern = fix_pattern<N>(
    [](auto i, auto) {
      if (i < N - M) return M + i;
      else           return i + M - N;
    }
  );

  namespace detail
  {
    template<std::ptrdiff_t N, std::ptrdiff_t... I>
    inline constexpr auto is_rotate = []() -> std::ptrdiff_t
    {
      std::array actual  = {I...};
      if (actual.size() != N) return 0;

      std::ptrdiff_t rotation = actual[0];
      for ( auto x : actual ) {
        if (x != rotation) {
          return 0;
        }
        rotation = (rotation + 1) % actual.size();
      }

      return rotation;
    }();

    template<std::ptrdiff_t M>
    struct rotate_lambda
    {
      EVE_FORCEINLINE auto operator()(auto x) const { return rotate(x, index<M>); }
    };

    template<callable_options O, simd_value T, std::ptrdiff_t M>
    EVE_FORCEINLINE T rotate_(EVE_REQUIRES(cpu_), O const&, T x, index_t<M>)
    {
      if      constexpr ((M == T::size()) || (M == 0))      return x;
      else if constexpr (M == (T::size() / 2))              return swap_adjacent(x, eve::lane<T::size() / 2>);
      else if constexpr (is_bundle_v<typename T::abi_type>) return T(kumi::map(rotate_lambda<M>{}, x));
      else                                                  return slide_right(x, x, index<T::size() - M>);
    }
  }
}
