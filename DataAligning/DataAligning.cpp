#include <iostream>

//64-bit
//32 - bit
//16 - bit
//8 - bit
//bool

struct PoorlyAlignedData {
    char c;     // 1 byte
    uint16_t u; // 2 bytes
    double d;   // 8 bytes
    int16_t i;  // 2 bytes
};

struct WellAlignedData {
    double d;   // 8 bytes
    uint16_t u; // 2 bytes
    int16_t i;  // 2 bytes
    char c;     // 1 byte
};

// Sets aligment to 1, sets fields one by one,
// Less memory but more reads for CPU
#pragma pack(push,1)
struct PackedData {
    double d;   // 8 bytes
    uint16_t u; // 2 bytes
    int16_t i;  // 2 bytes
    char c;     // 1 byte
};
#pragma pack(pop)

int main()
{
    printf("PoorlyAlignedData c:%lu u:%lu d:%lu i:%lu TotalSize::%lu \n", 
        offsetof(struct PoorlyAlignedData, c),
        offsetof(struct PoorlyAlignedData, u),
        offsetof(struct PoorlyAlignedData, d),
        offsetof(struct PoorlyAlignedData, i),
        sizeof(PoorlyAlignedData));

    printf("WellAlignedData d:%lu u:%lu d:%lu i:%lu TotalSize::%lu \n", 
        offsetof(struct WellAlignedData, d),
        offsetof(struct WellAlignedData, u),
        offsetof(struct WellAlignedData, i),
        offsetof(struct WellAlignedData, c),
        sizeof(WellAlignedData));

    printf("PackedData d:%lu u:%lu d:%lu i:%lu TotalSize::%lu \n",
        offsetof(struct PackedData, d),
        offsetof(struct PackedData, u),
        offsetof(struct PackedData, i),
        offsetof(struct PackedData, c),
        sizeof(PackedData));
}