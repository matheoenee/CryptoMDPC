#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mdpc.h"
#include "bitflipping.h"
#include "structures.h"


/**
* todo list:
 * randomVect(weight, size) -> usage : gen h0 h1, e0,e1
 * GenH(n) -> return h, first step of protocol
 * genC(t) -> return c1 second step
 * AliceSecret(c1) -> compute s, and BitFlpg(h0,h1,s,t,w) and hash result
 * BobSecret(e0,e1) -> hash(e0,e1)
*/