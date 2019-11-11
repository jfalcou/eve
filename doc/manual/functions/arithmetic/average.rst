.. _function-average:

###########
average
###########

**Required header:** ``#include <eve/function/average.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ average = {};
   }

Function object the average of  two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<T,M> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T>             constexpr   T         operator()( T s, T t ) noexcept;

* [1] Computes the element-wise average of the two :ref:`wide <type-wide>`.
* [2] Computes the average of the scalar and each elements of the :ref:`type-wide` instance.
* [3] Computes the average of the two scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``.
* **s**, **t**: Scalar values of type **U** satisfying ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.


*******
Notes
*******

* Using `average(x, y)` for :ref:`concept-ieeevalue` entries is similar to  `(x+y)/2`

* For :ref:`concept-integralvalue` types, it returns a rounded value at a distance guaranteed
  to be less than or equal to 0.5 of the average floating value, but may differ
  by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
  simd intrinsics, it is possible that the scalar results may differ by one unit from
  simd ones.



*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/average.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/average.txt
  :literal:
