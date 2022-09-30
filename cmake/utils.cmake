FUNCTION(LOAD_PROFILE __ARCH PLATFORM)
  # Obtain sources for the ISA
  FILE(GLOB LIBC_SRCS "${__ARCH}/*.c" "${ISA}/*.s")
  FILE(GLOB PLATFORM_SRCS "${__ARCH}/${PLATFORM}/*.c" "${__ARCH}/${PLATFORM}/*.s")
 
  # Load flags associated with ISA and Profile
  INCLUDE("${__ARCH}/flags.cmake")
  INCLUDE("${__ARCH}/${PLATFORM}/flags.cmake")
 
  # Now export our output variables
  SET(LIBC_SRCS ${LIBC_SRCS} PARENT_SCOPE)
  SET(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
  SET(PLATFORM_LAYOUT "${__ARCH}/${PLATFORM}/layout.ld" PARENT_SCOPE)
 
  # And specific flags
  SET(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
  SET(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
  # ...
ENDFUNCTION(LOAD_PROFILE)
