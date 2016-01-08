
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt5Quick library
find_package(Qt5Quick 5.1)


set (qmlFiles
	qml/main.qml
	qml/latex/CoffeeStains.qml
	)

set (HeaderFiles
	ImageProvider.h
	Reports/LatexCompiler.h
	Reports/LatexCompilerWorker.h
	Reports/LatexDocument.h
	Reports/LatexCodeBlock.h
	Reports/LatexSyntaxHighLighter.h
	#Reports/LatexModelMapper.h
	)
			
set (SourceFiles
	main.cpp
	ImageProvider.cpp
	Reports/LatexCompiler.cpp
	Reports/LatexCompilerWorker.cpp
	Reports/LatexDocument.cpp
	Reports/LatexCodeBlock.cpp
	Reports/LatexSyntaxHighLighter.cpp
	#Reports/LatexModelMapper.cpp
	)

# Tell CMake to create the executable
add_executable(qmlatex ${SourceFiles} ${HeaderFiles} ${qmlFiles})

# Use the Quick module from Qt 5.
target_link_libraries(qmlatex Qt5::Quick)

source_group("Reports" REGULAR_EXPRESSION "Reports/.*")
source_group("qml" REGULAR_EXPRESSION "qml/.*")
source_group("qml\\latex" REGULAR_EXPRESSION "qml/latex/.*")