

#if TARGET_LPC11XX
#include "peripherals/uart.h"
#include "peripherals/time.h"
#else

#include <stdint.h>
#include <sys/time.h>

#define uartInit(rate)
#define initTime()

uint64_t getTimeMs(void)
{
    struct timeval l_now;
    gettimeofday(&l_now, NULL);
    uint64_t l_time = ((uint64_t)(l_now.tv_sec)) * 1000 + l_now.tv_usec / 1000;
    return l_time;
}

#endif

#include "ecc.h"

#include <stdio.h>

void vli_print(uint32_t *p_vli)
{
    unsigned i;
    for(i=0; i<NUM_ECC_DIGITS; ++i)
	{
		printf("%08X ", (unsigned)p_vli[i]);
	}
}

#if (ECC_CURVE == secp128r1)
uint32_t g_private[10][NUM_ECC_DIGITS] = {
    {0xB66C17D0, 0xD21CD12E, 0x1885B2F7, 0x71D40584},
    {0x6C99B53A, 0x86686357, 0x3E34C5C4, 0x5314DFA3},
    {0x458B1408, 0x86D162A3, 0x7AB33E92, 0x92C9E643},
    {0x91872C30, 0x46F7AAEF, 0x45F7C29A, 0x9E2BCCA4},
    {0x9AC2ABD1, 0xAF62B5F0, 0x2EFDBA0B, 0x6A9221FE},
    {0x1CE0D4AD, 0x614EDCF0, 0x361314D4, 0xBF3687D2},
    {0x990B5252, 0xCE0038D9, 0xB4C9A00B, 0x1094CF4D},
    {0xF0A29720, 0x0140B5C9, 0x52CF21F3, 0x3294E456},
    {0xC01E9087, 0x47170C2D, 0x2C597A81, 0xE1D7FEB6},
    {0x8183C9A6, 0xA1C01A50, 0x592E9603, 0xDEB7FED9},
};

EccPoint g_public[10] = {
    {{0xE4C0291F, 0xA1F2E44A, 0x0B3653FD, 0x6930B1C5},
        {0x8FD9A49A, 0xAC811AB9, 0x428FAAEC, 0xDDFD5DEF}},
    {{0xC39CF076, 0xDE94A5CD, 0x73AEB0D7, 0xCE5451B4},
        {0x3BA9ED5F, 0xCF743693, 0x3C9A43C7, 0xEDDFD7E2}},
    {{0x80368A66, 0x5937CAAF, 0x3BEE2BE7, 0xE64E733D},
        {0x3AA8F7E9, 0xA483C9E6, 0x8F794AD1, 0xC337CB9E}},
    {{0x1E5EAFAF, 0x77D36D21, 0xE9532F7C, 0xAFE7E501},
        {0x7D79C739, 0x7EE43DCC, 0x6680981F, 0x7E114077}},
    {{0x8AF00B25, 0xE00AA428, 0xA6DFABA0, 0xF44E2CF0},
        {0xE243BA1D, 0x7F900DE8, 0xA944C17B, 0x4C11C099}},
    {{0xC39C6109, 0xB373DB65, 0xCDA94697, 0x27345B77},
        {0x401618E6, 0x13A6C49C, 0x5869940B, 0x5115144E}},
    {{0x80DCF189, 0x0B44F328, 0x50A421A2, 0x034FE115},
        {0x2E0C0BF9, 0xFE0F8E7D, 0x3EF947B3, 0x5879B903}},
    {{0x68ADE268, 0x7ECCF41C, 0x141BF575, 0x3876C94D},
        {0x8017B034, 0x7598E395, 0x3F979AC2, 0x70700920}},
    {{0xD1CBAE92, 0xA81BA5EC, 0xC4CF64D8, 0x8E30FCF2},
        {0x79A77D42, 0x84A578B8, 0xEDE0FAFB, 0xF67F3976}},
    {{0x08BAF713, 0x289B0411, 0x2FC8B73F, 0x19AB8B64},
        {0x80EE6E22, 0xF184553A, 0xBD4E27F1, 0x121DC4BF}},
};

EccPoint g_dsa_public[10] = {
    {{0x3BF40ACD, 0x47C43515, 0x7EF7776C, 0x4A1A56BD},
        {0x86C456C4, 0x7D5452B3, 0x5A71CB1C, 0x557E7DBA}},
    {{0xBB2C4BC5, 0x92A6F258, 0x698C4132, 0x77EBD4F6},
        {0x0DFCE2BE, 0x1E9F38D1, 0x1F1672BB, 0xE48AD5A6}},
    {{0xC53665DE, 0xF796CDF3, 0xAE0165D2, 0x75CBA47E},
        {0x7336153C, 0xCEE54F1A, 0x243001D7, 0x08C56FA2}},
    {{0xAC487684, 0x989A06FF, 0x5812CF70, 0x418451C5},
        {0xA092267D, 0xDB28AC7B, 0x79D772FA, 0x9898EE91}},
    {{0xB7AA3ED1, 0x6DD68A8B, 0xB796926D, 0xA45256A1},
        {0xE5D12EB9, 0xF56CE706, 0x9FA9840D, 0xE665F35E}},
    {{0xDB11B8C2, 0x9A78D801, 0x523A90D2, 0xBACAB029},
        {0x6C5C3F33, 0x34327C0D, 0x452020CC, 0x82BAE8A2}},
    {{0xB72B7EC5, 0x2AF6DAAD, 0x1E3440C1, 0xDB15D156},
        {0x04A0C7AF, 0xA262862B, 0xE9657086, 0x8196A8C9}},
    {{0xA561E856, 0x3E9712FC, 0x38B4EC8D, 0x2ADD982A},
        {0x3C45ECCB, 0xAD94F662, 0xDBA7EB71, 0xE50148A0}},
    {{0x0CA79470, 0x34C49E8E, 0xB6C5D67B, 0xE548B400},
        {0x219B9423, 0x2B1666AF, 0x8103E95D, 0xBA982BA1}},
    {{0x1FC73855, 0xDEE2951E, 0xD7B2EA31, 0x8D5198A5},
        {0x65463BE4, 0x91C22AED, 0xEBC4C954, 0xAC0F17CA}}
};

uint32_t g_dsa_hash[10][NUM_ECC_DIGITS] = {
    {0x7EDFA046, 0xEDEF56B0, 0x204E9405, 0x6C221091},
    {0x2F0A9913, 0xC0EBE74B, 0xFBF876BF, 0x5D85FC5A},
    {0xE14B6614, 0xCA6DFFFB, 0x9A6C4C2E, 0x2B29E976},
    {0xC8B0C1A0, 0x584FAC6D, 0xABC7A29C, 0x76B006BB},
    {0xB68F9E9E, 0xC71ED804, 0x4EE9D024, 0x5DF1E934},
    {0x2720E130, 0xCEC81D28, 0x34A948A3, 0xBB25B8AD},
    {0x9790D3F2, 0xAEB49860, 0x0A225C6F, 0x2A359D47},
    {0x3754231C, 0xDEAFB3C3, 0xEFD7EE61, 0x6D94A3CA},
    {0xBDCAB305, 0xF54F6A93, 0x3EF92B4B, 0xE677CE89},
    {0x2CD46627, 0xC8FEE21B, 0xF1C61AB0, 0x551DBF80}
};

uint32_t g_dsa_r[10][NUM_ECC_DIGITS] = {
    {0x5A790759, 0xEDE0720D, 0xAC4E0253, 0x3E801589},
    {0x78A47EC5, 0x7B1AD158, 0xE6477BCE, 0x3C60A807},
    {0xEB15FA62, 0x7A0FB1E5, 0x9D54F52A, 0xB71DED39},
    {0x7486F11C, 0x37278B55, 0x27BDB806, 0xB1DBC394},
    {0xE4CF5A49, 0xE8BB70CF, 0x464327BF, 0x353F859D},
    {0x7853BA1B, 0xDA416B63, 0x77E428D0, 0x16633DD3},
    {0xAABEAEC1, 0x102ECA60, 0x72D40FC5, 0x31D4D6F5},
    {0x79B42218, 0xA163F4E9, 0xF61B9347, 0x3966758B},
    {0x26864C41, 0x13166783, 0x14040893, 0xBEEF727E},
    {0x341E5A36, 0x1FB97317, 0x421F9268, 0xC93B8C3C}
};

uint32_t g_dsa_s[10][NUM_ECC_DIGITS] = {
    {0xDE092D94, 0x416B7122, 0xA4E4BBF1, 0x76780756},
    {0xDFC20351, 0x5D24542C, 0x387EF72C, 0x3CD22E7F},
    {0xFAE39822, 0x6DE6BB76, 0x8D0DBF2B, 0x31148CAF},
    {0xE07C437A, 0xECAD8CC0, 0xFB419885, 0xD391133D},
    {0xCD64EFD6, 0xC7104127, 0xC5F5DC9E, 0x04433A75},
    {0x3514A666, 0x0FDD88A3, 0x9D44DCD1, 0xC0852A04},
    {0xB4D1F036, 0xBF91D4F3, 0x70E95E03, 0x0343B7AE},
    {0x27A62A2B, 0x861B2FC3, 0x3411861F, 0xDA664A5F},
    {0x168DED9E, 0x47C10A41, 0x88DF9A30, 0xB30EE524},
    {0x7A19D7C2, 0x51AE91C0, 0x318DBAD9, 0xE520A100}
};

#elif (ECC_CURVE == secp192r1)
uint32_t g_private[10][NUM_ECC_DIGITS] = {
    {0x8A8590BC, 0xF8FC6B96, 0x216D16F6, 0x5D471999, 0x77B54115, 0xA1C40C96},
    {0x60867073, 0xC781509C, 0x36ACD71C, 0x58F5AD9E, 0xC2DB7360, 0x33BD208D},
    {0x57DE05EC, 0xBE8B9D15, 0xB0D84224, 0xD7E9176A, 0x5C97EE8D, 0x7D23952C},
    {0x0D4797E8, 0xAB361B2F, 0xFEE3BBF4, 0xBE23CF61, 0xA3F0D27B, 0xD1D49358},
    {0x681377E1, 0xF4DF8EB5, 0x9A55C8EA, 0x04816C18, 0x628B310F, 0x5019DC6E},
    {0x430A1A53, 0x16954A28, 0x3A675EB6, 0xC971CE03, 0xF6C628A5, 0x0FE11176},
    {0x7EB0C3B1, 0x55183558, 0x02BC274B, 0xFB1559AC, 0xAD50B416, 0xA185E502},
    {0x661666FD, 0xFC766ABB, 0xCCDA7437, 0x63B33C0D, 0x532B2329, 0x16A57B57},
    {0x3E540682, 0xE790A2F1, 0x9B3291E1, 0xB68EBC35, 0x0C88E534, 0x1F609E43},
    {0xE1C5244B, 0x9137E9E7, 0xD61F7DD0, 0x47200D7B, 0x71707AA7, 0x3BAF4CAE},
};

EccPoint g_public[10] = {
    {{0x58379FA5, 0xBF0AD3C0, 0x43C46341, 0x03C17E4C, 0x141E4B2D, 0x9262FBC4},
        {0xFD42BF5B, 0x2DA93B96, 0xA2F44FD2, 0xE49AC322, 0x325AD938, 0x7EC78924}},
    {{0xD43D49BD, 0x5E3EDC91, 0xC4B92D43, 0x23ABD7AC, 0x2393E81F, 0xAA44251A},
        {0xE2A45AD9, 0x824E616C, 0x8AF41F54, 0x9436A042, 0x01FC4560, 0xE8006868}},
    {{0x918FC426, 0xAF4B1667, 0x38C4DFBB, 0x84D79546, 0x5816A293, 0x620F572F},
        {0x1B11B853, 0x2A76C314, 0xD7E293D3, 0x147A3FE1, 0x023BA135, 0xE8C330FA}},
    {{0x9530DB5B, 0x04A24731, 0x819B1264, 0xF1BB7518, 0xFC52AD59, 0xCE8BBA3A},
        {0xCAA5226D, 0xB7F2E77F, 0x44A0AB8E, 0xE21FBA39, 0x2820E42B, 0xFE554CDE}},
    {{0xAEEB46D1, 0x6935EC9E, 0xE3D5CC2F, 0x4D4ACEA8, 0x86BC2CEB, 0xD1E57CA2},
        {0xBE3848A3, 0x444B0017, 0xA55D148B, 0x52DE7036, 0xFBEA0864, 0xBE0E7544}},
    {{0x18BF0DE7, 0xED6E7913, 0x85DB2AC4, 0xF62E1BE9, 0x41959A17, 0x1DF4E10D},
        {0x9E1B3C21, 0x64AEB0CF, 0x3A8F9D16, 0xCC035209, 0xE369B12C, 0xEFD688A4}},
    {{0xF478AA34, 0xEACAB900, 0x850E30F4, 0xA4C67968, 0xFC6DB77E, 0x6B31449B},
        {0x7CA20F13, 0xC07C04AF, 0x84910675, 0x0907C2A4, 0xCEFF2DB5, 0xF985D758}},
    {{0xF5C45632, 0x5C62C2B6, 0xFDCDFF27, 0x08776E9A, 0x3D55752D, 0x5C0ED6D6},
        {0x43650F59, 0x14AB4374, 0xD5882DFA, 0x9CBA7BF0, 0x67A6CF8D, 0xC7D584B2}},
    {{0x2254F7DA, 0x53330058, 0x90A9AC53, 0x9B062D1A, 0x27FE77AE, 0xE44D9D00},
        {0xB7E91646, 0x685C16FA, 0xB9078665, 0x3B5E976F, 0x61D9C103, 0x3A2DF683}},
    {{0xC0875126, 0x9734E867, 0x076D4DE0, 0x6EBEA5AE, 0x3CFC3372, 0xD6A91E78},
        {0xE103662D, 0x139FD338, 0x791610BA, 0xDE584994, 0xA12D8DA4, 0x63270A3E}},
    };

EccPoint g_dsa_public[10] = {
    {{0x4F4D9AAA, 0xAF60E114, 0x87991189, 0x1D24E7D3, 0x44760D0F, 0x9E1260BE},
        {0x9ED2F42B, 0x8B29265B, 0x8D6D800E, 0xBF05A3D2, 0x10604D33, 0xC9A56477}},
    {{0x29056368, 0x8281C7F2, 0x522BF2E9, 0xFC23BF79, 0xF9F2F269, 0xE27D0965},
        {0x4EF1C035, 0x3103FCD2, 0x67A056F1, 0x190A319D, 0x27BE1292, 0x734D6D12}},
    {{0x89BE85C6, 0x1130FBF1, 0x1288B622, 0x7F6891F0, 0xBA863A0E, 0x932669D1},
        {0x4AB1D95D, 0x7E0F41BE, 0xCA1F2313, 0x0A533CDA, 0xDC7585B3, 0x12BAB148}},
    {{0xF667FF6E, 0xC5C2C25E, 0x5EC82FC7, 0xF9164E06, 0xD139DDC5, 0xE1B80602},
        {0xD1B02660, 0x7ED41D69, 0x32CB6EA8, 0x7624EC39, 0xE21488C3, 0xE0DF21BF}},
    {{0x46A619F7, 0x0A8432F2, 0xF83A496B, 0x7A5C308F, 0x7877086A, 0x1826FF66},
        {0xE3E8745C, 0xA2409D62, 0x2D382294, 0xCB157A6D, 0x5614ED7B, 0x7B18F718}},
    {{0x2F1A3D3C, 0x88D0169B, 0xAA1D7280, 0xA212860B, 0x1D597CBC, 0xD584C38F},
        {0x4910C071, 0x23CA1B76, 0x4B5D8709, 0x7388E349, 0x375037EA, 0xEF7268AA}},
    {{0x4E3D4333, 0xBD81D238, 0xE767795F, 0xBD4B77EA, 0xF6601C06, 0xE1B28D5E},
        {0xAB80539B, 0xFCA494CB, 0xB2E41F4E, 0xC07A1457, 0xD7F85503, 0x4C174309}},
    {{0x77DD00F9, 0x09AEF548, 0xFF0DEA5B, 0xD74DF166, 0x13E26432, 0x231777B7},
        {0x08BD4BB5, 0x8F95C762, 0x04B85D29, 0x543E067D, 0x1CD608C3, 0x3875DAE1}},
    {{0x0EFE1F6B, 0x34E0D176, 0x371B1B4D, 0x6CE37184, 0xAA65F8D9, 0x20BFA9FA},
        {0xA73D521A, 0xEDBA519D, 0xE3284D58, 0x746F7B33, 0x2143470F, 0x691A594B}},
    {{0x07E1B563, 0x2D36492C, 0x70D6A263, 0x25083938, 0x865E89AC, 0x9838B413},
        {0xCEB52B3C, 0x7E44966A, 0x11626ACF, 0x877B0C41, 0x27C8DC61, 0xAFB47795}}
};

uint32_t g_dsa_hash[10][NUM_ECC_DIGITS] = {
    {0x1D6C1379, 0xDAD42F9B, 0x8BD6A2F0, 0xACD26FBF, 0xC40B6F7C, 0x0462B9CA},
    {0x94EDAF2C, 0x347C7F9B, 0x4FBF8D41, 0x9AF1A2B4, 0x4883C4AC, 0x15E6B84E},
    {0x8AEA8A44, 0x91B53FE0, 0x461713BC, 0xB151F4B7, 0x0211034B, 0x1CD92170},
    {0x895590EB, 0xBD754683, 0xAEE1E187, 0x9B2B57F4, 0x3AC0D433, 0x96ABA630},
    {0xA03CF2A7, 0x8AE3D7E6, 0x36873257, 0x78750301, 0x7A0FD080, 0x86FBC5C8},
    {0x679D91BE, 0x7B846175, 0x2DE64CD4, 0x1901A18A, 0x519752CF, 0x6E28C9F7},
    {0xC803BB9F, 0x96299814, 0x60716A01, 0x06E90392, 0x9C668935, 0x96526018},
    {0x5175B32C, 0x07DE2523, 0xAFAE4505, 0xABA98543, 0x83EDD1FA, 0x837E9D54},
    {0x1960CA88, 0xF4879B3E, 0x403D074A, 0x7A1285B3, 0xEF0D69B8, 0x7111561E},
    {0xA53D68EA, 0x01F24797, 0x34638643, 0x53B91EC2, 0xD92DEF7A, 0xE779C5E3}
};

uint32_t g_dsa_r[10][NUM_ECC_DIGITS] = {
    {0xB2DC9D7D, 0x5C3843F4, 0x3294B09D, 0x64AF06E0, 0x53BF1B00, 0x9B20E041},
    {0x0BF4F758, 0x77135710, 0x7267B744, 0x35BE95C1, 0xD50D3514, 0xD5951D31},
    {0x62988734, 0x5BA7FD18, 0x5F8C653B, 0xADCE852F, 0x2EF10629, 0x428B1E54},
    {0x11AA8309, 0x0565383E, 0xBD70FA44, 0xABFFD3F9, 0x70DC9311, 0x1B9F4F60},
    {0x9129F76D, 0xC60721BB, 0x32AA3511, 0x0E3A7BDF, 0xEFF2DC3C, 0xC61BF26D},
    {0xA701081F, 0xA4E74046, 0x2AFE9D9C, 0xDF4882E2, 0x5E14736F, 0x10CCC340},
    {0x33D4818D, 0x05A8EE0F, 0xE47BC3FB, 0x098C7DE9, 0x9E3049EF, 0xB3ABFEC3},
    {0xFF4D2A1C, 0xC72985B3, 0x9FD30478, 0x33B2F18F, 0x512734E4, 0x8202C268},
    {0x840AE2BD, 0xE1E2B411, 0xFF7C8F81, 0xEDEFC367, 0x42E8D60A, 0x5992F6B0},
    {0xCA211178, 0x149DC446, 0x321126E2, 0x4E326C5D, 0xA1910BE2, 0x8E057701}
};

uint32_t g_dsa_s[10][NUM_ECC_DIGITS] = {
    {0x459523A1, 0x119C77B6, 0x52A062CB, 0xA220571A, 0xC23E9B63, 0x931CAAFE},
    {0x491E1E0E, 0x17E23812, 0x34126B62, 0x4B4EF2A7, 0x030D94BE, 0xD586D8B3},
    {0xC088596E, 0x9FE84270, 0xCE794B6E, 0xD3F7D6DF, 0xD235CE8B, 0x50312465},
    {0xB0208487, 0x9891CECC, 0x17A249F9, 0xADFEBA80, 0xAC66DF48, 0x3DD853C5},
    {0x357ECBA5, 0x92801B5B, 0x98DA57E7, 0xD36CD45A, 0xCC159F90, 0x08154DCA},
    {0xB11CFA8B, 0x47D47046, 0x175EEB76, 0xC2B29A8D, 0xD097A3CB, 0xEFD653BF},
    {0xF988EF59, 0xE2210C4F, 0x8550D2EA, 0x807374B5, 0x35E5AA89, 0x2D7B1A39},
    {0x10C12F34, 0x3725D114, 0x0FC1B44C, 0x3F3170BA, 0x7B1E82AD, 0x331B5FC3},
    {0x2CE9055C, 0xAB799864, 0x0D5F4262, 0x08FD3096, 0xA8A32173, 0xFECF632F},
    {0x9C498FC9, 0x4FF7DCAC, 0xAD9B3A23, 0xAF9F3904, 0x5AD7681C, 0xA1C1C2E4}
};


#elif (ECC_CURVE == secp256r1)

uint32_t g_private[10][NUM_ECC_DIGITS] = {
    {0x9399E0FA, 0xEB887947, 0xFACC412E, 0xC7AFD411, 0x735EE1E8, 0x2B8AFAF4, 0x986E3E7F, 0x742B1953},
    {0x079F480E, 0x41BB4E51, 0x76EEA661, 0xE7B5665D, 0xDF831ED8, 0x2304A3FB, 0x80721097, 0xD06D913A},
    {0x4631C4C3, 0x7C834C62, 0x14208F18, 0x4EE69B3E, 0xFBA45EEE, 0xB3007D73, 0x18BBBA55, 0x3562A76D},
    {0x214CE3AC, 0x22A2D7BD, 0x32366839, 0x686F1754, 0x0560E79B, 0x2EC31C78, 0xFCDC5172, 0xD4E02BAD},
    {0x39F0CACF, 0x3A9526BB, 0xBC5BDAE9, 0x47E36683, 0xEBE1358B, 0xF1C4EA34, 0x547594D5, 0x7FF3B3F9},
    {0x560187FA, 0x37EE44A4, 0x524625E7, 0x923715EE, 0x16C9FB0C, 0x96DC2A1D, 0x8E90B7BD, 0xD22CC9F7},
    {0x2C75DA88, 0x183118DD, 0xDA8B5A44, 0xB752A9B1, 0x20D46DBE, 0xCF2A166C, 0x9140D4F8, 0xDDC8166D},
    {0x55F5771A, 0x7A857A15, 0xCB3613A2, 0x1E20937C, 0xE9A47203, 0x606AAC0A, 0x48366174, 0x9BB9B879},
    {0x6E86355B, 0xE206AAEA, 0xE191D709, 0xE0EA40BD, 0xA8653AF3, 0x49B89A91, 0x67ED6FFE, 0x143EB0FF},
    {0x14A5AC82, 0x34F7EC3E, 0xC70665AA, 0xB387BD6E, 0x639CA247, 0x83CD78A6, 0xD1E26A2C, 0x0C8BFEC3},
};

EccPoint g_public[10] = {
    {{0x3A2AA077, 0x64E128B2, 0x04283263, 0x855DD786, 0x84517CA5, 0x79EEB9C4, 0x4761C4D9, 0x4851C11A},
        {0xE2C8E320, 0x585715E0, 0x0B9C17B9, 0x08C4EC62, 0xB773B9C6, 0x4035ADB7, 0x0D1DD194, 0x2A5BD99F}},
    {{0xC8220251, 0x2BA5B0B7, 0x8A4FBDEC, 0x084E14F3, 0x60A067FC, 0x6DA71E54, 0xF114F6BC, 0x4F8636A6},
        {0xFAAFA6A2, 0xF3A9F005, 0x09635F4F, 0x43281A2B, 0xA3A0685D, 0x1124EDE0, 0xADA827AD, 0x75CCB25D}},
    {{0x30B3A94A, 0x9EE3F351, 0x3AC21A79, 0x0351D486, 0x8042DEE2, 0xBB971022, 0x51D285F7, 0x49694ED3},
        {0x41EE0B17, 0x70A9D359, 0x974BF5F2, 0x576EA6C2, 0xC3214FDF, 0x64B752DB, 0x7650F5E2, 0x5D677E9B}},
    {{0xEFB56CF3, 0xAC23EA6C, 0x1DA12B80, 0x9FF74D0D, 0x03A3663B, 0x7177D352, 0x64B14BEC, 0x3EF56C7E},
        {0x549101E9, 0xF03D5539, 0x27D4A683, 0xB56432D2, 0xA662CC60, 0xCFE89639, 0x30274D96, 0xA7EFB6EC}},
    {{0x5CC7F176, 0xB5D3208A, 0xC2BB2BD4, 0xEFC4CDB4, 0xEC6A0CD6, 0xE733AA5A, 0x815027F2, 0x18332BC7},
        {0x594B7EFA, 0x19349A62, 0x43D57414, 0xC5CF1AB7, 0xA82BA69A, 0x76482590, 0xC621B475, 0xD3F20EC1}},
    {{0x4768CA3E, 0x7676F0E7, 0x700BC293, 0x9BFD80FC, 0x09CB5972, 0xEC9EDF97, 0xFB7E6C7E, 0x3998857C},
        {0xC2B781F7, 0x0AA397AB, 0x8A7329FB, 0xB197B6B0, 0x0755B743, 0x16ACDF44, 0xDFF7ACA6, 0xCE5BA363}},
    {{0xA45922E4, 0xEAB23872, 0xE83BF0ED, 0x6FFCB209, 0xE5117BE2, 0xBB58E09E, 0xD63DF1B0, 0xE607C88B},
        {0xD0E9E95B, 0x0311ECF2, 0x017B3DA1, 0x864D0368, 0x2A52B273, 0xC5058519, 0xA8CB392C, 0xC2CD3E86}},
    {{0x99BD36AC, 0x1D5540EE, 0x9ACCB679, 0xEB1D4D54, 0xC741817D, 0x0F98A403, 0x11B62F1E, 0xF1AE3418},
        {0x22AB665B, 0x617816BF, 0xBDE76F04, 0xA0278809, 0x85B5CC9E, 0x5CF8F0CB, 0xD6409719, 0xFE650C36}},
    {{0x7F782BBE, 0x392C88EC, 0x06D72DF2, 0x4BA960B7, 0x671B67BA, 0xCA87AEBD, 0xCDC0A1D7, 0x1DF26BDA},
        {0x8D93428B, 0x15D1C1D5, 0x08811B1C, 0x84A76187, 0xDA64D286, 0x8E91AC70, 0x7F415FDB, 0x1EFB19C6}},
    {{0x7971B33A, 0x4DBDF01E, 0xEDB8DE50, 0xFFFF7DB5, 0x507960F2, 0xDC75EB7B, 0x8C486A0E, 0x394997BE},
        {0x0DDC16BF, 0xC42D11FB, 0x68BA6066, 0xD25FF9C3, 0xCFAC0568, 0x0409A896, 0x5A644927, 0xC0A34E8C}},
};

EccPoint g_dsa_public[10] = {
    {{0x18D873EA, 0x39AE8F76, 0x0D9DDF14, 0xFDF96E18, 0xD18C8DE2, 0x8135BB79, 0x15566888, 0x891E0DAF},
        {0x777D39B7, 0x98A90AD4, 0x7F216E61, 0x3E0F34E6, 0xF72D42FB, 0x1DEE8A56, 0x10673174, 0x9B611C5E}},
    {{0x75A2BC0F, 0x98885827, 0x3EB9B05E, 0xFC6CBDDB, 0xAB2BBB4E, 0x1EF5B0EF, 0xE352FEE3, 0x31103A4A},
        {0xE9E02511, 0xC6933F71, 0xF91CB770, 0x0BB32241, 0x8A3610A6, 0x5181CCFC, 0x7BF2B528, 0xC65EE328}},
    {{0x8E8FDA96, 0xD4940B61, 0x730FB48C, 0x8414D506, 0xC0FDE5D4, 0x76288DC2, 0x7E6CFD98, 0x74115202},
        {0xEAB8055B, 0xB8A30A36, 0x96A2B0FF, 0x9653526A, 0x51AC810D, 0xA15D5E20, 0x04F62D6E, 0xD0964AEF}},
    {{0xAD5584F7, 0xE5168460, 0x18CB97C5, 0x8CFD31E9, 0x43BC25DD, 0x95E892BB, 0x7D0D700B, 0xC6F56A48},
        {0xB82D1C29, 0x8D7A3CF4, 0x0895D559, 0xEEFC6253, 0xAE76FFB9, 0xD64AF148, 0x702581E6, 0x71F20602}},
    {{0x2BD179B3, 0xEA6394AE, 0xCC36D78C, 0xFA6C4C01, 0xFF80AB88, 0xF7822505, 0xA105C824, 0x264C601F},
        {0xFFA138F2, 0xD6A50FD5, 0x68C8E24E, 0x893BF859, 0xBE85ABE6, 0x1A18A545, 0x402DFC68, 0x97DECCA1}},
    {{0x989D70B9, 0xB9BC0F5A, 0xD254C3DE, 0xCFD676DC, 0x79036C40, 0xAFAE0328, 0x9C6D6FDE, 0x8AFD68EB},
        {0xDE7906E9, 0x5827CB3A, 0xE0ADF5D1, 0x4A15A28B, 0xCF578F38, 0x51BD9D84, 0x169D7BDF, 0xD6CD966C}},
    {{0xCED12835, 0x98FD1157, 0x982B6ABD, 0xC5598F07, 0x9470FA53, 0xAD15E384, 0xF4B2975E, 0x18823BD7},
        {0x4EF0A284, 0xCEBFE692, 0xF3AAE784, 0xDE44E1A6, 0x9D9C4C6B, 0x985B4D15, 0xEF9832E9, 0xC9B158F5}},
    {{0xA513F7BE, 0x228B5956, 0x17B8A7A1, 0x4BD679FA, 0x720039A2, 0xB8CCF1B0, 0xC3F6C90C, 0x59FCE442},
        {0x82C1C024, 0x8FE7418B, 0x262AB509, 0xDCCD9F8C, 0x0FF58433, 0x570A90C9, 0x7F74A949, 0xB14A8D63}},
    {{0x858B58D9, 0x9A050E73, 0x10C81CA4, 0x6D735E00, 0xD139EBCD, 0x0864A8A8, 0x485DFD2F, 0xE26D5883},
        {0x52450736, 0x225DEE93, 0x4650B225, 0x5BDAD103, 0x2E0125AF, 0x38E99BAF, 0x71564A8A, 0x2B50F076}},
    {{0x086EC167, 0x59A6A4FA, 0xB89841C8, 0x0155D1FF, 0xC99C16B3, 0xB540D0C4, 0x5E8667BA, 0xF2A38BE0},
        {0xC2DB84F9, 0xC3901B10, 0x384CCD24, 0x4F567D3A, 0x05EB2115, 0x81543E6E, 0x27327C2F, 0x2AA9F064}}
};

uint32_t g_dsa_hash[10][NUM_ECC_DIGITS] = {
    {0xE6728E95, 0xD3651B3C, 0xF6F7AC25, 0x75BAAF50, 0x47225E32, 0x107CB058, 0x5AC1BB66, 0xED8946C5},
    {0xC90D7661, 0x26F96DB3, 0xDD46904B, 0x9D034D54, 0x17837A40, 0x8CC03EB1, 0xA77AB5C7, 0x7D98F3F7},
    {0x045F5866, 0x4B889E18, 0x5C3F3A60, 0xE51B7A46, 0x8211110A, 0xB0A391D3, 0xF093DD69, 0x8B89ABAB},
    {0xD14CF5FB, 0x1908D2A1, 0x46AF8825, 0x3C328E6B, 0xEFAC82B1, 0x0C8EFC5B, 0xFF4B7A96, 0xF79CAD6C},
    {0xE1A0377D, 0xF7CC552F, 0xF1A77C9B, 0x970F2B2B, 0x8C0C941D, 0x4416C2E5, 0x43289FAE, 0x195709CE},
    {0x9BB76089, 0x58927F12, 0x6D34DE46, 0x049DA7D8, 0x7FD185B1, 0xE1623BF1, 0x4D6F114F, 0xBB46C8B1},
    {0x17C46C3D, 0xC8A78387, 0x5511FEFA, 0x663A06BB, 0x804D9C13, 0x8A7B4852, 0x0C216330, 0x47BC2C0D},
    {0x7BEE0A02, 0xB1EA6297, 0x1F833451, 0x38C46969, 0x8E1B57FA, 0x619E8010, 0x97E7CA3A, 0x852EFAC6},
    {0xCCB0A0BE, 0x002DD2B8, 0x5EC1E0C8, 0x902ADB5D, 0xEE61B6C2, 0xDC338B4D, 0x8971169B, 0xA025468F},
    {0xC25040D7, 0xEFA05D26, 0x06FD4164, 0x01685417, 0x65B26C18, 0xE507C63C, 0x78151835, 0xF21A1C81}
};

uint32_t g_dsa_r[10][NUM_ECC_DIGITS] = {
    {0x752CEDD6, 0x3ACF03F5, 0x7047C8DC, 0x666BB1F6, 0x5EF004A3, 0x43563063, 0xB0EC477F, 0x10D6DCFF},
    {0xB4E00247, 0xDA76FBD7, 0x0BBE6FE6, 0xA8AD335C, 0x3F310230, 0xE33435ED, 0x6E63988B, 0xAB21C237},
    {0x9D5D47B0, 0xF88F8750, 0x777F81FB, 0xDA43CF7E, 0x03C7747D, 0xD71F4EAE, 0xEB29DF0F, 0xA0463A84},
    {0x47B2CAB8, 0x1A63B65E, 0x9E51C28E, 0x2B498C62, 0x6393F35B, 0x7F8C0E6A, 0x54EF3E42, 0x00285CCE},
    {0x68B00F6A, 0x2D427150, 0x94A8EB56, 0xBF3889AE, 0x4F881BBD, 0x7FE09B9B, 0x5DF92E49, 0x691F937D},
    {0x24FDEA59, 0x11DD1413, 0x140FBE19, 0xAB93E6A8, 0x1CA4E023, 0x3FE40149, 0x66829974, 0x9B3DE3AC},
    {0x307C6772, 0xA23E25C8, 0xCA804A84, 0xBC79112D, 0xA9B93122, 0xBDC343D8, 0x7DD7AA62, 0xE9D627A0},
    {0xE2B9C6E2, 0x3E2968B9, 0xE521C4C6, 0x560D0118, 0x0108A120, 0x85D5A3F9, 0xA493E4DF, 0x8E343389},
    {0x6195BCCC, 0x5B8BFD58, 0x36AFEB2B, 0xD436795A, 0xBD5C703A, 0x632B17EF, 0x0C7CAB66, 0xD37543BC},
    {0xD366ED64, 0x52D4262B, 0xD5257578, 0x64148E33, 0xFE70C3A2, 0x918D6343, 0x7373D477, 0xEBB23764}
};

uint32_t g_dsa_s[10][NUM_ECC_DIGITS] = {
    {0x8689DA3C, 0x1AA06D96, 0x3BEF8370, 0x2AD62D8F, 0x496E16D6, 0xBF7DF354, 0xBD32DBD4, 0xD86CBAD6},
    {0x185F288B, 0x9576CB4D, 0xFE3B3177, 0xB5268219, 0x25D85B59, 0xA514D68B, 0x52A1B30F, 0xBCBE9ED0},
    {0x17FB6595, 0x8AEF955A, 0x17A6AFED, 0x7E875B5C, 0x6F87DF65, 0xB7C3180D, 0xBCA28436, 0x918D3C39},
    {0xEACB0CF3, 0x2704FA24, 0xB5C7188F, 0xBA98BE5E, 0x203568F4, 0xC0BA9C8F, 0xF9C2BC33, 0xF91ECE84},
    {0x33E76D6B, 0x3CA6435B, 0x3A7DF607, 0x8D2FD7A9, 0x82D90875, 0x5B878C00, 0xE4B1A979, 0x2B091507},
    {0x5BE25154, 0xB40EEEA1, 0x600EA30C, 0xC9B60488, 0x334A7F03, 0x357F9AE5, 0xD56BB833, 0x97229A95},
    {0xC06289E2, 0xD2E5DC74, 0x22510AD6, 0x8C8B2F7A, 0x22042D5D, 0x22380F73, 0x89F906E7, 0x81BAF5F4},
    {0x3CB28206, 0x6D5D9C9F, 0x1CDE19FC, 0x19127450, 0x495A1B0C, 0xFB477AE1, 0xA06B2169, 0x1CCB184D},
    {0xCA5A1EC4, 0x4FBF6CCD, 0x24CCAE61, 0x75C49C41, 0xCFA28FB5, 0xBA5D70BB, 0xB0D80AD5, 0x2A8E7A28},
    {0xAFC08C0C, 0x949EF819, 0xB80751E5, 0x9E77D36C, 0x2338ADBF, 0xD3F84E20, 0x10E30B97, 0x617F0EF3}
};

#elif (ECC_CURVE == secp384r1)

uint32_t g_private[10][NUM_ECC_DIGITS] = {
    {0x32D5EFC6, 0x0A6E70F1, 0x6CAE9125, 0x78D74ECF, 0x33E423FB, 0x2B9F9991, 0x188E04C0, 0x6FEA1C8E, 0x2B2634A3, 0xDC5C521A, 0xDBF7265D, 0xB2975791},
    {0xE3C04C90, 0x14F9D46B, 0x67B1B5B9, 0xB1634716, 0xF22C2A3C, 0xF6E316E5, 0x83AD27DB, 0x7E2C5F0A, 0x7D963221, 0xB5949669, 0x24D3CF9B, 0xECFB5D62},
    {0xAE2CD960, 0x967D0340, 0x63D9DBB7, 0x1ACC2775, 0xF4384742, 0x1E80A08C, 0xAC147E25, 0x816980AB, 0x4E328750, 0x74DFC446, 0xF97F88D8, 0xB7F41F61},
    {0xB2ACC82C, 0x990423A0, 0x406FC4B5, 0x85D15EAF, 0x8427A963, 0x4DE0B726, 0x2760A931, 0x61704F08, 0x11FAA49E, 0x49FD9040, 0x0DE599AA, 0x3B8C6DD4},
    {0xC3F1029C, 0x98C70907, 0x42EB53D5, 0xD2A9ABB2, 0x7A84563F, 0xEA2199E4, 0x13363CFF, 0x91799CFE, 0x9040433D, 0xF968D8E8, 0x3B141F14, 0x49520031},
    {0xD0E2F25D, 0xC4C607DF, 0x49B309E6, 0xB502AF9B, 0x23D6DC13, 0xF85D7B34, 0xE522128E, 0x16556518, 0xA0A0A79A, 0xF3AC2452, 0x9C2752E4, 0xAF1960ED},
    {0xF0CDF38E, 0xB9727287, 0x928ACBD6, 0xDEAB02FC, 0xE2F71DD7, 0x47BCCC87, 0xED069FC8, 0xF5CA23B2, 0xE5D4CCD8, 0xE20F292B, 0x9F5B74CF, 0xFDF078AA},
    {0xD8AB652E, 0x6132B605, 0x319463B6, 0xB197883C, 0x1ACE17F8, 0x691B656C, 0x9B3DD592, 0x61CDCAF6, 0x1DCEBCC3, 0xB86BC43A, 0x440DCDA7, 0x59EC5A22},
    {0x97401DB7, 0x470838F2, 0xA19A58D3, 0xF076BF50, 0xDFF21694, 0x1B8F8455, 0x653549B0, 0x1CCE5CFD, 0x66F90BBA, 0x09BF73AA, 0x1D01275D, 0xCEEB698B},
    {0xB86CA4E0, 0x64F504D2, 0x5E2B318E, 0x7AD31C33, 0x3F293C53, 0xA0346206, 0x2ACA2DD4, 0x5BC53F6B, 0x3BB83FC2, 0xFC7DD83D, 0xC9CDD04A, 0x15DF8AD8},
};

EccPoint g_public[10] = {
    {{0x65E712A5, 0xEDE6358A, 0xD8832C43, 0xE219F022, 0x38407198, 0xC5B58725, 0x14422FF2, 0x7D30DD2E, 0xCF59C6A9, 0x63B30AEF, 0x0EEBE494, 0x1E47A816},
        {0x1E1CF55A, 0xDCC29967, 0xE59976B8, 0x5B6BDB4E, 0x52FF2D3F, 0x9C479240, 0xD14CA6B6, 0x2347BBFC, 0x7699F6E7, 0x0982F63D, 0xCE4805FC, 0x7D812D30}},
    {{0xBA5F2023, 0x88C842A6, 0x46DFEA58, 0xD87B5F24, 0xCE9BE9A1, 0xBBCB9F4F, 0xD94DBDDB, 0x2B2C5EB7, 0x0F6DF89F, 0xDB7D9CA6, 0x1F23435E, 0x18F86C99},
        {0x70A0F5FF, 0xCDD27DE3, 0x555BC9CB, 0xC027FA5A, 0xD2A0AD9C, 0x2F946827, 0xABEE1613, 0x7E4167D7, 0x95ABCBDF, 0x70225A99, 0x47DD210C, 0xA318330B}},
    {{0xECE05D2E, 0xE10D26A4, 0x31D57E74, 0xC04A3DF0, 0x1D9997CB, 0xC39E66E2, 0x373C2023, 0xDE8D8A89, 0xF67A7B7E, 0x41EBCFC6, 0x2035863C, 0xF4623DF8},
        {0x36F925D1, 0xFCBDFBBE, 0x3FDF04A9, 0x3B57A2E2, 0xC46B87D7, 0x4156817F, 0x2C1A064B, 0x7DB38358, 0x70CD9B69, 0x75A434A2, 0x9F4A48C4, 0x4AD69C23}},
    {{0x07172FA0, 0xE6130A08, 0x4F388AC1, 0xD7F343C2, 0xF888C384, 0x287DE4E5, 0x9A30CF33, 0x73CDAC5C, 0x5F1136D8, 0x245ED4EE, 0x9C1211CD, 0x3D4C9433},
        {0x9626B202, 0x84AAB332, 0xD2D6DFFB, 0x705510EA, 0x224D6D99, 0xD9BBA972, 0x16BF0492, 0x47E3A9FF, 0x6B5A0C25, 0xEDA495EE, 0x8C16DE01, 0x7D855F54}},
    {{0xB955B50C, 0xA8A666A1, 0xEFA243B2, 0xB3EA4A8B, 0x55029497, 0x174ED0E1, 0x583C111E, 0xA2DA83DB, 0x450FE418, 0x9B0A438C, 0x160B0777, 0x2E9EC7C1},
        {0x52B12CA1, 0xF48B11CB, 0x10C4A002, 0x63CC9513, 0x7F145B27, 0xEF4BB6D0, 0xEF0477AD, 0x88DBB594, 0xD1430AA9, 0x10D02A03, 0x25FA025E, 0x601E15BB}},
    {{0x443646B3, 0xBA5E3E80, 0x108CF73F, 0x21227E4F, 0xE48FEF5C, 0xD6C22515, 0x55E92109, 0x0D022DF9, 0xB74714CA, 0xE80E561A, 0x9B20FBFD, 0x4DF69459},
        {0x81B6F66C, 0x2E9AD77E, 0x0F54976E, 0x78F0DC08, 0xCE768D94, 0xCC5C3910, 0x7CBBC93F, 0x0AF83DAC, 0xEBB0496B, 0x2D6F03D5, 0x13902055, 0xF51C25C4}},
    {{0xDE7FDB51, 0x6B9D9317, 0x2A2225C6, 0x1FAE273F, 0x9334773D, 0x71A61FB6, 0x8A78A53C, 0x89CD7DFC, 0xA8875AA4, 0xFBC76918, 0xCE9695F9, 0x526FF9D9},
        {0xB050A016, 0x09C0892B, 0xF89C8CAF, 0xE8E68D1A, 0xB67E643A, 0x4BD8FB6A, 0x03509AD1, 0xB7BF46CC, 0xB424C7EB, 0xF403CBC5, 0x83E1DF62, 0xAB86ADAD}},
    {{0x9280483C, 0x48DD933A, 0xEE4B9C96, 0x53EBC024, 0x12A66088, 0xF729E0D4, 0x43683F06, 0xB9243898, 0x22BBEF28, 0xF39CB448, 0x31072201, 0xACBAA281},
        {0xD2B604C9, 0xD98609C9, 0xB7DD4293, 0x5E64B4EA, 0xAC10FD00, 0x866F7BB7, 0x69172525, 0xCBA07D25, 0x0EB49A2D, 0xB581A1E5, 0xF6B9D1A3, 0xBD43603F}},
    {{0xCD2402D5, 0x422FF4F7, 0x47A2F23F, 0x77D3EE67, 0xB70510A4, 0x9AFFB807, 0xECE5E4DF, 0x7434FA59, 0x6F977E5D, 0x10075CD2, 0x58168CE5, 0x3D75FBFC},
        {0x905C6782, 0x22E0C173, 0xD17373CC, 0x4533FDF7, 0x6CC69390, 0xE45DEC16, 0xC754216E, 0x5553E1EA, 0x4B738B24, 0xF1D413E0, 0xC3A51813, 0xCD2E01D6}},
    {{0xE3C42EC6, 0x7838FDAA, 0x2603AE8D, 0x764E0E5B, 0x98FCBBF9, 0xC32B0EB8, 0x1BA3CFAD, 0x5C92A4C2, 0x868B2A51, 0x9BB53424, 0x0F1EA014, 0x532ADAF7},
        {0x577A106E, 0xC7AB93CD, 0x0E7A178A, 0x4B0A2242, 0xE3BAF83D, 0xEF4007E5, 0x24EF7AAF, 0x28B60061, 0xB7651BAA, 0xA8828076, 0x19A7406E, 0xAF38A8A1}},
};

EccPoint g_dsa_public[10] = {
    {{0xD3E332D6, 0x249BC077, 0x5CC755C3, 0x5714B8F4, 0xBA7E8953, 0x97290E56, 0x3BFF7465, 0x0B981E65, 0x71112CF6, 0x62DA4A20, 0x1DE6428E, 0x73473E2B},
        {0xDF4CBE72, 0x8B6D03F3, 0x449085DD, 0x76EF3C92, 0xF36EFCF8, 0x36D3BB2C, 0x660A2C2C, 0x61F0B283, 0x036BB8A4, 0x5BEF3386, 0xA02F73A0, 0xB971631A}},
    {{0xBD6E7E57, 0xC66B19FA, 0x33B3D43B, 0x1FE2B670, 0x01DC9E93, 0x0EBCA2F4, 0xC784EBC7, 0x5C1017AC, 0xB3E22FCE, 0x858DC71D, 0x04107B20, 0xD9382A43},
        {0xA24499FB, 0xCF6E973B, 0x7213CA47, 0x26F94F9F, 0x33C98928, 0x2669C8A4, 0x98A5F156, 0x722E9762, 0x90F895A0, 0x07C91FA6, 0x6C10228A, 0x6E5962FA}},
    {{0x98B83820, 0x581A5DC9, 0x96E67A9D, 0xAE3C0A49, 0x00F20767, 0x1D4A5A00, 0xEC9E121B, 0xFBF82B11, 0xAA294108, 0x7EDD30D4, 0xE7E205A6, 0x46728FD4},
        {0x710DCCFE, 0x0967BEC8, 0x232B4CBA, 0x3C923D5D, 0xA7803894, 0xCB2CE7B4, 0xBAB4E953, 0xFA0AEC5C, 0x4E0B974E, 0x528C95A9, 0x93CB093A, 0x25A69559}},
    {{0x8C298594, 0x86DCBD37, 0x90901637, 0xD1B5BF43, 0x9CE73447, 0x9E7F53FA, 0xD555BC6D, 0xC23D2FDE, 0x2168A205, 0xE588FBB5, 0xD28D8173, 0x6A18E61D},
        {0x48150D1D, 0xDB0BA409, 0xD231EA18, 0xFD066737, 0x9F9D9550, 0x1D0B0D54, 0xB5DBEA82, 0xA10DC099, 0xA544E10C, 0x7F8EED96, 0xA0FBAE6F, 0xCF0AEAFA}},
    {{0xF796D9C5, 0x676FF98A, 0x794B1693, 0xE58B9181, 0x21002760, 0x37FC8101, 0x3AD7D6CD, 0x59B2719E, 0xB752C203, 0x15A9EF4F, 0x6E74B535, 0x30C0272F},
        {0xA527EBA2, 0xFB4906B4, 0xF5A845CB, 0xD577692F, 0xDAEA139C, 0xE0EB23FA, 0xD41F46F1, 0xA8B81F21, 0x6AF0D9D7, 0x87DFE401, 0x8D4EB99A, 0xA797FB32}},
    {{0xF28F1939, 0x390B87A7, 0xDF8391F6, 0x02F5F9CE, 0xA5701A81, 0x11733E37, 0xA6CF238C, 0x641599F3, 0xE9004778, 0x944548CE, 0x994D666E, 0x1F7726B8},
        {0x9F1A4BA5, 0x9985A635, 0x77349744, 0x4C9CF84F, 0xF1C4B6C6, 0x95B1CEC8, 0xA01F1C30, 0xF6DAFDE3, 0xE02FB7B9, 0x549ACB11, 0x52AB9288, 0x485BD2B3}},
    {{0xA4EE4886, 0x02DA346B, 0x9D58309C, 0xAC1E23A8, 0x9F472A1B, 0x2D6F238C, 0x75F2AC35, 0x746A689A, 0x919F3BBE, 0x6E915DD8, 0x8E69BFB9, 0xA2330A06},
        {0x4A7206D6, 0x635611FD, 0x081C57B0, 0xD029A092, 0x9C861819, 0xFA113644, 0xCAC2C818, 0x8EBA15E4, 0x98C40CE4, 0x8165AFB7, 0x4289F7A1, 0x0B0BC00E}},
    {{0x59499ABC, 0x4C4B3D84, 0xCFFDE2BB, 0x9A27FC9F, 0xD78EF2A4, 0xFA72A4C6, 0xA5DC64A9, 0x3CEE8356, 0x2FBA35CA, 0x5102CD08, 0xFA02E5FA, 0x29677349},
        {0xA47BB38B, 0x3AE49D7F, 0xA18710D8, 0x5F693329, 0x01DC684D, 0xA33610C6, 0xD793A15C, 0x706240E2, 0x38430722, 0xCD0E8AB0, 0x6BB63B9C, 0x7DA17853}},
    {{0xA9445022, 0xFB15F156, 0xB34825A6, 0x25BACE3B, 0x23AA8A17, 0x7C8C8EF0, 0xEA1B80B7, 0xB12938CB, 0x72C48D94, 0x0DBFE460, 0xF8F22405, 0x99EF1308},
        {0xBAB95A43, 0xED9F7D5C, 0xE74CA167, 0xC11C03C3, 0x8B1C8A9A, 0xDC57E167, 0x77C237D1, 0x57148113, 0x77662710, 0x6FEB3110, 0x793FCCD7, 0x97CAF133}},
    {{0xB4ACB0CD, 0xA3E6D45F, 0x96B9BFD6, 0x4AA18709, 0xAAABB349, 0x647F5A48, 0x15501AFB, 0xB4F8A65F, 0xF159AFD6, 0x25049E5E, 0xAE5BBFE0, 0x96940F8E},
        {0xEC5DB2D0, 0x46484E71, 0x165E1430, 0x73F67EDF, 0x6D2AEE73, 0x8569DDAD, 0x76FF3CF2, 0x6A689B9B, 0x75D1D488, 0x8B587217, 0xD9B66858, 0x54258587}}
};

uint32_t g_dsa_hash[10][NUM_ECC_DIGITS] = {
    {0x8EBD48C2, 0x4AE57927, 0x10A7AED7, 0x7DCB1F1D, 0x20953C48, 0x9D6762FF, 0x452DC8D6, 0xB9F93326, 0xEBB72C61, 0xC0034A87, 0x9D3642DF, 0x274A5C6E},
    {0xED73018B, 0x1658F842, 0x2099D3EE, 0x6896C47E, 0x67FA1296, 0x5C6B9EB2, 0x3BCCDBC8, 0xF09C92B0, 0x8801852A, 0x3BE1F99D, 0xAF65FAB0, 0x13B6BD40},
    {0xD1149608, 0xF41D6D9D, 0xB72403C6, 0x357A8FE7, 0x3F903381, 0xFEE74F7D, 0x2568B1C2, 0xC549A3AC, 0x109BCB14, 0x0E76F529, 0x37504740, 0x60BD6DF0},
    {0x7D0EFBA7, 0x150EA6A3, 0xF6E62E78, 0x942F865C, 0x31E01B91, 0x7D143B36, 0x62760D9A, 0x70FEC370, 0x569FEEF9, 0x42FC0C7A, 0x8624F694, 0x99F8B104},
    {0x4B690BBA, 0x72E1E9B2, 0x7ED8FCD8, 0x72751DF7, 0xF906A1D7, 0xE6B1C6A8, 0xDCAE9E22, 0x9B206351, 0x44263C5D, 0x698E29A8, 0x09E5ECA3, 0xCC868050},
    {0x2A95C1C6, 0x40360467, 0x84FBFD3A, 0x02A7A88A, 0xB67BD9A7, 0x8F08763B, 0xA0F6E62C, 0x3D8FECB0, 0x87589B7A, 0xB379F745, 0x265EA359, 0x7E51F51E},
    {0xF5D87CC8, 0x8C6D3159, 0x5CAC6D42, 0xAAE00C8A, 0x71A9B06B, 0xB6E992A0, 0xCA7BC049, 0x5D027928, 0xE32960E1, 0x6D1DA473, 0xF989FC99, 0x001125A6},
    {0x0E9A59C1, 0x73667DD9, 0x38B91627, 0x5944E309, 0xC390D21C, 0xB7509C44, 0x772DFD29, 0x5894EC25, 0xAAA303EC, 0xA188B876, 0xE66A1B1A, 0x3AA4D54C},
    {0x30DD559B, 0x7EAAEDCA, 0x987A72BE, 0x294C98B6, 0xB5C4DB7D, 0x6E638132, 0x753DC9B6, 0x86EA89BA, 0x9AB70A04, 0x00E9796F, 0xA56C97F5, 0x83F51149},
    {0xBC39D992, 0x8BFE66FA, 0x36F4F688, 0x167129D1, 0x2D23177C, 0xA0E8F937, 0x43F718C8, 0xDDEC9037, 0x2E7A36D2, 0xA77FA995, 0xE8717D8D, 0x11A91DFD}
};

uint32_t g_dsa_r[10][NUM_ECC_DIGITS] = {
    {0xC026C2A5, 0xEDE697E4, 0x32C917D1, 0x7C5E5712, 0xCC5E08A5, 0x02055E5A, 0xD445BFF3, 0xB766A9A6, 0x0470A3EB, 0x7F2C4DD6, 0xE939CF6C, 0xB2D0B984},
    {0xDF066CB1, 0x53CFD07D, 0x784B473F, 0x91F8D082, 0x7555AFDC, 0x4E9B2D44, 0x53EBC293, 0xAB5F20F8, 0xD5DBBD43, 0xCE38EF93, 0x9C3E02CD, 0xBD4B054A},
    {0x4BD6EFA0, 0x5F6837AC, 0xDA378B30, 0x8BE2015E, 0xA4E38575, 0x9757B18F, 0x8128FA93, 0x58DDC246, 0x14DC7C50, 0xEE78BA84, 0x5DF2987E, 0xB3E59779},
    {0xBBF99F45, 0xCAA25920, 0xBFC3D5C5, 0x8B84E558, 0x7E815ABE, 0x02CEA18A, 0x2B13BC25, 0x5452BFDD, 0xDBD717C9, 0x0EF61393, 0x25AA51FA, 0x4A6C36B7},
    {0xAD6ACE59, 0xB15D6911, 0x40477030, 0x919C542F, 0xACB43FFB, 0x1D410C28, 0x369ECBCB, 0x8D4D4459, 0xEBA14D13, 0x02563F3B, 0x33B58A1B, 0xC559D457},
    {0x18B568E7, 0x45450917, 0xCAF4509D, 0x624D8FEB, 0x35DE782D, 0x503FD2F2, 0xD21D270B, 0x071E7ACB, 0x986E277B, 0x3EBE5C2E, 0x59CB49AB, 0xA898B4D8},
    {0xF59DE399, 0x88B2B5D3, 0x66DE64AB, 0x2FC4B1F1, 0xAAF8A2A1, 0x77D97A3C, 0x739C6ACA, 0x249DBC99, 0x1B1DE447, 0x9F36C9E5, 0xA6BEA84D, 0xBC24A822},
    {0x882BE6B7, 0x22FE63DD, 0xA55884D5, 0x93B040AE, 0xA660F93F, 0x011C187C, 0x09EFD7A8, 0x50CC8062, 0xB2502F8E, 0x149A4E6F, 0xD573B1D7, 0x0E281B44},
    {0x51E23E6F, 0x1ACACF54, 0x4AA16CA7, 0x2698EEB0, 0xAAB8011B, 0x7A91FE9C, 0xE9C10D66, 0xC8D2E920, 0x6572CBE6, 0x4CE3D7E3, 0x2DADEFCA, 0xA6CBF357},
    {0x6E1BA624, 0xEE319BA9, 0x23E55296, 0x9136FB3D, 0x6ADCB514, 0x765FCC58, 0xA07E4612, 0xA985A564, 0x012FD81A, 0xAD094F72, 0x3C1832F6, 0x4CE2096F}
    
};

uint32_t g_dsa_s[10][NUM_ECC_DIGITS] = {
    {0xD00CBA5E, 0x591A9330, 0x765422ED, 0x823C6714, 0x2499AC43, 0x9E1DF897, 0xE9E91EAD, 0xCA709622, 0xECFEE776, 0xCD83AC59, 0xB04487E2, 0x086749F5},
    {0xD72CB12C, 0xDD75FCF1, 0x702A8481, 0x5394D6F8, 0x93524A7F, 0x7D8BA760, 0x98BC3A01, 0x071F4E07, 0xCED4C4F3, 0x999A91AE, 0x4748B3AA, 0x05740D77},
    {0x19AC533E, 0x2CB86358, 0x1293DA0B, 0x37BD79D6, 0xB9CE58F4, 0x6093CAB8, 0x9E2A96BA, 0xF9339815, 0x1C18117D, 0x895EACF9, 0xF1F78304, 0x3D52CCF6},
    {0xB6D4385A, 0x3F8143B0, 0x61B54B1E, 0x3EE8A6E1, 0x918D1608, 0xE27D18AE, 0x9D2BB489, 0x28692E2D, 0x294ADBCF, 0xB1A1FEF6, 0xB992E240, 0x108C2E02},
    {0x267E8A43, 0x2701D68C, 0xD5C8C949, 0x572C8A36, 0x87F85B18, 0x0A2A1E6E, 0x25627357, 0xAB738EB7, 0x8ED7C835, 0x5E013069, 0x281B3568, 0x238F8304},
    {0x2EA963E5, 0x01A2A985, 0x2066A5FC, 0x6BF120D5, 0x3D18EEEE, 0x5AAF3865, 0xF6A0C084, 0xDEC73F42, 0x1365C42B, 0x9F173115, 0xE4C243C3, 0x5966782D},
    {0x8E605B5D, 0x6745F7C4, 0x632FEBF0, 0xD77637A7, 0x9B8664B7, 0xB2BE7CC0, 0xF145537F, 0xC070A49C, 0x9888D86C, 0x551D2E4B, 0x88BE3CE2, 0x85EAA64D},
    {0x9EDB17EB, 0xCE352939, 0xE7693C1A, 0xC5828FAA, 0x9ABC94FE, 0x645421AF, 0x0EC1CACB, 0x0A9594AC, 0xA5BEA008, 0x05B637DA, 0x1138AB32, 0x37D5C00B},
    {0x85348E58, 0x13F9D8B4, 0xA4689940, 0xAA6594C6, 0xBBF82A70, 0x154090CB, 0xFA33B2B7, 0xF75D1D82, 0x2F5EB370, 0x95F8CBED, 0xB54DAFFC, 0x44E01249},
    {0x01977D39, 0x691F5683, 0xCB0B32CC, 0x1A199DEB, 0x929A049F, 0xADDB297E, 0xC3F34E59, 0xA7276C0D, 0x18EA86EB, 0x2BCB655A, 0x104B963A, 0xE650D5A0}
};

#endif

int main()
{
    uartInit(BAUD_115200);
	initTime();
	
    uint32_t l_shared[NUM_ECC_DIGITS];
    uint64_t l_total = 0;
    
    unsigned i;
    for(i=0; i<10; ++i)
    {
        uint64_t l_start = getTimeMs();
        ecdh_shared_secret(l_shared, &g_public[i], g_private[i]);
        uint64_t l_diff = getTimeMs() - l_start;
        vli_print(l_shared);
        printf("\n");
        printf("Time = %llu\n", l_diff);
        l_total += l_diff;
    }
    
    printf("Total ECDH time: %llu\n", l_total);
    
    l_total = 0;
    for(i=0; i<10; ++i)
    {
        uint64_t l_start = getTimeMs();
        if(!ecdsa_verify(&g_dsa_public[i], g_dsa_hash[i], g_dsa_r[i], g_dsa_s[i]))
        {
            printf("ecdsa_verify() failed\n");
        }
        uint64_t l_diff = getTimeMs() - l_start;
        printf("Time = %llu\n", l_diff);
        l_total += l_diff;
    }
    
    printf("Total ECDSA time: %llu\n", l_total);
	
	return 0;
}
