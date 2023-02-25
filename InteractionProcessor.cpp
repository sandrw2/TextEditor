// InteractionProcessor.cpp
//
// ICS 45C Fall 2021
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include <vector>
#include "Command.hpp"

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();
    std::vector<Command*> undoList;
    std::vector<Command*> redoList;
    
    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            for(int i = 0; i < undoList.size(); i++){
                delete undoList.at(i);
            }
            for(int j = 0; j < redoList.size(); j++){
                delete redoList.at(j);
            }
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if(undoList.size() >0){
                //get from undoList
                Command* lastCommand = undoList.at(undoList.size()-1);
                //execute from undoList
                try{
                    lastCommand -> undo(model);
                    model.clearErrorMessage();
                    view.refresh();
                    //add to redoList 
                    redoList.push_back(lastCommand);
                    //remove from undoList
                    undoList.pop_back();
                }catch (EditorException& e)
                {
                    delete lastCommand;
                    model.setErrorMessage(e.getReason());
                }
                
            }
            
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (redoList.size()>0){
                //get from redoList 
                Command* lastCommand = redoList.at(redoList.size()-1);
                //execute from redoList
                try{
                    lastCommand ->execute(model);
                    model.clearErrorMessage();
                    view.refresh();
                    //add to undoList
                    undoList.push_back(lastCommand);
                    //remove from redoList
                    redoList.pop_back();
                }catch (EditorException& e)
                {
                    delete lastCommand;
                    model.setErrorMessage(e.getReason());
                }
            }
    
        }
        else if (interaction.type() == InteractionType::command)
        {
            
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                model.clearErrorMessage();
                //add to undoList
                undoList.push_back(command);
                
                //clear redoList
                for(int j = 0; j < redoList.size(); j++){
                    delete redoList.at(j);
                }
                redoList.clear();
            }
            catch (EditorException& e)
            {
                delete command;
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
        }
    }
}

