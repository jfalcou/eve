.. _function-is_ordered:

###########
is_ordered
###########

**Required header:** ``#include <eve/function/is_ordered.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ is_ordered = {};
   }

Function object performing 'none is nan' test with two :ref:`Values <concept-value>`.


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> as_logical_t<wide<T,N>> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   as_logical_t<T>         operator()( T s, U t ) noexcept;

* [1] Performs element-wise 'none is nan' test between both :ref:`wides <type-wide>`.
* [2,3] Performs 'none is nan' test between the scalar and each element of the :ref:`type-wide` instance.
* [4] Performs 'none is nan' test between both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.

.. rubric:: Return value

* [1,2] A value of type **as_logical_t<wide<T,N>>**.
* [3] A value of type **as_logical_t<T>**.


.. rubric:: Notes

* ``is_ordered(x,y)`` is equivalent to ``is_not_nan(x) && is_not_nan(y)`` 
* The return type is not ``bool`` as predicates applied on :ref:`concept-vectorized`` types need to store
  multiple values.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/is_ordered.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/is_ordered.txt
  :literal:
