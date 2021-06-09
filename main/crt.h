#ifndef __CRT_H__
#define __CRT_H__

extern const char ca_crt[] asm("_binary_ca_crt_start");

extern const char server_cert[] asm("_binary_cacert_pem_start");
extern const char server_cert_end[] asm("_binary_cacert_pem_end");

extern const char server_key[] asm("_binary_cakey_pem_start");
extern const char server_key_end[] asm("_binary_cakey_pem_end");


#endif
