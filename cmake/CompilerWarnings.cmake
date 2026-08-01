function(cppstuffmac_enable_warnings target_name)
  if(NOT CPPSTUFFMAC_ENABLE_WARNINGS)
    return()
  endif()

  if(MSVC)
    target_compile_options(${target_name} PRIVATE /W4)
  else()
    target_compile_options(${target_name} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wno-unused-parameter
      -Wno-unused-variable
    )
  endif()
endfunction()
