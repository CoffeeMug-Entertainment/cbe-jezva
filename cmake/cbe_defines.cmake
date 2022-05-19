 IF(WIN32)
 add_definitions(-DCBE_WINDOWS)
 ELSEIF(UNIX AND NOT APPLE) # Mac not supported atm
 add_definitions(-DCBE_LINUX)
ENDIF()