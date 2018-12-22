//#include "algid.h"

#ifndef _ENCODE_H_
#define _ENCODE_H_

/* tag definitions for ASN.1 encoding decoding */
#define INTEGER_TAG                     0x02
#define CHAR_STRING_TAG         0x16
#define OCTET_STRING_TAG        0x04
#define BIT_STRING_TAG          0x03
#define UTCTIME_TAG                     0x17
#define SEQUENCE_TAG            0x30
#define SET_OF_TAG                      0x11
#define OBJECT_ID_TAG           0x06
#define NULL_TAG            0x05

/* definitions of maximum lengths needed for the ASN.1 encoded
   form of some of the common fields in a certificate */
#define MAXVALIDITYLEN          0x24
#define MAXKEYINFOLEN           0x50
#define MAXALGIDLEN                     0x0A
#define MAXOBJIDLEN                     0x0A
#define MAXNAMEVALUELEN         0x40
#define UTCTIMELEN                      0x0F
#define MAXPUBKEYDATALEN        0x30
#define VERSIONLEN                      0x03
#define MAXENCODEDSIGLEN        0x30
#define MAXHEADERLEN            0x08
#define MINHEADERLEN            0x03
#define MAXTIMELEN                      0x20

/* definitions for scrubbing memory */
#define ALLBITSOFF                      0x00
#define ALLBITSON                       0xFF

/* prototypes for the functions in encode.c */
long EncodeLength (BYTE *pbEncoded, DWORD dwLen, BOOL Writeflag);
long EncodeAlgid (BYTE *pbEncoded, ALG_ID Algid, BOOL Writeflag);
long EncodeInteger (BYTE *pbEncoded, BYTE *pbInt, DWORD dwLen, BOOL Writeflag);
long EncodeString (BYTE *pbEncoded, BYTE *pbStr, DWORD dwLen, BOOL Writeflag);
long EncodeOctetString (BYTE *pbEncoded, BYTE *pbStr, DWORD dwLen, BOOL Writeflag);
long EncodeBitString (BYTE *pbEncoded, BYTE *pbStr, DWORD dwLen, BOOL Writeflag);
//long EncodeUTCTime (BYTE *pbEncoded, time_t Time, BOOL Writeflag);
long EncodeHeader (BYTE *pbEncoded, DWORD dwLen, BOOL Writeflag);
long EncodeSetOfHeader (BYTE *pbEncoded, DWORD dwLen, BOOL Writeflag);
long EncodeName (BYTE *pbEncoded, BYTE *pbName, DWORD dwLen, BOOL Writeflag);
long DecodeLength (DWORD *pdwLen, BYTE *pbEncoded);
long DecodeAlgid (ALG_ID *pAlgid, BYTE *pbEncoded, BOOL Writeflag);
long DecodeHeader (DWORD *pdwLen, BYTE *pbEncoded);
long DecodeSetOfHeader (DWORD *pdwLen, BYTE *pbEncoded);
long DecodeInteger (BYTE *pbInt, DWORD *pdwLen, BYTE *pbEncoded, BOOL Writeflag);
long DecodeString (BYTE *pbStr, DWORD *pdwLen, BYTE *pbEncoded, BOOL Writeflag);
long DecodeOctetString (BYTE *pbStr, DWORD *pdwLen, BYTE *pbEncoded, BOOL Writeflag);
long DecodeBitString (BYTE *pbStr, DWORD *pdwLen, BYTE *pbEncoded, BOOL Writeflag);
//long DecodeUTCTime (time_t *pTime, BYTE *pbEncoded, BOOL Writeflag);
long DecodeName (BYTE *pbName, DWORD *pdwLen, BYTE *pbEncoded, BOOL Writeflag);

long
EncodeAlgorithm(
    BYTE *  pbEncoded,
    ALG_ID  AlgId,
    BOOL    WriteFlag);

long
EncodeFileTime(
    BYTE *      pbEncoded,
    FILETIME    Time,
    BOOL        UTC,
    BOOL        WriteFlag);

long
DecodeFileTime(
    FILETIME *  pTime,
    BYTE *      pbEncoded,
    BOOL        WriteFlag);

long
DecodeNull(
    BYTE *  pbEncoded);

long
DecodeDN(
    PSTR    pName,
    DWORD * pdwLen,
    BYTE *  pbEncoded,
    BOOL    WriteFlag);

long
DecodeAlgorithm(
    ALG_ID *        pAlgId,
    PBYTE           pbEncoded,
    BOOL            WriteFlag);

long
DecodeBsafePubKey(
    LPBSAFE_PUB_KEY *   ppPubKey,
    PBYTE               pbEncoded);

long
DecodePrivateKeyFile(
    LPBSAFE_PRV_KEY *   ppKey,
    PBYTE               pbEncoded,
    DWORD               cbEncoded,
    PSTR                Password );


#endif  // _ENCODE_H_
