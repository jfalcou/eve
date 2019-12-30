.. _function-ulpdist:

#######
ulpdist
#######

**Required header:** ``#include <eve/function/ulpdist.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ulpdist = {};
   }

Function object computing the ulp-distance of  two :ref:`Values <concept-value>`. This is the number of values representable
in the base type between the two enties divided by 2.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<T,M> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T>             constexpr   T         operator()( T s, T t ) noexcept;

* [1] Computes the element-wise ulp-distance of the two :ref:`wide <type-wide>`.
* [2] Computes the ulp-distance of the scalar and each elements of the :ref:`type-wide` instance.
* [3] Computes the ulp-distance of the two scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``.
* **s**, **t**: Scalar values of type **U** satisfying ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.


*******
Example
*******

.. include:: ../../../../test/doc/core/ulpdist.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ulpdist.txt
  :literal:
