.. _function-rem:

###
rem
###

**Required header:** ``#include <eve/function/rem.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rem = {};
   }

Function object computing the remaider after division  of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w) noexcept;
   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v, T s) noexcept;
   template<typename T, typename N>  wide<T,N> operator()( T s, wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s, T t ) noexcept;

* [1:3] Computes the element-wise  remaider after division of the parameters.
* [4] Computes the remaider after division of the two scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. *TODO*

Notes
*****


  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``. This function object
    by default implements the ``to_nearest_`` version.

  - the  call to ``rem(a,b)`` is equivalent to the call ``rem(a,b,toward_zero_)``
  - the  call to ``rem(a,b,tag_)`` is equivalent to the call ``a-b*div(a, b, tag_));``

Options
*******

  this object function can be called with :ref:`pedantic_ <feature-decorator>` decorator in which case (pedantic_(div) is used internally instead of div.

.. seealso::  :ref:`round <function-round>`

Example
*******

.. include:: ../../../../test/doc/core/rem.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rem.txt
  :literal:
