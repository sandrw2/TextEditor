#include "RightShift.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

RightShift::RightShift()
    :prevLin{0}, prevCol{0}
{
}

void RightShift::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    
    //[1]check if current Col = one beyond the last column of current line 
    if(model.cursorColumn() == model.maxLineCol()+1){
        //[2]check if current Line = last line
        if(model.cursorLine() == model.lineCount()){
            //[case 1]: error
            //throw exception
            throw EditorException("Already at end");
        }else{
            //[case 2]: goes to next line
            //go to next line 
            model.setCursorLine(model.cursorLine()+1);
            //set cursor column --> beginning of next line
            model.setCursorColumn(1);
        }
    }else{
        //[case 3]: stays on same line
        model.setCursorColumn(model.cursorColumn()+1);
    }
}

void RightShift::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);

}