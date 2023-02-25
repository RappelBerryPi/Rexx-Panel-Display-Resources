#include <stdio.h>
#include <gskssl.h>

#include <string>
#include <map>
/* compile with xlc -o get_ciphers get_ciphers.cpp /usr/lpp/gskssl/lib/GSKSSL.x */

std::map<std::string, std::string> setupCipherMap();

int main() {
    gsk_all_cipher_suites allCiphers;
    allCiphers.size = sizeof(gsk_all_cipher_suites);
    int rcget = gsk_get_all_cipher_suites(&allCiphers);
    std::map<std::string, std::string> cipherMap = setupCipherMap();

    if (rcget == 0) {
        printf("Version:        %d\n", allCiphers.version);
        printf("Release:        %d\n", allCiphers.release);
        printf("Security Level: %d\n", (int)allCiphers.security_level);
        printf("v2 cipher string: %s\n", allCiphers.v2_cipher_suites);
        printf("v3 ciphers:     %s\n", allCiphers.v3_cipher_suites);
        printf("v3 ciphers expanded: %s\n", allCiphers.v3_cipher_suites_expanded);

        std::string v2_suites(allCiphers.v2_cipher_suites);

        printf("v2 ciphers:\n");
        for (int i = 0; i < v2_suites.size(); i++) {
            std::string ch(1, v2_suites[i]);
            printf("\t%c: %s\n",v2_suites[i], cipherMap[ch].c_str());
        }

        std::string v3_suites(allCiphers.v3_cipher_suites);

        printf("v3 ciphers:\n");
        for (int i = 0; i < v3_suites.size(); i+=2) {
            std::string ch = v3_suites.substr(i,2);
            printf("\t%s: %s\n",ch.c_str(), cipherMap[ch].c_str());
        }

        std::string v3_suites_exp(allCiphers.v3_cipher_suites_expanded);

        printf("v3 ciphers expanded:\n");
        for (int i = 0; i < v3_suites_exp.size(); i+=4) {
            std::string ch = v3_suites_exp.substr(i,4);
            printf("\t%s: %s\n",ch.c_str(), cipherMap[ch].c_str());
        }
        printf("See https://www.ibm.com/docs/en/zos/2.5.0?topic=programming-cipher-suite-definitions for the updated definitions of cipher suite definition codes.");
        printf("\n");

    }
    return 0;
}

std::map<std::string, std::string> setupCipherMap() {
    std::map<std::string, std::string> returnMap;
    returnMap["1"]    = "128-bit RC4 - MD5 Message Auth (128-bit key)";
    returnMap["2"]    = "128-bit RC4 - MD5 Message Auth (40-bit key)";
    returnMap["3"]    = "128-bit RC2 - MD5 Message Auth (128-bit key)";
    returnMap["4"]    = "128-bit RC2 - MD5 Message Auth (40-bit key)";
    returnMap["6"]    = "56-bit  DES - MD5 Message Auth (56-bit key)";
    returnMap["7"]    = "168-bit Triple DES - MD5 Message Auth (168-bit key)";
    returnMap["00"]   = "TLS_NULL_WITH_NULL_NULL";
    returnMap["01"]   = "TLS_RSA_WITH_NULL_MD5";
    returnMap["02"]   = "TLS_RSA_WITH_NULL_SHA";
    returnMap["03"]   = "TLS_RSA_EXPORT_WITH_RC4_40_MD5";
    returnMap["04"]   = "TLS_RSA_WITH_RC4_128_MD5";
    returnMap["05"]   = "TLS_RSA_WITH_RC4_128_SHA";
    returnMap["06"]   = "TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5";
    returnMap["09"]   = "TLS_RSA_WITH_DES_CBC_SHA";
    returnMap["0A"]   = "TLS_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["0C"]   = "TLS_DH_DSS_WITH_DES_CBC_SHA";
    returnMap["0D"]   = "TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA";
    returnMap["0F"]   = "TLS_DH_RSA_WITH_DES_CBC_SHA";
    returnMap["10"]   = "TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["12"]   = "TLS_DHE_DSS_WITH_DES_CBC_SHA";
    returnMap["13"]   = "TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA";
    returnMap["15"]   = "TLS_DHE_RSA_WITH_DES_CBC_SHA";
    returnMap["16"]   = "TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["2F"]   = "TLS_RSA_WITH_AES_128_CBC_SHA";
    returnMap["30"]   = "TLS_DH_DSS_WITH_AES_128_CBC_SHA";
    returnMap["31"]   = "TLS_DH_RSA_WITH_AES_128_CBC_SHA";
    returnMap["32"]   = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA";
    returnMap["33"]   = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA";
    returnMap["35"]   = "TLS_RSA_WITH_AES_256_CBC_SHA";
    returnMap["36"]   = "TLS_DH_DSS_WITH_AES_256_CBC_SHA";
    returnMap["37"]   = "TLS_DH_RSA_WITH_AES_256_CBC_SHA";
    returnMap["38"]   = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA";
    returnMap["39"]   = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA";
    returnMap["3B"]   = "TLS_RSA_WITH_NULL_SHA256";
    returnMap["3C"]   = "TLS_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["3D"]   = "TLS_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["3E"]   = "TLS_DH_DSS_WITH_AES_128_CBC_SHA256";
    returnMap["3F"]   = "TLS_DH_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["40"]   = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA256";
    returnMap["67"]   = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["68"]   = "TLS_DH_DSS_WITH_AES_256_CBC_SHA256";
    returnMap["69"]   = "TLS_DH_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["6A"]   = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA256";
    returnMap["6B"]   = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["9C"]   = "TLS_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["9D"]   = "TLS_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["9E"]   = "TLS_DHE_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["9F"]   = "TLS_DHE_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["A0"]   = "TLS_DH_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["A1"]   = "TLS_DH_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["A2"]   = "TLS_DHE_DSS_WITH_AES_128_GCM_SHA256";
    returnMap["A3"]   = "TLS_DHE_DSS_WITH_AES_256_GCM_SHA384";
    returnMap["A4"]   = "TLS_DH_DSS_WITH_AES_128_GCM_SHA256";
    returnMap["A5"]   = "TLS_DH_DSS_WITH_AES_256_GCM_SHA384";
    returnMap["0000"] = "TLS_NULL_WITH_NULL_NULL";
    returnMap["0001"] = "TLS_RSA_WITH_NULL_MD5";
    returnMap["0002"] = "TLS_RSA_WITH_NULL_SHA";
    returnMap["0003"] = "TLS_RSA_EXPORT_WITH_RC4_40_MD5";
    returnMap["0004"] = "TLS_RSA_WITH_RC4_128_MD5";
    returnMap["0005"] = "TLS_RSA_WITH_RC4_128_SHA";
    returnMap["0006"] = "TLS_RSA_EXPORT_WITH_RC2_CBC_40_MD5";
    returnMap["0009"] = "TLS_RSA_WITH_DES_CBC_SHA";
    returnMap["000A"] = "TLS_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["000C"] = "TLS_DH_DSS_WITH_DES_CBC_SHA";
    returnMap["000D"] = "TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA";
    returnMap["000F"] = "TLS_DH_RSA_WITH_DES_CBC_SHA";
    returnMap["0010"] = "TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["0012"] = "TLS_DHE_DSS_WITH_DES_CBC_SHA";
    returnMap["0013"] = "TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA";
    returnMap["0015"] = "TLS_DHE_RSA_WITH_DES_CBC_SHA";
    returnMap["0016"] = "TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["002F"] = "TLS_RSA_WITH_AES_128_CBC_SHA";
    returnMap["0030"] = "TLS_DH_DSS_WITH_AES_128_CBC_SHA";
    returnMap["0031"] = "TLS_DH_RSA_WITH_AES_128_CBC_SHA";
    returnMap["0032"] = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA";
    returnMap["0033"] = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA";
    returnMap["0035"] = "TLS_RSA_WITH_AES_256_CBC_SHA";
    returnMap["0036"] = "TLS_DH_DSS_WITH_AES_256_CBC_SHA";
    returnMap["0037"] = "TLS_DH_RSA_WITH_AES_256_CBC_SHA";
    returnMap["0038"] = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA";
    returnMap["0039"] = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA";
    returnMap["003B"] = "TLS_RSA_WITH_NULL_SHA256";
    returnMap["003C"] = "TLS_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["003D"] = "TLS_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["003E"] = "TLS_DH_DSS_WITH_AES_128_CBC_SHA256";
    returnMap["003F"] = "TLS_DH_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["0040"] = "TLS_DHE_DSS_WITH_AES_128_CBC_SHA256";
    returnMap["0067"] = "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["0068"] = "TLS_DH_DSS_WITH_AES_256_CBC_SHA256";
    returnMap["0069"] = "TLS_DH_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["006A"] = "TLS_DHE_DSS_WITH_AES_256_CBC_SHA256";
    returnMap["006B"] = "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256";
    returnMap["009C"] = "TLS_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["009D"] = "TLS_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["009E"] = "TLS_DHE_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["009F"] = "TLS_DHE_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["00A0"] = "TLS_DH_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["00A1"] = "TLS_DH_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["00A2"] = "TLS_DHE_DSS_WITH_AES_128_GCM_SHA256";
    returnMap["00A3"] = "TLS_DHE_DSS_WITH_AES_256_GCM_SHA384";
    returnMap["00A4"] = "TLS_DH_DSS_WITH_AES_128_GCM_SHA256";
    returnMap["00A5"] = "TLS_DH_DSS_WITH_AES_256_GCM_SHA384";
    returnMap["1301"] = "TLS_AES_128_GCM_SHA256";
    returnMap["1302"] = "TLS_AES_256_GCM_SHA384";
    returnMap["1303"] = "TLS_CHACHA20_POLY1305_SHA256";
    returnMap["C001"] = "TLS_ECDH_ECDSA_WITH_NULL_SHA";
    returnMap["C002"] = "TLS_ECDH_ECDSA_WITH_RC4_128_SHA";
    returnMap["C003"] = "TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["C004"] = "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA";
    returnMap["C005"] = "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA";
    returnMap["C006"] = "TLS_ECDHE_ECDSA_WITH_NULL_SHA";
    returnMap["C007"] = "TLS_ECDHE_ECDSA_WITH_RC4_128_SHA";
    returnMap["C008"] = "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["C009"] = "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA";
    returnMap["C00A"] = "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA";
    returnMap["C00B"] = "TLS_ECDH_RSA_WITH_NULL_SHA";
    returnMap["C00C"] = "TLS_ECDH_RSA_WITH_RC4_128_SHA";
    returnMap["C00D"] = "TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["C00E"] = "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA";
    returnMap["C00F"] = "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA";
    returnMap["C010"] = "TLS_ECDHE_RSA_WITH_NULL_SHA";
    returnMap["C011"] = "TLS_ECDHE_RSA_WITH_RC4_128_SHA";
    returnMap["C012"] = "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA";
    returnMap["C013"] = "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA";
    returnMap["C014"] = "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA";
    returnMap["C023"] = "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256";
    returnMap["C024"] = "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384";
    returnMap["C025"] = "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256";
    returnMap["C026"] = "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384";
    returnMap["C027"] = "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["C028"] = "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384";
    returnMap["C029"] = "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256";
    returnMap["C02A"] = "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384";
    returnMap["C02B"] = "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256";
    returnMap["C02C"] = "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384";
    returnMap["C02D"] = "TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256";
    returnMap["C02E"] = "TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384";
    returnMap["C02F"] = "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["C030"] = "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384";
    returnMap["C031"] = "TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256";
    returnMap["C032"] = "TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384";

    return returnMap;
}

/* https://www.ibm.com/docs/en/zos/2.5.0?topic=programming-cipher-suite-definitions */
