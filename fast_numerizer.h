#ifndef FAST_NUMERIZER_H
#define FAST_NUMERIZER_H

#include "scanner.h"
#include "scan.h"
#include "readmem.h"
#include "sds.h"
#include "parser.h"

void initFastNumerizer(void);
void freeFastNumerizer(void);
void numerize(const char *data, size_t data_len, ParserState *state);

#endif // FAST_NUMERIZER_H
