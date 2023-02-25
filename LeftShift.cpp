#include "LeftShift.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

LeftShift::LeftShift()
    :prevLin{0}, prevCol{0}
{
}

void LeftShift::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    
    //[case1]: cursorCol == 1, cursorLine == 1 --> error
    //[case2]: cursorCol == 1, CursorLine !=1 --> previous line
    //[case3]: cursorCol !=1, cursorLine != 1 --> same line

    if(model.cursorColumn() == 1){
        if(model.cursorLine() == 1){
            //[case 1]: error
            throw EditorException("Already at beginning");
        }else{
            //[case 2]: goes to previous line
            //go to previous line 
            model.setCursorLine(model.cursorLine()-1);
            //set cursor column --> 1 beyond it's last character
            model.setCursorColumn(model.maxLineCol()+1);
        }
    }else{
        //[case 3]: stays on same line
        model.setCursorColumn(model.cursorColumn()-1);
    }
}

void LeftShift::undo(EditorModel& model){
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);

}