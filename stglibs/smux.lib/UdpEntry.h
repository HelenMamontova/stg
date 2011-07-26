/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "RFC1213-MIB"
 * 	found in "RFC1213-MIB.asn1"
 * 	`asn1c -fskeletons-copy`
 */

#ifndef	_UdpEntry_H_
#define	_UdpEntry_H_


#include <asn_application.h>

/* Including external dependencies */
#include "IpAddress.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UdpEntry */
typedef struct UdpEntry {
	IpAddress_t	 udpLocalAddress;
	long	 udpLocalPort;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UdpEntry_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UdpEntry;

#ifdef __cplusplus
}
#endif

#endif	/* _UdpEntry_H_ */