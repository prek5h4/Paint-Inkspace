cmake_minimum_required(VERSION 3.16)
project(COL290_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

set(COP290_1
    main.cpp

    GUI/MainWindow.cpp
    GUI/MainWindow_1.cpp
    GUI/MainWindow_2.cpp
    GUI/CanvasWidget.cpp
    GUI/CanvasWidget_1.cpp
    GUI/CanvasWidget_2.cpp
    GUI/AddandRemove_CW.cpp
    GUI/Clipboard_CW.cpp
    GUI/getSVGDocument.cpp
    GUI/loadSVGDocument_CW.cpp
    GUI/Move_Erase_CW.cpp
    GUI/SelectShape_CW.cpp
    GUI/TextToolBar.cpp
    GUI/ToolMenu.cpp
    resources.qrc

    Commands/BucketShapeCommand.cpp
    Commands/ChangeStrokeColor.cpp
    Commands/ChangeStrokeSizeCommand.cpp
   
    Commands/DeleteShapeCommand.cpp
    Commands/DrawShapeCommand.cpp
    Commands/MoveShapeCommand.cpp
    Commands/ResizeShapeCommand.cpp

    History/CommandManager.cpp

    Parser/SVGDocument.cpp
    Parser/SVGElement.cpp
    Parser/SvgParser.cpp
    Parser/SvgParser_1.cpp
    Parser/SVGWriter.cpp
    Parser/XmlTokenizer_1.cpp
    Parser/XmlTokenizer.cpp
)

add_executable(vector_editor ${COP290_1})

target_include_directories(vector_editor PRIVATE  
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands
    ${CMAKE_CURRENT_SOURCE_DIR}/History
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser
)
target_link_libraries(vector_editor
    Qt6::Widgets
    Qt6::Svg
)