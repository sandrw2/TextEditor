#ifndef CURSOREND_HPP
#define CURSOREND_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class CursorEnd : public Command
{
public:
    CursorEnd();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevCol;
};

#endif