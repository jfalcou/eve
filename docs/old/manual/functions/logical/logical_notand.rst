.. _function-logical_notand:

##############
logical_notand
##############

**Required header:** ``#include <eve/function/logical_notand.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ logical_notand = {};
   }

Function object performing a logical AND between a :ref:`Value <concept-value>` and the NEGATION of
another :ref:`Value <concept-value>` (of same type if they are both :ref:`wide <type-wide>` instances).

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N> logical<wide<T,N>> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U> logical<wide<T,N>> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> logical<wide<T,N>> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   as_logical_t<T>    operator()( T s, U t ) noexcept;

* [1] Performs a logical AND between the NEGATION of **v** and **w**.
* [2] Performs a logical AND between the NEGATION of each elements of **v** and  **s**.
* [3] Performs a logical AND between the NEGATION of **s** and ach elements of **v**
* [4] Performs a logical AND between the NEGATION of **s** and **t**.

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

.. include:: ../../../../test/doc/core/logical_notand.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/logical_notand.txt
  :literal:
