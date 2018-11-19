# Plan of Attack

## Parsing
- function within Normal mode
- traverse through string / linearly
    - check if motion character
    - any type of commands `make_unique`

## UML

### Legend

```plantuml
abstract class LEGEND {
    -private field
    #protected field
    +public field

    -private method() 
    #protected method()
    +public method()
}

```
### General Architecture

```plantuml
abstract class Controller {
    -ControllerViews
    -Mode*
    -Stack<TrackableCommand*> UndoStack
    -Stack<TrackableCommand*> RedoStack

    +addControllerView()
    +remoteControllerView()
    +getMode()
}
Controller --o ControllerView
Controller --* Application
Controller --o FileBuffer

abstract class Mode {
    -commandMap

    +exit()
    +interpret()
}
Mode --* Controller
Mode <|-- CommandMode

CommandMode <|-- CommandLineMode
CommandMode <|-- MutateMode

abstract class MutateMode
MutateMode <|-- InsertMode
MutateMode <|-- ReplaceMode

abstract class View {
    +resize()
}
View <|-- NCursesView
View <|-- DecoratedView
View --o DecoratedView
View --o Application

abstract class DecoratedView

class BufferView {
    +notify()
    +updateScreen()
}
BufferView --* View

class ControllerView {
    +notify()
    +updateScreen()
}
ControllerView --* View

abstract class FileBuffer {
    -BufferViews

    -notifyBufferViews()
    +addBufferView
    +removeBufferView
    +getState()
}
FileBuffer --o BufferView

Cursor --* FileBuffer

Lines --* FileBuffer
```

### Commands

```plantuml
abstract class Command {
    -repetitions

    +do() 
    +undo()
    +redo()
}
Command <|-- MovementCommand
Command <|-- MutateCommand

abstract class MovementCommand {
    +getPosition()
    +move()
}
MovementCommand --* MutateCommand
MovementCommand <|-- Find
MovementCommand <|-- Search

abstract class TrackableCommand
TrackableCommand <|-- Cut

abstract class MutateCommand
MutateCommand <|-- Cut
```

## An Idea to Consider

```plantuml
QuantifierMode --|> MODE
MotionMode --|> QuantifierMode
NormalMode --|> MotionMode
```
