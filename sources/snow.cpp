#include "snow.hpp"
#include <stdexcept>

static uint32_t sosemanuk_mul_a[] = {
    0x00000000, 0xE19FCF13, 0x6B973726, 0x8A08F835, 0xD6876E4C, 0x3718A15F,
    0xBD10596A, 0x5C8F9679, 0x05A7DC98, 0xE438138B, 0x6E30EBBE, 0x8FAF24AD,
    0xD320B2D4, 0x32BF7DC7, 0xB8B785F2, 0x59284AE1, 0x0AE71199, 0xEB78DE8A,
    0x617026BF, 0x80EFE9AC, 0xDC607FD5, 0x3DFFB0C6, 0xB7F748F3, 0x566887E0,
    0x0F40CD01, 0xEEDF0212, 0x64D7FA27, 0x85483534, 0xD9C7A34D, 0x38586C5E,
    0xB250946B, 0x53CF5B78, 0x1467229B, 0xF5F8ED88, 0x7FF015BD, 0x9E6FDAAE,
    0xC2E04CD7, 0x237F83C4, 0xA9777BF1, 0x48E8B4E2, 0x11C0FE03, 0xF05F3110,
    0x7A57C925, 0x9BC80636, 0xC747904F, 0x26D85F5C, 0xACD0A769, 0x4D4F687A,
    0x1E803302, 0xFF1FFC11, 0x75170424, 0x9488CB37, 0xC8075D4E, 0x2998925D,
    0xA3906A68, 0x420FA57B, 0x1B27EF9A, 0xFAB82089, 0x70B0D8BC, 0x912F17AF,
    0xCDA081D6, 0x2C3F4EC5, 0xA637B6F0, 0x47A879E3, 0x28CE449F, 0xC9518B8C,
    0x435973B9, 0xA2C6BCAA, 0xFE492AD3, 0x1FD6E5C0, 0x95DE1DF5, 0x7441D2E6,
    0x2D699807, 0xCCF65714, 0x46FEAF21, 0xA7616032, 0xFBEEF64B, 0x1A713958,
    0x9079C16D, 0x71E60E7E, 0x22295506, 0xC3B69A15, 0x49BE6220, 0xA821AD33,
    0xF4AE3B4A, 0x1531F459, 0x9F390C6C, 0x7EA6C37F, 0x278E899E, 0xC611468D,
    0x4C19BEB8, 0xAD8671AB, 0xF109E7D2, 0x109628C1, 0x9A9ED0F4, 0x7B011FE7,
    0x3CA96604, 0xDD36A917, 0x573E5122, 0xB6A19E31, 0xEA2E0848, 0x0BB1C75B,
    0x81B93F6E, 0x6026F07D, 0x390EBA9C, 0xD891758F, 0x52998DBA, 0xB30642A9,
    0xEF89D4D0, 0x0E161BC3, 0x841EE3F6, 0x65812CE5, 0x364E779D, 0xD7D1B88E,
    0x5DD940BB, 0xBC468FA8, 0xE0C919D1, 0x0156D6C2, 0x8B5E2EF7, 0x6AC1E1E4,
    0x33E9AB05, 0xD2766416, 0x587E9C23, 0xB9E15330, 0xE56EC549, 0x04F10A5A,
    0x8EF9F26F, 0x6F663D7C, 0x50358897, 0xB1AA4784, 0x3BA2BFB1, 0xDA3D70A2,
    0x86B2E6DB, 0x672D29C8, 0xED25D1FD, 0x0CBA1EEE, 0x5592540F, 0xB40D9B1C,
    0x3E056329, 0xDF9AAC3A, 0x83153A43, 0x628AF550, 0xE8820D65, 0x091DC276,
    0x5AD2990E, 0xBB4D561D, 0x3145AE28, 0xD0DA613B, 0x8C55F742, 0x6DCA3851,
    0xE7C2C064, 0x065D0F77, 0x5F754596, 0xBEEA8A85, 0x34E272B0, 0xD57DBDA3,
    0x89F22BDA, 0x686DE4C9, 0xE2651CFC, 0x03FAD3EF, 0x4452AA0C, 0xA5CD651F,
    0x2FC59D2A, 0xCE5A5239, 0x92D5C440, 0x734A0B53, 0xF942F366, 0x18DD3C75,
    0x41F57694, 0xA06AB987, 0x2A6241B2, 0xCBFD8EA1, 0x977218D8, 0x76EDD7CB,
    0xFCE52FFE, 0x1D7AE0ED, 0x4EB5BB95, 0xAF2A7486, 0x25228CB3, 0xC4BD43A0,
    0x9832D5D9, 0x79AD1ACA, 0xF3A5E2FF, 0x123A2DEC, 0x4B12670D, 0xAA8DA81E,
    0x2085502B, 0xC11A9F38, 0x9D950941, 0x7C0AC652, 0xF6023E67, 0x179DF174,
    0x78FBCC08, 0x9964031B, 0x136CFB2E, 0xF2F3343D, 0xAE7CA244, 0x4FE36D57,
    0xC5EB9562, 0x24745A71, 0x7D5C1090, 0x9CC3DF83, 0x16CB27B6, 0xF754E8A5,
    0xABDB7EDC, 0x4A44B1CF, 0xC04C49FA, 0x21D386E9, 0x721CDD91, 0x93831282,
    0x198BEAB7, 0xF81425A4, 0xA49BB3DD, 0x45047CCE, 0xCF0C84FB, 0x2E934BE8,
    0x77BB0109, 0x9624CE1A, 0x1C2C362F, 0xFDB3F93C, 0xA13C6F45, 0x40A3A056,
    0xCAAB5863, 0x2B349770, 0x6C9CEE93, 0x8D032180, 0x070BD9B5, 0xE69416A6,
    0xBA1B80DF, 0x5B844FCC, 0xD18CB7F9, 0x301378EA, 0x693B320B, 0x88A4FD18,
    0x02AC052D, 0xE333CA3E, 0xBFBC5C47, 0x5E239354, 0xD42B6B61, 0x35B4A472,
    0x667BFF0A, 0x87E43019, 0x0DECC82C, 0xEC73073F, 0xB0FC9146, 0x51635E55,
    0xDB6BA660, 0x3AF46973, 0x63DC2392, 0x8243EC81, 0x084B14B4, 0xE9D4DBA7,
    0xB55B4DDE, 0x54C482CD, 0xDECC7AF8, 0x3F53B5EB
};

static uint32_t sosemanuk_div_a[] = {
    0x00000000, 0x180F40CD, 0x301E8033, 0x2811C0FE, 0x603CA966, 0x7833E9AB,
    0x50222955, 0x482D6998, 0xC078FBCC, 0xD877BB01, 0xF0667BFF, 0xE8693B32,
    0xA04452AA, 0xB84B1267, 0x905AD299, 0x88559254, 0x29F05F31, 0x31FF1FFC,
    0x19EEDF02, 0x01E19FCF, 0x49CCF657, 0x51C3B69A, 0x79D27664, 0x61DD36A9,
    0xE988A4FD, 0xF187E430, 0xD99624CE, 0xC1996403, 0x89B40D9B, 0x91BB4D56,
    0xB9AA8DA8, 0xA1A5CD65, 0x5249BE62, 0x4A46FEAF, 0x62573E51, 0x7A587E9C,
    0x32751704, 0x2A7A57C9, 0x026B9737, 0x1A64D7FA, 0x923145AE, 0x8A3E0563,
    0xA22FC59D, 0xBA208550, 0xF20DECC8, 0xEA02AC05, 0xC2136CFB, 0xDA1C2C36,
    0x7BB9E153, 0x63B6A19E, 0x4BA76160, 0x53A821AD, 0x1B854835, 0x038A08F8,
    0x2B9BC806, 0x339488CB, 0xBBC11A9F, 0xA3CE5A52, 0x8BDF9AAC, 0x93D0DA61,
    0xDBFDB3F9, 0xC3F2F334, 0xEBE333CA, 0xF3EC7307, 0xA492D5C4, 0xBC9D9509,
    0x948C55F7, 0x8C83153A, 0xC4AE7CA2, 0xDCA13C6F, 0xF4B0FC91, 0xECBFBC5C,
    0x64EA2E08, 0x7CE56EC5, 0x54F4AE3B, 0x4CFBEEF6, 0x04D6876E, 0x1CD9C7A3,
    0x34C8075D, 0x2CC74790, 0x8D628AF5, 0x956DCA38, 0xBD7C0AC6, 0xA5734A0B,
    0xED5E2393, 0xF551635E, 0xDD40A3A0, 0xC54FE36D, 0x4D1A7139, 0x551531F4,
    0x7D04F10A, 0x650BB1C7, 0x2D26D85F, 0x35299892, 0x1D38586C, 0x053718A1,
    0xF6DB6BA6, 0xEED42B6B, 0xC6C5EB95, 0xDECAAB58, 0x96E7C2C0, 0x8EE8820D,
    0xA6F942F3, 0xBEF6023E, 0x36A3906A, 0x2EACD0A7, 0x06BD1059, 0x1EB25094,
    0x569F390C, 0x4E9079C1, 0x6681B93F, 0x7E8EF9F2, 0xDF2B3497, 0xC724745A,
    0xEF35B4A4, 0xF73AF469, 0xBF179DF1, 0xA718DD3C, 0x8F091DC2, 0x97065D0F,
    0x1F53CF5B, 0x075C8F96, 0x2F4D4F68, 0x37420FA5, 0x7F6F663D, 0x676026F0,
    0x4F71E60E, 0x577EA6C3, 0xE18D0321, 0xF98243EC, 0xD1938312, 0xC99CC3DF,
    0x81B1AA47, 0x99BEEA8A, 0xB1AF2A74, 0xA9A06AB9, 0x21F5F8ED, 0x39FAB820,
    0x11EB78DE, 0x09E43813, 0x41C9518B, 0x59C61146, 0x71D7D1B8, 0x69D89175,
    0xC87D5C10, 0xD0721CDD, 0xF863DC23, 0xE06C9CEE, 0xA841F576, 0xB04EB5BB,
    0x985F7545, 0x80503588, 0x0805A7DC, 0x100AE711, 0x381B27EF, 0x20146722,
    0x68390EBA, 0x70364E77, 0x58278E89, 0x4028CE44, 0xB3C4BD43, 0xABCBFD8E,
    0x83DA3D70, 0x9BD57DBD, 0xD3F81425, 0xCBF754E8, 0xE3E69416, 0xFBE9D4DB,
    0x73BC468F, 0x6BB30642, 0x43A2C6BC, 0x5BAD8671, 0x1380EFE9, 0x0B8FAF24,
    0x239E6FDA, 0x3B912F17, 0x9A34E272, 0x823BA2BF, 0xAA2A6241, 0xB225228C,
    0xFA084B14, 0xE2070BD9, 0xCA16CB27, 0xD2198BEA, 0x5A4C19BE, 0x42435973,
    0x6A52998D, 0x725DD940, 0x3A70B0D8, 0x227FF015, 0x0A6E30EB, 0x12617026,
    0x451FD6E5, 0x5D109628, 0x750156D6, 0x6D0E161B, 0x25237F83, 0x3D2C3F4E,
    0x153DFFB0, 0x0D32BF7D, 0x85672D29, 0x9D686DE4, 0xB579AD1A, 0xAD76EDD7,
    0xE55B844F, 0xFD54C482, 0xD545047C, 0xCD4A44B1, 0x6CEF89D4, 0x74E0C919,
    0x5CF109E7, 0x44FE492A, 0x0CD320B2, 0x14DC607F, 0x3CCDA081, 0x24C2E04C,
    0xAC977218, 0xB49832D5, 0x9C89F22B, 0x8486B2E6, 0xCCABDB7E, 0xD4A49BB3,
    0xFCB55B4D, 0xE4BA1B80, 0x17566887, 0x0F59284A, 0x2748E8B4, 0x3F47A879,
    0x776AC1E1, 0x6F65812C, 0x477441D2, 0x5F7B011F, 0xD72E934B, 0xCF21D386,
    0xE7301378, 0xFF3F53B5, 0xB7123A2D, 0xAF1D7AE0, 0x870CBA1E, 0x9F03FAD3,
    0x3EA637B6, 0x26A9777B, 0x0EB8B785, 0x16B7F748, 0x5E9A9ED0, 0x4695DE1D,
    0x6E841EE3, 0x768B5E2E, 0xFEDECC7A, 0xE6D18CB7, 0xCEC04C49, 0xD6CF0C84,
    0x9EE2651C, 0x86ED25D1, 0xAEFCE52F, 0xB6F3A5E2
};

static const uint32_t rijndael_dtbl[] = {
    0xA56363C6, 0x847C7CF8, 0x997777EE, 0x8D7B7BF6, 0x0DF2F2FF, 0xBD6B6BD6,
    0xB16F6FDE, 0x54C5C591, 0x50303060, 0x03010102, 0xA96767CE, 0x7D2B2B56,
    0x19FEFEE7, 0x62D7D7B5, 0xE6ABAB4D, 0x9A7676EC, 0x45CACA8F, 0x9D82821F,
    0x40C9C989, 0x877D7DFA, 0x15FAFAEF, 0xEB5959B2, 0xC947478E, 0x0BF0F0FB,
    0xECADAD41, 0x67D4D4B3, 0xFDA2A25F, 0xEAAFAF45, 0xBF9C9C23, 0xF7A4A453,
    0x967272E4, 0x5BC0C09B, 0xC2B7B775, 0x1CFDFDE1, 0xAE93933D, 0x6A26264C,
    0x5A36366C, 0x413F3F7E, 0x02F7F7F5, 0x4FCCCC83, 0x5C343468, 0xF4A5A551,
    0x34E5E5D1, 0x08F1F1F9, 0x937171E2, 0x73D8D8AB, 0x53313162, 0x3F15152A,
    0x0C040408, 0x52C7C795, 0x65232346, 0x5EC3C39D, 0x28181830, 0xA1969637,
    0x0F05050A, 0xB59A9A2F, 0x0907070E, 0x36121224, 0x9B80801B, 0x3DE2E2DF,
    0x26EBEBCD, 0x6927274E, 0xCDB2B27F, 0x9F7575EA, 0x1B090912, 0x9E83831D,
    0x742C2C58, 0x2E1A1A34, 0x2D1B1B36, 0xB26E6EDC, 0xEE5A5AB4, 0xFBA0A05B,
    0xF65252A4, 0x4D3B3B76, 0x61D6D6B7, 0xCEB3B37D, 0x7B292952, 0x3EE3E3DD,
    0x712F2F5E, 0x97848413, 0xF55353A6, 0x68D1D1B9, 0x00000000, 0x2CEDEDC1,
    0x60202040, 0x1FFCFCE3, 0xC8B1B179, 0xED5B5BB6, 0xBE6A6AD4, 0x46CBCB8D,
    0xD9BEBE67, 0x4B393972, 0xDE4A4A94, 0xD44C4C98, 0xE85858B0, 0x4ACFCF85,
    0x6BD0D0BB, 0x2AEFEFC5, 0xE5AAAA4F, 0x16FBFBED, 0xC5434386, 0xD74D4D9A,
    0x55333366, 0x94858511, 0xCF45458A, 0x10F9F9E9, 0x06020204, 0x817F7FFE,
    0xF05050A0, 0x443C3C78, 0xBA9F9F25, 0xE3A8A84B, 0xF35151A2, 0xFEA3A35D,
    0xC0404080, 0x8A8F8F05, 0xAD92923F, 0xBC9D9D21, 0x48383870, 0x04F5F5F1,
    0xDFBCBC63, 0xC1B6B677, 0x75DADAAF, 0x63212142, 0x30101020, 0x1AFFFFE5,
    0x0EF3F3FD, 0x6DD2D2BF, 0x4CCDCD81, 0x140C0C18, 0x35131326, 0x2FECECC3,
    0xE15F5FBE, 0xA2979735, 0xCC444488, 0x3917172E, 0x57C4C493, 0xF2A7A755,
    0x827E7EFC, 0x473D3D7A, 0xAC6464C8, 0xE75D5DBA, 0x2B191932, 0x957373E6,
    0xA06060C0, 0x98818119, 0xD14F4F9E, 0x7FDCDCA3, 0x66222244, 0x7E2A2A54,
    0xAB90903B, 0x8388880B, 0xCA46468C, 0x29EEEEC7, 0xD3B8B86B, 0x3C141428,
    0x79DEDEA7, 0xE25E5EBC, 0x1D0B0B16, 0x76DBDBAD, 0x3BE0E0DB, 0x56323264,
    0x4E3A3A74, 0x1E0A0A14, 0xDB494992, 0x0A06060C, 0x6C242448, 0xE45C5CB8,
    0x5DC2C29F, 0x6ED3D3BD, 0xEFACAC43, 0xA66262C4, 0xA8919139, 0xA4959531,
    0x37E4E4D3, 0x8B7979F2, 0x32E7E7D5, 0x43C8C88B, 0x5937376E, 0xB76D6DDA,
    0x8C8D8D01, 0x64D5D5B1, 0xD24E4E9C, 0xE0A9A949, 0xB46C6CD8, 0xFA5656AC,
    0x07F4F4F3, 0x25EAEACF, 0xAF6565CA, 0x8E7A7AF4, 0xE9AEAE47, 0x18080810,
    0xD5BABA6F, 0x887878F0, 0x6F25254A, 0x722E2E5C, 0x241C1C38, 0xF1A6A657,
    0xC7B4B473, 0x51C6C697, 0x23E8E8CB, 0x7CDDDDA1, 0x9C7474E8, 0x211F1F3E,
    0xDD4B4B96, 0xDCBDBD61, 0x868B8B0D, 0x858A8A0F, 0x907070E0, 0x423E3E7C,
    0xC4B5B571, 0xAA6666CC, 0xD8484890, 0x05030306, 0x01F6F6F7, 0x120E0E1C,
    0xA36161C2, 0x5F35356A, 0xF95757AE, 0xD0B9B969, 0x91868617, 0x58C1C199,
    0x271D1D3A, 0xB99E9E27, 0x38E1E1D9, 0x13F8F8EB, 0xB398982B, 0x33111122,
    0xBB6969D2, 0x70D9D9A9, 0x898E8E07, 0xA7949433, 0xB69B9B2D, 0x221E1E3C,
    0x92878715, 0x20E9E9C9, 0x49CECE87, 0xFF5555AA, 0x78282850, 0x7ADFDFA5,
    0x8F8C8C03, 0xF8A1A159, 0x80898909, 0x170D0D1A, 0xDABFBF65, 0x31E6E6D7,
    0xC6424284, 0xB86868D0, 0xC3414182, 0xB0999929, 0x772D2D5A, 0x110F0F1E,
    0xCBB0B07B, 0xFC5454A8, 0xD6BBBB6D, 0x3A16162C
};

static const uint32_t rijndael_dtbl2[] = {
    0x6363C6A5, 0x7C7CF884, 0x7777EE99, 0x7B7BF68D, 0xF2F2FF0D, 0x6B6BD6BD,
    0x6F6FDEB1, 0xC5C59154, 0x30306050, 0x01010203, 0x6767CEA9, 0x2B2B567D,
    0xFEFEE719, 0xD7D7B562, 0xABAB4DE6, 0x7676EC9A, 0xCACA8F45, 0x82821F9D,
    0xC9C98940, 0x7D7DFA87, 0xFAFAEF15, 0x5959B2EB, 0x47478EC9, 0xF0F0FB0B,
    0xADAD41EC, 0xD4D4B367, 0xA2A25FFD, 0xAFAF45EA, 0x9C9C23BF, 0xA4A453F7,
    0x7272E496, 0xC0C09B5B, 0xB7B775C2, 0xFDFDE11C, 0x93933DAE, 0x26264C6A,
    0x36366C5A, 0x3F3F7E41, 0xF7F7F502, 0xCCCC834F, 0x3434685C, 0xA5A551F4,
    0xE5E5D134, 0xF1F1F908, 0x7171E293, 0xD8D8AB73, 0x31316253, 0x15152A3F,
    0x0404080C, 0xC7C79552, 0x23234665, 0xC3C39D5E, 0x18183028, 0x969637A1,
    0x05050A0F, 0x9A9A2FB5, 0x07070E09, 0x12122436, 0x80801B9B, 0xE2E2DF3D,
    0xEBEBCD26, 0x27274E69, 0xB2B27FCD, 0x7575EA9F, 0x0909121B, 0x83831D9E,
    0x2C2C5874, 0x1A1A342E, 0x1B1B362D, 0x6E6EDCB2, 0x5A5AB4EE, 0xA0A05BFB,
    0x5252A4F6, 0x3B3B764D, 0xD6D6B761, 0xB3B37DCE, 0x2929527B, 0xE3E3DD3E,
    0x2F2F5E71, 0x84841397, 0x5353A6F5, 0xD1D1B968, 0x00000000, 0xEDEDC12C,
    0x20204060, 0xFCFCE31F, 0xB1B179C8, 0x5B5BB6ED, 0x6A6AD4BE, 0xCBCB8D46,
    0xBEBE67D9, 0x3939724B, 0x4A4A94DE, 0x4C4C98D4, 0x5858B0E8, 0xCFCF854A,
    0xD0D0BB6B, 0xEFEFC52A, 0xAAAA4FE5, 0xFBFBED16, 0x434386C5, 0x4D4D9AD7,
    0x33336655, 0x85851194, 0x45458ACF, 0xF9F9E910, 0x02020406, 0x7F7FFE81,
    0x5050A0F0, 0x3C3C7844, 0x9F9F25BA, 0xA8A84BE3, 0x5151A2F3, 0xA3A35DFE,
    0x404080C0, 0x8F8F058A, 0x92923FAD, 0x9D9D21BC, 0x38387048, 0xF5F5F104,
    0xBCBC63DF, 0xB6B677C1, 0xDADAAF75, 0x21214263, 0x10102030, 0xFFFFE51A,
    0xF3F3FD0E, 0xD2D2BF6D, 0xCDCD814C, 0x0C0C1814, 0x13132635, 0xECECC32F,
    0x5F5FBEE1, 0x979735A2, 0x444488CC, 0x17172E39, 0xC4C49357, 0xA7A755F2,
    0x7E7EFC82, 0x3D3D7A47, 0x6464C8AC, 0x5D5DBAE7, 0x1919322B, 0x7373E695,
    0x6060C0A0, 0x81811998, 0x4F4F9ED1, 0xDCDCA37F, 0x22224466, 0x2A2A547E,
    0x90903BAB, 0x88880B83, 0x46468CCA, 0xEEEEC729, 0xB8B86BD3, 0x1414283C,
    0xDEDEA779, 0x5E5EBCE2, 0x0B0B161D, 0xDBDBAD76, 0xE0E0DB3B, 0x32326456,
    0x3A3A744E, 0x0A0A141E, 0x494992DB, 0x06060C0A, 0x2424486C, 0x5C5CB8E4,
    0xC2C29F5D, 0xD3D3BD6E, 0xACAC43EF, 0x6262C4A6, 0x919139A8, 0x959531A4,
    0xE4E4D337, 0x7979F28B, 0xE7E7D532, 0xC8C88B43, 0x37376E59, 0x6D6DDAB7,
    0x8D8D018C, 0xD5D5B164, 0x4E4E9CD2, 0xA9A949E0, 0x6C6CD8B4, 0x5656ACFA,
    0xF4F4F307, 0xEAEACF25, 0x6565CAAF, 0x7A7AF48E, 0xAEAE47E9, 0x08081018,
    0xBABA6FD5, 0x7878F088, 0x25254A6F, 0x2E2E5C72, 0x1C1C3824, 0xA6A657F1,
    0xB4B473C7, 0xC6C69751, 0xE8E8CB23, 0xDDDDA17C, 0x7474E89C, 0x1F1F3E21,
    0x4B4B96DD, 0xBDBD61DC, 0x8B8B0D86, 0x8A8A0F85, 0x7070E090, 0x3E3E7C42,
    0xB5B571C4, 0x6666CCAA, 0x484890D8, 0x03030605, 0xF6F6F701, 0x0E0E1C12,
    0x6161C2A3, 0x35356A5F, 0x5757AEF9, 0xB9B969D0, 0x86861791, 0xC1C19958,
    0x1D1D3A27, 0x9E9E27B9, 0xE1E1D938, 0xF8F8EB13, 0x98982BB3, 0x11112233,
    0x6969D2BB, 0xD9D9A970, 0x8E8E0789, 0x949433A7, 0x9B9B2DB6, 0x1E1E3C22,
    0x87871592, 0xE9E9C920, 0xCECE8749, 0x5555AAFF, 0x28285078, 0xDFDFA57A,
    0x8C8C038F, 0xA1A159F8, 0x89890980, 0x0D0D1A17, 0xBFBF65DA, 0xE6E6D731,
    0x424284C6, 0x6868D0B8, 0x414182C3, 0x999929B0, 0x2D2D5A77, 0x0F0F1E11,
    0xB0B07BCB, 0x5454A8FC, 0xBBBB6DD6, 0x16162C3A
};

static const uint32_t rijndael_dtbl3[] = {
    0x63C6A563, 0x7CF8847C, 0x77EE9977, 0x7BF68D7B, 0xF2FF0DF2, 0x6BD6BD6B,
    0x6FDEB16F, 0xC59154C5, 0x30605030, 0x01020301, 0x67CEA967, 0x2B567D2B,
    0xFEE719FE, 0xD7B562D7, 0xAB4DE6AB, 0x76EC9A76, 0xCA8F45CA, 0x821F9D82,
    0xC98940C9, 0x7DFA877D, 0xFAEF15FA, 0x59B2EB59, 0x478EC947, 0xF0FB0BF0,
    0xAD41ECAD, 0xD4B367D4, 0xA25FFDA2, 0xAF45EAAF, 0x9C23BF9C, 0xA453F7A4,
    0x72E49672, 0xC09B5BC0, 0xB775C2B7, 0xFDE11CFD, 0x933DAE93, 0x264C6A26,
    0x366C5A36, 0x3F7E413F, 0xF7F502F7, 0xCC834FCC, 0x34685C34, 0xA551F4A5,
    0xE5D134E5, 0xF1F908F1, 0x71E29371, 0xD8AB73D8, 0x31625331, 0x152A3F15,
    0x04080C04, 0xC79552C7, 0x23466523, 0xC39D5EC3, 0x18302818, 0x9637A196,
    0x050A0F05, 0x9A2FB59A, 0x070E0907, 0x12243612, 0x801B9B80, 0xE2DF3DE2,
    0xEBCD26EB, 0x274E6927, 0xB27FCDB2, 0x75EA9F75, 0x09121B09, 0x831D9E83,
    0x2C58742C, 0x1A342E1A, 0x1B362D1B, 0x6EDCB26E, 0x5AB4EE5A, 0xA05BFBA0,
    0x52A4F652, 0x3B764D3B, 0xD6B761D6, 0xB37DCEB3, 0x29527B29, 0xE3DD3EE3,
    0x2F5E712F, 0x84139784, 0x53A6F553, 0xD1B968D1, 0x00000000, 0xEDC12CED,
    0x20406020, 0xFCE31FFC, 0xB179C8B1, 0x5BB6ED5B, 0x6AD4BE6A, 0xCB8D46CB,
    0xBE67D9BE, 0x39724B39, 0x4A94DE4A, 0x4C98D44C, 0x58B0E858, 0xCF854ACF,
    0xD0BB6BD0, 0xEFC52AEF, 0xAA4FE5AA, 0xFBED16FB, 0x4386C543, 0x4D9AD74D,
    0x33665533, 0x85119485, 0x458ACF45, 0xF9E910F9, 0x02040602, 0x7FFE817F,
    0x50A0F050, 0x3C78443C, 0x9F25BA9F, 0xA84BE3A8, 0x51A2F351, 0xA35DFEA3,
    0x4080C040, 0x8F058A8F, 0x923FAD92, 0x9D21BC9D, 0x38704838, 0xF5F104F5,
    0xBC63DFBC, 0xB677C1B6, 0xDAAF75DA, 0x21426321, 0x10203010, 0xFFE51AFF,
    0xF3FD0EF3, 0xD2BF6DD2, 0xCD814CCD, 0x0C18140C, 0x13263513, 0xECC32FEC,
    0x5FBEE15F, 0x9735A297, 0x4488CC44, 0x172E3917, 0xC49357C4, 0xA755F2A7,
    0x7EFC827E, 0x3D7A473D, 0x64C8AC64, 0x5DBAE75D, 0x19322B19, 0x73E69573,
    0x60C0A060, 0x81199881, 0x4F9ED14F, 0xDCA37FDC, 0x22446622, 0x2A547E2A,
    0x903BAB90, 0x880B8388, 0x468CCA46, 0xEEC729EE, 0xB86BD3B8, 0x14283C14,
    0xDEA779DE, 0x5EBCE25E, 0x0B161D0B, 0xDBAD76DB, 0xE0DB3BE0, 0x32645632,
    0x3A744E3A, 0x0A141E0A, 0x4992DB49, 0x060C0A06, 0x24486C24, 0x5CB8E45C,
    0xC29F5DC2, 0xD3BD6ED3, 0xAC43EFAC, 0x62C4A662, 0x9139A891, 0x9531A495,
    0xE4D337E4, 0x79F28B79, 0xE7D532E7, 0xC88B43C8, 0x376E5937, 0x6DDAB76D,
    0x8D018C8D, 0xD5B164D5, 0x4E9CD24E, 0xA949E0A9, 0x6CD8B46C, 0x56ACFA56,
    0xF4F307F4, 0xEACF25EA, 0x65CAAF65, 0x7AF48E7A, 0xAE47E9AE, 0x08101808,
    0xBA6FD5BA, 0x78F08878, 0x254A6F25, 0x2E5C722E, 0x1C38241C, 0xA657F1A6,
    0xB473C7B4, 0xC69751C6, 0xE8CB23E8, 0xDDA17CDD, 0x74E89C74, 0x1F3E211F,
    0x4B96DD4B, 0xBD61DCBD, 0x8B0D868B, 0x8A0F858A, 0x70E09070, 0x3E7C423E,
    0xB571C4B5, 0x66CCAA66, 0x4890D848, 0x03060503, 0xF6F701F6, 0x0E1C120E,
    0x61C2A361, 0x356A5F35, 0x57AEF957, 0xB969D0B9, 0x86179186, 0xC19958C1,
    0x1D3A271D, 0x9E27B99E, 0xE1D938E1, 0xF8EB13F8, 0x982BB398, 0x11223311,
    0x69D2BB69, 0xD9A970D9, 0x8E07898E, 0x9433A794, 0x9B2DB69B, 0x1E3C221E,
    0x87159287, 0xE9C920E9, 0xCE8749CE, 0x55AAFF55, 0x28507828, 0xDFA57ADF,
    0x8C038F8C, 0xA159F8A1, 0x89098089, 0x0D1A170D, 0xBF65DABF, 0xE6D731E6,
    0x4284C642, 0x68D0B868, 0x4182C341, 0x9929B099, 0x2D5A772D, 0x0F1E110F,
    0xB07BCBB0, 0x54A8FC54, 0xBB6DD6BB, 0x162C3A16
};

static const uint32_t rijndael_dtbl4[] = {
    0xC6A56363, 0xF8847C7C, 0xEE997777, 0xF68D7B7B, 0xFF0DF2F2, 0xD6BD6B6B,
    0xDEB16F6F, 0x9154C5C5, 0x60503030, 0x02030101, 0xCEA96767, 0x567D2B2B,
    0xE719FEFE, 0xB562D7D7, 0x4DE6ABAB, 0xEC9A7676, 0x8F45CACA, 0x1F9D8282,
    0x8940C9C9, 0xFA877D7D, 0xEF15FAFA, 0xB2EB5959, 0x8EC94747, 0xFB0BF0F0,
    0x41ECADAD, 0xB367D4D4, 0x5FFDA2A2, 0x45EAAFAF, 0x23BF9C9C, 0x53F7A4A4,
    0xE4967272, 0x9B5BC0C0, 0x75C2B7B7, 0xE11CFDFD, 0x3DAE9393, 0x4C6A2626,
    0x6C5A3636, 0x7E413F3F, 0xF502F7F7, 0x834FCCCC, 0x685C3434, 0x51F4A5A5,
    0xD134E5E5, 0xF908F1F1, 0xE2937171, 0xAB73D8D8, 0x62533131, 0x2A3F1515,
    0x080C0404, 0x9552C7C7, 0x46652323, 0x9D5EC3C3, 0x30281818, 0x37A19696,
    0x0A0F0505, 0x2FB59A9A, 0x0E090707, 0x24361212, 0x1B9B8080, 0xDF3DE2E2,
    0xCD26EBEB, 0x4E692727, 0x7FCDB2B2, 0xEA9F7575, 0x121B0909, 0x1D9E8383,
    0x58742C2C, 0x342E1A1A, 0x362D1B1B, 0xDCB26E6E, 0xB4EE5A5A, 0x5BFBA0A0,
    0xA4F65252, 0x764D3B3B, 0xB761D6D6, 0x7DCEB3B3, 0x527B2929, 0xDD3EE3E3,
    0x5E712F2F, 0x13978484, 0xA6F55353, 0xB968D1D1, 0x00000000, 0xC12CEDED,
    0x40602020, 0xE31FFCFC, 0x79C8B1B1, 0xB6ED5B5B, 0xD4BE6A6A, 0x8D46CBCB,
    0x67D9BEBE, 0x724B3939, 0x94DE4A4A, 0x98D44C4C, 0xB0E85858, 0x854ACFCF,
    0xBB6BD0D0, 0xC52AEFEF, 0x4FE5AAAA, 0xED16FBFB, 0x86C54343, 0x9AD74D4D,
    0x66553333, 0x11948585, 0x8ACF4545, 0xE910F9F9, 0x04060202, 0xFE817F7F,
    0xA0F05050, 0x78443C3C, 0x25BA9F9F, 0x4BE3A8A8, 0xA2F35151, 0x5DFEA3A3,
    0x80C04040, 0x058A8F8F, 0x3FAD9292, 0x21BC9D9D, 0x70483838, 0xF104F5F5,
    0x63DFBCBC, 0x77C1B6B6, 0xAF75DADA, 0x42632121, 0x20301010, 0xE51AFFFF,
    0xFD0EF3F3, 0xBF6DD2D2, 0x814CCDCD, 0x18140C0C, 0x26351313, 0xC32FECEC,
    0xBEE15F5F, 0x35A29797, 0x88CC4444, 0x2E391717, 0x9357C4C4, 0x55F2A7A7,
    0xFC827E7E, 0x7A473D3D, 0xC8AC6464, 0xBAE75D5D, 0x322B1919, 0xE6957373,
    0xC0A06060, 0x19988181, 0x9ED14F4F, 0xA37FDCDC, 0x44662222, 0x547E2A2A,
    0x3BAB9090, 0x0B838888, 0x8CCA4646, 0xC729EEEE, 0x6BD3B8B8, 0x283C1414,
    0xA779DEDE, 0xBCE25E5E, 0x161D0B0B, 0xAD76DBDB, 0xDB3BE0E0, 0x64563232,
    0x744E3A3A, 0x141E0A0A, 0x92DB4949, 0x0C0A0606, 0x486C2424, 0xB8E45C5C,
    0x9F5DC2C2, 0xBD6ED3D3, 0x43EFACAC, 0xC4A66262, 0x39A89191, 0x31A49595,
    0xD337E4E4, 0xF28B7979, 0xD532E7E7, 0x8B43C8C8, 0x6E593737, 0xDAB76D6D,
    0x018C8D8D, 0xB164D5D5, 0x9CD24E4E, 0x49E0A9A9, 0xD8B46C6C, 0xACFA5656,
    0xF307F4F4, 0xCF25EAEA, 0xCAAF6565, 0xF48E7A7A, 0x47E9AEAE, 0x10180808,
    0x6FD5BABA, 0xF0887878, 0x4A6F2525, 0x5C722E2E, 0x38241C1C, 0x57F1A6A6,
    0x73C7B4B4, 0x9751C6C6, 0xCB23E8E8, 0xA17CDDDD, 0xE89C7474, 0x3E211F1F,
    0x96DD4B4B, 0x61DCBDBD, 0x0D868B8B, 0x0F858A8A, 0xE0907070, 0x7C423E3E,
    0x71C4B5B5, 0xCCAA6666, 0x90D84848, 0x06050303, 0xF701F6F6, 0x1C120E0E,
    0xC2A36161, 0x6A5F3535, 0xAEF95757, 0x69D0B9B9, 0x17918686, 0x9958C1C1,
    0x3A271D1D, 0x27B99E9E, 0xD938E1E1, 0xEB13F8F8, 0x2BB39898, 0x22331111,
    0xD2BB6969, 0xA970D9D9, 0x07898E8E, 0x33A79494, 0x2DB69B9B, 0x3C221E1E,
    0x15928787, 0xC920E9E9, 0x8749CECE, 0xAAFF5555, 0x50782828, 0xA57ADFDF,
    0x038F8C8C, 0x59F8A1A1, 0x09808989, 0x1A170D0D, 0x65DABFBF, 0xD731E6E6,
    0x84C64242, 0xD0B86868, 0x82C34141, 0x29B09999, 0x5A772D2D, 0x1E110F0F,
    0x7BCBB0B0, 0xA8FC5454, 0x6DD6BBBB, 0x2C3A1616
};

#define LOBYTE(x) *reinterpret_cast<uint8_t*>(&x)  // low byte

inline int32_t LE_DecodeSigned32(const char* data)
{
    return data[3] | ((data[2] | ((data[1] | (data[0] << 8)) << 8)) << 8);
}

template <typename T>
inline uint8_t GetByteFrom(T value, size_t bytePos)
{
    if (bytePos >= sizeof(T))
    {
        throw std::runtime_error("The byte position is too large");
    }

    return reinterpret_cast<uint8_t*>(&value)[bytePos];
}

void SnowCipher::SetKey(const uint8_t* key)
{
    int v10;            // edi@1
    unsigned int v11;   // ebx@1
    int v12;            // esi@1
    unsigned int v13;   // eax@1
    unsigned int v14;   // ebx@3
    int v15;            // esi@3
    int v16;            // edx@3
    int v17;            // edi@3
    unsigned int v18;   // ebx@3
    int v19;            // edi@3
    int v20;            // edx@3
    int v21;            // esi@3
    uint8_t v22;        // ST14_1@3
    int v23;            // edi@3
    int v24;            // ebx@3
    int v25;            // edi@3
    int v26;            // eax@3
    int v27;            // edx@3
    int v28;            // edi@3
    int v29;            // ST14_4@3
    int v30;            // eax@3
    int v31;            // esi@3
    int v32;            // edi@3
    int v33;            // eax@3
    int v34;            // edi@3
    int v35;            // ST14_4@3
    int v36;            // eax@3
    int v37;            // esi@3
    int v38;            // edi@3
    int v39;            // eax@3
    int v40;            // edi@3
    int v41;            // ST14_4@3
    int v42;            // eax@3
    int v43;            // esi@3
    int v44;            // edi@3
    int v45;            // eax@3
    int v46;            // edi@3
    int v47;            // ST14_4@3
    int v48;            // eax@3
    int v49;            // esi@3
    int v50;            // edi@3
    int v51;            // eax@3
    int v52;            // edi@3
    int v53;            // ST14_4@3
    int v54;            // esi@3
    int v55;            // eax@3
    int v56;            // edi@3
    int v57;            // eax@3
    int v58;            // edi@3
    int v59;            // edx@3
    int v60;            // ST14_4@3
    int v61;            // eax@3
    int v62;            // edi@3
    int v63;            // eax@3
    int v64;            // edi@3
    int v65;            // edx@3
    int v66;            // ST14_4@3
    int v67;            // eax@3
    int v68;            // edi@3
    int v69;            // eax@3
    int v70;            // edi@3
    int v71;            // ST14_4@3
    int v72;            // eax@3
    int v73;            // esi@3
    int v74;            // edi@3
    int v75;            // edx@3
    int v76;            // eax@3
    int v77;            // edi@3
    int v78;            // ST1C_4@3
    int v79;            // edx@3
    int v80;            // edi@3
    int v81;            // esi@3
    int v82;            // eax@3
    int v83;            // esi@3
    int v84;            // edi@3
    int v85;            // edx@3
    int v86;            // esi@3
    int v87;            // eax@3
    bool v88;           // zf@3
    int v90;            // [sp+Ch] [bp-50h]@3
    signed int v91;     // [sp+10h] [bp-4Ch]@1
    int v92;            // [sp+14h] [bp-48h]@1
    unsigned int v93;   // [sp+18h] [bp-44h]@1
    unsigned int v94;   // [sp+1Ch] [bp-40h]@1
    unsigned int v95;   // [sp+20h] [bp-3Ch]@1
    unsigned int v96;   // [sp+24h] [bp-38h]@3
    unsigned int v97;   // [sp+28h] [bp-34h]@1
    unsigned int v98;   // [sp+2Ch] [bp-30h]@1
    unsigned int v99;   // [sp+30h] [bp-2Ch]@1
    unsigned int v100;  // [sp+34h] [bp-28h]@1
    unsigned int v101;  // [sp+38h] [bp-24h]@1
    unsigned int v102;  // [sp+3Ch] [bp-20h]@1
    unsigned int v103;  // [sp+40h] [bp-1Ch]@1
    unsigned int v104;  // [sp+44h] [bp-18h]@1
    unsigned int v105;  // [sp+48h] [bp-14h]@1
    unsigned int v106;  // [sp+4Ch] [bp-10h]@1
    unsigned int v107;  // [sp+50h] [bp-Ch]@1
    unsigned int v108;  // [sp+54h] [bp-8h]@1
    unsigned int v109;  // [sp+58h] [bp-4h]@1
    unsigned int v110;  // [sp+64h] [bp+8h]@1

    const auto castedKey = reinterpret_cast<const char*>(key);

    this->m_State[0] = LE_DecodeSigned32(castedKey);
    this->m_State[1] = LE_DecodeSigned32(castedKey + 4);
    this->m_State[2] = LE_DecodeSigned32(castedKey + 8);
    this->m_State[3] = LE_DecodeSigned32(castedKey + 12);
    this->m_State[4] = ~this->m_State[0];
    this->m_State[5] = ~this->m_State[1];
    this->m_State[6] = ~this->m_State[2];
    this->m_State[7] = ~this->m_State[3];

    this->m_State[8] = this->m_State[0];
    this->m_State[9] = this->m_State[1];
    this->m_State[10] = this->m_State[2];
    this->m_State[11] = this->m_State[3];
    this->m_State[12] = this->m_State[4];
    this->m_State[13] = this->m_State[5];
    this->m_State[14] = this->m_State[6];
    this->m_State[15] = this->m_State[7];

    v104 = this->m_State[3];
    v10 = 0;
    v11 = this->m_State[10];
    v12 = 0;
    v102 = this->m_State[5];
    v98 = this->m_State[6];
    v110 = this->m_State[0];
    v109 = this->m_State[8];
    v108 = this->m_State[1];
    v107 = this->m_State[9];
    v106 = this->m_State[2];
    v99 = this->m_State[11];
    v93 = this->m_State[13];
    v95 = this->m_State[13];
    v103 = this->m_State[4];
    v100 = this->m_State[14];
    v101 = this->m_State[7];
    v13 = this->m_State[15];
    v105 = this->m_State[10];
    v94 = 0;
    v92 = 0;
    v97 = this->m_State[12];
    v91 = 2;
    while (1)
    {
        v14 = v92 + v11;
        v96 = v12 ^ (v110 + v10) ^ v93 ^ (v13 << 8) ^ (v103 >> 8) ^
              sosemanuk_div_a[(uint8_t)v103] ^ sosemanuk_mul_a[v13 >> 24];
        v15 = rijndael_dtbl[(uint8_t)v94] ^ rijndael_dtbl4[v94 >> 24] ^
              rijndael_dtbl2[(uint8_t)(v94 >> 8)] ^
              rijndael_dtbl3[(uint8_t)(v94 >> 16)];

        v16 = v97 ^ (v104 >> 8) ^ (v100 << 8) ^ (v14 + v96) ^
              sosemanuk_div_a[(uint8_t)v104] ^ sosemanuk_mul_a[v100 >> 24];
        v100 = v15 ^ v16;
        v17 = rijndael_dtbl[(uint8_t)v14] ^ rijndael_dtbl4[v14 >> 24] ^
              rijndael_dtbl2[(uint8_t)(v14 >> 8)] ^
              rijndael_dtbl3[(uint8_t)(v14 >> 16)];

        v18 = v17 + v109;
        v95 = v17 ^ ((v15 ^ v16) + v15 + v107) ^ (v106 >> 8) ^ (v95 << 8) ^
              sosemanuk_div_a[(uint8_t)v106] ^
              sosemanuk_mul_a[(uint64_t)v95 >> 24] ^ v99;
        v19 = rijndael_dtbl[(uint8_t)(v15 + v107)] ^
              rijndael_dtbl4[(v15 + v107) >> 24] ^
              rijndael_dtbl2[(uint8_t)((uint16_t)(v15 + v107) >> 8)] ^
              rijndael_dtbl3[(uint8_t)((v15 + v107) >> 16)];
        v20 = (v108 >> 8) ^ (v97 << 8) ^ sosemanuk_div_a[(uint8_t)v108] ^
              sosemanuk_mul_a[(uint64_t)v97 >> 24];

        this->m_State[18] = v19 + v101;
        v97 = v19 ^ (v18 + v95) ^ v105 ^ v20;
        v21 = v19 + v101 + v97;
        v22 = v19 + v101;
        v23 = rijndael_dtbl[(uint8_t)v18] ^ rijndael_dtbl4[v18 >> 24] ^
              rijndael_dtbl2[(uint8_t)(v18 >> 8)] ^
              rijndael_dtbl3[(uint8_t)(v18 >> 16)];
        v24 = v23 + v98;
        v99 = v23 ^ v21 ^ v107 ^ (v99 << 8) ^ (v110 >> 8) ^
              sosemanuk_div_a[(uint8_t)v110] ^
              sosemanuk_mul_a[(uint64_t)v99 >> 24];
        v25 = rijndael_dtbl[v22] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v26 = GetByteFrom(this->m_State[18], 3);
        v27 = sosemanuk_mul_a[v105 >> 24];
        this->m_State[18] = v24;
        v28 = rijndael_dtbl4[v26] ^ v25;
        v29 = v28 + v102;
        v105 = v28 ^ (v24 + v99) ^ v109 ^ (v96 >> 8) ^ (v105 << 8) ^
               sosemanuk_div_a[(uint8_t)v96] ^ v27;
        v30 = (uint8_t)v24;
        LOBYTE(v24) = v28 + v102;
        v31 = v28 + v102 + v105;
        v32 = rijndael_dtbl[v30] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v33 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v29;
        v34 = rijndael_dtbl4[v33] ^ v32;
        v35 = v34 + v103;
        v107 = v34 ^ v31 ^ v101 ^ (v107 << 8) ^ (v100 >> 8) ^
               sosemanuk_div_a[(uint8_t)v100] ^ sosemanuk_mul_a[v107 >> 24];
        v36 = (uint8_t)v24;
        LOBYTE(v24) = v34 + v103;
        v37 = v34 + v103 + v107;
        v38 = rijndael_dtbl[v36] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v39 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v35;
        v40 = rijndael_dtbl4[v39] ^ v38;
        v41 = v40 + v104;
        v109 = v40 ^ v37 ^ v98 ^ (v109 << 8) ^ (v95 >> 8) ^
               sosemanuk_div_a[(uint8_t)v95] ^ sosemanuk_mul_a[v109 >> 24];
        v42 = (uint8_t)v24;
        LOBYTE(v24) = v40 + v104;
        v43 = v40 + v104 + v109;
        v44 = rijndael_dtbl[v42] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v45 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v41;
        v46 = rijndael_dtbl4[v45] ^ v44;
        v47 = v46 + v106;
        v101 = v46 ^ v43 ^ v102 ^ (v101 << 8) ^ (v97 >> 8) ^
               sosemanuk_div_a[(uint8_t)v97] ^ sosemanuk_mul_a[v101 >> 24];
        v48 = (uint8_t)v24;
        LOBYTE(v24) = v46 + v106;
        v49 = v46 + v106 + v101;
        v50 = rijndael_dtbl[v48] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v51 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v47;
        v52 = rijndael_dtbl4[v51] ^ v50;
        v53 = v52 + v108;
        v54 = v52 ^ v49 ^ v103 ^ (v99 >> 8) ^ (v98 << 8) ^
              sosemanuk_div_a[(uint8_t)v99] ^ sosemanuk_mul_a[v98 >> 24];
        v98 = v54;
        v55 = (uint8_t)v24;
        LOBYTE(v24) = v52 + v108;
        v56 = rijndael_dtbl[v55] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v57 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v53;
        v58 = rijndael_dtbl4[v57] ^ v56;
        v59 = v58 ^ (v53 + v54) ^ v104 ^ (v105 >> 8) ^ (v102 << 8) ^
              sosemanuk_div_a[(uint8_t)v105] ^ sosemanuk_mul_a[v102 >> 24];
        v60 = v58 + v110;
        v102 = v59;
        v61 = (uint8_t)v24;
        LOBYTE(v24) = v58 + v110;
        v62 = rijndael_dtbl[v61] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v63 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v60;
        v64 = rijndael_dtbl4[v63] ^ v62;
        v65 = v64 ^ (v60 + v59) ^ v106 ^ (v107 >> 8) ^ (v103 << 8) ^
              sosemanuk_div_a[(uint8_t)v107] ^ sosemanuk_mul_a[v103 >> 24];
        v66 = v64 + v96;
        v103 = v65;
        v67 = (uint8_t)v24;
        LOBYTE(v24) = v64 + v96;
        v68 = rijndael_dtbl[v67] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v69 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v66;
        v70 = rijndael_dtbl4[v69] ^ v68;
        v104 = v70 ^ (v66 + v65) ^ v108 ^ (v109 >> 8) ^ (v104 << 8) ^
               sosemanuk_div_a[(uint8_t)v109] ^ sosemanuk_mul_a[v104 >> 24];
        v71 = v70 + v100;
        v72 = (uint8_t)v24;
        LOBYTE(v24) = v70 + v100;
        v73 = v70 + v100 + v104;
        v74 = rijndael_dtbl[v72] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v75 = sosemanuk_mul_a[v106 >> 24];
        v76 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v71;
        v77 = rijndael_dtbl4[v76] ^ v74;
        v93 = v95;
        v106 = v77 ^ v73 ^ v110 ^ (v101 >> 8) ^ (v106 << 8) ^
               sosemanuk_div_a[(uint8_t)v101] ^ v75;
        v78 = v77 + v95;
        v79 = sosemanuk_mul_a[v108 >> 24];
        v80 = rijndael_dtbl4[GetByteFrom(this->m_State[18], 3)] ^
              rijndael_dtbl[(uint8_t)v24] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        this->m_State[18] = v78;
        LOBYTE(v24) = v80 + v97;
        v108 = v80 ^ (v78 + v106) ^ v96 ^ (v98 >> 8) ^ (v108 << 8) ^
               sosemanuk_div_a[(uint8_t)v98] ^ v79;
        v81 = rijndael_dtbl[(uint8_t)v78] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v82 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v80 + v97;
        v83 = rijndael_dtbl4[v82] ^ v81;
        v84 = v83 ^ (v80 + v97 + v108);
        v90 = v84;
        v94 = v83 + v99;
        v85 = v84 ^ v100 ^ (v102 >> 8) ^ (v110 << 8) ^
              sosemanuk_div_a[(uint8_t)v102] ^ sosemanuk_mul_a[v110 >> 24];
        v10 = v83 + v99;
        v110 = v85;
        v86 = rijndael_dtbl[(uint8_t)v24] ^
              rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
              rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)];
        v87 = GetByteFrom(this->m_State[18], 3);
        this->m_State[18] = v10;
        v12 = rijndael_dtbl4[v87] ^ v86;
        v88 = v91-- == 1;
        v92 = v12;
        if (v88)
            break;
        v13 = v96;
        v11 = v105;
    }
    this->m_State[0] = v85;
    this->m_State[8] = v109;
    this->m_State[1] = v108;
    this->m_State[9] = v107;
    this->m_State[2] = v106;
    this->m_State[10] = v105;
    this->m_State[3] = v104;
    this->m_State[11] = v99;
    this->m_State[4] = v103;
    this->m_State[5] = v102;
    this->m_State[6] = v98;
    this->m_State[7] = v101;
    this->m_State[16] = v90;
    this->m_State[15] = v96;
    this->m_State[13] = v95;
    this->m_State[17] = v10;
    this->m_State[14] = v100;
    this->m_State[19] = v12;
    this->m_State[12] = v97;

    this->m_BlocksAvailable = 16;
}
void SnowCipher::DecryptBlock()
{
    int v2;            // esi@1
    unsigned int v3;   // edx@1
    unsigned int v4;   // ecx@1
    int v5;            // edi@1
    unsigned int v6;   // edx@1
    int v7;            // edi@1
    int v8;            // esi@1
    int v9;            // ecx@1
    int v10;           // eax@1
    int v11;           // ecx@1
    unsigned int v12;  // edx@1
    int v13;           // edi@1
    int v14;           // esi@1
    int v15;           // ecx@1
    int v16;           // eax@1
    int v17;           // ecx@1
    int v18;           // ecx@1
    unsigned int v19;  // edx@1
    int v20;           // edi@1
    int v21;           // esi@1
    int v22;           // ecx@1
    int v23;           // eax@1
    int v24;           // ecx@1
    int v25;           // edi@1
    unsigned int v26;  // eax@1
    int v27;           // ecx@1
    int v28;           // eax@1
    int v29;           // ecx@1
    int v30;           // edi@1
    int v31;           // eax@1
    int v32;           // edx@1
    int v33;           // eax@1
    int v34;           // eax@1
    int v35;           // ecx@1
    int v36;           // esi@1
    int v37;           // eax@1
    int v38;           // edx@1
    int v39;           // eax@1
    int v40;           // ecx@1
    int v41;           // esi@1
    int v42;           // eax@1
    int v43;           // edx@1
    int v44;           // eax@1
    int v45;           // esi@1
    int v46;           // eax@1
    int v47;           // ecx@1
    int v48;           // esi@1
    int v49;           // edx@1
    int v50;           // eax@1
    int v51;           // ecx@1
    int v52;           // esi@1
    int v53;           // eax@1
    int v54;           // edx@1
    int v55;           // ax@1
    int v56;           // ecx@1
    int v57;           // esi@1
    int v58;           // eax@1
    int v59;           // edx@1
    int v60;           // eax@1
    int v61;           // esi@1
    int v62;           // ecx@1
    int v63;           // eax@1
    int v64;           // esi@1
    int v65;           // edx@1
    int v66;           // eax@1
    int v67;           // eax@1
    int v68;           // ecx@1
    int v69;           // esi@1
    int v70;           // eax@1
    int v71;           // edx@1
    int v72;           // eax@1
    int v73;           // ecx@1
    int v74;           // esi@1
    int v75;           // eax@1
    int v76;           // edx@1
    int v77;           // eax@1
    int v78;           // ecx@1
    int v79;           // esi@1
    int v80;           // eax@1
    int v81;           // edx@1
    int v82;           // eax@1
    int v83;           // ecx@1
    int v84;           // esi@1
    int v85;           // eax@1
    int v86;           // edx@1
    int v87;           // eax@1
    int v88;           // eax@1
    int v89;           // esi@1
    int v90;           // ecx@1
    int v91;           // edx@1
    int v92;           // eax@1

    v2 = this->m_State[15];
    v3 = this->m_State[15];
    v4 = this->m_State[4];
    v5 = sosemanuk_div_a[(uint8_t)v4] ^ sosemanuk_mul_a[v3 >> 24];
    v6 = this->m_State[18];
    v7 = this->m_State[13] ^ (v2 << 8) ^ (v4 >> 8) ^ v5;
    v8 = this->m_State[19] + this->m_State[10];
    v9 = rijndael_dtbl3[(uint8_t)(this->m_State[18] >> 16)];
    v10 = (uint8_t)((uint16_t)this->m_State[18] >> 8);
    this->m_State[15] = v7;
    this->m_State[18] = v8;
    v11 = rijndael_dtbl[(uint8_t)v6] ^ rijndael_dtbl4[v6 >> 24] ^
          rijndael_dtbl2[v10] ^ v9;
    this->m_State[19] = v11;
    this->m_Buffer[0] = this->m_State[14] ^ v11 ^ (v8 + v7);
    v12 = this->m_State[18];
    v13 = this->m_State[12] ^ (this->m_State[14] << 8) ^
          (this->m_State[3] >> 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[3]] ^
          sosemanuk_mul_a[this->m_State[14] >> 24];
    v14 = this->m_State[9] + this->m_State[19];
    v15 = (uint8_t)(this->m_State[18] >> 16);
    v16 = (uint8_t)((uint16_t)this->m_State[18] >> 8);
    this->m_State[14] = v13;
    v17 = rijndael_dtbl3[v15];
    this->m_State[18] = v14;
    v18 = rijndael_dtbl[(uint8_t)v12] ^ rijndael_dtbl4[v12 >> 24] ^
          rijndael_dtbl2[v16] ^ v17;
    this->m_State[19] = v18;
    this->m_Buffer[1] = this->m_State[13] ^ v18 ^ (v14 + v13);
    v19 = this->m_State[18];
    v20 = this->m_State[11] ^ (this->m_State[13] << 8) ^
          (this->m_State[2] >> 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[2]] ^
          sosemanuk_mul_a[this->m_State[13] >> 24];
    v21 = this->m_State[8] + this->m_State[19];
    v22 = rijndael_dtbl3[(uint8_t)(this->m_State[18] >> 16)];
    v23 = (uint8_t)((uint16_t)this->m_State[18] >> 8);
    this->m_State[13] = v20;
    this->m_State[18] = v21;
    v24 = rijndael_dtbl[(uint8_t)v19] ^ rijndael_dtbl4[v19 >> 24] ^
          rijndael_dtbl2[v23] ^ v22;
    this->m_State[19] = v24;
    this->m_Buffer[2] = this->m_State[12] ^ v24 ^ (v21 + v20);
    v25 = this->m_State[10] ^ (this->m_State[12] << 8) ^
          (this->m_State[1] >> 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[1]] ^
          sosemanuk_mul_a[this->m_State[12] >> 24];
    this->m_State[17] = this->m_State[7] + this->m_State[19];
    v26 = this->m_State[18];
    this->m_State[12] = v25;
    v27 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl[(uint8_t)v26] ^ rijndael_dtbl4[v26 >> 24];
    v28 = this->m_State[17];
    this->m_State[18] = v28;
    this->m_State[19] = v27;
    this->m_Buffer[3] = this->m_State[11] ^ v27 ^ (v25 + v28);
    v29 = GetByteFrom(this->m_State[18], 3);
    v30 = this->m_State[9] ^ (this->m_State[11] << 8) ^
          (this->m_State[0] >> 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[0]] ^
          sosemanuk_mul_a[this->m_State[11] >> 24];
    this->m_State[17] = this->m_State[6] + this->m_State[19];
    v31 = (uint8_t)this->m_State[18];
    this->m_State[11] = v30;
    v32 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v29] ^ rijndael_dtbl[v31];
    v33 = this->m_State[17];
    this->m_State[18] = v33;
    v34 = v32 ^ this->m_State[10] ^ (v30 + v33);
    this->m_State[19] = v32;
    this->m_Buffer[4] = v34;
    v35 = GetByteFrom(this->m_State[18], 3);
    v36 = this->m_State[8] ^ (this->m_State[10] << 8) ^
          (this->m_State[15] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[15]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[10], 3)];
    this->m_State[17] = this->m_State[5] + this->m_State[19];
    v37 = (uint8_t)this->m_State[18];
    this->m_State[10] = v36;
    v38 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v35] ^ rijndael_dtbl[v37];
    v39 = this->m_State[17];
    this->m_State[18] = v39;
    this->m_State[19] = v38;
    this->m_Buffer[5] = this->m_State[9] ^ v38 ^ (v36 + v39);
    v40 = GetByteFrom(this->m_State[18], 3);
    v41 = this->m_State[7] ^ (this->m_State[9] << 8) ^
          (this->m_State[14] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[14]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[9], 3)];
    this->m_State[17] = this->m_State[19] + this->m_State[4];
    v42 = (uint8_t)this->m_State[18];
    this->m_State[9] = v41;
    v43 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v40] ^ rijndael_dtbl[v42];
    v44 = this->m_State[17];
    this->m_State[18] = v44;
    this->m_State[19] = v43;
    this->m_Buffer[6] = this->m_State[8] ^ v43 ^ (v41 + v44);
    v45 = (this->m_State[8] << 8) ^ (this->m_State[13] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[13]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[8], 3)];
    this->m_State[17] = this->m_State[3] + this->m_State[19];
    v46 = (uint8_t)this->m_State[18];
    v47 = GetByteFrom(this->m_State[18], 3);
    v48 = this->m_State[6] ^ v45;
    this->m_State[8] = v48;
    v49 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v47] ^ rijndael_dtbl[v46];
    v50 = this->m_State[17];
    this->m_State[18] = v50;
    this->m_State[19] = v49;
    this->m_Buffer[7] = this->m_State[7] ^ v49 ^ (v48 + v50);
    v51 = GetByteFrom(this->m_State[18], 3);
    v52 = this->m_State[5] ^ (this->m_State[7] << 8) ^
          (this->m_State[12] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[12]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[7], 3)];
    this->m_State[17] = this->m_State[2] + this->m_State[19];
    v53 = (uint8_t)this->m_State[18];
    this->m_State[7] = v52;
    v54 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v51] ^ rijndael_dtbl[v53];
    v55 = this->m_State[17];
    this->m_State[18] = v55;
    this->m_State[19] = v54;
    this->m_Buffer[8] = this->m_State[6] ^ v54 ^ (v52 + v55);
    v56 = GetByteFrom(this->m_State[18], 3);
    v57 = this->m_State[4] ^ (this->m_State[6] << 8) ^
          (this->m_State[11] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[11]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[6], 3)];
    this->m_State[17] = this->m_State[1] + this->m_State[19];
    v58 = (uint8_t)this->m_State[18];
    this->m_State[6] = v57;
    v59 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v56] ^ rijndael_dtbl[v58];
    v60 = this->m_State[17];
    this->m_State[18] = v60;
    this->m_State[19] = v59;
    this->m_Buffer[9] = this->m_State[5] ^ v59 ^ (v57 + v60);
    v61 = (this->m_State[5] << 8) ^ (this->m_State[10] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[10]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[5], 3)];
    v62 = GetByteFrom(this->m_State[18], 3);
    this->m_State[17] = this->m_State[0] + this->m_State[19];
    v63 = (uint8_t)this->m_State[18];
    v64 = this->m_State[3] ^ v61;
    this->m_State[5] = v64;
    v65 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v62] ^ rijndael_dtbl[v63];
    v66 = this->m_State[17];
    this->m_State[18] = v66;
    v67 = v65 ^ this->m_State[4] ^ (v64 + v66);
    this->m_State[19] = v65;
    this->m_Buffer[10] = v67;
    v68 = GetByteFrom(this->m_State[18], 3);
    v69 = this->m_State[2] ^ (this->m_State[4] << 8) ^ (this->m_State[9] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[9]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[4], 3)];
    this->m_State[17] = this->m_State[15] + this->m_State[19];
    v70 = (uint8_t)this->m_State[18];
    this->m_State[4] = v69;
    v71 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v68] ^ rijndael_dtbl[v70];
    v72 = this->m_State[17];
    this->m_State[18] = v72;
    this->m_State[19] = v71;
    this->m_Buffer[11] = this->m_State[3] ^ v71 ^ (v69 + v72);
    v73 = GetByteFrom(this->m_State[18], 3);
    v74 = this->m_State[1] ^ (this->m_State[3] << 8) ^ (this->m_State[8] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[8]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[3], 3)];
    this->m_State[17] = this->m_State[14] + this->m_State[19];
    v75 = (uint8_t)this->m_State[18];
    this->m_State[3] = v74;
    v76 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v73] ^ rijndael_dtbl[v75];
    v77 = this->m_State[17];
    this->m_State[18] = v77;
    this->m_State[19] = v76;
    this->m_Buffer[12] = this->m_State[2] ^ v76 ^ (v74 + v77);
    v78 = GetByteFrom(this->m_State[18], 3);
    v79 = this->m_State[0] ^ (this->m_State[2] << 8) ^ (this->m_State[7] >> 8) ^
          sosemanuk_div_a[(uint8_t)this->m_State[7]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[2], 3)];
    this->m_State[17] = this->m_State[13] + this->m_State[19];
    v80 = (uint8_t)(this->m_State[18]);
    this->m_State[2] = v79;
    v81 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v78] ^ rijndael_dtbl[v80];
    v82 = this->m_State[17];
    this->m_State[18] = v82;
    this->m_State[19] = v81;
    this->m_Buffer[13] = this->m_State[1] ^ v81 ^ (v79 + v82);
    v83 = GetByteFrom(this->m_State[18], 3);
    v84 = this->m_State[15] ^ (this->m_State[1] << 8) ^
          (this->m_State[6] >> 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[6]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[1], 3)];
    this->m_State[17] = this->m_State[12] + this->m_State[19];
    v85 = (uint8_t)(this->m_State[18]);
    this->m_State[1] = v84;
    v86 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v83] ^ rijndael_dtbl[v85];
    v87 = this->m_State[17];
    this->m_State[18] = v87;
    this->m_State[19] = v86;
    this->m_Buffer[14] = this->m_State[0] ^ v86 ^ (v84 + v87);
    v88 = this->m_State[19];
    v89 = this->m_State[14] ^ (this->m_State[5] >> 8) ^
          (this->m_State[0] << 8) ^ sosemanuk_div_a[(uint8_t)this->m_State[5]] ^
          sosemanuk_mul_a[GetByteFrom(this->m_State[0], 3)];
    this->m_State[0] = v89;
    v90 = GetByteFrom(this->m_State[18], 3);
    this->m_State[17] = this->m_State[11] + v88;
    v91 = rijndael_dtbl3[GetByteFrom(this->m_State[18], 2)] ^
          rijndael_dtbl2[GetByteFrom(this->m_State[18], 1)] ^
          rijndael_dtbl4[v90] ^ rijndael_dtbl[(uint8_t)this->m_State[18]];
    v92 = this->m_State[17];
    this->m_State[18] = v92;
    this->m_State[19] = v91;
    this->m_Buffer[15] = this->m_State[15] ^ v91 ^ (v89 + v92);
}

void SnowCipher::DecryptBufferImpl(uint32_t* outBuffer, const uint8_t* inBuffer,
                                   uint32_t dataSize)
{
    uint32_t numBlocks = dataSize / SNOW_BLOCKS_SIZE;
    auto diff = GetPtrDiff(inBuffer, outBuffer);

    for (; numBlocks > 0; numBlocks--)
    {
        if (this->m_BlocksAvailable == 16)
        {
            this->DecryptBlock();
            this->m_BlocksAvailable = 0;
        }

        const uint32_t sourceData = *reinterpret_cast<uint32_t*>(
            reinterpret_cast<uint8_t*>(outBuffer) + diff);

        *outBuffer++ = sourceData - this->m_Buffer[this->m_BlocksAvailable];

        this->m_BlocksAvailable++;
    }
}
