#ifndef THREE_ADDRESS_CODE_HPP
#define THREE_ADDRESS_CODE_HPP

#include "stack.hpp"
#include "queue.hpp"
#include "lexiconPart.hpp"
#include "lexiconTypeEnum.hpp"
#include <iostream>
#include <fstream>

void createThreeAddressCode(std::string fileName, Queue &instructionsQueue);

#endif