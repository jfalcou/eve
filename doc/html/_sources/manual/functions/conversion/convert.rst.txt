.. _function-convert:

#######
convert
#######

**Required header:** ``#include <eve/function/convert.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ convert = {};
   }

Function object converting value of a type to another.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr U  operator()( T const &x, as_<U> const & target) noexcept;

*  Converts the first parameter to the targeted type of the second one.

Parameter
*********

* ``x``: Instance of :ref:`Value <concept-value>`.
* ``target`` must be an instance of of a scalar :ref:` targeted value <concept-targetvalue>`.

Return value
************

* A value of the type defined by **U** and the wideness of the first parameter. 

Notes
*****
  
  - U is always a scalar type.

  - If the first parameter is a wide type the output is a wide the cardinal of which is the same.

  - For scalar types ``convert(a,as<U>())`` is equivalent to ``static_cast<U>(a)``.

  - if ``sizeof(T)`` is less than 8 the associated base type is ``float`` else ``double``.


Options
*******

  - :ref:`saturated_ <feature-decorator>` decorator saturate the conversion.


.. seealso::  :ref:`convert <function-convert>`,  :ref:`toint <function-toint>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/convert.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/convert.txt
  :literal:
