#ifndef INSERTCHAR_HPP
#define INSERTCHAR_HPP
#include "Command.hpp"
#include "EditorModel.hpp"
#include <string>

class InsertChar : public Command
{
public:
    InsertChar(const std::string& character);
    void execute(EditorModel& model) override;
    void undo(EditorModel& model) override;
private:
    std::string insertChar;
    unsigned int prevCol;
};

#endif