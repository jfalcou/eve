.. _function-touint:

######
touint
######

**Required header:** ``#include <eve/function/touint.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ touint = {};
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

  - if ``sizeof(T)`` is less than 8 the associated base type is ``uint32_t`` else ``uint64_t``

Options
*******

  - :ref:`saturated_ <feature-decorator>` decorator saturate the conversion.

.. seealso::  :ref:`convert <function-convert>`,  :ref:`tofloat <function-tofloat>`,  :ref:`toint <function-toint>`

Example
*******

.. include:: ../../../../test/doc/core/touint.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/touint.txt
  :literal:
