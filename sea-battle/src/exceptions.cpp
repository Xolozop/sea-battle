#include "exceptions.h"

// ship exceptions 
const char* impoperLenException::what() const noexcept {
    return "Improper length of ship! Must be a number from 1 to 4. ";
}

const char* impoperOriException::what() const noexcept {
    return "Improper orientation of ship! Must be a char V or H. ";
}

// ship manager exceptions
const char* shipListIsFullException::what() const noexcept {
    return "All ships of this length are already in the list! ";
}

const char* shellingException::what() const noexcept {
    return "All ships are damaged! Shelling will be used to the already damaged ships. ";
}

// field exceptions
const char* invalidShipPlacementException::what() const noexcept {
    return "You can't put a ship right next to another one! ";
}

const char* outOfFieldException::what() const noexcept {
    return "Coordinates out of field! ";
}

const char* improperInputException::what() const noexcept {
    return "Improper input! ";
}

const char* incorrectSizeException::what() const noexcept {
    return "Incorrect size of field! Must be a number from 0 to 26. ";
}

const char* reEnterException::what() const noexcept {
    return "Please, re-enter your coordinates: ";
}

const char* alreadyDestroyedException::what() const noexcept {
    return "You already destroyed ship segment at these coordinates! ";
}

const char* alreadyShootedException::what() const noexcept {
    return "You can't shoot at these coordinates! ";
}

// skill manager exceptions
const char* noSkillsException::what() const noexcept {
    return "No skills left! ";
}