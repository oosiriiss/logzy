if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/logzy-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package logzy)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT logzy_Development
)

install(
    TARGETS logzy_logzy
    EXPORT logzyTargets
    RUNTIME #
    COMPONENT logzy_Runtime
    LIBRARY #
    COMPONENT logzy_Runtime
    NAMELINK_COMPONENT logzy_Development
    ARCHIVE #
    COMPONENT logzy_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    logzy_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE logzy_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(logzy_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${logzy_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT logzy_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${logzy_INSTALL_CMAKEDIR}"
    COMPONENT logzy_Development
)

install(
    EXPORT logzyTargets
    NAMESPACE logzy::
    DESTINATION "${logzy_INSTALL_CMAKEDIR}"
    COMPONENT logzy_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
