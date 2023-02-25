#include "InsertChar.hpp"
#include "EditorModel.hpp"
#include <string>

InsertChar::InsertChar(const std::string& character)
    :insertChar{character}, prevCol{0}
{
}
void InsertChar::execute(EditorModel& model){
    //[0] save previous state 
    prevCol = model.cursorColumn();
    //insert
    model.insert(insertChar);
    //move cursor 
    model.setCursorColumn(model.cursorColumn()+1);
}

void InsertChar::undo(EditorModel& model){
    //move cursor back 
    model.setCursorColumn(prevCol);
    //delete character 
    model.deleting(prevCol, 1);

}