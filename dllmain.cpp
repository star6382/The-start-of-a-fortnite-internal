#include "hook.hpp"
#include "impl.hpp"

bool dll_entry() {




	return true;
}

bool DllMain(void* exports, int caller, void* lp) {
    if (caller == 0x1) {
		//erase_pe(exports);
		dll_entry();
	}

	return true;
}