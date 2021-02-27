
set(SEQ64_SHARED_SOURCES
    CommandLine.hpp
    CommandLine.cpp
    Common.hpp
    SeqFile.cpp 
    SeqFile.hpp
PARENT_SCOPE)

set(SEQ64_CONSOLE_ONLY_SOURCES
    MainConsole.cpp
PARENT_SCOPE)

set(SEQ64_GUI_ONLY_SOURCES
    MainGUI.cpp
    SeqABIEditor.cpp
    SeqABIEditor.hpp
    SeqEditor.cpp
    SeqEditor.hpp
    TextListBox.cpp
    TextListBox.hpp
PARENT_SCOPE)
