##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup a target that take a source file and turn it into MarkDeep
##==================================================================================================
function(generate_html source destination header output)
  string(REPLACE ".cpp" ".src.html" base ${output})
  string(REPLACE ".hpp" ".src.html" base ${base})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})

  set( HTML_DESTINATION "${PROJECT_SOURCE_DIR}/${destination}/${base}" )

  add_custom_command(OUTPUT ${HTML_DESTINATION}
    COMMAND sh -c "${PROJECT_SOURCE_DIR}/cmake/txt2html.sh ${source} ${header} > ${HTML_DESTINATION}"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    DEPENDS "${PROJECT_SOURCE_DIR}/${source}"
    COMMENT "Converting ${source} to Markdeep"
    VERBATIM
  )

  add_custom_target(${base} DEPENDS ${HTML_DESTINATION})
  add_dependencies(html ${base})

endfunction()
