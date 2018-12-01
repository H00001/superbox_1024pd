#include "sig_h.h"

void Ctrl_C()
{
	 fputs("process has stop", stderr);
	_exit(0);
}
