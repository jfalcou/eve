//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_TYPE_COMPLEX_HPP_INCLUDED
#define EVE_MODULE_TYPE_COMPLEX_HPP_INCLUDED

namespace eve::cmplx
{
  template<typename Type> struct complex
  {
    using value_type = Type;
    Type real,imag;

    auto& operator+=(complex const& z2)
    {
      real += z2.real;
      imag += z2.imag;
      return *this;
    }

    auto& operator+=(Type r)
    {
      real += r;
      return *this;
    }
  };

  template<typename Type> complex(Type,Type) -> complex<Type>;

  template<typename Type>
  inline constexpr complex<Type>
  operator+(complex<Type> const& z1, complex<Type> const& z2) noexcept
  {
    auto zz = z1;
    zz += z2;
    return zz;
  }

  template<typename Type>
  inline constexpr complex<Type> operator+(complex<Type> const& z, Type r) noexcept
  {
    auto zz = z;
    zz += r;
    return zz;
  }

  template<typename Type>
  inline constexpr complex<Type> operator+(Type r, complex<Type> const& z) noexcept
  {
    auto zz = z;
    zz += r;
    return zz;
  }
}

namespace eve::literal
{
  // complex generator
  inline cmplx::complex<double> operator""_i(long double  d) noexcept
  {
    return {0., static_cast<double>(d)};
  }

  inline cmplx::complex<float> operator""_if(long double  d) noexcept
  {
    return {0.f, static_cast<float>(d)};
  }
}

namespace eve
{
  using cmplx::complex;
}

#endif
