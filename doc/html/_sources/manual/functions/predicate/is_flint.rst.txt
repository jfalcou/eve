.. _function-is_flint:

#########
is_flint
#########

**Required header** ``#include <eve/function/is_flint.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_flint = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is the representation of an integer

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element represents an integral value.
* [2] returns :ref:`True <constant-true_>` if **s** represents of an integral value.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.


Options
*******

Example
*******

.. include:: ../../../../test/doc/is_flint.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_flint.txt
  :literal:

