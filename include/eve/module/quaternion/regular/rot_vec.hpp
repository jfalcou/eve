//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var rot_vecrot_vec
  //!
  //! @brief Callable object rotatating an \f$\mathbb{R}\f$ using a quaternion.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of rot_vec part                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < typename T > auto operator()(value auto q, std::span<T> x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [quaternion](@ref eve::value) defining the rotation.
  //!`x`:   span of 3 elements to rotate
  //!
  //! **Return value**
  //!
  //!   the span rotated by q
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/rot_vec.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct rot_vec_; }
  template<> struct supports_conditional<tag::rot_vec_> : std::false_type {};

  EVE_MAKE_CALLABLE(rot_vec_, rot_vec);

  namespace detail
  {
    template<ordered_value V1, ordered_value T, bool normalize>
    EVE_FORCEINLINE auto rot_vec_( EVE_SUPPORTS(cpu_), [[maybe_unused]] V1 const & q
                                 , std::span<T, 3> const &x
                                 , eve:: nor<normalize>) noexcept
    {
      if(!normalize)
        EVE_ASSERT(eve::all(is_unit(q)), "some quaternion is not unitary");
      return x;
    }

    template<ordered_value V1, ordered_value T>
    EVE_FORCEINLINE auto rot_vec_( EVE_SUPPORTS(cpu_), [[maybe_unused]] V1 const &
                                 , std::span<T, 3> const &x) noexcept
    {
      return x;
    }

    template<value V1, ordered_value T, bool normalize>
    EVE_FORCEINLINE auto rot_vec_( EVE_SUPPORTS(cpu_), eve::complex<V1> const & q
                                 , std::span<T, 3> const &v
                                 ,  eve:: nor<normalize>) noexcept
    {
      using e_t = std::decay_t<decltype(real(q))>;
      using v_t = decltype(T()+e_t());
      if constexpr (!normalize) EVE_ASSERT(eve::all(pedantic(is_unit(q))), "some quaternions are not unitary");

      using a_t = decltype(abs(q));
      a_t fac(2);
      if constexpr(normalize) fac *= rec(abs(q));
      auto [r, i] = q;
      std::array<v_t, 3> w{r*v[0], diff_of_prod(r, v[1], i, v[2]), sum_of_prod (r, v[2], i, v[1])};
      std::array<v_t, 3> wp{v[0], fam(v[1], fac, -i*w[2]), fam(v[2], fac, i*w[1])};
      return wp;
    }

    template<value V1, ordered_value T>
    EVE_FORCEINLINE auto rot_vec_( EVE_SUPPORTS(cpu_), eve::complex<V1> const & q
                                 , std::span<T, 3> const &v) noexcept
    {
      return rot_vec(q, v, Normalize);
    }
  }
}
