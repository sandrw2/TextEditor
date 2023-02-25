#ifndef NEWLINE_HPP
#define NEWLINE_HPP
#include "Command.hpp"
#include "EditorModel.hpp"
#include <string>

class NewLine : public Command
{
public:
    NewLine();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevLin;
    unsigned int prevCol;
    std::string beyondCursor;
};

#endif