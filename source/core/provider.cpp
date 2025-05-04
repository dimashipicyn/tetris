#include "provider.h"

Provider& Provider::Self() {
    static Provider self;
    return self;
}