#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class CursorHome : public Command
{
public:
    CursorHome();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevCol;
};

#endif