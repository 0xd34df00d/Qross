SET(SRC_CS ${CMAKE_CURRENT_SOURCE_DIR}/listnames.cs)
CSHARP_ADD_EXECUTABLE(listnames "${SRC_CS}" REFERENCES qt-dotnet COMPILE_FLAGS /warn:0)
ADD_DEPENDENCIES(listnames qt-dotnet)
