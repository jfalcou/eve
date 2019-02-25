.. _function-is_real:

################
is_real
################

**Required header** ``#include <eve/function/is_real.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_real = {};
   }

Function object returning True for real inputs.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` 
* [2] returns :ref:`True <constant-true_>` if **s** .

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

.. include:: ../../../../test/doc/is_real.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_real.txt
  :literal:

