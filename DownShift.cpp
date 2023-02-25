#include "DownShift.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

DownShift::DownShift()
    :prevLin{0}, prevCol{0}
{
}

void DownShift::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    
    //[case1]: cursorLine == numLines
    //[case2]: cursorLine != numLines

    if(model.cursorLine() == model.lineCount()){
        throw EditorException("Already at bottom");
    }else{
        //change cursor line 
        model.setCursorLine(model.cursorLine()+1);
        //check if column beyond maxCol
        if(model.cursorColumn() > model.maxLineCol()){
            model.setCursorColumn(model.maxLineCol()+1);
        }
    }
}

void DownShift::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);

}