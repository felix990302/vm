# Plan of Attack

## Parsing
- function within Normal mode
- traverse through string / linearly
    - check if motion character
    - any type of commands `make_unique`

## UML

### Legend

```plantuml

class Class

abstract class AbstractClass

object LEGEND {
    -private field
    #protected field
    +public field
    {static} static field

    -private method() 
    #protected method()
    +public method()
    {abstract} virtual method()
    {static} static method()
}

```
### General Architecture

```plantuml
class Application {
    -argc : Int
    -argv : char**
}

abstract class Controller {
    -Stack<UndoableCommand*> UndoStack
    -Stack<UndoableCommand*> RedoStack

    {abstract} +getAndProcessChar() : Void
}
Controller --* Application
Controller --o FileBuffer

abstract class Input {
    {abstract} +getChar() : Char
}
Input --* Controller
Input <|-- NCursesInput

class NCursesInput {
    +getChar() : Char
}

abstract class Mode {
    {abstract} +processChar() : void
}
Mode --* Controller
Mode <|-- InsertMode

class InsertMode {
    +processChar() : void
}

class BufferView {
    +draw(Coordinates, TextDisplay) : void
}
BufferView --* Application

abstract class Component {
    {abstract} +setSize(Coordinates) : void
    {abstract} +setPosn(Coordinates) : void
    {abstract} +draw(Coordinates, TextDisplay) : void
    +getSize() : Coordinates
    +getPosn() : Coordinates
    +enforceFitIntoSize(Coordinates) : void
    +appendChildren(Component *) : void
    +detachChildren(Component *) : void
}
Component --o TextDisplay
Component --o Component
Component <|-- BufferView

abstract class TextDisplay {
    {abstract} +putc(Coordinates, char) : void 
    {abstract} +putc(Coordinates, string) : void 
    {abstract} +redraw() : void;
    {abstract} +resizeHandler(Coordinates) : void
    +getMainComponent() : Component *
    +setMainCompoenent(Component *) : void
}
TextDisplay --o Application
TextDisplay <|-- NCursesDisplay

class NCursesDisplay {
    {static} NCursesDisplay

    {static} +resizeHandler(int) : void
    {static} +getMainDisplay() : NCursesDisplay
    +putc(Coordinates, char) : void
    +puts(Coordinates, string) : void
    +redraw() : void
}

class Coordinates {
    +cor_t x
    +cor_t y
}
Coordinates --* Component

class BufferType
BufferType --* FileBuffer

class FileBuffer {
    +type(char) : void
    +type(String) : void
    +delete_forward(int) : void
    +delete_backward(int) : void
    +getBuffer() : BufferType
}
FileBuffer --* Application
FileBuffer --o Controller
FileBuffer --o BufferView

class Cursor {
    +line : size_t
    +col : size_t
}
Cursor --* BufferView
Cursor <|-- PtrCursor

class PtrCursor {
    +linePosn : BufferType::iterator
    +charPosn : LineType::iterator:w
}
PtrCursor --* FileBuffer
```

### Commands

```plantuml
abstract class Command {
    -quant : size_t

    +doCommand() : void 
}
Command <|-- MoveCommand
Command <|-- UndoableCommand
Command <|-- EnterInsertCommand

abstract class MoveCommand {
}

abstract class UndoableCommand {
    {abstract} +UndoCommand() : void
    {abstract} +RedoCommand() : void
}
UndoableCommand <|-- MutateCommand

abstract class MutateCommand
MutateCommand <|-- InsertCommand
MutateCommand <|-- DeleteCommand

class InsertCommand {
    +doCommmand() : void
    +UndoCommand() : void
    +RedoCommand() : void
}

class DeleteCommand {
    +doCommmand() : void
    +UndoCommand() : void
    +RedoCommand() : void
}

class Motion {
    +nextPosition(Cursor) : Cursor    
}
Motion --* MoveCommand
Motion --* UndoableCommand

object Direction {
    Up
    Down
    Forward
    Backward
}
Direction --* MutateCommand
```
