#include "DeleteLine.hpp"
#include "EditorModel.hpp"
#include <string>
#include "EditorException.hpp"

DeleteLine::DeleteLine()
    :prevLin{0}, prevCol{0}, lineText{""}
{
}

void DeleteLine::execute(EditorModel& model){
    //[0] save previous state 
    prevLin = model.cursorLine();
    prevCol = model.cursorColumn();
    lineText = model.line(model.cursorLine());

    //[case 1]: cursor is at line 1, numLines = 1, line == "" --> error 
    //[case 2]: cursor is at line 1, numlines =1, line 1!= "" 
    //[case 3]: cursor is !@ line 1 or numlines !=1
    //case[3.1]: cursor is beyond LineCol
    //[case 3.2]: cursor is not beyond LineCol


    
    if(model.lineCount() == 1 && model.cursorLine() == 1){
        if(model.line(model.cursorLine()) == ""){
            //[case 1]
            throw EditorException("Already empty");
        }else{
            //[case 2]
            //delete line 
            model.deleteLine(model.cursorLine());
            //move cursor
            model.setCursorColumn(1);
        }
    }else{
        //[case 3]
        model.deleteLine(model.cursorLine());
        // if cursorLine num is > numLines --> set line as last line
        if(model.cursorLine() > model.lineCount()){
            model.setCursorLine(model.lineCount());
        }
        
        if(model.cursorColumn() > model.maxLineCol()){
            //[case 3.1]
            //move cursor to 1 beyond maxLineCol
            model.setCursorColumn(model.maxLineCol()+1);
        }
        //[case 3.2] no need to change cursor column 
    }
}

void DeleteLine::undo(EditorModel& model){
    if(model.cursorLine() ==1 && model.lineCount() ==1){
        if(model.line(model.cursorLine())==""){
            //don't add newline just add text back
            model.insert(lineText);
            //move cursor
            model.setCursorColumn(prevCol);
            model.setCursorLine(prevLin);
        }else{
            //move cursor
            model.setCursorColumn(prevCol);
            model.setCursorLine(prevLin);
            //make newline at cursor add text back 
            model.createNewLine(lineText);
        }
    }else{
        //move cursor
        model.setCursorColumn(prevCol);
        model.setCursorLine(prevLin);
        //make newline add text back 
        model.createNewLine(lineText);
    }

}