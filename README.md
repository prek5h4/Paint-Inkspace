# Micro-Vector Editor (SVG)

A Qt-based vector graphics editor supporting SVG file manipulation with a graphical user interface.

## Overview

This application is a vector graphics editor inspired by tools like Inkscape. It provides functionality to:
- Read and parse SVG files (restricted subset)
- Display and edit vector graphics on a canvas
- Create new drawings from scratch
- Export edited diagrams to SVG format

## Features

### Supported Shapes
1. **Rectangle** - Standard rectangular shapes with configurable dimensions
2. **Rounded Rectangle** - Rectangles with rounded corners (radius configurable)
3. **Circle** - Circular shapes with center point and radius
4. **Line** - Straight lines between two points
5. **Hexagon** - Regular hexagonal shapes
6. **Freehand** - Free-form drawing with mouse/stylus
7. **Text** - Text objects with configurable font and size

### Drawing Tools
- **Shape Creation**: Click and drag to create shapes
- **Move Tool**: Select and move existing shapes
- **Resize Tool**: Modify shape dimensions
- **Erase Tool**: Delete unwanted shapes
- **Bucket Fill**: Change fill color of existing shapes
- **Stroke Tools**: Modify stroke color and width

### Menu Features

#### File Menu
- **New**: Create a new blank canvas
- **Open**: Load existing SVG files
- **Save**: Save edits made to file
- **Save As**: Save current drawing to SVG format
- **Exit**: Close the application

#### Edit Menu
- **Undo** (Ctrl+Z): Revert last action
- **Redo** (Ctrl+Y): Reapply undone action

#### Clipboard Menu
- **Cut** (Ctrl+X): Remove and copy selected shape
- **Copy** (Ctrl+C): Copy selected shape
- **Paste** (Ctrl+V): Paste copied shape at cursor position

### Drawing Properties
- **Brush Color**: Configure stroke/outline color
- **Fill Color**: Configure interior color
- **Brush Size**: Set stroke width
- **Font Selection**: Configure text properties (for Text tool)

## Architecture

### Core Components

#### 1. Shape Representation - Design Decision

**Architecture Choice: Type-Discriminated Struct**

This project uses a monolithic `Shape` struct with type discrimination rather than an inheritance hierarchy:

```cpp
struct Shape {
    enum Type { Rectangle, Circle, Line, Hexagon, Freehand, Text };
    Type type;
    QPoint startPoint, endPoint;
    QColor brush_color, fillColor;
    int width;
    // ... shape-specific data
};
```

**Rationale for This Design:**

1. **Simplified Qt Integration**: Works seamlessly with Qt's signal/slot mechanism and event handling
2. **Command Pattern Efficiency**: Easier to implement undo/redo with uniform type representation
3. **Natural SVG Mapping**: Direct correspondence to SVG's type-based element structure
4. **Simplified Serialization**: All shape data in one place simplifies save/load operations
5. **Clipboard Operations**: Easy to clone/copy shapes with all data together
6. **Reduced Complexity**: Fewer files, simpler codebase maintenance

**Trade-offs Acknowledged:**

- Uses enum-based type discrimination instead of polymorphism
- Switch statements rather than virtual function calls
- Less "textbook OOP" but more pragmatic for this application's scope

**Alternative Considered:**

An inheritance hierarchy (`GraphicsObject` base class with derived `Circle`, `Rectangle`, etc.) was considered but found to add complexity in:
- Qt signal/slot integration
- Command pattern implementation (storing mixed-type pointers)
- SVG serialization/deserialization
- Shape cloning for clipboard operations

For this application's requirements, the struct approach provides the best balance of simplicity, functionality, and maintainability. This pragmatic decision prioritizes working software and clean implementation over theoretical OOP purity.

#### 2. SVG Parsing System

**XmlTokenizer** (`XmlTokenizer.cpp`)
- Tokenizes XML/SVG input into structured tokens
- Handles tags, attributes, and text nodes
- Supports self-closing tags

**SVGParser** (`SvgParser.cpp`)
- Converts XML tokens into shape objects
- Parses SVG-specific attributes (stroke, fill, dimensions)
- Builds document model from SVG structure

**SVGDocument** (`SVGDocument.cpp`)
- Container for SVG elements
- Manages document-level attributes (width, height, viewBox)
- Provides element collection interface

**SVGWriter** (`SvgWriter.cpp`)
- Serializes document model back to SVG format
- Handles proper XML escaping
- Generates valid SVG 1.1 output

#### 3. GUI Components

**MainWindow** (`MainWindow.cpp`)
- Application main window and menu system
- Manages toolbars and action handlers
- Coordinates file I/O operations

**CanvasWidget** (`CanvasWidget.cpp`)
- Main drawing surface
- Handles mouse events for drawing/editing
- Manages shape collection and rendering
- Implements tool selection logic

**ToolMenu** (`ToolMenu.cpp`)
- Toolbar for shape selection tools
- Icon-based tool switching

**TextToolBar** (`TextToolBar.cpp`)
- Specialized toolbar for text tool
- Font selection interface

#### 4. Command Pattern (Undo/Redo)

**CommandManager**
- Maintains undo/redo stacks
- Executes and manages commands

**Command Types**
- `DrawShapeCommand`: Add new shape
- `DeleteShapeCommand`: Remove shape
- `MoveShapeCommand`: Change position
- `ResizeShapeCommand`: Modify dimensions
- `BucketShapeCommand`: Change fill color
- `ChangeStrokeCommand`: Modify stroke properties
- `ClipboardCommands`: Cut/copy/paste operations

### File Organization

```
project/
├── GUI/                     # User interface components
│   ├── MainWindow.{h,cpp}
│   ├── MainWindow_1.cpp     # File operations
│   ├── MainWindow_2.cpp     # Edit operations  
│   ├── CanvasWidget.{h,cpp}
│   ├── CanvasWidget_1.cpp   # Rendering
│   ├── CanvasWidget_2.cpp   # Event handling
│   ├── AddandRemove_CW.cpp  # Shape management
│   ├── Move_Erase_CW.cpp    # Transform tools
│   ├── Clipboard_CW.cpp     # Clipboard operations
│   ├── SelectShape_CW.cpp   # Selection logic
│   ├── getSVGDocument.cpp   # SVG export from shapes
│   ├── loadSVGDocument_CW.cpp # SVG import to shapes
│   ├── ToolMenu.{h,cpp}
│   ├── TextToolBar.{h,cpp}
│   └── Canvas.{h,cpp}
│
├── Parser/                  # SVG I/O
│   ├── XmlTokenizer.{h,cpp}
│   ├── XmlTokenizer_1.cpp
│   ├── SVGParser.{h,cpp}
│   ├── SvgParser_1.cpp
│   ├── SVGElement.{h,cpp}
│   ├── SVGDocument.{h,cpp}
│   └── SvgWriter.{h,cpp}
│
├── History/                 # Command pattern
│   └── CommandManager.h
│
├── Commands/                # Undo/redo commands
│   ├── DrawShapeCommand.h
│   ├── DeleteShapeCommand.h
│   ├── MoveShapeCommand.h
│   ├── ResizeShapeCommand.h
│   ├── BucketShapeCommand.h
│   ├── ChangeStrokeCommand.h
│   ├── ChangeStrokeSizeCommand.h
│   └── ClipboardCommands.h
│
├── resources/               # Icons and assets
│   └── icons/*.png
│
├── main.cpp                # Application entry point
├── CMakeLists.txt         # CMake build configuration
├── test_3.pro             # Qt project file (qmake - legacy)
└── resources.qrc          # Qt resource file
```

**Note on File Organization**: Some implementation files are currently split (e.g., `CanvasWidget_1.cpp`, `CanvasWidget_2.cpp`), as mentioned in assignment no file has more than ~100-120 lines.

## Building and Running

### Prerequisites

- **Qt 5/6**: Qt framework (Community Edition)
  - Download from: https://www.qt.io/download-open-source
- **C++17** or later compiler
- **CMake** 3.10+ (required for submission)

### Build Instructions

#### Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Run
./paint-editor
```

#### Using Qt Creator

1. Open `test_3.pro` in Qt Creator
2. Configure project with appropriate kit
3. Build and run

#### Using qmake (Alternative)

```bash
qmake test_3.pro
make
./paint-editor
```

## Usage Guide

### Creating Shapes

1. Select desired shape tool from toolbar
2. Click and drag on canvas to create shape
3. Release mouse to finalize
4. For text tool: enter text in dialog after placing

### Editing Shapes

**Moving Shapes**
1. Select Move tool
2. Click on shape to select
3. Drag to new position

**Resizing Shapes**
1. Select Resize tool
2. Click on shape to select
3. Drag to adjust size

**Changing Colors**
1. Use Brush → Brush Color for stroke
2. Use Brush → Fill Color for interior
3. Or use Bucket tool to fill selected shape

**Deleting Shapes**
1. Select Erase tool
2. Click on shape to delete

### File Operations

**Opening SVG Files**
1. File → Open (Ctrl+O)
2. Select SVG file
3. Drawing loads on canvas

**Saving Work**
1. File → Save (Ctrl+S)
2. Choose location and filename
3. File saves as SVG format

**Clipboard Operations**
1. Select Move tool and click shape
2. Edit → Copy/Cut (Ctrl+C/X)
3. Edit → Paste (Ctrl+V)
4. Pasted shape appears at cursor

### Undo/Redo

- **Undo**: Edit → Undo (Ctrl+Z)
- **Redo**: Edit → Redo (Ctrl+Y)

## Technical Implementation Details

### Shape Representation

Each shape is stored as a `Shape` struct containing:
- **Type**: Enum identifying shape kind (Rectangle, Circle, Line, Hexagon, Freehand, Text)
- **Geometry**: Position (startPoint, endPoint), control points
- **Appearance**: Stroke color (brush_color), fill color (fillColor), stroke width (width)
- **Type-specific Data**: Font (text), radius (rounded rect), points array (freehand)

This unified representation simplifies:
- Shape management in vectors
- Command pattern for undo/redo
- SVG serialization/deserialization
- Clipboard operations (cut/copy/paste)

### SVG Subset Support

The parser handles:
- `<svg>` root element with width/height/viewBox
- `<rect>` for rectangles
- `<circle>` for circles
- `<line>` for lines
- `<polygon>` for hexagons
- `<path>` for freehand (M/L commands)
- `<text>` for text elements

Attributes supported:
- Geometry: `x`, `y`, `width`, `height`, `cx`, `cy`, `r`, `x1`, `y1`, `x2`, `y2`, `rx`, `ry`
- Appearance: `fill`, `stroke`, `stroke-width`
- Text: `font-family`, `font-size`

### Command Pattern Implementation

The undo/redo system uses the Command design pattern:

```cpp
class Command {
    virtual void execute() = 0;
    virtual void undo() = 0;
};
```

Each user action creates a Command object that:
1. Stores state needed for undo
2. Implements execute() to perform action
3. Implements undo() to reverse action

CommandManager maintains two stacks:
- **Undo stack**: Completed commands
- **Redo stack**: Undone commands available for redo

### Memory Management

- **Smart Pointers**: All shapes use `std::shared_ptr<Shape>`
- **RAII**: Automatic cleanup prevents memory leaks
- **Qt Parent-Child**: GUI elements use Qt's ownership model

## Design Patterns Used

1. **Command Pattern**: Undo/redo system
2. **Factory Pattern**: Shape creation from SVG
3. **MVC Pattern**: Model (shapes), View (canvas), Controller (MainWindow)

## Design Philosophy

### Pragmatic Over Pure

This project prioritizes pragmatic solutions that work reliably over theoretical perfection:

- **Type-discriminated structs** instead of inheritance hierarchy for shapes
- **Unified shape representation** simplifies serialization and command pattern
- **Direct Qt integration** without unnecessary abstraction layers

### Why This Approach?

**Real-world Benefits:**
- Simpler codebase (easier to maintain and debug)
- Faster development (less boilerplate)
- Better Qt integration (natural fit with signal/slot)
- Easier testing (fewer moving parts)

## Known Limitations

1. **SVG Subset**: Only supports listed shapes, not full SVG spec
2. **Advanced SVG**: No support for gradients, filters, animations
3. **Transform Attributes**: SVG transform attribute not supported
4. **Layers**: No layer system
5. **Groups**: Limited support for grouped elements

## Code Quality Guidelines

Following Google C++ Style Guide:

### Naming Conventions
- **Classes**: PascalCase (`CanvasWidget`)
- **Functions**: camelCase (`drawShape()`)
- **Variables**: snake_case or camelCase
- **Member Variables**: trailing underscore (`cx_`, `cy_`)
- **Constants**: kConstantName

### Header Files
- Use include guards or `#pragma once`
- Headers contain declarations only
- Implementation in .cpp files
- Minimal dependencies

### Smart Pointers
- Use `std::shared_ptr` for shared ownership
- Use `std::unique_ptr` for exclusive ownership
- Avoid raw pointers for ownership

### Comments
- File-level comments describing purpose
- Class-level documentation
- Function documentation for complex logic
- Inline comments for non-obvious code

## Testing

### Manual Testing Workflow

1. **Shape Creation**
   - Test each shape tool
   - Verify appearance matches expectations

2. **File I/O**
   - Save and reload file
   - Open sample SVG files
   - Verify parsed correctly

3. **Editing**
   - Move, resize, delete shapes
   - Test undo/redo after each operation
   - Verify clipboard operations

4. **Edge Cases**
   - Empty document
   - Large/small shapes
   - Overlapping shapes
   - Invalid SVG files

## Troubleshooting

### Build Issues

**Qt not found**
```bash
export CMAKE_PREFIX_PATH=/path/to/Qt/5.15.2/gcc_64
```

**Missing includes**
- Verify all Qt modules installed
- Check Qt version compatibility

### Runtime Issues

**Shapes not appearing**
- Check brush/fill colors (might be same as background)
- Verify shape has non-zero dimensions

**File won't open**
- Ensure file is valid SVG
- Check file permissions
- Verify parser handles the SVG structure

**Undo/Redo not working**
- Check command is properly recorded
- Verify CommandManager is used for all edits

## Future Enhancements

Potential improvements:
1. Layer system
2. Group/ungroup shapes
3. Alignment tools
4. Distribution tools
5. More shape types (ellipse, polygon, star)
6. Gradient fills
7. Export to other formats (PNG, PDF)
8. Keyboard shortcuts for tools
9. Snap to grid
10. Rulers and guides

## References

- SVG Specification: https://www.w3.org/TR/SVG2/
- XML Standard: https://www.w3schools.com/xml/
- Qt Documentation: https://doc.qt.io/
- Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html
