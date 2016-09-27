get_filename_component(SenOGL_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(SenOGL_INCLUDE_DIRS "${SenOGL_CMAKE_DIR}/external" "${SenOGL_CMAKE_DIR}/include/textures" "${SenOGL_CMAKE_DIR}/include/shaders" "${SenOGL_CMAKE_DIR}/include")
set(SenOGL_LIBRARIES SenOGL gl3w)
