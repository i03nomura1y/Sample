// created date : 2011/10/15 22:03:33
// last updated : 2011/12/13 22:34:49
// 
// AES128 CBC PKCS7
// Windows, WinCrypt
// ファイル 'in.txt' を暗号化/復号化して ファイル 'out.txt' に書き出し
// 暗号化/復号化 のスイッチは  enc

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501

#include <Windows.h>
#include <Wincrypt.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 1024

int main(){
  // 暗号化/復号化のスイッチ
  bool enc = false;

  BYTE buf[BUF_LEN];
  int len;
  BYTE key[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  BYTE iv[16]  = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


  // buf <- file("in.txt")
  {
	FILE *fp;
	len = 0;
	if( (fp = fopen("in.txt","rb")) != NULL ){
	  int c;
	  for(len=0; (c=fgetc(fp))!=EOF && len<BUF_LEN; len++ ) buf[len] = c;
	}
	fclose(fp);
  }

  // MS_ENH_RSA_AES_PROV の値
  // win7: "Microsoft Enhanced RSA and AES Cryptographic Provider"
  // xp  : "Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)"

  HCRYPTPROV hProv;
  HCRYPTKEY hkey;
  DWORD	mode = CRYPT_MODE_CBC;
  struct KeyBLOB{
	BLOBHEADER hdr;
	DWORD cbKeySize;
	BYTE rgbKeyData[16]; // 16:AES_128のキー長
  };
  KeyBLOB kb;
  kb.hdr.bType = PLAINTEXTKEYBLOB;
  kb.hdr.bVersion = CUR_BLOB_VERSION;
  kb.hdr.reserved = 0;
  kb.hdr.aiKeyAlg = CALG_AES_128;	// AES_128
  kb.cbKeySize = 16;
  CopyMemory( kb.rgbKeyData, key, 16 );
  DWORD dwCount = len;

  if(  !CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0) )
	if(!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET))
	  return fprintf(stderr,"error0\n");
  // Key,IV 作成
  if( !CryptImportKey(hProv,(BYTE*)&kb, sizeof(kb),0,0,&hkey) )	return fprintf(stderr,"error1\n");
  if( !CryptSetKeyParam(hkey, KP_IV, iv, 0) )					return fprintf(stderr,"error2\n");
  if( !CryptSetKeyParam(hkey, KP_MODE, (BYTE*)&mode, 0) )		return fprintf(stderr,"error3\n");
  // 暗号化 or 復号化  3番目の引数: データに続きがあればfalse, データ最後のときtrue
  if(  enc && !CryptEncrypt(hkey, 0, true, 0, buf, &dwCount, BUF_LEN) ) return fprintf(stderr,"error4\n");
  if( !enc && !CryptDecrypt(hkey, 0, true, 0, buf, &dwCount) ) return fprintf(stderr,"error4\n");
  
  fprintf(stderr,"%s in.txt to out.txt\n",enc?"encrypt":"decrypt");
  
  
  // file("out.txt")  <-  buf
  // buf 長さ dwCount
  {
	FILE *fp;
	if( (fp = fopen("out.txt","wb")) == NULL ) fp = stdout;
	for(int i=0;i<dwCount;i++){
	  if(i%16==0) fprintf(stderr,"\n");
	  fprintf(stderr,"%02x ",buf[i]);
	  fprintf(fp,"%c",buf[i]);
	}
	fprintf(stderr,"\n");
	fclose(fp);
  }

  CryptDestroyKey( hkey );
  CryptReleaseContext(hProv, 0);

  return 0;
}
