//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <eve/module/polynomial/regular/horner.hpp>
#include <eve/module/polynomial/regular/derivative.hpp>
#include <eve/module/polynomial/regular/primitive.hpp>
#include <eve/module/polynomial/regular/polyval.hpp>
#include <eve/module/polynomial/regular/coefs.hpp>
#include <eve/module/polynomial/regular/exponents.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/range.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/reduce2.hpp>
#include <eve/algo/reverse.hpp>
#include <eve/algo/views/reverse.hpp>
#include <eve/views/reverse.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief representation of polynoms and monoms
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! eve::polynom and monom are templates structure representing respactivly polynomials with real
  //! or complex floating coefficients (resp polynomials with only one non zero coefficient).
  //! polynomials are internally based on std:vectors of coefficients on the fundamental basis and in
  //! decreasing powers order, but:
  //!
  //!  \f$ \displaystyle p(x) = \sum_0^n p[i]x^{i]\f$
  //!
  //!
  //! @tparam Type  Underlying scalar floating point type
  //!
  //! provided operators and functions are :
  //!
  //! - constructors
  //!    - trivial constructor provides the null polynomial (of degree -1) with no coefficients
  //!    - a constructor from a range of coefficients in decreasing power order
  //!    - a constructor from an initializer list of coefficients in decreasing power order
  //!    - a constructor from a range of elements in increasing power order (with second parameter eve::upward);
  //!
  //! - operators :
  //!     - +,  -, *, /, %, +=, -=, *=, /=, %=, <<, >>
  //!
  //!       binary operators accept mix of polynom, momom, value_type in any order.
  //!       monomial multiplication can be replaced by shift operators
  //!       division and remainder with null second parameter are UB.
  //!
  //!    - operator(): p(x) evaluates the polynomial p at x. x can be a scalar, an simd value or a range of scalar
  //!                  of the underlying type
  //!                  Take care that if a non const range is evaluted,  it is evaluated in place
  //!    - operator[]: p[i] return the coefficient of order i of the polynomial (i.e. of the monomial \f$x^i\f$.
  //!                  In particular 0 if i is not in the range \f$[0, degree(p)]\f$. (This operator is const).
  //!    - operator==: Two polynomials are equal if and only if they have the same degree and the same coefficients.
  //!    - operator!=: Two polynomials are not equal if and only if they do not have the same degree or two coefficients differ.
  //!
  //!@warning : this is a simple polynomial class not fit for big or sparse polynomials,  but for monomials or
  //!           dense polynomials of small degrees (in particular fft is not used for implementing *
  //!           (i.e. polynomial multiplication which could be written as a convolution)
  //!
  //! - friend functions
  //!     - degree returns the polynomial degree, i.e. the greatest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - valuation returns the polynomial valuation i.e. the lest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - remquo computes both the quotient and remainder of euclidian division
  //!     - young(n, p0) suppress all coefficients of degree greater than n,  thus giving the regular part
  //!       of the Taylor-Young devlopment of the polynom
  //!     - young_remainder(n, p0) zeroes all the lower n coefficients of p0 : one have
  //!       young(n, p0)+young_remainder(n, p0) == p0.
  //!       concat(p1, p0) if n is the degree of p0, return the polynom \f$x^{n+1}p1+p0\f$.
  //!     - is_null returns true if and only if the polynomial is of degree -1
  //!     - is_constant returns true if and only if the polynomial is of degree less than 1
  //!     - is_monomial returns true if and only if the polynomial has only one non null coef
  //!     - derivative(p, n) computes the nth derivative of p
  //!     - primive(p, n)    computes a primitive of order n of p (the one with valuation greater or equal to n)
  //!
  //================================================================================================

  template<floating_scalar_value Type>
  struct sparse_polynom;
  
  template<floating_scalar_value Type>
  struct polynom;

  template<floating_scalar_value Type>
  struct monom
  {
    /// Underlying type
    using value_type = Type;
    using monom_t  = monom<value_type>;
    using polynom_t = polynom<value_type>;
    using data_t = typename polynom_t::data_t;

    monom():deg(-1), data(0){};
    monom(value_type val, int degree) :deg(degree), data(val){if (data == 0) deg = -1; };
    monom(kumi::tuple<int, value_type> pair) : monom(pair.second, pair.first){};
    monom(int degree) :deg(degree), data(value_type(1)){};

    explicit operator polynom_t()
    {
      return *this;
    };

    template<integral_value I>
    auto operator[](I const & i) const noexcept
    {
      if constexpr(scalar_value<I>)
        return (i == 0) ? data :value_type(0);
      else
        return if_else(is_eqz(i), data, zero);
    }

    monom_t friend operator*(monom_t const & m1,  monom_t const & m2)
    {
      if (m1.deg < 0 || m2.deg < 0) return monom_t();
      return monom_t(m1.data*m2.data, m1.deg+m2.deg);
    }

    monom_t friend operator*(monom_t const & m1,  value_type const & m2)
    {
      if (m1.deg < 0 || is_eqz(m2)) return monom_t();
      return monom_t(m1.data*m2, m1.deg);
    }

    monom_t friend operator*(value_type const & m1, monom_t const & m2 )
    {
      return m2*m1;
    }

    monom_t & operator*= (monom_t const & m)
    {
      return *this = (*this)*m;
    }

    polynom_t friend operator+(monom_t const & m0,  monom_t const & m1)
    {
      auto maxd = max(m0.deg, m1.deg);
      data_t r;
      r.resize(maxd+1);
      auto d = m0.deg-m1.deg;
      if (d == 0)
      {
        r[0] = m1.data+m0.data;
      }
      else if (m0.deg > m1.deg)
      {
        r[0] = m0.data;
        r[d] = m1.data;
      }
      else
      {
        r[0] = m1.data;
        r[-d] = m0.data;
      }
      return polynom_t(r);
    }

    polynom_t friend operator+(monom_t const & m0,  value_type const & m1)
    {
      if(is_null(m0)) return polynom_t(m1);
      else
      {
        polynom_t p(m0);
        p += m1;
        return p;
      }
    }

    polynom_t friend operator-(monom_t const & m0,  monom_t const & m1)
    {
      return m0+(-m1);
    }

    polynom_t friend operator-(monom_t const & m1,  value_type const & m0)
    {
      if(is_eqz(m0)) return polynom_t(m1);
      else
      {
        polynom_t p(m1);
        p -= m0;
        return p;
      }
    }

    int friend degree(monom_t const & m)
    {
      return m.deg;
    }

    value_type friend valuation(monom_t const & m)
    {
      return m.deg;
    }

    bool friend is_null(monom_t const & m)
    {
      return is_eqz(m.data);
    }

    bool friend is_constant(monom_t const & m)
    {
      return m.deg == 0;
    }

     bool friend is_monomial(monom_t const & )
    {
      return true;
    }

    monom_t friend operator-(monom_t const & m)
    {
      return monom_t(-m.data, m.deg);
    }

    kumi::tuple<monom_t, monom_t> friend remquo(monom_t const & m0, monom_t const & m1)
    {
      if (m1.data == 0) return {monom_t(-1, nan(as<value_type>())), monom_t(-1, nan(as<value_type>()))};
      if (m0.deg >= m1.deg)
        return {monom_t(), monom_t(m0.data/m1.data, m0.deg-m1.deg)};
      else
        return {monom_t(m0.data, m0.deg), monom_t()};
    }

    monom_t friend operator/(monom_t const & m0, monom_t const & m1)
    {
      auto [_, q] = remquo(m0, m1);
      return q;
    }

    auto operator/=(monom_t const & m1)
    {
      auto [_, q] = remquo(*this, m1);
      return *this = q;
    }

    monom_t friend operator%(monom_t const & m0, monom_t const & m1)
    {
      auto [r, _] = remquo(m0, m1);
      return r;
    }

    auto operator%=(monom_t const & m1)
    {
      auto [r, _] = remquo(*this, m1);
      return *this = r;
    }
    auto operator()(floating_value auto const & x)
    {
      return pow(x, deg)*data;
    }

    template <detail::range R>
    friend void tagged_dispatch( eve::tag::polyval_, inplace_type const&
                               , monom_t const & p, R & x)  noexcept
    {
      auto eval = [ p ](auto e){return pow(e, p.deg)*p.data; };
      eve::algo::transform_inplace(x, eval);
    }

    template <detail::range R>
    friend  R tagged_dispatch( eve::tag::polyval_, monom_t const & p, const R & x)  noexcept
    {
      return p(x);
    }

    template <detail::range R> [[nodiscard]] R operator()(R const & x) const noexcept
    {
      auto px(x);
      auto eval = [ this ](auto e){return pow(e, this->deg)*this->data; };
      eve::algo::transform_inplace(px, eval);
      return px;
    }

    friend bool operator==(monom_t const & p0, monom_t const & p1)
    {
      return (degree(p0) == degree(p1) && (p0.data == p1.data));
    }

    friend bool operator!=(monom_t const & p0, monom_t const & p1)
    {
      return (degree(p0) != degree(p1) || (p0.data == p1.data));
      if(degree(p0) != degree(p1)) return true;
      return degree(p0-p1) != -1;
    }

    template <class charT, class traits> friend
    inline std::basic_ostream<charT, traits>&
    operator << (std::basic_ostream<charT, traits>& os, const monom_t& m)
    {
      os << polynom_t(m);
      return os;
    }

    void normalize()
    {
      if (data == 0) deg = -1;
    }

    friend monom_t young(int n, monom_t const & m0)
    {
      return (n >= degree(m0)) ? m0 : monom_t();
    }

    friend monom_t young_remainder(int n, monom_t const & m0)
    {
      return (n >= degree(m0)) ? monom_t() : m0;
    }

    friend value_type coef(monom_t const & m)
    {
      return m.data;
    }

  private :
    int deg;
    value_type data;
  };

}
