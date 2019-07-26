.. _function-logical_andnot:

##############
logical_andnot
##############

**Required header:** ``#include <eve/function/logical_andnot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ logical_andnot = {};
   }

Function object performing a logical AND between a :ref:`Value <concept-value>` and the NEGATION of
another :ref:`Value <concept-value>` (of same type if they are both :ref:`wide <type-wide>` instances).

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N> wide<T,N>          operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N>          operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> logical<wide<T,N>> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   as_logical_t<T>    operator()( T s, U t ) noexcept;

* [1] Performs a logical AND between **v** and the NEGATION of **w**.
* [2] Performs a logical AND between each elements of **v** and the NEGATION of **s**.
* [3] Performs a logical AND between **s** and ach elements of NEGATION of **v**
* [4] Performs a logical AND between **s** and the NEGATION of **t**.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` of same type.
* **s**, **t**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value with the same type as the :ref:`wide <type-wide>` instance.
* [4] A value of type **T**.

.. rubric:: Notes

*  Take care that SIMD logical operations do not short-circuit.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/logical_andnot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/logical_andnot.txt
  :literal:
