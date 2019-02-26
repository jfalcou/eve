.. _function-is_not_greater:

##############
is_not_greater
##############

**Required header:** ``#include <eve/function/is_not_greater.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ is_not_greater = {};
   }

Function object performing 'is not greater' comparison between two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   as_logical_t<T>         operator()( T s, U t ) noexcept;

* [1] Performs element-wise 'is not greater' comparison between both :ref:`wides <type-wide>`.
* [2,3] Performs 'is not greater' comparison between the scalar and each element of the :ref:`type-wide` instance.
* [4] Performs 'is not greater' comparison between both scalars.

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

.. include:: ../../../../test/doc/is_not_greater.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/is_not_greater.txt
  :literal:
