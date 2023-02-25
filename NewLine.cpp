#include "NewLine.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

NewLine::NewLine()
    :prevLin{0}, prevCol{0}, beyondCursor{""}
{
}

void NewLine::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    beyondCursor = model.line(model.cursorLine()).substr(prevCol-1);

    //[1] delete previous line substring
    model.deleting(prevCol, beyondCursor.length()); 

    //[2] shift cursor to beginning of the next line
    model.setCursorColumn(1);
    model.setCursorLine(model.cursorLine()+1);

    //[3] create newLine
    //accounts for index already
    model.createNewLine(beyondCursor);
 
    
}

void NewLine::undo(EditorModel& model){
    //delete current line
    model.deleteLine(model.cursorLine());
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);
    //insert previous text "beyondCursor" back
    model.insert(beyondCursor);

}