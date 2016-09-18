
#include "Nes.h"

using namespace NintendoEntertainmentSystem;

// rom start address on address 0xFFFC in the last PRG-RAM

int main(int argc, char* argv[])
{
	Nes nes;
	nes.loadCartridge("C:/Users/Julian/Desktop/Mega Man III (E).nes");
	return 0;
}
