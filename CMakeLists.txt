
INCLUDE(BuildPlugin)

# SET(RESOURCES icons.qrc)

BUILD_PLUGIN(
  melodyeditor
    MelodyEditor.cpp
    MelodyEditorTextArea.cpp
    MelodyEditorView.cpp
    src/includes/Utilities.cpp
    #src/parsers/AldaParser.cpp
    #src/parsers/SimpleParser.cpp
    #src/parsers/StringReader.cpp
    #src/parsers/LuaParser.cpp
    src/parsers/ABCParser.cpp
    ABC-parser/abc_parser.c

  MOCFILES
    MelodyEditor.h
    MelodyEditorTextArea.h
    MelodyEditorView.h
    src/includes/Utilities.h
 
  EMBEDDED_RESOURCES
    src/assets/logo.svg
    src/assets/logo.ico

    # Notation System Icons
    src/assets/ns-hindustani.svg
    src/assets/ns-carnatic.svg
    src/assets/ns-english.svg
)
