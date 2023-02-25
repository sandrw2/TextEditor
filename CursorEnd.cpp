#include "CursorEnd.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

CursorEnd::CursorEnd()
    : prevCol{0}
{
}

void CursorEnd::execute(EditorModel& model){
    //[0] save previous state 
    prevCol = model.cursorColumn();
    
    //move cursor to end of line
    model.setCursorColumn(model.maxLineCol()+1);
}

void CursorEnd::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);

}