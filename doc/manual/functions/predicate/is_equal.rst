.. _function-is_equal:

########
is_equal
########

**Required header:** ``#include <eve/function/is_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ is_equal = {};
   }

Function object performing equality comparison between two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   as_logical_t<T>         operator()( T s, U t ) noexcept;

* [1] Performs element-wise equality comparison between both :ref:`wides <type-wide>`.
* [2,3] Performs equality comparison between the scalar and each element of the :ref:`type-wide` instance.
* [4] Performs equality comparison between both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.

.. rubric:: Return value

* [1,2] A value of type **as_logical_t<wide<T,N>>**.
* [3] A value of type **as_logical_t<T>**.


.. rubric:: Notes

* The return type is not ``bool`` as predicates applied on :ref:`concept-vectorized` types need to store
  multiple values.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/is_equal.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/is_equal.txt
  :literal:
