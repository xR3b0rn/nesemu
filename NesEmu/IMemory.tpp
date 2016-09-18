
using namespace NintendoEntertainmentSystem;

template <UINT32 SIZE>
UINT8* IMemory<SIZE>::getMemoryPointer(address_t address)
{
	return &m_pMemory[address];
}
template <UINT32 SIZE>
UINT8 IMemory<SIZE>::readMemory8(address_t address)
{
	return m_pMemory[address];
}
template <UINT32 SIZE>
void IMemory<SIZE>::writeMemory8(address_t address, UINT8 data)
{
	m_pMemory[address] = data;
}
template <UINT32 SIZE>
UINT8* IMemory<SIZE>::getMemory()
{
	return m_pMemory;
}
