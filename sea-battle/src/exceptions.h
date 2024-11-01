#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

// ship exceptions
class impoperLenException : public std::exception {
public:
    const char* what() const noexcept override;
};

class impoperOriException : public std::exception {
public:
    const char* what() const noexcept override;
};

// ship manager exceptions
class shipListIsFullException : public std::exception {
public:
    const char* what() const noexcept override;
};

class shellingException : public std::exception {
public:
    const char* what() const noexcept override;
};

// field exceptions
class invalidShipPlacementException : public std::exception {
public:
    const char* what() const noexcept override;
};

class outOfFieldException : public std::exception {
public:
    const char* what() const noexcept override;
};

class improperInputException : public std::exception {
public:
    const char* what() const noexcept override;
};

class incorrectSizeException : public std::exception {
public:
    const char* what() const noexcept override;
};

class reEnterException : public std::exception {
public:
    const char* what() const noexcept override;
};

class alreadyDestroyedException : public std::exception {
public:
    const char* what() const noexcept override;
};

class alreadyShootedException : public std::exception {
public:
    const char* what() const noexcept override;
};

// skill manager exceptions
class noSkillsException : public std::exception {
public:
    const char* what() const noexcept override;
};

#endif