#include "CursorHome.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

CursorHome::CursorHome()
    : prevCol{0}
{
}

void CursorHome::execute(EditorModel& model){
    //[0] save previous state 
    prevCol = model.cursorColumn();
    
    //move cursor to beginning of line
    model.setCursorColumn(1);
}

void CursorHome::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);

}