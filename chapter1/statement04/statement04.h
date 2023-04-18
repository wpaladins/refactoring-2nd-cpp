#ifndef REFACTORING_2ND_CHAPTER1_STATEMENT04_STATEMENT04_H
#define REFACTORING_2ND_CHAPTER1_STATEMENT04_STATEMENT04_H

#include "plays.h"
#include "invoices.h"

std::string statement04(const invoice_t& invoce, const plays_t& plays);
std::string htmlStatement04(const invoice_t& invoice, const plays_t& plays);

#endif  // REFACTORING_2ND_CHAPTER1_STATEMENT04_STATEMENT04_H
