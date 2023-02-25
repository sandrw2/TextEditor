// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2021
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE
#include <string>
#include "KeypressInteractionReader.hpp"
#include "RightShift.hpp"
#include "LeftShift.hpp"
#include "InsertChar.hpp"
#include "NewLine.hpp"
#include "DeleteLine.hpp"
#include "Backspace.hpp"
#include "UpShift.hpp"
#include "DownShift.hpp"
#include "CursorHome.hpp"
#include "CursorEnd.hpp"



// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
            case 'X':
                return Interaction::quit();
            case 'O':
                return Interaction::command(new RightShift());
            case 'U':
                return Interaction::command(new LeftShift());
            case 'M':
                return Interaction::command(new NewLine());
            case 'J':
                return Interaction::command(new NewLine());
            case 'D':
                return Interaction::command(new DeleteLine());
            case 'H':
                return Interaction::command(new Backspace());
            case 'I':
                return Interaction::command(new UpShift());
            case 'K':
                return Interaction::command(new DownShift());
            case 'Y':
                return Interaction::command(new CursorHome());
            case 'P':
                return Interaction::command(new CursorEnd());
            case 'Z':
                return Interaction::undo();
            case 'A':
                return Interaction::redo();
            }
        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
            //insert character
            std::string character  = "";
            character += keypress.code();
            return Interaction::command(new InsertChar(character));
            

        }
    }
}

