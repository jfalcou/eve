.. _function-bitwise_cast:

bitwise_cast
============

**Required header** ``#include <eve/function/bitwise_cast.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_cast<Value0>(Value1 lhs) noexcept
   }

Function object for performing bitwise cast to a :ref:`Value <concept-value>` of a possibly different type
than the input, but of same bit size.

The result type is the template parameter.

Parameters
----------

  - ``Value0`` : output Type
  - ``lhs``: input value

Return value
------------

The bits of  ``lhs``  :ref:`Value1 <concept-value>` as a  :ref:`Value0 <concept-value>`.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_cast.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_cast.txt
  :literal:

