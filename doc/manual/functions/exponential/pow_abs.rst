.. _function-pow_abs:

###########
pow_abs
###########

**Required header:** ``#include <eve/function/pow_abs.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ pow_abs = {};
   }

Function object computing :math:`x^y`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U x                ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U         const& x, wide<T,N> const& w ) noexcept;
   template<typename T>             constexpr T           operator()( T s, T t ) noexcept;

* [1-3] Computes  element-wise the absolute value of the first parameter raised to the power  of the second.
* [4]   Computes the  absolute value of the first parameter raised to the power  of the second.   

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`IEEEValue <concept-ieeevalue>`.
* **x** : Scalar floating point value. 
* **s**, **t**: Scalar floating point values of same type.

.. rubric:: Return value

* [1-3] A value with the same type as wide parameter.
* [4] A value of type **T**.


*******
Notes
*******

* Using `pow_abs(x, y)` for :ref:`concept-ieeevalue` entries is similar to :math:`|x|^y`.

* The implementation is conform to the IEEE requirements, but no exeception is ever raised.

    - pow_abs(:math:`\pm0`, exp), where exp is a negative odd integer, returns :math:`+\infty` 
    - pow_abs(:math:`\pm0`, exp), where exp is negative, finite, and is an even integer or a non-integer, returns :math:`+\infty`
    - pow_abs(:math:`\pm0`, :math:`-\infty`) returns :math:`+\infty`
    - pow_abs(:math:`\pm0`, exp), where exp is a positive odd integer, returns :math:`+0`
    - pow_abs(:math:`\pm0`, exp), where exp is positive non-integer or a positive even integer, returns :math:`+0`
    - pow_abs(\pm1, exp) returns 1 for any exp, even when exp is NaN
    - pow_abs(base, :math:`\pm0`) returns 1 for any base, even when base is NaN
    - pow_abs(base, exp) returns NaN if base is finite and negative and exp is finite and non-integer.
    - pow_abs(base, :math:`-\infty`) returns :math:`+\infty` for any |base|<1
    - pow_abs(base, :math:`-\infty`) returns :math:`+0` for any |base|>1
    - pow_abs(base, :math:`+\infty`) returns :math:`+0` for any |base|<1
    - pow_abs(base, :math:`+\infty`) returns :math:`+\infty` for any |base|>1
    - pow_abs(:math:`\pm\infty`, exp) returns :math:`+0` for any negative exp
    - pow_abs(:math:`\pm\infty`, exp) returns :math:`+\infty` for any positive exp
    except where specified above, if any argument is NaN, NaN is returned 

* With raw_ decorator  uses the naive formula :math:`e^{y\log |x|}'
         and so does not care for limits and leads to lower accuracy. In particular it returns NaN for negative base
 
 
*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/pow_abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/pow_abs.txt
  :literal:
