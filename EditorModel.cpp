// EditorModel.cpp
//
// ICS 45C Fall 2021
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"
#include <string>
#include <vector>
#include <iostream>


EditorModel::EditorModel()
    :lin{1}, col{1}, numLines{1}, errorString{""}, texts{""}
{
}


int EditorModel::cursorLine() const
{
    return lin;
}


int EditorModel::cursorColumn() const
{
    return col;
}


int EditorModel::lineCount() const
{
    return numLines;
}


const std::string& EditorModel::line(int lineNumber) const
{
    //offset cause text index starts at 0
    return texts[lineNumber-1];
}


const std::string& EditorModel::currentErrorMessage() const
{
    return errorString;
}

//[ADDITIONAL INFO FUNCTIONS] -----------------------------------------
//returns the column of the last character on the current line
int EditorModel::maxLineCol(){
    return line(lin).length();
}


//[EDITING FUNCTIONS]-----------------------------------------------
// sets cursorLine 
void EditorModel::setCursorLine(const unsigned int& newLin){
    lin = newLin;
}

//sets cursorColumn
void EditorModel::setCursorColumn(const unsigned int& newCol){
    col = newCol;
}

//at current position inserts string into line
void EditorModel::insert(const std::string& somestring){
    //offset col with -1 for index
    texts[lin-1].insert(col-1, somestring);

}

//delete from starting index  to end index
//accounts for index offset  
void EditorModel::deleting(unsigned int start, unsigned int numChars){
    texts[lin-1].erase(start-1, numChars);
}

//deletes line
void EditorModel::deleteLine(unsigned int lineNum){
    //delete line from vector array IF IT IS NOT THE ONLY LINE
    //accounts for index offset already 
    //--> deletes current cursorLine --> begin+index
    if (numLines > 1){
        unsigned int lineIndex = lineNum-1;
        auto it = texts.begin();
        texts.erase(it+lineIndex);
        //substract 1 from numlines 
        numLines--;
    }else{
        texts[0] = "";
    }


}

//create new line at line
//moves everything at and beyond cursor to new line 
void EditorModel::createNewLine(const std::string& beyondCursor){
    //create newline in vector array and place substring
    //accounts for index offset already 
    //--> create newline after cursor line --> begin + lin(index+1)
    auto it = texts.begin();
    texts.insert(it+(lin-1), beyondCursor);
    
    //add 1 to numlines
    numLines++;
}



//sets error message
void EditorModel::setErrorMessage(const std::string& errorMessage)
{
    errorString = errorMessage;
}

//clears error message --> ""
void EditorModel::clearErrorMessage()
{
    errorString = "";
}