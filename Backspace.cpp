#include "Backspace.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

Backspace::Backspace()
    :prevLin{0}, prevCol{0}, previous{false}
{
}

void Backspace::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    if(prevCol > 1){
        character = model.line(prevLin).substr(prevCol-2,1);
    }else{
        character = "";
    }
    
    std::string beyondCursor = model.line(prevLin).substr(prevCol-1);
    //[case1]: cursorCol == 1, cursorLine == 1 --> error
    //[case2]: cursorCol == 1, CursorLine !=1 --> previous line
    //[case3]: cursorCol !=1--> same line

    if(model.cursorColumn() == 1){
        if(model.cursorLine() == 1){
            //[case 1]: error
            throw EditorException("Already at beginning");
        }else{
            //[case 2]: previous line
            //set previous bool --> true 
            previous = true;
            //set cursor line to previous line
            model.setCursorLine(model.cursorLine()-1);
            //set cursor column --> 1 beyond it's last character
            model.setCursorColumn(model.maxLineCol()+1);
            //insert beyondCursor line
            model.insert(beyondCursor);
            //delete oldLine
            model.deleteLine(model.cursorLine()+1);
        }
    }else{
        //[case 3]: stays on same line
        //delete character before the cursor --> prevCol -1 
        int left = prevCol-1;
        model.deleting(left, 1);
        model.setCursorColumn(model.cursorColumn()-1);
    }
    
}

void Backspace::undo(EditorModel& model){
    //[case1]: previous == true --> return from previous string
    //[case2]: previous == false --> stay in same line add character 

    if(previous){
        //get substring after cursor  
        std::string currentLine = model.line(model.cursorLine());
        std::string afterCursor = currentLine.substr(model.cursorColumn()-1);
        //delete substring from previous line 
        model.deleting(model.cursorColumn(), afterCursor.length());
        //return to previous position 
        model.setCursorColumn(prevCol);
        model.setCursorLine(prevLin);
        //create newline with afterCursor string
        model.createNewLine(afterCursor);
    }else{
        //insert deleted character at column
        model.insert(character);
    }
    //return to previous position 
    model.setCursorColumn(prevCol);
    model.setCursorLine(prevLin);

}