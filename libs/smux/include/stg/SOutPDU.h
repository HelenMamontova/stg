/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "SMUX"
 * 	found in "SMUX.asn1"
 * 	`asn1c -S/mnt/data/software/asn1c/skeletons -fcompound-names -fwide-types`
 */

#ifndef	_SOutPDU_H_
#define	_SOutPDU_H_


#include <asn_application.h>

/* Including external dependencies */
#include <INTEGER.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SOutPDU {
	SOutPDU_commit	= 0,
	SOutPDU_rollback	= 1
} e_SOutPDU;

/* SOutPDU */
typedef INTEGER_t	 SOutPDU_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SOutPDU;
asn_struct_free_f SOutPDU_free;
asn_struct_print_f SOutPDU_print;
asn_constr_check_f SOutPDU_constraint;
ber_type_decoder_f SOutPDU_decode_ber;
der_type_encoder_f SOutPDU_encode_der;
xer_type_decoder_f SOutPDU_decode_xer;
xer_type_encoder_f SOutPDU_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _SOutPDU_H_ */
#include <asn_internal.h>
