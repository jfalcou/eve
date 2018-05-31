##===================================================================================================
##                                 Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
##===================================================================================================

##===================================================================================================
## Parse revision number in variables
##===================================================================================================
function(parse_revision version_string prefix)
  set(version_regex_release "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
  set(version_regex_prerelease "^([0-9]+)\\.([0-9]+)\\.([0-9]+)-([0-9A-Za-z.-]+)$")

  if("${version_string}" MATCHES ${version_regex_release})
    set(version_regex ${version_regex_release})
  elseif("${version_string}" MATCHES ${version_regex_prerelease})
    set(version_regex ${version_regex_prerelease})
  else()
    message(STATUS "[spy] Unknown version format - Assume WIP")
    set(${prefix}_IS_PRERELEASE 0)
    set(${prefix}_IS_WIP 1)
    foreach(ARG "" _IS_WIP _IS_PRERELEASE)
      set(${prefix}${ARG} ${${prefix}${ARG}} PARENT_SCOPE)
    endforeach()
    return()
  endif()

  string(REGEX REPLACE ${version_regex} "\\1" ${prefix}_MAJOR "${version_string}")
  string(REGEX REPLACE ${version_regex} "\\2" ${prefix}_MINOR "${version_string}")
  string(REGEX REPLACE ${version_regex} "\\3" ${prefix}_PATCH "${version_string}")
  set(${prefix}_IS_PRERELEASE 0)

  if("${version_string}" MATCHES ${version_regex_prerelease})
    string(REGEX REPLACE ${version_regex} "\\4" ${prefix}_PRERELEASE "${version_string}")
    set(${prefix}_IS_PRERELEASE 1)
  endif()

  math(EXPR ${prefix} "${${prefix}_MAJOR} * 10000 + ${${prefix}_MINOR} * 100 + ${${prefix}_PATCH}")

  foreach(ARG "" _MAJOR _MINOR _PATCH _IS_WIP _PRERELEASE _IS_PRERELEASE)
    set(${prefix}${ARG} ${${prefix}${ARG}} PARENT_SCOPE)
  endforeach()

endfunction()

##===================================================================================================
## Setup revision ID
##===================================================================================================
if(GIT_EXECUTABLE AND NOT EXISTS GIT_EXECUTABLE)
  unset(GIT_EXECUTABLE CACHE)
endif()

find_package(Git QUIET)
if(GIT_EXECUTABLE)
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  OUTPUT_VARIABLE SPY_VERSION_STRING
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  ERROR_QUIET
                 )
endif()

if(NOT DEFINED SPY_VERSION_STRING)
  if((NOT GIT_EXECUTABLE OR NOT EXISTS GIT_EXECUTABLE) AND IS_DIRECTORY ${PROJECT_SOURCE_DIR}/.git)

    message ( FATAL_ERROR "[spy] Git not found, verify your GIT_EXECUTABLE variable "
                          "or specify SPY_VERSION_STRING manually"
            )

  elseif(NOT EXISTS ${PROJECT_SOURCE_DIR}/tagname)

  message ( FATAL_ERROR "SPY_VERSION_STRING must be specified "
                        "manually if no tagname file nor Git"
          )

  endif()

  file(READ tagname SPY_VERSION_STRING)
  string(REGEX REPLACE "[ \r\n\t]+$" "" SPY_VERSION_STRING "${SPY_VERSION_STRING}")

endif()

parse_revision("${SPY_VERSION_STRING}" SPY_VERSION)

if(SPY_VERSION_IS_WIP)
  set(spy_release "(internal version)")
else()
  if(SPY_VERSION_IS_PRERELEASE)
    set(spy_release "(pre-release)")
  endif()
endif()

message(STATUS "[spy] Configuring version ${SPY_VERSION_STRING} ${spy_release}")
