#=============================================================================
#  MuseScore
#  Music Composition & Notation
#  $Id:$
#
#  Copyright (C) 2011 Werner Schweer
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2
#  as published by the Free Software Foundation and appearing in
#  the file LICENSE.GPL
#=============================================================================

QT4_ADD_RESOURCES(qrc_files ${PROJECT_SOURCE_DIR}/mtest/mtest.qrc)

add_executable(
      ${TARGET}
      ${ui_headers}
      ${qrc_files}
      ${mocs}
      ${TARGET}.cpp
      )

target_link_libraries(
      ${TARGET}
      ${QT_QTTEST_LIBRARY}
      testutils
      libmscore
      msynth
      ${QT_LIBRARIES}
      )

if (NOT MINGW)
      target_link_libraries(${TARGET} 
      z 
      dl       
      pthread
      fontconfig
      freetype)
endif (NOT MINGW)

if (OMR)
      target_link_libraries(${TARGET} omr fitz openjpeg jbig2dec jpeg)
      if (OCR)
            target_link_libraries(mscore tesseract_api)
      endif (OCR)
endif (OMR)


set_target_properties (
      ${TARGET}
      PROPERTIES
      AUTOMOC true
      COMPILE_FLAGS "-include all.h -D TESTROOT=\\\"${PROJECT_SOURCE_DIR}\\\" -g -Wall -Wextra"
      LINK_FLAGS    "-g"
      )
add_test(${TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}  -xunitxml -o result.xml)
