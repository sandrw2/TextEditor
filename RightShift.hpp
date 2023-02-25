#ifndef RIGHTSHIFT_HPP
#define RIGHTSHIFT_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class RightShift : public Command
{
public:
    RightShift();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevLin;
    unsigned int prevCol;
};

#endif