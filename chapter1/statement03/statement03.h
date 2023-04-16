#ifndef REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H
#define REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H

#include "plays.h"
#include "invoices.h"

std::string statement03(const invoice_t& invoce, const plays_t& plays);
std::string htmlStatement03(const invoice_t& invoice, const plays_t& plays);

#endif  // REFACTORING_2ND_CHAPTER1_STATEMENT03_STATEMENT03_H
