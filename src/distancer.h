#include "lcd1602.h"
#define RATE_HOT  (0.18446)
#define RATE_COLD (0.18746)

#define RATE RATE_COLD

void UltInit();
void UltStart();
void UltCount();
void ShowDistance();
void CalAverage();
