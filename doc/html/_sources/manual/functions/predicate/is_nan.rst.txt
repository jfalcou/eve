.. _function-is_nan:

################
is_nan
################

**Required header** ``#include <eve/function/is_nan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_nan = {};
   }

Function object determining if the given :ref:`Value <concept-value>` element is a :ref:`Nan <constant-nan>` value

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is nan.
* [2] returns :ref:`True <constant-true_>` if **s** is nan.

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

.. include:: ../../../../test/doc/is_nan.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_nan.txt
  :literal:

