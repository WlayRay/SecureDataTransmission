#include "Codec.h"
#include <cstddef>

Codec::Codec()
{
}

Codec::~Codec()
{
}

int Codec::msgEncode(char **outData, int &len)
{
	return 0;
}

void *Codec::msgDecode(char *inData, int inLen)
{
	return NULL;
}
