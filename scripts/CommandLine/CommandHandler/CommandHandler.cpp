#include "CommandHandler.h"

size_t CommandHandler::commandCount = 0;
CommandHandler::Command* CommandHandler::commands = nullptr;

CommandHandler::CommandHandler(size_t maxCommands, size_t maxArgs)
    : maxCommands(maxCommands), maxArgs(maxArgs) {
    commands = new Command[maxCommands];
    memset(commands, 0, sizeof(Command) * maxCommands);

    registerCommand("help", &CommandHandler::helpCommand, "Lists all available commands.", 0, 0, nullptr, 0);
}

void CommandHandler::registerCommand(const String& command, CommandCallback callback, const String& description,
                                     size_t minArgs, size_t maxArgs, const ArgType* argTypes, size_t argTypesCount) {
    if (commandCount < maxCommands) {
        commands[commandCount] = {command, callback, description, minArgs, maxArgs, nullptr, argTypesCount};
        if (argTypes != nullptr && argTypesCount > 0) {
            commands[commandCount].argTypes = new ArgType[argTypesCount];
            memcpy(commands[commandCount].argTypes, argTypes, sizeof(ArgType) * argTypesCount);
        }
        commandCount++;
    } else {
        Serial.println("Error: Maximum number of commands reached");
    }
}

String CommandHandler::parseCommand(String& command, String args[], size_t& argCount) {
    int firstSpace = command.indexOf(' ');
    if (firstSpace != -1) {
        String arguments = command.substring(firstSpace + 1);
        command = command.substring(0, firstSpace);

        size_t start = 0, end;
        while ((end = arguments.indexOf(' ', start)) != -1 && argCount < maxArgs) {
            args[argCount++] = arguments.substring(start, end);
            start = end + 1;
        }
        if (start < arguments.length() && argCount < maxArgs) {
            args[argCount++] = arguments.substring(start);
        }
    }
    return command;
}

bool CommandHandler::validateArgs(const String args[], size_t argCount, const Command& cmd) {
    if (argCount < cmd.minArgs || argCount > cmd.maxArgs) {
        return false;
    }

    if (cmd.argTypes != nullptr) {
        for (size_t i = 0; i < argCount; i++) {
            switch (cmd.argTypes[i]) {
            case INT:
                if (args[i].toInt() == 0 && args[i] != "0") {
                    return false;
                }
                break;
            case FLOAT:
                if (args[i].toFloat() == 0.0f && args[i] != "0" && args[i] != "0.0") {
                    return false;
                }
                break;
            case STRING:
                break;
            }
        }
    }
    return true;
}

void CommandHandler::executeCommand(const String& command, const String args[], size_t argCount, String& response) {
    for (size_t i = 0; i < commandCount; i++) {
        if (commands[i].name == command) {
            if (!validateArgs(args, argCount, commands[i])) {
                response = "Error: Invalid arguments for command: " + command;
                return;
            }
            response = commands[i].callback(args, argCount);
            return;
        }
    }
    response = "Unknown command: " + command + ". Use 'help' for a list of commands.";
}

String CommandHandler::processInput(const String& input) {
    String* args = new String[maxArgs];
    size_t argCount = 0;
    String command = input;
    parseCommand(command, args, argCount);

    String response;
    executeCommand(command, args, argCount, response);
    delete[] args;
    return response;
}

String CommandHandler::helpCommand(const String args[], size_t argCount) {
    String result = "Available commands:\n";
    for (size_t i = 0; i < commandCount; i++) {
        result += commands[i].name + " - " + commands[i].description + "\n";
    }
    return result;
}

CommandHandler::~CommandHandler() {
    for (size_t i = 0; i < commandCount; i++) {
        delete[] commands[i].argTypes;
    }
    delete[] commands;
}
