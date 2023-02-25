#ifndef LEFTSHIFT_HPP
#define LEFTSHIFT_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class LeftShift : public Command
{
public:
    LeftShift();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevLin;
    unsigned int prevCol;
};

#endif