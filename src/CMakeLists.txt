
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt5Quick library
find_package(Qt5Quick)
find_package(Qt5Sql)
find_package(Qt5Widgets)


set (qmlFiles
	qml/main.qml
	qml/MyLatexDocument.qml
	qml/latex/CoffeeStains.qml
	qml/latex/LatexChart.qml
	qml/latex/LatexEnumerate.qml
	qml/latex/LatexGeometry.qml
	qml/latex/LatexItem.qml
	qml/latex/LatexLongTable.qml
	qml/latex/LatexParagraph.qml
	qml/latex/LatexSampleChart.qml
	qml/latex/LatexSection.qml
	qml/latex/LatexSubSection.qml
	qml/latex/LatexSubSubSection.qml
	)

set (HeaderFiles
	ImageProvider.h
	IQmlModelSchemaPresenter.h
	SqlQueryModel.h
	Reports/LatexCompiler.h
	Reports/LatexCompilerWorker.h
	Reports/LatexDocument.h
	Reports/LatexCodeBlock.h
	Reports/LatexSyntaxHighLighter.h
	Reports/LatexModelMapper.h
	)
			
set (SourceFiles
	main.cpp
	ImageProvider.cpp
	SqlQueryModel.cpp
	Reports/LatexCompiler.cpp
	Reports/LatexCompilerWorker.cpp
	Reports/LatexDocument.cpp
	Reports/LatexCodeBlock.cpp
	Reports/LatexSyntaxHighLighter.cpp
	Reports/LatexModelMapper.cpp
	)

# Tell CMake to create the executable
add_executable(qmlatex ${SourceFiles} ${HeaderFiles} ${qmlFiles})

# Use the Quick module from Qt 5.
target_link_libraries(qmlatex Qt5::Quick Qt5::Sql Qt5::Widgets)

source_group("Reports" REGULAR_EXPRESSION "Reports/.*")
source_group("qml" REGULAR_EXPRESSION "qml/.*")
source_group("qml\\latex" REGULAR_EXPRESSION "qml/latex/.*")
