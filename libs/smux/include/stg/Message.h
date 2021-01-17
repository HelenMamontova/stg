/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RFC1157-SNMP"
 * 	found in "RFC1157-SNMP.asn1"
 * 	`asn1c -S/mnt/data/software/asn1c/skeletons -fcompound-names -fwide-types`
 */

#ifndef	_Message_H_
#define	_Message_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>
#include <OCTET_STRING.h>
#include <ANY.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Message__version {
	Message__version_version_1	= 0
} e_Message__version;

/* Message */
typedef struct Message {
	INTEGER_t	 version;
	OCTET_STRING_t	 community;
	ANY_t	 data;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Message_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Message;

#ifdef __cplusplus
}
#endif

#endif	/* _Message_H_ */
#include <asn_internal.h>
