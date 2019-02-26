.. _function-is_normal:

################
is_normal
################

**Required header** ``#include <eve/function/is_normal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_normal = {};
   }

Function object determining if the given :ref:`IEEEValue <concept-ieeevalue>` is normal, that is not zero, not invalid and not denormal

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is normal.
* [2] returns :ref:`True <constant-true_>` if **s** is normal.

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

.. include:: ../../../../test/doc/is_normal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_normal.txt
  :literal:

