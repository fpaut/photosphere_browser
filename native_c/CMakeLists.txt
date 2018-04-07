cmake_minimum_required (VERSION 2.6)
project (PhotoSphereBwr)
set(CMAKE_BUILD_TYPE Debug)

# The version number.
set (PhotoSphereBwr_VERSION_MAJOR 1)
set (PhotoSphereBwr_VERSION_MINOR 0)
 
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/PhotoSphereBwrConfig.h.in"
  "${PROJECT_BINARY_DIR}/PhotoSphereBwrConfig.h"
  )
  
find_package(OpenGL)
find_package(X11)
include(FindFreetype)
include_directories(${FREETYPE_INCLUDE_DIRS})
#--------------------------------------------------------------
#               Source files
#--------------------------------------------------------------
#add_executable(PhotoSphereBwr main.c wingl.c  bmp.c fonts.c mat_vect.c mat_matr.c 3ds.c)
add_executable(PhotoSphereBwr   main.c 
                                glmodels.c
                                glwin.c
                                bmp.c
                                3ds.c
                                font_truetype/src/draw.c
                                font_truetype/src/drawgl.c
                                font_truetype/src/drawrast.c
                                font_truetype/src/font.c
                                font_truetype/src/tpool.c
                                font_truetype/src/utf8.c)

#--------------------------------------------------------------
#               Include directories
#--------------------------------------------------------------
include_directories(
	"${PROJECT_BINARY_DIR}"
)

#--------------------------------------------------------------
#               Libraries used
#--------------------------------------------------------------
## foreach(_LIB X11 Xext Xcursor Xinerama Xi Xrandr Xrender Xss Xxf86vm)
foreach(_LIB Xext GL GLU m X11 freetype)
   string(TOUPPER ${_LIB} _LNAME)
   find_library(${_LNAME}_LIB ${_LIB})
   if(${_LNAME}_LIB)
    # reduce the library name for shared linking
    get_filename_component(_TMP ${${_LNAME}_LIB} NAME)
    set(${_LNAME}_LIB ${_TMP})
   	MESSAGE(">>> DBG : " "TARGET_LINK_LIBRARIES " ${_TMP})
	TARGET_LINK_LIBRARIES(PhotoSphereBwr ${_TMP})
  endif()
endforeach()

if (XEXT_LIB)
   MESSAGE(">>> XEXT_LIB Correctly Found")
else (XEXT_LIB)
   MESSAGE(">>> XEXT_LIB Not Found")
endif(XEXT_LIB)

if (OPENGL_FOUND)
   MESSAGE(">>> OpenGL Correctly Found")
else (OPENGL_FOUND)
   MESSAGE(">>> OpenGL environment missing")
endif (OPENGL_FOUND)



# add the install targets
install (TARGETS PhotoSphereBwr DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/PhotoSphereBwrConfig.h"        
         DESTINATION include)