add
===

**Required header** ``#include <eve/function/add.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value add( Value lhs, Value rhs ) noexcept
   }

Function object for performing addition over two :ref:`concept-value` of the same type.

Parameters
----------

  - ``lhs``, ``rhs`` : values to sum

Return value
------------

The sum of  ``arg0`` and ``arg1`` for every element of each parameters.

Options
-------


Example
-------

.. include:: ../../../../test/doc/add.cpp
  :literal:

Possible output

.. code-block:: c++

   add(3.f, 5.5f) = 8.5
   add(3_wf, {1,2,3,4}) = {4,5,6,7}
