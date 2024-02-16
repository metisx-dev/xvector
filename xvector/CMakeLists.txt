cmake_minimum_required(VERSION 3.11)

message("Building core only ${XVECTOR_BUILD_CORE_ONLY}")

if (${XVECTOR_BUILD_SIM})
  message("XVECTOR_BUILD_SIM")
  add_subdirectory(core)
  add_subdirectory(sim)
elseif (${XVECTOR_BUILD_CORE_ONLY})
  message("XVECTOR_BUILD_CORE_ONLY")
  add_subdirectory(core)
else()
  #add_subdirectory(mu)
endif()
