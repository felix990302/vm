# UML

## Parsing
- function within Normal mode
- traverse through string / linearly
    - check if motion character
    - any type of commands `make_unique`

```plantuml
Controller o-- Application
Controller *-- FileBuffer
Controller *-- Mode
Controller : Mode *

abstract class Mode {
    -commandMap

    +exit()
    +interpret
}
CommandMode --|> Mode
MutateMode --|> CommandMode
InsertMode --|> MutateMode
ReplaceMode --|> MutateMode
CommandLineMode --|> Mode
QuantifierMode --|> MODE
MotionMode --|> QuantifierMode
NormalMode --|> MotionMode


Application o-- Controller
Application o-- View

View *-- BufferView
View *-- ControllerView
BufferView o-- FileBuffer
ControllerView o-- Controller

FileBuffer o-- Controller
FileBuffer *-- Cursor
FileBuffer *-- Lines

abstract class NotUndoable
NotUndoable --|> Command
Movement --|> NotUndoable
Search --|> Movement

abstract class Undoable
Undoable --|> Command
Cut --|> Undoable
Cut *-- Movement
```
