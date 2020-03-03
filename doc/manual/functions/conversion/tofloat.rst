.. _function-tofloat:

#######
tofloat
#######

**Required header:** ``#include <eve/function/tofloat.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ tofloat = {};
   }

Function object converts to the associated floating type.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Converts element-wise  the :ref:`wide <type-wide>` to the associated floating type.
* [2] Converts the scalar to the associated floating type.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value of the floating type associated to the parameter. 

Notes
*****

  - if ``sizeof(T)`` is less than 8 the associated base type is ``float`` else ``double``


Options
*******

  - :ref:`saturated_ <feature-decorator>` decorator saturate the conversion.


.. seealso::  :ref:`convert <function-convert>`,  :ref:`toint <function-toint>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/tofloat.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/tofloat.txt
  :literal:
