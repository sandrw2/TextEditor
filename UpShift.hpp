#ifndef UPSHIFT_HPP
#define UPSHIFT_HPP
#include "Command.hpp"
#include "EditorModel.hpp"

class UpShift : public Command
{
public:
    UpShift();
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    unsigned int prevLin;
    unsigned int prevCol;
};

#endif