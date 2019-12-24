.. _function-toint:

#####
toint
#####

**Required header:** ``#include <eve/function/toint.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ toint = {};
   }

Function object computing the conversion  of a :ref:`Value <concept-value>` to the associated signed integral type.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Converts element-wise  the :ref:`wide <type-wide>` to the associated signed integral type.
* [2] Converts the scalar to the associated signed integral type.


.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2]  A value of the signed integral type associated to the parameter. 

Notes
*****

  - if ``sizeof(T)`` is less than 8 the associated base type is ``int32_t`` else ``int64_t``

Options
*******

  - saturated_ decorator saturate the conversion.

.. seealso::  :ref:`convert <function-convert>`,  :ref:`tofloat <function-tofloat>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/toint.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/toint.txt
  :literal:
