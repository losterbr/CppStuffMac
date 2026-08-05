function(cppstuffmac_enable_warnings target_name)
  if(NOT CPPSTUFFMAC_ENABLE_WARNINGS)
    return()
  endif()

  if(MSVC)
    target_compile_options(${target_name} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target_name} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wshadow
      -Werror
    )
  endif()
endfunction()
