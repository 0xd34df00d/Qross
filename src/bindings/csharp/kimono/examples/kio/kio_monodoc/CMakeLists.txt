project(kio-monodoc)

find_package(PkgConfig)

if(PKG_CONFIG_FOUND)
	pkg_check_modules(MONODOC monodoc)
endif(PKG_CONFIG_FOUND)

if(MONODOC_FOUND)

	set(kio_monodoc_src kio_monodoc.cs)

	csharp_add_library(kio_monodoc "${kio_monodoc_src}" REFERENCES qt-dotnet kde-dotnet COMPILE_FLAGS ${MONODOC_LDFLAGS})

	install(FILES ${LIBRARY_OUTPUT_PATH}/kio_monodoc.dll DESTINATION ${DATA_INSTALL_DIR}/kio_monodoc RENAME main.dll)
	install(FILES monodoc.protocol DESTINATION ${SERVICES_INSTALL_DIR})

else(MONODOC_FOUND)

	message("monodoc was not found, not building kio_monodoc")

endif(MONODOC_FOUND)
