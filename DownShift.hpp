#ifndef DOWNSHIFT_HPP
#define DOWNSHIFT_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class DownShift : public Command
{
public:
    DownShift();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevLin;
    unsigned int prevCol;
};

#endif