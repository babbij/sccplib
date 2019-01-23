#include <iostream>
#include <string>
#include <cassert>
#include <openabe/openabe.h>

using namespace std;
using namespace oabe;
using namespace oabe::crypto;

#define FALSE 0
#define TRUE 1 

#define ZCRYPTOBOX_ERROR 1000
#define DECRYPTION_FAILED 10000

extern "C" {
  typedef struct _KeyPair {
    char *szPublicKey;
    char *szSecretKey;
  } KeyPair;
  
  typedef struct _OutString {
    int cb;
    char* sz;
  } OutString;
}


extern "C" int newKeyPair(KeyPair* pKeyPair) {
  InitializeOpenABE();

  OpenABECryptoContext kpabe("KP-ABE");
  kpabe.generateParams();

  string sPublicKey;
  kpabe.exportPublicParams(sPublicKey);

  string sSecretKey;
  kpabe.exportSecretParams(sSecretKey);

  ShutdownOpenABE();

  pKeyPair->szPublicKey = (char*)malloc( (sPublicKey.size() + 1) * sizeof(char));
  strcpy(pKeyPair->szPublicKey, sPublicKey.c_str());

  pKeyPair->szSecretKey = (char*)malloc( (sSecretKey.size() + 1) * sizeof(char));
  strcpy(pKeyPair->szSecretKey, sSecretKey.c_str());
  
  return OpenABE_NOERROR;
}

extern "C" int encrypt(KeyPair* pKeyPair, char* szAttrs, char* szInput, OutString* pOutput) {
  string sAttrs(szAttrs);
  string sInput(szInput);
  string sOutput;
  
  InitializeOpenABE();

  try {
    OpenABECryptoContext kpabe("KP-ABE");
    
    kpabe.importPublicParams(pKeyPair->szPublicKey);
    kpabe.importSecretParams(pKeyPair->szSecretKey);
    kpabe.encrypt(sAttrs, sInput, sOutput);
  }
  catch (OpenABE_ERROR e) {
    ShutdownOpenABE();
    return e;
  }
  catch (...) {
    ShutdownOpenABE();
    return ZCRYPTOBOX_ERROR;
  }
  
  ShutdownOpenABE();

  pOutput->cb = sOutput.size();
  pOutput->sz = new char[sOutput.size() + 1];
  strcpy(pOutput->sz, sOutput.c_str());
  
  return OpenABE_NOERROR;
}

extern "C" int shareKey(KeyPair* pKeyPair, char* szAttrs, OutString* pOutput) {
  string sAttrs(szAttrs);
  string sOutput;
  
  InitializeOpenABE();

  try {
    OpenABECryptoContext kpabe("KP-ABE");
    
    kpabe.importPublicParams(pKeyPair->szPublicKey);
    kpabe.importSecretParams(pKeyPair->szSecretKey);
    kpabe.keygen(sAttrs, "key", "", "");
    kpabe.exportUserKey("key", sOutput);
  }
  catch (OpenABE_ERROR e) {
    ShutdownOpenABE();
    return e;
  }
  catch (...) {
    ShutdownOpenABE();
    return ZCRYPTOBOX_ERROR;
  }
  
  ShutdownOpenABE();

  pOutput->cb = sOutput.size();
  pOutput->sz = new char[sOutput.size() + 1];
  strcpy(pOutput->sz, sOutput.c_str());
  
  return OpenABE_NOERROR;
}

extern "C" int decrypt(char* szPublicKey, char* szCipher, char* szShareKey, OutString* pOutput) {  
  bool result = FALSE;
  
  string sPublicKey(szPublicKey);
  string sCipher(szCipher);
  string sShareKey(szShareKey);
  string sOutput;
  
  InitializeOpenABE();

  try {
    OpenABECryptoContext kpabe("KP-ABE");
    
    kpabe.importPublicParams(szPublicKey);
    kpabe.importUserKey("key", sShareKey);
    
    result = kpabe.decrypt("key", sCipher, sOutput);
  }
  catch (OpenABE_ERROR e) {
    ShutdownOpenABE();
    return e;
  }
  catch (...) {
    ShutdownOpenABE();
    return ZCRYPTOBOX_ERROR;
  }
  
  ShutdownOpenABE();

  pOutput->cb = sOutput.size();
  pOutput->sz = new char[sOutput.size() + 1];
  strcpy(pOutput->sz, sOutput.c_str());
  
  if (result) {
    return OpenABE_NOERROR;
  }
  else {
    return DECRYPTION_FAILED;
  }
}

int main(int argc, char** argv) {
  // KeyPair kp;
  // newKeyPair(&kp);
  //
  // cout << "public key = " << kp.szPublicKey << endl;
  // cout << "secret key = " << kp.szSecretKey << endl;
  // cout << endl;
  //
  // OutString cipher;
  // encrypt(&kp, "foo|bar", "hello world", &cipher);
  // cout << "cipher = " << cipher.sz << endl << endl;
  //
  // OutString share;
  // shareKey(&kp, "bar", &share);
  // cout << "share = " << share.sz << endl << endl;
  //
  // OutString clear;
  // int result = decrypt(&kp, cipher.sz, share.sz, &clear);
  // cout << "result = " << result << endl;
  // cout << "clear = " << clear.sz << endl << endl;

  return 0;
}

