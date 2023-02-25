#include "UpShift.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

UpShift::UpShift()
    :prevLin{0}, prevCol{0}
{
}

void UpShift::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    
    //[case1]: cursorLine == 1
    //[case2]: cursorLine != 1

    if(model.cursorLine()==1){
        throw EditorException("Already at top");
    }else{
        //change cursor line 
        model.setCursorLine(model.cursorLine()-1);
        //check if column beyond maxCol
        if(model.cursorColumn() > model.maxLineCol()){
            model.setCursorColumn(model.maxLineCol()+1);
        }
    }
}

void UpShift::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);

}