# Googletest
if(BUILD_TESTING)
  set(BUILD_GMOCK OFF)
  set(INSTALL_GTEST OFF)
  add_subdirectory(googletest)
endif()
# Google benchmark
if(BUILD_BENCHMARK)
  set(BENCHMARK_ENABLE_TESTING OFF)
  set(BENCHMARK_ENABLE_INSTALL OFF)
  add_subdirectory(benchmark)
endif()