cmake_minimum_required(VERSION 3.8)

cmake_policy(SET CMP0072 NEW) # new in 3.11. The NEW behavior for this policy is to set OpenGL_GL_PREFERENCE to GLVND.
cmake_policy(SET CMP0068 NEW) # new in 3.9. The NEW behavior of this policy is to ignore the RPATH settings for install_name on macOS.


project(QtNodesLibrary CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(OpenGL_GL_PREFERENCE LEGACY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_directory_property(_has_parent PARENT_DIRECTORY)
if(_has_parent)
  set(is_root_project OFF)
else()
  set(is_root_project ON)
endif()

set(QT_NODES_DEVELOPER_DEFAULTS "${is_root_project}" CACHE BOOL "Turns on default settings for development of QtNodes")

option(BUILD_TESTING "Build tests" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_EXAMPLES "Build Examples" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_DOCS "Build Documentation" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)
option(QT_NODES_FORCE_TEST_COLOR "Force colorized unit test output" OFF)
option(USE_QT6 "Build with Qt6 (Enabled by default)" ON)

enable_testing()

if(QT_NODES_DEVELOPER_DEFAULTS)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

if(BUILD_DEBUG_POSTFIX_D)
  set(CMAKE_DEBUG_POSTFIX "d")
  set(CMAKE_RELEASE_POSTFIX "")
  set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
  set(CMAKE_MINSIZEREL_POSTFIX "s")
endif()

#add_subdirectory(external)

if(USE_QT6)
  find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
else()
  find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
endif()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui OpenGL)
message(STATUS "QT_VERSION: ${QT_VERSION}, QT_DIR: ${QT_DIR}")

if (${QT_VERSION} VERSION_LESS 5.11.0)
  message(FATAL_ERROR "Requires qt version >= 5.11.0, Your current version is ${QT_VERSION}")
endif()

if (${QT_VERSION_MAJOR} EQUAL 6)
  qt_add_resources(RESOURCES ./NodeEditorEngine/resources/resources.qrc)
else()
  qt5_add_resources(RESOURCES ./NodeEditorEngine/resources/resources.qrc)
endif()

# Unfortunately, as we have a split include/src, AUTOMOC doesn't work.
# We'll have to manually specify some files
set(CMAKE_AUTOMOC ON)

set(CPP_SOURCE_FILES
  NodeEditorEngine/src/AbstractGraphModel.cpp
  NodeEditorEngine/src/AbstractNodeGeometry.cpp
  NodeEditorEngine/src/BasicGraphicsScene.cpp
  NodeEditorEngine/src/ConnectionGraphicsObject.cpp
  NodeEditorEngine/src/ConnectionState.cpp
  NodeEditorEngine/src/ConnectionStyle.cpp
  NodeEditorEngine/src/DataFlowGraphModel.cpp
  NodeEditorEngine/src/DataFlowGraphicsScene.cpp
  NodeEditorEngine/src/DefaultConnectionPainter.cpp
  NodeEditorEngine/src/DefaultHorizontalNodeGeometry.cpp
  NodeEditorEngine/src/DefaultNodePainter.cpp
  NodeEditorEngine/src/DefaultVerticalNodeGeometry.cpp
  NodeEditorEngine/src/Definitions.cpp
  NodeEditorEngine/src/GraphicsView.cpp
  NodeEditorEngine/src/GraphicsViewStyle.cpp
  NodeEditorEngine/src/NodeConnectionInteraction.cpp
  NodeEditorEngine/src/NodeDelegateModel.cpp
  NodeEditorEngine/src/NodeDelegateModelRegistry.cpp
  NodeEditorEngine/src/NodeGraphicsObject.cpp
  NodeEditorEngine/src/NodeState.cpp
  NodeEditorEngine/src/NodeStyle.cpp
  NodeEditorEngine/src/StyleCollection.cpp
  NodeEditorEngine/src/UndoCommands.cpp
  NodeEditorEngine/src/locateNode.cpp

  #user main

  src/main._cpp
  src/Nodes/MathOperationDataModel.cpp
  src/Nodes/NumberDisplayDataModel.cpp
  src/Nodes/NumberSourceDataModel.cpp
)

set(HPP_HEADER_FILES
  NodeEditorEngine/include/QtNodes/internal/AbstractConnectionPainter.hpp
  NodeEditorEngine/include/QtNodes/internal/AbstractGraphModel.hpp
  NodeEditorEngine/include/QtNodes/internal/AbstractNodeGeometry.hpp
  NodeEditorEngine/include/QtNodes/internal/AbstractNodePainter.hpp
  NodeEditorEngine/include/QtNodes/internal/BasicGraphicsScene.hpp
  NodeEditorEngine/include/QtNodes/internal/Compiler.hpp
  NodeEditorEngine/include/QtNodes/internal/ConnectionGraphicsObject.hpp
  NodeEditorEngine/include/QtNodes/internal/ConnectionIdHash.hpp
  NodeEditorEngine/include/QtNodes/internal/ConnectionIdUtils.hpp
  NodeEditorEngine/include/QtNodes/internal/ConnectionState.hpp
  NodeEditorEngine/include/QtNodes/internal/ConnectionStyle.hpp
  NodeEditorEngine/include/QtNodes/internal/DataFlowGraphicsScene.hpp
  NodeEditorEngine/include/QtNodes/internal/DataFlowGraphModel.hpp
  NodeEditorEngine/include/QtNodes/internal/Definitions.hpp
  NodeEditorEngine/include/QtNodes/internal/Export.hpp
  NodeEditorEngine/include/QtNodes/internal/GraphicsView.hpp
  NodeEditorEngine/include/QtNodes/internal/GraphicsViewStyle.hpp
  NodeEditorEngine/include/QtNodes/internal/locateNode.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeData.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeDelegateModel.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeDelegateModelRegistry.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeGraphicsObject.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeState.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeStyle.hpp
  NodeEditorEngine/include/QtNodes/internal/OperatingSystem.hpp
  NodeEditorEngine/include/QtNodes/internal/QStringStdHash.hpp
  NodeEditorEngine/include/QtNodes/internal/QUuidStdHash.hpp
  NodeEditorEngine/include/QtNodes/internal/Serializable.hpp
  NodeEditorEngine/include/QtNodes/internal/Style.hpp
  NodeEditorEngine/include/QtNodes/internal/StyleCollection.hpp
  NodeEditorEngine/include/QtNodes/internal/DefaultConnectionPainter.hpp
  NodeEditorEngine/include/QtNodes/internal/DefaultHorizontalNodeGeometry.hpp
  NodeEditorEngine/include/QtNodes/internal/DefaultNodePainter.hpp
  NodeEditorEngine/include/QtNodes/internal/DefaultVerticalNodeGeometry.hpp
  NodeEditorEngine/include/QtNodes/internal/NodeConnectionInteraction.hpp
  NodeEditorEngine/include/QtNodes/internal/UndoCommands.hpp

  #user include 

  src/Nodes/AdditionModel.hpp
  src/Nodes/DivisionModel.hpp
  src/Nodes/DecimalData.hpp
  src/Nodes/MathOperationDataModel.hpp
  src/Nodes/NumberDisplayDataModel.hpp
  src/Nodes/NumberSourceDataModel.hpp
  src/Nodes/SubtractionModel.hpp


  src/Nodes/FxData.hpp
  src/Nodes/FxBaseModel.hpp
  src/Nodes/FxExample.hpp
  src/Nodes/FxBaseModel.cpp
  src/Nodes/FxDataSource.hpp

  src/main.cpp
)

# If we want to give the option to build a static library,
# set BUILD_SHARED_LIBS option to OFF
add_executable(QtNodes
  ${CPP_SOURCE_FILES}
  ${HPP_HEADER_FILES}
  ${RESOURCES}
  src/Nodes/FxDataSource.cpp
  src/Nodes/FxDataset.hpp

)

#add_library(QtNodes::QtNodes ALIAS QtNodes)

target_include_directories(QtNodes PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/NodeEditorEngine/include/QtNodes/internal
)

target_include_directories(QtNodes PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/NodeEditorEngine/include
)

target_include_directories(QtNodes PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Nodes
)

target_link_libraries(QtNodes
  PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
)

target_compile_definitions(QtNodes
  PUBLIC
    $<IF:$<BOOL:${BUILD_SHARED_LIBS}>, NODE_EDITOR_SHARED, NODE_EDITOR_STATIC>
  PRIVATE
    NODE_EDITOR_EXPORTS
    #NODE_DEBUG_DRAWING
    QT_NO_KEYWORDS
)


target_compile_options(QtNodes
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc /utf-8>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Werror>
)
if(NOT "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
  # Clang-Cl on MSVC identifies as "Clang" but behaves more like MSVC:
  target_compile_options(QtNodes
    PRIVATE
      $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  )
endif()

if(QT_NODES_DEVELOPER_DEFAULTS)
  target_compile_features(QtNodes PUBLIC cxx_std_14)
  set_target_properties(QtNodes PROPERTIES CXX_EXTENSIONS OFF)
endif()


#set_target_properties(QtNodes
#  PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)

######
# Moc
##

file(GLOB_RECURSE HEADERS_TO_MOC include/QtNodes/internal/*.hpp)

if (${QT_VERSION_MAJOR} EQUAL 6)
  qt_wrap_cpp(nodes_moc
      ${HEADERS_TO_MOC}
      TARGET QtNodes
    OPTIONS --no-notes # Don't display a note for the headers which don't produce a moc_*.cpp
  )
else()
  qt5_wrap_cpp(nodes_moc
  ${HEADERS_TO_MOC}
  TARGET QtNodes
  OPTIONS --no-notes # Don't display a note for the headers which don't produce a moc_*.cpp
  )
endif()

target_sources(QtNodes PRIVATE ${nodes_moc})

###########
# Examples
##


##################
# Automated Tests
##

###############
# Installation
##
