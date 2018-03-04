# CMake generated Testfile for 
# Source directory: C:/VulkanSDK/spirv-tools
# Build directory: C:/Projects/Tracy/Source/spirvtools
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(spirv-tools-copyrights "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python36_64/python.exe" "utils/check_copyright.py")
  set_tests_properties(spirv-tools-copyrights PROPERTIES  WORKING_DIRECTORY "C:/VulkanSDK/spirv-tools")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(spirv-tools-copyrights "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python36_64/python.exe" "utils/check_copyright.py")
  set_tests_properties(spirv-tools-copyrights PROPERTIES  WORKING_DIRECTORY "C:/VulkanSDK/spirv-tools")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(spirv-tools-copyrights "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python36_64/python.exe" "utils/check_copyright.py")
  set_tests_properties(spirv-tools-copyrights PROPERTIES  WORKING_DIRECTORY "C:/VulkanSDK/spirv-tools")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(spirv-tools-copyrights "C:/Program Files (x86)/Microsoft Visual Studio/Shared/Python36_64/python.exe" "utils/check_copyright.py")
  set_tests_properties(spirv-tools-copyrights PROPERTIES  WORKING_DIRECTORY "C:/VulkanSDK/spirv-tools")
else()
  add_test(spirv-tools-copyrights NOT_AVAILABLE)
endif()
subdirs("external")
subdirs("source")
subdirs("tools")
subdirs("test")
subdirs("examples")
