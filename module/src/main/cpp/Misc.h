#ifndef MISC_H
#define MISC_H
#include "Dobby/dobby.h"
#include "KittyMemory/KittyMemory.h"
#include "KittyMemory/KittyScanner.h"
#include "KittyMemory/MemoryPatch.h"
#include "Unity/Vector2.h"
#include "Data/obfuscate.h"

using KittyMemory::ProcMap;
using KittyScanner::RegisterNativeFn;

ProcMap g_il2cppBaseMap;

void hook(void *offset, void* ptr, void **orig)
{
    DobbyHook(offset, ptr, orig);
}

std::vector<MemoryPatch> memoryPatches;
std::vector<uint64_t> offsetVector;

// Patching a offset with switch.
void patchOffset(uint64_t offset, std::string hexBytes, bool isOn) {

    MemoryPatch patch = MemoryPatch::createWithHex(g_il2cppBaseMap, offset, hexBytes);

    //Check if offset exists in the offsetVector
    if (std::find(offsetVector.begin(), offsetVector.end(), offset) != offsetVector.end()) {
        std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), offset);
        patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; //Get index of memoryPatches vector
    } else {
        memoryPatches.push_back(patch);
        offsetVector.push_back(offset);
    }

    if (!patch.isValid()) {
        return;
    }
    if (isOn && patch.get_CurrBytes() == patch.get_OrigBytes()) {
        patch.Modify();
    } else if (!isOn && patch.get_CurrBytes() != patch.get_OrigBytes()) {
        patch.Restore();
    }
}

uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

#define HOOK(offset, ptr, orig) hook((void *)(g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define PATCH(offset, hex) patchOffset(string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), true)
#define PATCH_SWITCH(offset, hex, boolean) patchOffset(string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), boolean)
#define RESTORE(offset) patchOffset(string2Offset(OBFUSCATE(offset)), "", false)

#endif // MISC_H
