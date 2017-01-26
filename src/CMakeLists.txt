# Copyright (c) 2017, EPL-Vizards
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the EPL-Vizards nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL EPL-Vizards BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Automatically generated file; DO NOT EDIT

project( funcRedirect )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

set( FUNCREDIRECT_SRC

   ${CMAKE_CURRENT_SOURCE_DIR}/FuncRedirect.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MemProtectBase.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/posix/MemProtectPosix.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/x86/CodeWriterX86.cpp
)

set( FUNCREDIRECT_INC

   ${CMAKE_CURRENT_SOURCE_DIR}/CodeWriterBase.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/FuncRedirect.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MemProtectBase.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/posix/MemProtectPosix.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/x86/CodeWriterX86.hpp
)


add_library( funcRedirect_obj    OBJECT ${FUNCREDIRECT_SRC} ${FUNCREDIRECT_INC} )
add_library( funcRedirect_shared SHARED $<TARGET_OBJECTS:funcRedirect_obj> )
add_library( funcRedirect_static STATIC $<TARGET_OBJECTS:funcRedirect_obj> )

target_link_libraries( funcRedirect_shared  )
target_link_libraries( funcRedirect_static  )

string( REGEX REPLACE "^[^:]+::" "" OUT_LIB_NAME "funcRedirect" )
string( REGEX REPLACE "^lib"     "" OUT_LIB_NAME "${OUT_LIB_NAME}" )

set_target_properties(
  funcRedirect_shared funcRedirect_static
  PROPERTIES
    VERSION      0.0.1
    SOVERSION    0
  PUBLIC_HEADER  "${FUNCREDIRECT_INC}"
  OUTPUT_NAME    "${OUT_LIB_NAME}"
)

install(
  TARGETS       funcRedirect_shared funcRedirect_static
  EXPORT        funcRedirectTargets
  RUNTIME       DESTINATION bin
  LIBRARY       DESTINATION lib
  ARCHIVE       DESTINATION lib
  PUBLIC_HEADER DESTINATION include/eplViz
)


