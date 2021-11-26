//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatePrinter.h"

WizardStatePrinter::WizardStatePrinter(const std::shared_ptr<ConsolePrinter>& printer,
                                       const std::shared_ptr<ConsoleReader>& reader) :
                                       console_printer_(printer),
                                       console_reader_(reader) {

}
